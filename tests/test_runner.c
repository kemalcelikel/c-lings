#define _POSIX_C_SOURCE 200809L
#include "../src/runner.h"
#include "../src/course.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static unsigned int tests = 0;

#define REQUIRE(condition) do { \
    if (!(condition)) { \
        fprintf(stderr, "FAIL line %d: %s\n", __LINE__, #condition); \
        exit(1); \
    } \
} while (0)

static void passed(const char *name) {
    tests++;
    printf("PASS %s\n", name);
}

static void write_source(const char *directory, const char *body, const char *checks) {
    char path[PATH_MAX], error[ERROR_SIZE];
    REQUIRE(join_path(path, directory, "001_test.c", error));
    FILE *file = fopen(path, "w");
    REQUIRE(file != NULL);
    REQUIRE(fprintf(file, "#define _POSIX_C_SOURCE 200809L\n"
                         "#include <stdio.h>\n#include <stdlib.h>\n#include <limits.h>\n"
                         "#include <unistd.h>\n#include <time.h>\n#include <sys/stat.h>\n"
                         "int main(void) { %s }\n%s\n", body, checks) > 0);
    REQUIRE(fclose(file) == 0);
}

static void no_temporary_files(const char *directory) {
    DIR *dir = opendir(directory);
    REQUIRE(dir != NULL);
    struct dirent *entry;
    while ((entry = readdir(dir))) REQUIRE(strncmp(entry->d_name, "clings-", 7) != 0);
    REQUIRE(closedir(dir) == 0);
}

static Result example(const char *directory, const char *body, Options options) {
    write_source(directory, body, "// CHECK-EXACT: hello");
    Result result = run_exercise(directory, "001_test.c", options);
    no_temporary_files(directory);
    return result;
}

int main(int argc, char *argv[]) {
    char error[ERROR_SIZE], base[PATH_MAX];
    Options options = {.compiler = argc > 1 ? argv[1] : "gcc", .timeout = 5, .quiet = true};
    REQUIRE(temp_directory(base, error));
    REQUIRE(setenv("TMPDIR", base, 1) == 0);

    REQUIRE(COURSE_COUNT == 97);
    REQUIRE(!strcmp(course[31].id, "032"));
    REQUIRE(!strcmp(course[32].id, "032b"));
    REQUIRE(!strcmp(course[33].id, "032c"));
    REQUIRE(!strcmp(course[34].id, "033"));
    REQUIRE(!strcmp(course[35].id, "033b"));
    passed("explicit course inventory and suffix order");

    REQUIRE(!check_output("", "hello", error));
    REQUIRE(strstr(error, "Missing output"));
    passed("missing expectations fail");
    REQUIRE(check_output("// CHECK: first\n// CHECK: second\n", "first then second", error));
    REQUIRE(!check_output("// CHECK: first\n// CHECK: second\n", "second first", error));
    passed("ordered substring checks");
    REQUIRE(check_output("// CHECK-ANY: first\n// CHECK-ANY: second\n", "second first", error));
    REQUIRE(!check_output("// CHECK-ANY: missing\n", "first", error));
    passed("unordered checks require every value");
    REQUIRE(check_output("// CHECK-EXACT: n=10\n", " \nn=10\n ", error));
    REQUIRE(!check_output("// CHECK-EXACT: n=10\n", "n=100", error));
    REQUIRE(check_output("// CHECK-EXACT: a\n// CHECK-EXACT: b\n", "a\nb\n", error));
    REQUIRE(check_output("// CHECK-EXACT: a\r\n// CHECK-EXACT: b\r\n", "a\r\nb\r\n", error));
    passed("exact and multiline output checks");

    Result result = example(base, "puts(\"hello\"); return 0;", options);
    REQUIRE(result.status == PASS && !strcmp(result.output, "hello\n"));
    free_result(&result);
    passed("successful compilation and execution");

    result = example(base, "not C code", options);
    REQUIRE(result.status == FAIL && strstr(result.message, "COMPILATION ERROR"));
    free_result(&result);
    passed("compiler failure and cleanup");

    result = example(base, "return 7;", options);
    REQUIRE(result.status == FAIL && strstr(result.message, "RUNTIME ERROR (exit 7)"));
    free_result(&result);
    result = example(base, "return 127;", options);
    REQUIRE(result.status == FAIL && strstr(result.message, "exit 127"));
    free_result(&result);
    passed("runtime exit codes are distinct from exec failure");

    result = example(base, "abort();", options);
    REQUIRE(result.status == FAIL && strstr(result.message, "signal"));
    free_result(&result);
    passed("abnormal runtime termination");

    result = example(base, "puts(\"wrong\"); return 0;", options);
    REQUIRE(result.status == FAIL && strstr(result.message, "OUTPUT MISMATCH"));
    free_result(&result);
    passed("output mismatch");

    const char *compiler = options.compiler;
    options.compiler = "clings-nonexistent-compiler";
    result = example(base, "puts(\"hello\"); return 0;", options);
    REQUIRE(result.status == ERROR && strstr(result.message, "cannot execute"));
    free_result(&result);
    options.compiler = compiler;
    passed("missing compiler is an infrastructure error");

    result = example(base, "FILE *f = fopen(\"001_test.c\", \"r\"); if (!f) return 1; "
                           "fclose(f); if (mkdir(\"created\", 0700)) return 1; "
                           "f = fopen(\"created/data\", \"w\"); if (!f) return 1; fclose(f); "
                           "puts(\"hello\"); return 0;", options);
    REQUIRE(result.status == PASS);
    free_result(&result);
    passed("relative source I/O and nested data cleanup");

    char outside[PATH_MAX], body[PATH_MAX + 256];
    REQUIRE(join_path(outside, base, "sentinel", error));
    FILE *file = fopen(outside, "w");
    REQUIRE(file != NULL && fclose(file) == 0);
    snprintf(body, sizeof(body), "if (symlink(\"%s\", \"external\")) return 1; "
                                "puts(\"hello\"); return 0;", outside);
    result = example(base, body, options);
    REQUIRE(result.status == PASS && access(outside, F_OK) == 0);
    free_result(&result);
    passed("cleanup does not follow symlinks");

    options.timeout = 0.15;
    result = example(base, "for (;;) {}", options);
    REQUIRE(result.status == FAIL && strstr(result.message, "RUNTIME TIMEOUT"));
    free_result(&result);
    passed("runtime timeout and cleanup");

    REQUIRE(join_path(outside, base, "child-survived", error));
    snprintf(body, sizeof(body), "pid_t child = fork(); if (child < 0) return 1; "
        "if (child == 0) { struct timespec delay = {0, 600000000}; nanosleep(&delay, NULL); "
        "FILE *f = fopen(\"%s\", \"w\"); if (f) fclose(f); return 0; } for (;;) {}", outside);
    result = example(base, body, options);
    REQUIRE(result.status == FAIL && strstr(result.message, "TIMEOUT"));
    free_result(&result);
    struct timespec delay = {0, 700000000};
    nanosleep(&delay, NULL);
    REQUIRE(access(outside, F_OK) != 0);
    passed("timeout terminates the entire process group");
    options.timeout = 5;

    char *sleep_command[] = {"sh", "-c", "sleep 10", NULL};
    result = run_command(sleep_command, base, 0.1, "COMPILATION", true);
    REQUIRE(result.status == FAIL && strstr(result.message, "COMPILATION TIMEOUT"));
    free_result(&result);
    passed("compilation subprocess timeout");

    result = example(base, "for (;;) puts(\"flood\");", options);
    REQUIRE(result.status == FAIL && strstr(result.message, "exceeds 1 MiB"));
    free_result(&result);
    passed("bounded captured output");

    options.sanitize = true;
    result = example(base, "volatile int n = INT_MAX; n++; puts(\"hello\"); return 0;", options);
    REQUIRE(result.status == FAIL && strstr(result.message, "RUNTIME ERROR"));
    free_result(&result);
    options.sanitize = false;
    passed("sanitizer-detected undefined behavior is fatal");

    interrupted = 1;
    result = example(base, "puts(\"hello\"); return 0;", options);
    REQUIRE(result.status == INTERRUPTED);
    free_result(&result);
    interrupted = 0;
    passed("interruption returns a distinct status and cleans up");

    char empty[PATH_MAX];
    REQUIRE(temp_directory(empty, error));
    result = run_exercise(empty, "001_test.c", options);
    REQUIRE(result.status == ERROR && strstr(result.message, "No exercises"));
    free_result(&result);
    REQUIRE(remove_tree(base, error));
    printf("%u native runner tests passed.\n", tests);
    return 0;
}
