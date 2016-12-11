
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
    mu_assert("1 should succeed", vertexset_push(vertexset, vertex_p_make(4)) == SUCCESS);
    mu_assert("nelements should have increased", vertexset.set->nelements == 1);
    mu_assert("1 should fail", vertexset_push(vertexset, vertex_p_make(75)) == FAIL);
    mu_assert("should stay the same", vertexset.set->nelements == 1);
    mu_assert("2 should fail", vertexset_push(vertexset, vertex_p_make(11)) == FAIL);
    mu_assert("4 should fail", vertexset_push(vertexset, vertex_p_make(5)) == FAIL);
    mu_assert("2 should succeed", vertexset_push(vertexset , vertex_p_make(3)) == SUCCESS);
    mu_assert("should increase ", vertexset.set->nelements == 2);
    mu_assert("2 should succeed", vertexset_push(vertexset , vertex_p_make(3)) == FAIL);
    mu_assert("3 should succeed", vertexset_push(vertexset, vertex_p_make(2)) == SUCCESS);
    mu_assert("4 should succeed", vertexset_push(vertexset, vertex_p_make(1)) == SUCCESS);
    mu_assert("should now have 4 elements", vertexset.set->nelements == 4); 
    mu_assert("should be 4", vertexset_get(vertexset, 0)->label == 4);
    mu_assert("should be 4", vertexset_get(vertexset, 1)->label == 3);
    mu_assert("should be 4", vertexset_get(vertexset, 2)->label == 2);
    mu_assert("should be 4", vertexset_get(vertexset, 3)->label == 1);
    mu_assert("6 should fail", vertexset_push(vertexset, vertex_p_make(2)) == FAIL);
    mu_assert("7 should fail becaus vertex2 still exists", vertexset_push(vertexset, vertex_p_make(2)) == FAIL);
    mu_assert("should be 3", vertexset_get(vertexset, 0)->label == 4);
    vertexset_destroy(vertexset);
    return NULL;
}

char *utest_vertexset_contains_vertex()
{
    VertexSet vertexset = vertexset_init(3);
    mu_assert("2 should not contain any vertex", !vertexset_contains_vertex(vertexset, vertex_p_make(0)));
    mu_assert("3 should not contain any vertex", !vertexset_contains_vertex(vertexset, vertex_p_make(1)));
    mu_assert("4 should not contain any vertex", !vertexset_contains_vertex(vertexset, vertex_p_make(7)));
    vertexset_push(vertexset, vertex_p_make(1));
    mu_assert("should now contain 1 ", vertexset_contains_vertex(vertexset, vertex_p_make(1)));
    vertexset_push(vertexset, vertex_p_make(1));
    mu_assert("should still contain 1", vertexset_contains_vertex(vertexset, vertex_p_make(1)));
    mu_assert("should not contains malformed", !vertexset_contains_vertex(vertexset, vertex_p_make(4)));
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
    mu_assert("should be NULL", vertexset_get(vertexset, 8) == NULL);
    mu_assert("should be NULL", vertexset_get(vertexset, -1) == NULL);
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
    VertexSet c = vertexset_init(10);
    VertexSet d = vertexset_init(10);
    for (size_t i = 0; i < 5; i++) {
        vertexset_push(e, vertex_p_make(i));
    }
    for (size_t i = 0; i < 10; i++) {
        vertexset_push(a, vertex_p_make(i));
    }
    for (size_t i = 5; i < 10; i++) {
        vertexset_push(b, vertex_p_make(i));
    }
    vertexset_complement(a, b, &c);
    for (size_t i = 0; i < 10; i++) {
        if (i < 5) {
            VertexPointer va = vertexset_get(a, i);
            mu_assert("a: c contains", vertexset_contains_vertex(c, va));
        } else {
            VertexPointer vb = vertexset_get(b, i);
            mu_assert("b: c does not contains", !vertexset_contains_vertex(c, vb));
        }
    }
    vertexset_complement(a, e, &d);
    for (size_t i = 0; i < 10; i++) {
        if (i < 5) {
            VertexPointer ve = vertexset_get(e, i);
            mu_assert("a: d not contains", !vertexset_contains_vertex(d, ve));
        } else {
            VertexPointer vb = vertexset_get(b, i);
            mu_assert("b: d contains", vertexset_contains_vertex(d, vb));
        }
    }
    return NULL;
}

char *test_vertexset() {
    mu_message(UNIT, "vertexset_init\n");
    mu_run_utest(utest_vertexset_init);
    mu_message(UNIT, "vertexset_contains_vertex\n");
    mu_run_utest(utest_vertexset_contains_vertex);
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
