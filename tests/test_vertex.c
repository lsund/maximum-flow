

#include <stdlib.h>
#include "test.h"

char *utest_make_vertex()
{
    return NULL;
}

char *utest_make_p_vertex()
{
    return NULL;
}

char *utest_vertices_equal()
{
    return NULL;
}

char *utest_vertex_to_bitpos()
{
    return NULL;
}

char *utest_copy_vertex()
{
    return NULL;
}

char *test_vertex() {
    mu_run_utest(utest_make_vertex);
    mu_run_utest(utest_make_p_vertex);
    mu_run_utest(utest_vertices_equal);
    mu_run_utest(utest_vertex_to_bitpos);
    mu_run_utest(utest_copy_vertex);
    return NULL;
}

