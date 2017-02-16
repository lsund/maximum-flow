
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
    vertexcollection_push(vertexcollection, vertex_p_make(4));
    mu_assert("length should have increased", vertexcollection.members->length == 1);
    mu_assert("should stay the same", vertexcollection.members->length == 1);
    vertexcollection_push(vertexcollection , vertex_p_make(3));
    mu_assert("should increase ", vertexcollection.members->length == 2);
    vertexcollection_push(vertexcollection, vertex_p_make(2));
    vertexcollection_push(vertexcollection, vertex_p_make(1));
    mu_assert("should now have 4 elements", vertexcollection.members->length == 4); 
    mu_assert("should be 4", vertexcollection_get(vertexcollection, 0)->label == 4);
    mu_assert("should be 4", vertexcollection_get(vertexcollection, 1)->label == 3);
    mu_assert("should be 4", vertexcollection_get(vertexcollection, 2)->label == 2);
    mu_assert("should be 4", vertexcollection_get(vertexcollection, 3)->label == 1);
    mu_assert("should be 3", vertexcollection_get(vertexcollection, 0)->label == 4);
    vertexcollection_destroy(vertexcollection);
    return NULL;
}

char *utest_vertexcollection_contains_label()
{
    VertexCollection vertexcollection = vertexcollection_init(3);
    mu_assert("2 should not contain any vertex", !vertexcollection_contains_label(vertexcollection, 0));
    mu_assert("3 should not contain any vertex", !vertexcollection_contains_label(vertexcollection, 1));
    mu_assert("4 should not contain any vertex", !vertexcollection_contains_label(vertexcollection, 7));
    vertexcollection_push(vertexcollection, vertex_p_make(1));
    mu_assert("should now contain 1 ", vertexcollection_contains_label(vertexcollection, 1));
    vertexcollection_push(vertexcollection, vertex_p_make(1));
    mu_assert("should still contain 1", vertexcollection_contains_label(vertexcollection, 1));
    mu_assert("should not contains malformed", !vertexcollection_contains_label(vertexcollection, 4));
    vertexcollection_destroy(vertexcollection);

    return NULL;
}

char *utest_vertexcollection_get()
{
    VertexCollection vertexcollection;
    vertexcollection = vertexcollection_init(7);
    vertexcollection_push(vertexcollection, vertex_p_make(6));
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
    mu_message(UNIT, "vertexcollection_contains_label\n");
    mu_run_utest(utest_vertexcollection_contains_label);
    mu_message(UNIT, "vertexcollection_get\n");
    mu_run_utest(utest_vertexcollection_get);
    mu_message(UNIT, "vertexcollection_push\n");
    mu_run_utest(utest_vertexcollection_push);
    return NULL;
}
