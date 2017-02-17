
#include <stdlib.h>
#include "test.h"

char *utest_vertexcollection_init()
{
    return NULL;
}

char *utest_vertexcollection_push()
{
    VertexCollection vertexcollection;
    vertexcollection = vertexcollection_init(4);
    vertexcollection_push(vertexcollection, vertex_make(1));
    mu_assert("length should have increased", vertexcollection.members->length == 1);
    mu_assert("should stay the same", vertexcollection.members->length == 1);
    vertexcollection_push(vertexcollection , vertex_make(2));
    mu_assert("should increase ", vertexcollection.members->length == 2);
    vertexcollection_push(vertexcollection, vertex_make(3));
    vertexcollection_push(vertexcollection, vertex_make(4));
    mu_assert("should now have 4 elements", vertexcollection.members->length == 4); 
    vertexcollection_destroy(vertexcollection);
    return NULL;
}

char *utest_vertexcollection_contains()
{
    return NULL;
}

char *utest_vertexcollection_get()
{
    VertexCollection vertexcollection;
    vertexcollection = vertexcollection_init(7);
    vertexcollection_push(vertexcollection, vertex_make(6));
    vertexcollection_destroy(vertexcollection);
    return NULL;
}

char *utest_vertexcollection_destroy()
{
    return NULL;
}

char *test_vertexcollection() {
    mu_message(UNIT, "vertexcollection_init\n");
    mu_run_utest(utest_vertexcollection_init);
    mu_message(UNIT, "vertexcollection_contains\n");
    mu_run_utest(utest_vertexcollection_contains);
    mu_message(UNIT, "vertexcollection_get\n");
    mu_run_utest(utest_vertexcollection_get);
    mu_message(UNIT, "vertexcollection_push\n");
    mu_run_utest(utest_vertexcollection_push);
    return NULL;
}
