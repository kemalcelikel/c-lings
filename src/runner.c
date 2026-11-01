#define _POSIX_C_SOURCE 200809L
#include "runner.h"

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

volatile sig_atomic_t interrupted = 0;

static void message(char error[ERROR_SIZE], const char *format, ...) {
    va_list args;
    va_start(args, format);
    vsnprintf(error, ERROR_SIZE, format, args);
    va_end(args);
}

bool join_path(char dest[PATH_MAX], const char *dir, const char *name,
               char error[ERROR_SIZE]) {
    int length = snprintf(dest, PATH_MAX, "%s/%s", dir, name);
    if (length < 0 || length >= PATH_MAX) {
        message(error, "Path too long");
        return false;
    }
    return true;
}

bool temp_directory(char dest[PATH_MAX], char error[ERROR_SIZE]) {
    const char *base = getenv("TMPDIR");
    if (!base || !*base) base = "/tmp";
    if (!join_path(dest, base, "clings-XXXXXX", error)) return false;
    if (!mkdtemp(dest)) {
        message(error, "Cannot create temporary directory: %s", strerror(errno));
        return false;
    }
    return true;
}

bool remove_tree(const char *path, char error[ERROR_SIZE]) {
    struct stat info;
    if (lstat(path, &info) != 0) {
        if (errno == ENOENT) return true;
        message(error, "Cannot inspect temporary file: %s", strerror(errno));
        return false;
    }
    /* Do not follow symlinks created by an exercise. */
    if (!S_ISDIR(info.st_mode)) {
        if (unlink(path) == 0) return true;
    } else {
        DIR *dir = opendir(path);
        if (!dir) {
            message(error, "Cannot open temporary directory: %s", strerror(errno));
            return false;
        }
        bool ok = true;
        struct dirent *entry;
        while ((entry = readdir(dir))) {
            if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) continue;
            char child[PATH_MAX];
            if (!join_path(child, path, entry->d_name, error) || !remove_tree(child, error)) {
                ok = false;
                break;
            }
        }
        closedir(dir);
        if (!ok) return false;
        if (rmdir(path) == 0) return true;
    }
    message(error, "Cannot clean temporary path: %s", strerror(errno));
    return false;
}

static bool ends_with(const char *name, const char *suffix) {
    size_t n = strlen(name), s = strlen(suffix);
    return n >= s && !strcmp(name + n - s, suffix);
}

bool copy_sources(const char *source, const char *destination, char error[ERROR_SIZE]) {
    DIR *dir = opendir(source);
    if (!dir) {
        message(error, "Cannot open course directory: %s", strerror(errno));
        return false;
    }
    bool ok = true;
    size_t count = 0;
    struct dirent *entry;
    while ((entry = readdir(dir))) {
        if (!ends_with(entry->d_name, ".c")) continue;
        char from[PATH_MAX], to[PATH_MAX];
        if (!join_path(from, source, entry->d_name, error) ||
            !join_path(to, destination, entry->d_name, error)) {
            ok = false;
            break;
        }
        FILE *in = fopen(from, "rb");
        FILE *out = in ? fopen(to, "wb") : NULL;
        if (!in || !out) {
            message(error, "Cannot copy %s: %s", entry->d_name, strerror(errno));
            if (in) fclose(in);
            ok = false;
            break;
        }
        char buffer[8192];
        size_t length;
        while ((length = fread(buffer, 1, sizeof(buffer), in))) {
            if (fwrite(buffer, 1, length, out) != length) { ok = false; break; }
        }
        if (ferror(in)) ok = false;
        if (fclose(in) != 0) ok = false;
        if (fclose(out) != 0) ok = false;
        if (!ok) {
            message(error, "Cannot copy %s", entry->d_name);
            break;
        }
        count++;
    }
    closedir(dir);
    if (ok && !count) {
        message(error, "No exercises found in %s", source);
        ok = false;
    }
    return ok;
}

static bool append(char **text, size_t *length, const char *data, size_t count) {
    if (count > OUTPUT_LIMIT - *length) return false;
    char *next = realloc(*text, *length + count + 1);
    if (!next) return false;
    memcpy(next + *length, data, count);
    *length += count;
    next[*length] = '\0';
    *text = next;
    return true;
}

char *read_text(const char *path, char error[ERROR_SIZE]) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        message(error, "Cannot read %s: %s", path, strerror(errno));
        return NULL;
    }
    char *text = NULL;
    size_t length = 0, count;
    char buffer[8192];
    bool ok = true;
    while ((count = fread(buffer, 1, sizeof(buffer), file))) {
        if (memchr(buffer, '\0', count) || !append(&text, &length, buffer, count)) {
            ok = false;
            break;
        }
    }
    if (ferror(file)) ok = false;
    if (fclose(file) != 0) ok = false;
    if (!ok || !append(&text, &length, "", 0)) {
        free(text);
        message(error, "Cannot read text file (invalid, too large, or out of memory): %s", path);
        return NULL;
    }
    return text;
}

static char *trim(char *text) {
    while (isspace((unsigned char)*text)) text++;
    size_t length = strlen(text);
    while (length && isspace((unsigned char)text[length - 1])) text[--length] = '\0';
    return text;
}

static char *normalize_lines(const char *text) {
    char *copy = malloc(strlen(text) + 1);
    if (!copy) return NULL;
    char *to = copy;
    while (*text) {
        if (*text == '\r') {
            *to++ = '\n';
            text++;
            if (*text == '\n') text++;
        } else *to++ = *text++;
    }
    *to = '\0';
    return copy;
}

bool check_output(const char *source, const char *output, char error[ERROR_SIZE]) {
    char *lines = normalize_lines(source), *actual = normalize_lines(output), *exact = NULL;
    if (!lines || !actual) {
        free(lines); free(actual);
        message(error, "Out of memory checking output");
        return false;
    }
    char *value = trim(actual), *cursor = value, *line = lines;
    size_t count = 0, exact_length = 0;
    bool ok = true, has_exact = false;
    while (line && ok) {
        char *next = strchr(line, '\n');
        if (next) *next++ = '\0';
        while (*line == ' ' || *line == '\t' || *line == '\r') line++;
        if (!strncmp(line, "// CHECK-EXACT: ", 16)) {
            has_exact = true; count++;
            const char *expected = line + 16;
            ok = append(&exact, &exact_length, expected, strlen(expected)) &&
                 append(&exact, &exact_length, "\n", 1);
            if (!ok) message(error, "Expected output too large or out of memory");
        } else if (!strncmp(line, "// CHECK: ", 10) || !strncmp(line, "// CHECK-ANY: ", 14)) {
            bool any = !strncmp(line, "// CHECK-ANY: ", 14);
            char *expected = trim(line + (any ? 14 : 10));
            char *found = strstr(any ? value : cursor, expected);
            count++;
            if (!found) {
                message(error, "OUTPUT MISMATCH: expected '%s'", expected);
                ok = false;
            } else if (!any) cursor = found + strlen(expected);
        }
        line = next;
    }
    if (ok && !count) { message(error, "Missing output expectations"); ok = false; }
    if (ok && has_exact && strcmp(value, trim(exact))) {
        message(error, "OUTPUT MISMATCH: expected exactly:\n%s", trim(exact));
        ok = false;
    }
    free(lines); free(actual); free(exact);
    return ok;
}

static double now(void) {
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return (double)time.tv_sec + (double)time.tv_nsec / 1000000000.0;
}

static void child_error(int fd) {
    int saved = errno;
    while (write(fd, &saved, sizeof(saved)) < 0 && errno == EINTR) {}
    _exit(127);
}

Result run_command(char *const args[], const char *dir, double timeout,
                   const char *stage, bool quiet) {
    Result result = {.status = PASS};
    int output_pipe[2], error_pipe[2];
    if (pipe(output_pipe) != 0) goto setup_error;
    if (pipe(error_pipe) != 0) {
        close(output_pipe[0]); close(output_pipe[1]);
        goto setup_error;
    }
    if (fcntl(error_pipe[1], F_SETFD, FD_CLOEXEC) < 0 ||
        fcntl(output_pipe[0], F_SETFL, O_NONBLOCK) < 0) {
        close(output_pipe[0]); close(output_pipe[1]);
        close(error_pipe[0]); close(error_pipe[1]);
        goto setup_error;
    }
    fflush(NULL);
    pid_t pid = fork();
    if (pid == 0) {
        close(output_pipe[0]); close(error_pipe[0]);
        if (setpgid(0, 0) != 0 || chdir(dir) != 0 ||
            dup2(output_pipe[1], STDOUT_FILENO) < 0) child_error(error_pipe[1]);
        close(output_pipe[1]);
        if (quiet) {
            int null = open("/dev/null", O_WRONLY);
            if (null < 0 || dup2(null, STDERR_FILENO) < 0) child_error(error_pipe[1]);
            close(null);
        }
        execvp(args[0], args);
        child_error(error_pipe[1]);
    }
    close(output_pipe[1]); close(error_pipe[1]);
    if (pid < 0) {
        close(output_pipe[0]); close(error_pipe[0]);
        goto setup_error;
    }
    /* Both sides set the group to close the fork/exec race. */
    (void)setpgid(pid, pid);
    double deadline = now() + timeout;
    bool eof = false, done = false;
    int status = 0;
    size_t length = 0;
    while (!(eof && done)) {
        if (interrupted) {
            result.status = INTERRUPTED;
            message(result.message, "Interrupted; temporary files cleaned up");
            break;
        }
        if (now() >= deadline) {
            result.status = FAIL;
            message(result.message, "%s TIMEOUT after %.3g seconds", stage, timeout);
            break;
        }
        if (!done) {
            pid_t waited = waitpid(pid, &status, WNOHANG);
            if (waited == pid) done = true;
            else if (waited < 0 && errno != EINTR) {
                result.status = ERROR;
                message(result.message, "Cannot wait for %s: %s", stage, strerror(errno));
                break;
            }
        }
        struct pollfd fd = {.fd = eof ? -1 : output_pipe[0], .events = POLLIN};
        int polled = poll(&fd, 1, 20);
        if (polled < 0 && errno != EINTR) {
            result.status = ERROR;
            message(result.message, "Cannot capture %s output: %s", stage, strerror(errno));
            break;
        }
        if (polled > 0) {
            char buffer[8192];
            ssize_t count;
            while ((count = read(output_pipe[0], buffer, sizeof(buffer))) > 0) {
                if (memchr(buffer, '\0', (size_t)count) ||
                    !append(&result.output, &length, buffer, (size_t)count)) {
                    result.status = FAIL;
                    message(result.message, "%s output is invalid or exceeds 1 MiB", stage);
                    break;
                }
            }
            if (count == 0) eof = true;
            else if (count < 0 && errno != EAGAIN && errno != EINTR) {
                result.status = ERROR;
                message(result.message, "Cannot read %s output: %s", stage, strerror(errno));
            }
            if (result.status != PASS) break;
        }
    }
    /* Also stop children that kept running after their parent exited. */
    (void)kill(-pid, SIGKILL);
    if (!done) while (waitpid(pid, &status, 0) < 0 && errno == EINTR) {}
    close(output_pipe[0]);
    int exec_error = 0;
    ssize_t bytes;
    do { bytes = read(error_pipe[0], &exec_error, sizeof(exec_error)); } while (bytes < 0 && errno == EINTR);
    close(error_pipe[0]);
    if (result.status == PASS && bytes > 0) {
        result.status = ERROR;
        message(result.message, "%s ERROR: cannot execute %s: %s", stage, args[0], strerror(exec_error));
    } else if (result.status == PASS && (!WIFEXITED(status) || WEXITSTATUS(status) != 0)) {
        result.status = FAIL;
        if (WIFEXITED(status)) message(result.message, "%s ERROR (exit %d)", stage, WEXITSTATUS(status));
        else message(result.message, "%s ERROR (signal %d)", stage, WTERMSIG(status));
    }
    if (!result.output && !append(&result.output, &length, "", 0)) {
        result.status = ERROR;
        message(result.message, "Out of memory capturing output");
    }
    return result;

setup_error:
    result.status = ERROR;
    message(result.message, "%s ERROR: %s", stage, strerror(errno));
    return result;
}

void free_result(Result *result) {
    free(result->output);
    result->output = NULL;
}

Result run_exercise(const char *directory, const char *filename, Options options) {
    Result result = {.status = ERROR};
    char temp[PATH_MAX], source_path[PATH_MAX], exe[PATH_MAX];
    if (!temp_directory(temp, result.message)) return result;
    char *source = NULL;
    if (!copy_sources(directory, temp, result.message) ||
        !join_path(source_path, temp, filename, result.message)) goto cleanup;
    source = read_text(source_path, result.message);
    if (!source) goto cleanup;
    size_t length = strlen(filename);
    if (length < 3 || length > PATH_MAX - 7 || strcmp(filename + length - 2, ".c")) {
        message(result.message, "Invalid exercise filename");
        goto cleanup;
    }
    snprintf(exe, sizeof(exe), "./%.*s.out", (int)(length - 2), filename);
    char *args[24];
    size_t n = 0;
    args[n++] = (char *)options.compiler;
    args[n++] = "-std=c11"; args[n++] = "-Wall"; args[n++] = "-Wextra";
    args[n++] = "-Werror"; args[n++] = "-pedantic";
    if (options.sanitize) {
        args[n++] = "-fsanitize=address,undefined"; args[n++] = "-g";
        args[n++] = "-fno-sanitize-recover=all"; args[n++] = "-fno-omit-frame-pointer";
        args[n++] = "-fno-pie"; args[n++] = "-no-pie";
    }
    args[n++] = (char *)filename; args[n++] = "-o"; args[n++] = exe;
    args[n++] = "-pthread"; args[n++] = "-lm"; args[n] = NULL;
    result = run_command(args, temp, options.timeout > 30 ? options.timeout : 30,
                         "COMPILATION", options.quiet);
    if (result.status != PASS) goto cleanup;
    free_result(&result);
    char *run[] = {exe, NULL};
    result = run_command(run, temp, options.timeout, "RUNTIME", options.quiet);
    if (result.status == PASS && !check_output(source, result.output, result.message)) result.status = FAIL;

cleanup:
    free(source);
    char error[ERROR_SIZE];
    if (!remove_tree(temp, error)) {
        result.status = ERROR;
        snprintf(result.message, sizeof(result.message), "%s", error);
    }
    return result;
}
