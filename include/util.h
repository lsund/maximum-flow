#ifndef UTIL_H
#define UTIL_H

#define MAX_VERTICES 1000
#define MAX_EDGES 1000
#define TKN_MAX_LEN 64
#define LINE_MAX_TKNS 64
#define MAX_LINES 50000

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Errno codes used:
// EFAULT - the preceeding operation would have resulted in invalid read/write
// ERANGE - out of range for mathematical function
// EINVAL - invalid arguments to function

// Two dimensional structure
typedef struct point {
    int x, y;
} Point;

// The result type used instead of something unclear like return 0. 
typedef enum result { FAIL, SUCCESS } Result; 

// Exit program with an error and print the error text to stderr.
void runtime_error(const char error_text[]);

// Does the array contain the value up to index len?
bool contains(const unsigned int *value, void **arr, const unsigned int len);

// Return the larger of the two inputs
size_t larger(const size_t size_a, const size_t size_b);

// Return the smaller of the two inputs
size_t smaller(const size_t size_a, const size_t size_b);

#endif
