CC=gcc
CFLAGS=-std=c99 -Wall -g -D_POSIX_SOURCE -D_GNU_SOURCE -I'include' -I'include/third_party'
SRC_DIR=src
3P_SRC_DIR=src/third_party
TEST_DIR=tests
SRCS := $(shell find $(SRC_DIR)/* -maxdepth 0 -name '*.c')
3P_SRCS := $(shell find $(3P_SRC_DIR)/* -maxdepth 0 -name '*.c')
TEST_SRCS := $(shell find $(TEST_DIR)/* -maxdepth 0 -name '*.c')

all: dirs lib
	$(CC) $(CFLAGS) $(SRCS) $(3P_SRCS) main.c lib/map.a -o bin/main -lm -lstdc++

lib: dirs
	g++ -c src/cpp/map.cpp && ar rvs lib/map.a map.o && rm map.o

run: all
	./bin/main

test: dirs lib
	$(CC) $(CFLAGS) $(SRCS) $(3P_SRCS) $(TEST_SRCS) lib/map.a -o bin/test -lm -lstdc++

runtest: test
	./bin/test

memcheck: all
	valgrind --leak-check=full --show-leak-kinds=all ./bin/main

gprof: dirs
	$(CC) $(CFLAGS) -pg main.c $(SRCS) $(3P_SRCS) -o bin/main -lm && ./bin/main && \
		gprof ./bin/main > prof/gprof.info && mv gmon.out prof


dirs: 
	mkdir -p bin prof lib

