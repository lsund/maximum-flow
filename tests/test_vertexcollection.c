
#include <stdlib.h>
#include "test.h"

char *utest_vertexcollection_init()
{
    return NULL;
}

char *utest_vertexcollection_pop()
{
    VertexCollection vertices = vertexcollection_init(4);
    vertexcollection_push(vertices, vertex_p_make(1));
    vertexcollection_push(vertices, vertex_p_make(2));
    vertexcollection_push(vertices, vertex_p_make(3));
    vertexcollection_push(vertices, vertex_p_make(4));
    mu_assert("should have 4 elements", vertexcollection_length(vertices) == 4);
    vertexcollection_pop(vertices);
    mu_assert("should have 3 elements", vertexcollection_length(vertices) == 3);
    mu_assert("should not contain 4", !vertexcollection_contains_label(vertices, 4));
    mu_assert("should contain 3", vertexcollection_contains_label(vertices, 3));
    mu_assert("should contain 2", vertexcollection_contains_label(vertices, 2));
    mu_assert("should contain 1", vertexcollection_contains_label(vertices, 1));
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

char *utest_vertexcollection_contains_vertices()
{
    VertexCollection vertexcollection = vertexcollection_init(5);
    vertexcollection_push(vertexcollection, vertex_p_make(1));
    vertexcollection_push(vertexcollection, vertex_p_make(0));
    vertexcollection_push(vertexcollection, vertex_p_make(5));
    vertexcollection_push(vertexcollection, vertex_p_make(3));
    VertexCollection sub1 = vertexcollection_init(5);
    VertexCollection sub2 = vertexcollection_init(5);
    VertexCollection sub3 = vertexcollection_init(5);

    vertexcollection_push(sub1, vertex_p_make(1));
    vertexcollection_push(sub1, vertex_p_make(0));
    vertexcollection_push(sub1, vertex_p_make(5));
    vertexcollection_push(sub1, vertex_p_make(3));

    vertexcollection_push(sub2, vertex_p_make(0));
    vertexcollection_push(sub2, vertex_p_make(5));
    vertexcollection_push(sub2, vertex_p_make(3));

    mu_assert("should contain", vertexcollection_is_super(vertexcollection, sub1));
    mu_assert("should not contain", !vertexcollection_is_super(vertexcollection, sub2));
    mu_assert("should contain", vertexcollection_is_super(vertexcollection_init(10), sub3));

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

char *utest_vertexcollection_complement()
{
    VertexCollection e = vertexcollection_init(10); // 0-4
    VertexCollection a = vertexcollection_init(10); // 0-9
    VertexCollection b = vertexcollection_init(10); // 5-9
    vertexcollection_push(e, vertex_p_make(0));
    vertexcollection_push(e, vertex_p_make(1));
    vertexcollection_push(e, vertex_p_make(2));
    vertexcollection_push(a, vertex_p_make(0));
    vertexcollection_complement(e, a, &b);
    mu_assert("should contain", vertexcollection_contains_label(b, 1));
    mu_assert("should contain", vertexcollection_contains_label(b, 2));
    mu_assert("should not contain", !vertexcollection_contains_label(b, 0));
    return NULL;
}

char *test_vertexcollection() {
    mu_message(UNIT, "vertexcollection_init\n");
    mu_run_utest(utest_vertexcollection_init);
    mu_message(UNIT, "vertexcollection_contains_label\n");
    mu_run_utest(utest_vertexcollection_contains_label);
    mu_message(UNIT, "vertexcollection_centains_vertices\n");
    mu_run_utest(utest_vertexcollection_contains_vertices);
    mu_message(UNIT, "vertexcollection_get\n");
    mu_run_utest(utest_vertexcollection_get);
    mu_message(UNIT, "vertexcollection_push\n");
    mu_run_utest(utest_vertexcollection_push);
    mu_message(UNIT, "vertexcollection_complement\n");
    mu_run_utest(utest_vertexcollection_complement);
    mu_message(UNIT, "vertexcollection_pop\n");
    mu_run_utest(utest_vertexcollection_pop);
    return NULL;
}
