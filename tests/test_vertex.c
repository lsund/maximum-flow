

#include <stdlib.h>
#include "test.h"

char *utest_vertex_make()
{
    Vertex x = vertex_make(8);
    mu_assert("should be 8", x.label == 8);
    return NULL;
}

char *utest_vertex_p_make()
{
    VertexPointer x = vertex_p_make(8);
    mu_assert("should exist", x);
    mu_assert("should be 8", x->label == 8);
    return NULL;
}

char *utest_vertex_equals()
{
    VertexPointer x = vertex_p_make(8);
    VertexPointer y = vertex_p_make(9);
    VertexPointer z = vertex_p_make(8);
    mu_assert("should equal", vertex_equals(x, z));
    mu_assert("should equal", !vertex_equals(x, y));
    return NULL;
}

char *test_vertex() {
    mu_run_utest(utest_vertex_make);
    mu_run_utest(utest_vertex_p_make);
    mu_run_utest(utest_vertex_equals);
    return NULL;
}

