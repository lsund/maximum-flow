CC=gcc
CFLAGS=-std=c99 -Wall -g -D_POSIX_SOURCE -D_GNU_SOURCE -I'include' -I'include/third_party'
SRC_DIR=src
TEST_DIR=tests
PR_SRCS := $(shell find $(SRC_DIR)/* -maxdepth 0 -name '*.c')
PF_SRCS := $(shell find $(SRC_DIR)/* -maxdepth 0 -name '*.c' \
	! -name 'push_relabel_network.c' \
	! -name 'push_relabel.c')
TEST_SRCS := $(shell find $(TEST_DIR)/* -maxdepth 0 -name '*.c')

all: dirs lib
	$(CC) $(CFLAGS) $(PR_SRCS) main.c lib/map.a -o bin/main -D PUSH_RELABEL -lm -lstdc++

push-relabel: dirs lib
	$(CC) $(CFLAGS) $(PR_SRCS) main.c lib/map.a -o bin/main -D PUSH_RELABEL -lm -lstdc++

pseudoflow: dirs lib
	$(CC) $(CFLAGS) $(PF_SRCS) main.c lib/map.a -o bin/main -D PSEUDOFLOW -lm -lstdc++

run: all
	./bin/main

lib: dirs
	g++ -std=c++11 -c src/cpp/map.cpp && ar rvs lib/map.a map.o && rm map.o

test: dirs lib
	$(CC) $(CFLAGS) $(PR_SRCS) $(TEST_SRCS) lib/map.a -o bin/test -lm -lstdc++

runtest: test
	./bin/test

memcheck: all
	valgrind --leak-check=full --show-leak-kinds=all ./bin/main

gprof: dirs
	$(CC) $(CFLAGS) $(PR_SRCS) -pg main.c lib/map.a -o bin/main -lm -lstdc++ \
		&& ./bin/main && gprof ./bin/main > prof/gprof.info \
		&& mv gmon.out prof

dirs:
	mkdir -p bin prof lib

