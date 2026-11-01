#ifndef CLINGS_RUNNER_H
#define CLINGS_RUNNER_H

#include <limits.h>
#include <signal.h>
#include <stdbool.h>

#define ERROR_SIZE 512
#define OUTPUT_LIMIT (1024u * 1024u)

typedef enum { PASS = 0, FAIL = 1, ERROR = 2, INTERRUPTED = 130 } Status;

typedef struct {
    Status status;
    char message[ERROR_SIZE];
    char *output;
} Result;

typedef struct {
    const char *compiler;
    double timeout;
    bool sanitize;
    bool quiet;
} Options;

extern volatile sig_atomic_t interrupted;

bool join_path(char dest[PATH_MAX], const char *dir, const char *name,
               char error[ERROR_SIZE]);
bool temp_directory(char dest[PATH_MAX], char error[ERROR_SIZE]);
bool copy_sources(const char *source, const char *destination, char error[ERROR_SIZE]);
bool remove_tree(const char *path, char error[ERROR_SIZE]);
char *read_text(const char *path, char error[ERROR_SIZE]);
bool check_output(const char *source, const char *output, char error[ERROR_SIZE]);
Result run_command(char *const args[], const char *dir, double timeout,
                   const char *stage, bool quiet);
Result run_exercise(const char *directory, const char *filename, Options options);
void free_result(Result *result);

#endif
