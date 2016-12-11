CC=gcc
CFLAGS=-std=c99 -Wall -g -D_POSIX_SOURCE -D_GNU_SOURCE -I'include'
SRC_DIR=src
TEST_DIR=tests
SRCS := $(shell find $(SRC_DIR)/* -maxdepth 0 -name '*.c')
TEST_SRCS := $(shell find $(TEST_DIR)/* -maxdepth 0 -name '*.c')

all: dirs
	$(CC) $(CFLAGS) $(SRCS) main.c -o bin/main -lm

run: all
	./bin/main

test: dirs
	$(CC) $(CFLAGS) $(SRCS) $(TEST_SRCS) -o bin/test -lm

runtest: test
	./bin/test

memcheck: all
	valgrind --leak-check=full --show-leak-kinds=all ./bin/main


dirs: 
	mkdir -p bin

