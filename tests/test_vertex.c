

#include <stdlib.h>
#include "test.h"

char *utest_vertex_make()
{
    return NULL;
}

char *utest_vertex_p_make()
{
    return NULL;
}

char *utest_vertex_equals()
{
    return NULL;
}

char *utest_vertex_to_bitpos()
{
    return NULL;
}

char *utest_vertex_copy()
{
    return NULL;
}

char *test_vertex() {
    mu_run_utest(utest_vertex_make);
    mu_run_utest(utest_vertex_p_make);
    mu_run_utest(utest_vertex_equals);
    mu_run_utest(utest_vertex_to_bitpos);
    mu_run_utest(utest_vertex_copy);
    return NULL;
}

