CC=gcc
INCLUDE=-I'include' -I'include/third_party'
CFLAGS=-std=c99 -Wall -g -D_POSIX_SOURCE -D_GNU_SOURCE $(INCLUDE)
SRC_DIR=src
TEST_DIR=tests
SRCS := $(shell find $(SRC_DIR)/* -maxdepth 0 -name '*.c')
TEST_SRCS := $(shell find $(TEST_DIR)/* -maxdepth 0 -name '*.c')

all: dirs
	$(CC) $(CFLAGS) $(SRCS) main.c -o bin/main -lm

optimized: dirs
	$(CC) -O2 $(CFLAGS) $(SRCS) main.c -o bin/main -lm -lstdc++

run: all
	./bin/main

test: dirs
	$(CC) $(CFLAGS) $(SRCS) $(TEST_SRCS) -o bin/test \
		-lm -lstdc++

runtest: test
	./bin/test

memcheck: all
	valgrind --leak-check=full --show-leak-kinds=all ./bin/main

gprof: dirs
	$(CC) $(CFLAGS) $(SRCS) -pg main.c -o bin/main -lm+ \
		&& ./bin/main && gprof ./bin/main > prof/gprof.info \
		&& mv gmon.out prof

dirs:
	mkdir -p bin prof lib

clean:
	rm prof/gmon.out && rm prof/gprof.info
