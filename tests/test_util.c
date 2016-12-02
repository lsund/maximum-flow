
#include <stdlib.h>
#include "test.h"

char *utest_contains() 
{
    void **arr = malloc(sizeof(void *) * 5);
    for (ssize_t i = 0; i < 5; i++) {
        *(arr + i) = malloc(sizeof(ssize_t));
    }
    void **arr2 = NULL;
    for (ssize_t i = 0; i < 5; i++) {
        int *val = *(arr + i);
        *val = i + 1;
    }
    unsigned int a, b, c, d; 
    a = 1;
    b = 2;
    c = 3;
    d = -1;

    mu_assert("should be in", contains(&a, arr, 5));
    mu_assert("should be in", contains(&b, arr, 5));
    mu_assert("should be in", contains(&c, arr, 5));
    mu_assert("should not be in", !contains(&d, arr, 5));
    mu_assert("should not be in", !contains(&d, arr2, 0));
    return NULL;
}

char *test_util() {
    mu_message(UNIT, "contains\n");
    mu_run_utest(utest_contains);
    return NULL;
}
