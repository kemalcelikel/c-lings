#define _XOPEN_SOURCE 700
#include "runner.h"
#include "course.h"

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

typedef enum { RESUME, SINGLE, START, RANDOM, ALL, RESET, CHECK_FILE } Mode;

static void handle_signal(int signal_number) {
    (void)signal_number;
    interrupted = 1;
}

static int course_index(const char *id) {
    if (!id || !isdigit((unsigned char)*id)) return -1;
    while (*id == '0' && isdigit((unsigned char)id[1])) id++;
    for (size_t i = 0; i < COURSE_COUNT; i++) {
        const char *key = course[i].id;
        while (*key == '0') key++;
        if (!strcmp(id, key)) return (int)i;
    }
    return -1;
}

static int file_index(const char *name) {
    for (size_t i = 0; i < COURSE_COUNT; i++) {
        if (!strcmp(name, course[i].file)) return (int)i;
    }
    return -1;
}

static bool suffix(const char *name, const char *ending) {
    size_t n = strlen(name), e = strlen(ending);
    return n >= e && !strcmp(name + n - e, ending);
}

static int compare_ids(const char *left, const char *right) {
    char *left_suffix, *right_suffix;
    unsigned long a = strtoul(left, &left_suffix, 10);
    unsigned long b = strtoul(right, &right_suffix, 10);
    if (a != b) return a < b ? -1 : 1;
    return strcmp(left_suffix, right_suffix);
}

static bool validate_course(const char *directory, char error[ERROR_SIZE]) {
    DIR *dir = opendir(directory);
    if (!dir) {
        snprintf(error, ERROR_SIZE, "Cannot open course directory: %s", strerror(errno));
        return false;
    }
    bool ok = true;
    struct dirent *entry;
    while ((entry = readdir(dir))) {
        if (isdigit((unsigned char)entry->d_name[0]) && suffix(entry->d_name, ".c") &&
            file_index(entry->d_name) < 0) {
            snprintf(error, ERROR_SIZE, "Course coverage mismatch: extra or renamed exercise %s", entry->d_name);
            ok = false;
            break;
        }
    }
    closedir(dir);
    for (size_t i = 0; i < COURSE_COUNT && ok; i++) {
        char path[PATH_MAX];
        struct stat info;
        if (!join_path(path, directory, course[i].file, error)) return false;
        if (stat(path, &info) != 0 || !S_ISREG(info.st_mode)) {
            snprintf(error, ERROR_SIZE, "Course coverage mismatch: missing exercise %s", course[i].file);
            ok = false;
        }
        if (course_index(course[i].id) != (int)i) {
            snprintf(error, ERROR_SIZE, "Duplicate course identifier %s", course[i].id);
            ok = false;
        }
        if (i && compare_ids(course[i - 1].id, course[i].id) >= 0) {
            snprintf(error, ERROR_SIZE, "Course registry is not in numeric/suffix order at %s", course[i].id);
            ok = false;
        }
    }
    return ok;
}

static bool patch_name(char name[PATH_MAX], size_t index, char error[ERROR_SIZE]) {
    int length = snprintf(name, PATH_MAX, "%.*s.patch",
                          (int)(strlen(course[index].file) - 2), course[index].file);
    if (length < 0 || length >= PATH_MAX) {
        snprintf(error, ERROR_SIZE, "Patch filename too long");
        return false;
    }
    return true;
}

static bool validate_patches(const char *directory, char error[ERROR_SIZE]) {
    DIR *dir = opendir(directory);
    if (!dir) {
        snprintf(error, ERROR_SIZE, "Cannot open solutions directory: %s", strerror(errno));
        return false;
    }
    bool ok = true;
    struct dirent *entry;
    while ((entry = readdir(dir))) {
        if (!suffix(entry->d_name, ".patch")) continue;
        bool found = false;
        for (size_t i = 0; i < COURSE_COUNT - 1; i++) {
            char name[PATH_MAX];
            if (!patch_name(name, i, error)) { ok = false; break; }
            if (!strcmp(entry->d_name, name)) { found = true; break; }
        }
        if (!found) {
            snprintf(error, ERROR_SIZE, "Solution coverage mismatch: extra patch %s", entry->d_name);
            ok = false;
        }
        if (!ok) break;
    }
    closedir(dir);
    for (size_t i = 0; i < COURSE_COUNT - 1 && ok; i++) {
        char name[PATH_MAX], path[PATH_MAX];
        struct stat info;
        if (!patch_name(name, i, error) || !join_path(path, directory, name, error)) return false;
        if (stat(path, &info) != 0 || !S_ISREG(info.st_mode)) {
            snprintf(error, ERROR_SIZE, "Solution coverage mismatch: missing patch %.200s", name);
            ok = false;
        }
    }
    return ok;
}

static void display_failure(const Result *result) {
    fprintf(stderr, "%s\n", result->message);
    if (result->output && *result->output) fprintf(stderr, "Captured stdout:\n%s\n", result->output);
}

static int verify(const char *root, const char *exercises, Options options, int selected) {
    char solutions[PATH_MAX], temp[PATH_MAX], error[ERROR_SIZE];
    if (!join_path(solutions, root, "solutions", error) || !validate_patches(solutions, error) ||
        !temp_directory(temp, error)) {
        fprintf(stderr, "%s\n", error);
        return ERROR;
    }
    int code = ERROR;
    if (!copy_sources(exercises, temp, error)) goto cleanup;
    for (size_t i = 0; i < COURSE_COUNT - 1; i++) {
        char name[PATH_MAX], path[PATH_MAX];
        if (!patch_name(name, i, error) || !join_path(path, solutions, name, error)) goto cleanup;
        char *args[] = {"patch", "--batch", "--forward", "--fuzz=0", (char *)course[i].file, path, NULL};
        Result result = run_command(args, temp, 10, "PATCH", false);
        if (result.status != PASS) {
            display_failure(&result);
            code = result.status;
            free_result(&result);
            error[0] = '\0';
            goto cleanup;
        }
        free_result(&result);
    }
    size_t checked = 0, failed = 0;
    for (size_t i = 0; i < COURSE_COUNT; i++) {
        if (selected >= 0 && i != (size_t)selected) continue;
        Result result = run_exercise(temp, course[i].file, options);
        if (result.status == PASS && i != COURSE_COUNT - 1) {
            Options starter_options = options;
            starter_options.sanitize = false;
            starter_options.quiet = true;
            Result starter = run_exercise(exercises, course[i].file, starter_options);
            if (starter.status == PASS) {
                result.status = FAIL;
                snprintf(result.message, sizeof(result.message), "Starter already passes; restore its intended task");
            } else if (starter.status != FAIL) {
                result.status = starter.status;
                snprintf(result.message, sizeof(result.message), "%s", starter.message);
            }
            free_result(&starter);
        }
        checked++;
        if (result.status == PASS) printf("PASS %s\n", course[i].file);
        else {
            printf("FAIL %s\n", course[i].file);
            display_failure(&result);
            failed++;
        }
        fflush(stdout);
        if (result.status == INTERRUPTED) {
            code = INTERRUPTED;
            free_result(&result);
            error[0] = '\0';
            goto cleanup;
        }
        free_result(&result);
    }
    printf("Verified %zu lessons; %zu failed.\n", checked, failed);
    code = failed ? FAIL : PASS;
    error[0] = '\0';

cleanup:
    if (*error) fprintf(stderr, "%s\n", error);
    if (!remove_tree(temp, error)) { fprintf(stderr, "%s\n", error); code = ERROR; }
    return code;
}

static bool load_progress(const char *path, size_t *start, char error[ERROR_SIZE]) {
    struct stat info;
    if (lstat(path, &info) != 0) {
        if (errno == ENOENT) { *start = 0; return true; }
        snprintf(error, ERROR_SIZE, "Cannot inspect progress: %s", strerror(errno));
        return false;
    }
    char *text = read_text(path, error);
    if (!text) return false;
    char *id = text;
    while (isspace((unsigned char)*id)) id++;
    size_t length = strlen(id);
    while (length && isspace((unsigned char)id[length - 1])) id[--length] = '\0';
    int index = course_index(id);
    free(text);
    if (index < 0) {
        snprintf(error, ERROR_SIZE, "Invalid saved progress; use 'make reset' to reset it");
        return false;
    }
    *start = (size_t)index + 1;
    return true;
}

static bool save_progress(const char *root, const char *path, const char *id, char error[ERROR_SIZE]) {
    char temp[PATH_MAX];
    if (!join_path(temp, root, ".clings-progress.XXXXXX", error)) return false;
    int fd = mkstemp(temp);
    if (fd < 0) {
        snprintf(error, ERROR_SIZE, "Cannot save progress: %s", strerror(errno));
        return false;
    }
    FILE *file = fdopen(fd, "w");
    bool ok = file && fprintf(file, "%s\n", id) > 0;
    if (file) { if (fclose(file) != 0) ok = false; }
    else close(fd);
    if (ok && rename(temp, path) == 0) return true;
    unlink(temp);
    snprintf(error, ERROR_SIZE, "Cannot save progress: %s", strerror(errno));
    return false;
}

static void help(void) {
    puts("Clings: learn C by fixing broken programs.\n"
         "  make                      Build checker and resume the course\n"
         "  make n=032b               Check a single lesson\n"
         "  make s=039                Check from a selected lesson\n"
         "  make random | reset | all | list\n"
         "  make test | verify | verify-sanitize\n\n"
         "Direct options:\n"
         "  --exercise ID  --start ID  --random  --reset  --all  --list\n"
         "  --cc EXECUTABLE           Compiler (default: CC or gcc)\n"
         "  --timeout SECONDS         Runtime limit (default: 5)\n"
         "  --verify                  Verify patches and all solved lessons\n"
         "  --sanitize                Enable fatal address/undefined sanitizers\n"
         "  --check-file PATH         Validate a maintainer's solved copy\n"
         "  --help\n\n"
         "Only normal resume runs update progress. --reset preserves your edits.");
}

int main(int argc, char *argv[]) {
    Options options = {.compiler = getenv("CC"), .timeout = 5};
    if (!options.compiler || !*options.compiler) options.compiler = "gcc";
    Mode mode = RESUME;
    const char *id = NULL, *answer = NULL;
    bool listing = false, verifying = false;
    for (int i = 1; i < argc; i++) {
        const char *arg = argv[i];
        if (!strcmp(arg, "--help")) { help(); return PASS; }
        if (!strcmp(arg, "--list")) { listing = true; continue; }
        if (!strcmp(arg, "--verify")) { verifying = true; continue; }
        if (!strcmp(arg, "--sanitize")) { options.sanitize = true; continue; }
        if (!strcmp(arg, "--cc") || !strcmp(arg, "--timeout")) {
            if (++i == argc) { fprintf(stderr, "Missing value for %s\n", arg); return ERROR; }
            if (!strcmp(arg, "--cc")) options.compiler = argv[i];
            else {
                char *end;
                errno = 0;
                options.timeout = strtod(argv[i], &end);
                if (errno || end == argv[i] || *end || !isfinite(options.timeout) || options.timeout <= 0) {
                    fprintf(stderr, "Timeout must be a finite positive number\n");
                    return ERROR;
                }
            }
            continue;
        }
        Mode requested;
        if (!strcmp(arg, "--exercise")) requested = SINGLE;
        else if (!strcmp(arg, "--start")) requested = START;
        else if (!strcmp(arg, "--random")) requested = RANDOM;
        else if (!strcmp(arg, "--all")) requested = ALL;
        else if (!strcmp(arg, "--reset")) requested = RESET;
        else if (!strcmp(arg, "--check-file")) requested = CHECK_FILE;
        else { fprintf(stderr, "Unknown option: %s (see --help)\n", arg); return ERROR; }
        if (mode != RESUME) { fprintf(stderr, "Selection options are mutually exclusive\n"); return ERROR; }
        mode = requested;
        if (mode == SINGLE || mode == START || mode == CHECK_FILE) {
            if (++i == argc) { fprintf(stderr, "Missing value for %s\n", arg); return ERROR; }
            if (mode == CHECK_FILE) answer = argv[i];
            else id = argv[i];
        }
    }
    if ((verifying && mode != RESUME && mode != SINGLE) ||
        (listing && (verifying || mode == RESET || mode == CHECK_FILE))) {
        fprintf(stderr, "Incompatible checking modes\n");
        return ERROR;
    }
    struct sigaction action = {0};
    action.sa_handler = handle_signal;
    sigemptyset(&action.sa_mask);
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGTERM, &action, NULL);
    char root[PATH_MAX], exercises[PATH_MAX], progress[PATH_MAX], error[ERROR_SIZE];
    ssize_t length = readlink("/proc/self/exe", root, sizeof(root) - 1);
    if (length < 0 || length == (ssize_t)sizeof(root) - 1) {
        fprintf(stderr, "Cannot locate Clings executable via Linux /proc/self/exe\n");
        return ERROR;
    }
    root[length] = '\0';
    char *slash = strrchr(root, '/');
    if (!slash) return ERROR;
    if (slash == root) slash[1] = '\0';
    else *slash = '\0';
    if (!join_path(exercises, root, "exercises", error) ||
        !join_path(progress, root, ".clings-progress", error)) {
        fprintf(stderr, "%s\n", error);
        return ERROR;
    }
    if (mode == RESET) {
        if (unlink(progress) != 0 && errno != ENOENT) {
            fprintf(stderr, "Cannot reset progress: %s\n", strerror(errno)); return ERROR;
        }
        puts("Progress reset. Your exercise edits are preserved.");
        return PASS;
    }
    if (mode == CHECK_FILE) {
        char path[PATH_MAX];
        if (!realpath(answer, path)) { perror("Cannot open answer"); return ERROR; }
        char *name = strrchr(path, '/');
        if (!name || file_index(name + 1) < 0) {
            fprintf(stderr, "Answer must use an original course filename\n"); return ERROR;
        }
        *name++ = '\0';
        Result result = run_exercise(path, name, options);
        int code = result.status;
        if (code) display_failure(&result);
        else puts("Solved copy passed.");
        free_result(&result);
        return code;
    }
    if (!validate_course(exercises, error)) { fprintf(stderr, "%s\n", error); return ERROR; }
    int selected = id ? course_index(id) : -1;
    if (id && selected < 0) { fprintf(stderr, "Unknown exercise: %s\n", id); return ERROR; }
    if (verifying) return verify(root, exercises, options, selected);
    size_t start = selected >= 0 ? (size_t)selected : 0, end = COURSE_COUNT;
    if (mode == RANDOM) {
        srand((unsigned int)time(NULL) ^ (unsigned int)getpid());
        start = (size_t)rand() % COURSE_COUNT;
    }
    if (mode == SINGLE || mode == RANDOM) end = start + 1;
    if (mode == RESUME && !listing && !load_progress(progress, &start, error)) {
        fprintf(stderr, "%s\n", error); return ERROR;
    }
    if (start == COURSE_COUNT && !listing) {
        puts("All C exercises completed! Use 'make all' to recheck them.");
        return PASS;
    }
    for (size_t i = start; i < end; i++) {
        if (listing) { printf("%4s  %s\n", course[i].id, course[i].file); continue; }
        printf("[%zu/%zu] Checking %s...\n", i + 1, COURSE_COUNT, course[i].file);
        fflush(stdout);
        Result result = run_exercise(exercises, course[i].file, options);
        int code = result.status;
        if (code) {
            display_failure(&result);
            if (code != INTERRUPTED) fprintf(stderr, "Edit exercises/%s and rerun the same command.\n", course[i].file);
            free_result(&result);
            return code;
        }
        if (result.output && *result.output) {
            fputs(result.output, stdout);
            if (result.output[strlen(result.output) - 1] != '\n') putchar('\n');
        }
        free_result(&result);
        if (mode == RESUME && !save_progress(root, progress, course[i].id, error)) {
            fprintf(stderr, "%s\n", error); return ERROR;
        }
        puts("PASSED!\n");
    }
    if (!listing) puts("All selected C exercises passed!");
    return PASS;
}
