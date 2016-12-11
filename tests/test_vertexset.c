
#include <stdlib.h>
#include "test.h"

char *utest_vertexset_init()
{
    return NULL;
}

char *utest_vertexset_push()
{
    VertexSet vertexset;
    vertexset = vertexset_init(4);
    mu_assert("1 should succeed", vertexset_push(vertexset, vertex_p_make(4)));
    mu_assert("length should have increased", vertexset.set->length == 1);
    mu_assert("should stay the same", vertexset.set->length == 1);
    mu_assert("2 should succeed", vertexset_push(vertexset , vertex_p_make(3)) == SUCCESS);
    mu_assert("should increase ", vertexset.set->length == 2);
    mu_assert("4 should succeed", vertexset_push(vertexset, vertex_p_make(2)) == SUCCESS);
    mu_assert("5 should succeed", vertexset_push(vertexset, vertex_p_make(1)) == SUCCESS);
    mu_assert("should now have 4 elements", vertexset.set->length == 4); 
    mu_assert("should be 4", vertexset_get(vertexset, 0)->label == 4);
    mu_assert("should be 4", vertexset_get(vertexset, 1)->label == 3);
    mu_assert("should be 4", vertexset_get(vertexset, 2)->label == 2);
    mu_assert("should be 4", vertexset_get(vertexset, 3)->label == 1);
    mu_assert("should be 3", vertexset_get(vertexset, 0)->label == 4);
    vertexset_destroy(vertexset);
    return NULL;
}

char *utest_vertexset_contains_label()
{
    VertexSet vertexset = vertexset_init(3);
    mu_assert("2 should not contain any vertex", !vertexset_contains_label(vertexset, 0));
    mu_assert("3 should not contain any vertex", !vertexset_contains_label(vertexset, 1));
    mu_assert("4 should not contain any vertex", !vertexset_contains_label(vertexset, 7));
    vertexset_push(vertexset, vertex_p_make(1));
    mu_assert("should now contain 1 ", vertexset_contains_label(vertexset, 1));
    vertexset_push(vertexset, vertex_p_make(1));
    mu_assert("should still contain 1", vertexset_contains_label(vertexset, 1));
    mu_assert("should not contains malformed", !vertexset_contains_label(vertexset, 4));
    vertexset_destroy(vertexset);

    return NULL;
}

char *utest_vertexset_contains_vertices()
{
    VertexSet vertexset = vertexset_init(5);
    vertexset_push(vertexset, vertex_p_make(1));
    vertexset_push(vertexset, vertex_p_make(0));
    vertexset_push(vertexset, vertex_p_make(5));
    vertexset_push(vertexset, vertex_p_make(3));
    VertexSet sub1 = vertexset_init(5);
    VertexSet sub2 = vertexset_init(5);
    VertexSet sub3 = vertexset_init(5);

    vertexset_push(sub1, vertex_p_make(1));
    vertexset_push(sub1, vertex_p_make(0));
    vertexset_push(sub1, vertex_p_make(5));
    vertexset_push(sub1, vertex_p_make(3));

    vertexset_push(sub2, vertex_p_make(0));
    vertexset_push(sub2, vertex_p_make(5));
    vertexset_push(sub2, vertex_p_make(3));

    mu_assert("should contain", vertexset_is_super(vertexset, sub1));
    mu_assert("should not contain", !vertexset_is_super(vertexset, sub2));
    mu_assert("should contain", vertexset_is_super(vertexset_init(10), sub3));

    return NULL;
}
char *utest_vertexset_get()
{
    VertexSet vertexset;
    vertexset = vertexset_init(7);
    mu_assert("2 should succeed", vertexset_push(vertexset, vertex_p_make(6)) == SUCCESS);
    vertexset_destroy(vertexset);
    return NULL;
}

char *utest_vertexset_destroy()
{
    return NULL;
}

char *utest_vertexset_complement()
{
    VertexSet e = vertexset_init(10); // 0-4
    VertexSet a = vertexset_init(10); // 0-9
    VertexSet b = vertexset_init(10); // 5-9
    vertexset_push(e, vertex_p_make(0));
    vertexset_push(e, vertex_p_make(1));
    vertexset_push(e, vertex_p_make(2));
    vertexset_push(a, vertex_p_make(0));
    vertexset_complement(e, a, &b);
    mu_assert("should contain", vertexset_contains_label(b, 1));
    mu_assert("should contain", vertexset_contains_label(b, 2));
    mu_assert("should not contain", !vertexset_contains_label(b, 0));
    return NULL;
}

char *test_vertexset() {
    mu_message(UNIT, "vertexset_init\n");
    mu_run_utest(utest_vertexset_init);
    mu_message(UNIT, "vertexset_contains_label\n");
    mu_run_utest(utest_vertexset_contains_label);
    mu_message(UNIT, "vertexset_centains_vertices\n");
    mu_run_utest(utest_vertexset_contains_vertices);
    mu_message(UNIT, "vertexset_get\n");
    mu_run_utest(utest_vertexset_get);
    mu_message(UNIT, "vertexset_push\n");
    mu_run_utest(utest_vertexset_push);
    mu_message(UNIT, "vertexset_complement\n");
    mu_run_utest(utest_vertexset_complement);
    return NULL;
}
