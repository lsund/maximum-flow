
#include <stdlib.h>
#include "test.h"

char *utest_init_vertexset()
{
    return NULL;
}

char *utest_push_vertex()
{
    VertexSet vertexset;
    vertexset = init_vertexset(4);
    mu_assert("1 should succeed", push_vertex(vertexset, make_p_vertex(4)) == SUCCESS);
    mu_assert("nelements should have increased", vertexset.set->nelements == 1);
    mu_assert("1 should fail", push_vertex(vertexset, make_p_vertex(75)) == FAIL);
    mu_assert("should stay the same", vertexset.set->nelements == 1);
    mu_assert("2 should fail", push_vertex(vertexset, make_p_vertex(11)) == FAIL);
    mu_assert("4 should fail", push_vertex(vertexset, make_p_vertex(5)) == FAIL);
    mu_assert("2 should succeed", push_vertex(vertexset , make_p_vertex(3)) == SUCCESS);
    mu_assert("should increase ", vertexset.set->nelements == 2);
    mu_assert("2 should succeed", push_vertex(vertexset , make_p_vertex(3)) == FAIL);
    mu_assert("3 should succeed", push_vertex(vertexset, make_p_vertex(2)) == SUCCESS);
    mu_assert("4 should succeed", push_vertex(vertexset, make_p_vertex(1)) == SUCCESS);
    mu_assert("should now have 4 elements", vertexset.set->nelements == 4); 
    mu_assert("should be 4", get_vertex(vertexset, 0)->label == 4);
    mu_assert("should be 4", get_vertex(vertexset, 1)->label == 3);
    mu_assert("should be 4", get_vertex(vertexset, 2)->label == 2);
    mu_assert("should be 4", get_vertex(vertexset, 3)->label == 1);
    mu_assert("6 should fail", push_vertex(vertexset, make_p_vertex(2)) == FAIL);
    mu_assert("7 should fail becaus vertex2 still exists", push_vertex(vertexset, make_p_vertex(2)) == FAIL);
    mu_assert("should be 3", get_vertex(vertexset, 0)->label == 4);
    destroy_vertexset(vertexset);
    return NULL;
}

char *utest_vertexset_contains_vertex()
{
    VertexSet vertexset = init_vertexset(3);
    mu_assert("2 should not contain any vertex", !vertexset_contains_vertex(vertexset, make_p_vertex(0)));
    mu_assert("3 should not contain any vertex", !vertexset_contains_vertex(vertexset, make_p_vertex(1)));
    mu_assert("4 should not contain any vertex", !vertexset_contains_vertex(vertexset, make_p_vertex(7)));
    push_vertex(vertexset, make_p_vertex(1));
    mu_assert("should now contain 1 ", vertexset_contains_vertex(vertexset, make_p_vertex(1)));
    push_vertex(vertexset, make_p_vertex(1));
    mu_assert("should still contain 1", vertexset_contains_vertex(vertexset, make_p_vertex(1)));
    mu_assert("should not contains malformed", !vertexset_contains_vertex(vertexset, make_p_vertex(4)));
    destroy_vertexset(vertexset);

    return NULL;
}

char *utest_vertexset_contains_vertices()
{
    VertexSet vertexset = init_vertexset(5);
    push_vertex(vertexset, make_p_vertex(1));
    push_vertex(vertexset, make_p_vertex(0));
    push_vertex(vertexset, make_p_vertex(5));
    push_vertex(vertexset, make_p_vertex(3));
    VertexSet sub1 = init_vertexset(5);
    VertexSet sub2 = init_vertexset(5);
    VertexSet sub3 = init_vertexset(5);

    push_vertex(sub1, make_p_vertex(1));
    push_vertex(sub1, make_p_vertex(0));
    push_vertex(sub1, make_p_vertex(5));
    push_vertex(sub1, make_p_vertex(3));

    push_vertex(sub2, make_p_vertex(0));
    push_vertex(sub2, make_p_vertex(5));
    push_vertex(sub2, make_p_vertex(3));

    mu_assert("should contain", is_super_vertexset(vertexset, sub1));
    mu_assert("should not contain", !is_super_vertexset(vertexset, sub2));
    mu_assert("should contain", is_super_vertexset(init_vertexset(10), sub3));

    return NULL;
}
char *utest_get_vertex()
{
    VertexSet vertexset;
    vertexset = init_vertexset(7);
    mu_assert("2 should succeed", push_vertex(vertexset, make_p_vertex(6)) == SUCCESS);
    mu_assert("should be NULL", get_vertex(vertexset, 8) == NULL);
    mu_assert("should be NULL", get_vertex(vertexset, -1) == NULL);
    destroy_vertexset(vertexset);
    return NULL;
}

char *utest_destroy_vertexset()
{
    return NULL;
}

char *utest_vertexset_complement()
{
    VertexSet e = init_vertexset(10); // 0-4
    VertexSet a = init_vertexset(10); // 0-9
    VertexSet b = init_vertexset(10); // 5-9
    VertexSet c = init_vertexset(10);
    VertexSet d = init_vertexset(10);
    for (size_t i = 0; i < 5; i++) {
        push_vertex(e, make_p_vertex(i));
    }
    for (size_t i = 0; i < 10; i++) {
        push_vertex(a, make_p_vertex(i));
    }
    for (size_t i = 5; i < 10; i++) {
        push_vertex(b, make_p_vertex(i));
    }
    vertexset_complement(a, b, &c);
    for (size_t i = 0; i < 10; i++) {
        if (i < 5) {
            VertexPointer va = get_vertex(a, i);
            mu_assert("a: c contains", vertexset_contains_vertex(c, va));
        } else {
            VertexPointer vb = get_vertex(b, i);
            mu_assert("b: c does not contains", !vertexset_contains_vertex(c, vb));
        }
    }
    vertexset_complement(a, e, &d);
    for (size_t i = 0; i < 10; i++) {
        if (i < 5) {
            VertexPointer ve = get_vertex(e, i);
            mu_assert("a: d not contains", !vertexset_contains_vertex(d, ve));
        } else {
            VertexPointer vb = get_vertex(b, i);
            mu_assert("b: d contains", vertexset_contains_vertex(d, vb));
        }
    }
    return NULL;
}

char *test_vertexset() {
    mu_message(UNIT, "init_vertexset\n");
    mu_run_utest(utest_init_vertexset);
    mu_message(UNIT, "vertexset_contains_vertex\n");
    mu_run_utest(utest_vertexset_contains_vertex);
    mu_message(UNIT, "vertexset_centains_vertices\n");
    mu_run_utest(utest_vertexset_contains_vertices);
    mu_message(UNIT, "get_vertex\n");
    mu_run_utest(utest_get_vertex);
    mu_message(UNIT, "push_vertex\n");
    mu_run_utest(utest_push_vertex);
    mu_message(UNIT, "vertexset_complement\n");
    mu_run_utest(utest_vertexset_complement);
    return NULL;
}
