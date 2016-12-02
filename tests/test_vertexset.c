
#include <stdlib.h>
#include "test.h"

char *utest_init_vertexset()
{
    VertexSet vertexset;
    vertexset = init_vertexset(MAX_VERTICES + 1);
    mu_assert("should be null", vertexset.set == NULL);
    /* mu_assert("should be null", vertexset.set->length == 0); */
    /* vertexset = init_vertexset(MAX_VERTICES); */
    /* mu_assert("should have space for all vertices + 1 (the uninitialized one)", */
    /*         vertexset.set->length == MAX_VERTICES + 1); */
    /* for (size_t i = 0; i < vertexset.set->length; i++) { */
    /*     mu_assert("should be initialized to UNINIT_VERTEX", */ 
    /*             get_vertex(vertexset, i)->label == UNINIT_VERTEX); */
    /* } */
    /* mu_assert("initialized elements should be 0", vertexset.set->nelements == 0); */
    return NULL;
}

char *utest_add_vertex()
{
    VertexSet vertexset;
    vertexset = init_vertexset(4);
    mu_assert("1 should succeed", add_vertex(vertexset, make_vertex(4)) == SUCCESS);
    mu_assert("nelements should have increased", vertexset.set->nelements == 1);
    mu_assert("1 should fail", add_vertex(vertexset, make_vertex(75)) == FAIL);
    mu_assert("should stay the same", vertexset.set->nelements == 1);
    mu_assert("2 should fail", add_vertex(vertexset, make_vertex(11)) == FAIL);
    mu_assert("4 should fail", add_vertex(vertexset, make_vertex(5)) == FAIL);
    mu_assert("2 should succeed", add_vertex(vertexset , make_vertex(3)) == SUCCESS);
    mu_assert("should increase ", vertexset.set->nelements == 2);
    mu_assert("2 should succeed", add_vertex(vertexset , make_vertex(3)) == FAIL);
    mu_assert("3 should succeed", add_vertex(vertexset, make_vertex(2)) == SUCCESS);
    mu_assert("4 should succeed", add_vertex(vertexset, make_vertex(1)) == SUCCESS);
    mu_assert("should be false", get_vertex(vertexset, 4)->initialized == false);
    mu_assert("should now have 4 elements", vertexset.set->nelements == 4); 
    mu_assert("should be 4", get_vertex(vertexset, 0)->label == 4);
    mu_assert("should be 4", get_vertex(vertexset, 1)->label == 3);
    mu_assert("should be 4", get_vertex(vertexset, 2)->label == 2);
    mu_assert("should be 4", get_vertex(vertexset, 3)->label == 1);
    mu_assert("6 should fail", add_vertex(vertexset, make_vertex(2)) == FAIL);
    mu_assert("5 should fail to add empty ", add_vertex(vertexset, *make_p_empty_vertex()) == FAIL);
    mu_assert("7 should fail becaus vertex2 still exists", add_vertex(vertexset, make_vertex(2)) == FAIL);
    mu_assert("should be 3", get_vertex(vertexset, 0)->label == 4);
    destroy_vertexset(vertexset);
    return NULL;
}

char *utest_vertexset_contains_vertex()
{
    VertexSet vertexset = init_vertexset(3);
    mu_assert("1 should not contain any vertex", !vertexset_contains_vertex(vertexset, *make_p_empty_vertex()));
    mu_assert("2 should not contain any vertex", !vertexset_contains_vertex(vertexset, make_vertex(0)));
    mu_assert("3 should not contain any vertex", !vertexset_contains_vertex(vertexset, make_vertex(1)));
    mu_assert("4 should not contain any vertex", !vertexset_contains_vertex(vertexset, make_vertex(7)));
    add_vertex(vertexset, make_vertex(1));
    mu_assert("should now contain 1 ", vertexset_contains_vertex(vertexset, make_vertex(1)));
    add_vertex(vertexset, make_vertex(1));
    mu_assert("should still contain 1", vertexset_contains_vertex(vertexset, make_vertex(1)));
    mu_assert("should not contains malformed", !vertexset_contains_vertex(vertexset, make_vertex(4)));
    destroy_vertexset(vertexset);

    return NULL;
}

char *utest_vertexset_contains_vertices()
{
    VertexSet vertexset = init_vertexset(5);
    add_vertex(vertexset, make_vertex(1));
    add_vertex(vertexset, make_vertex(0));
    add_vertex(vertexset, make_vertex(5));
    add_vertex(vertexset, make_vertex(3));
    Vertex vertices[] = { make_vertex(1), make_vertex(0), make_vertex(5), make_vertex(3) };
    Vertex vertices2[] = { make_vertex(0), make_vertex(5), make_vertex(3) };
    Vertex vertices3[] = {};
    mu_assert("should contain", vertexset_contains_vertices(vertexset, vertices, 4));
    mu_assert("should not contain", !vertexset_contains_vertices(vertexset, vertices2, 3));
    mu_assert("should contain", vertexset_contains_vertices(init_vertexset(10), vertices3, 0));

    return NULL;
}
char *utest_get_vertex()
{
    VertexSet vertexset;
    vertexset = init_vertexset(7);
    mu_assert("1 should succeed", get_vertex(vertexset, 3)->initialized == false);
    mu_assert("2 should succeed", add_vertex(vertexset, make_vertex(6)) == SUCCESS);
    mu_assert("should be NULL", get_vertex(vertexset, 8) == NULL);
    mu_assert("should be NULL", get_vertex(vertexset, -1) == NULL);
    destroy_vertexset(vertexset);
    return NULL;
}

char *utest_destroy_vertexset()
{
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
    mu_message(UNIT, "add_vertex\n");
    mu_run_utest(utest_add_vertex);
    return NULL;
}
