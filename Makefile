ifeq ($(origin CC),default)
CC = gcc
endif
CFLAGS ?= -std=c11 -Wall -Wextra -Werror -pedantic -O2
CPPFLAGS += -D_POSIX_C_SOURCE=200809L

.DEFAULT_GOAL := run
.PHONY: run build list random reset all test verify verify-sanitize clean

run: clings
	./clings --cc "$(CC)" $(if $(n),--exercise "$(n)") $(if $(s),--start "$(s)")

build: clings

clings: src/clings.c src/runner.c src/runner.h src/course.h
	"$(CC)" $(CPPFLAGS) $(CFLAGS) src/clings.c src/runner.c -o $@

list random reset all: clings
	./clings --cc "$(CC)" --$@

verify: clings
	./clings --cc "$(CC)" --verify $(if $(n),--exercise "$(n)")

verify-sanitize: clings
	./clings --cc "$(CC)" --verify --sanitize $(if $(n),--exercise "$(n)")

test: clings tests/test_runner
	./tests/test_runner "$(CC)"
	sh tests/test_cli.sh "$(CC)"

tests/test_runner: tests/test_runner.c src/runner.c src/runner.h src/course.h
	"$(CC)" $(CPPFLAGS) $(CFLAGS) tests/test_runner.c src/runner.c -o $@

clean:
	rm -f clings tests/test_runner
