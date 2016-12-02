
#include "util.h"

void runtime_error(const char error_text[])
{
    fprintf(stderr,ANSI_COLOR_RED "Runtime-error: %s\n" ANSI_COLOR_RESET,
            error_text);
    exit(1);
}

bool contains(const unsigned int *val, void **arr, const unsigned int len)
{
    if (!arr) {
        return false;
    }
    unsigned int i;
    for (i = 0; i < len; i++) {
        if (*((unsigned int *) *(arr + i)) == *val) {
            return true;
        }
    }
    return false;
}

size_t larger(const size_t size_a, const size_t size_b)
{
    return size_a > size_b ? size_a : size_b;
}

size_t smaller(const size_t size_a, const size_t size_b)
{
    return size_a < size_b ? size_a : size_b;
}


