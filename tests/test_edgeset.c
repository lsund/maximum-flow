
#include <stdlib.h>
#include "test.h"

char *utest_init_edgeset()
{
    EdgeSet edgeset = init_edgeset(1000);
    mu_assert("Too large input should give null", edgeset.set == NULL);
    edgeset = init_edgeset(3);
    mu_assert("should have length 9", edgeset.set->length == 9);
    mu_assert("should not contain any vertex", !edgeset_contains_vertex(edgeset, make_p_vertex(0)));
    mu_assert("should not contain any vertex", !edgeset_contains_vertex(edgeset, make_p_vertex(1)));
    return NULL;
}

char *utest_destroy_edgeset()
{
    EdgeSet edgeset = init_edgeset(2);
    mu_assert("should succeed", destroy_edgeset(edgeset) == SUCCESS);
    edgeset = init_edgeset(2);
    edgeset.set->head = NULL;
    mu_assert("should succeed", destroy_edgeset(edgeset) == SUCCESS);
    return NULL;
}

char *utest_push_edge()
{
    EdgeSet edgeset;
    edgeset = init_edgeset(4);
    mu_assert("should fail", push_edge(edgeset, make_p_edge_label(2, 2)) == FAIL);
    mu_assert("should not contain vertex 2", !edgeset_contains_vertex(edgeset, make_p_vertex(2)));
    mu_assert("1 should succeed", push_edge(edgeset, make_p_edge_label(2, 3)) == SUCCESS);
    mu_assert("should fail", push_edge(edgeset, make_p_edge_label(77,77)) == FAIL);
    mu_assert("should be 2", get_edge(edgeset, 0)->first->label == 2);
    mu_assert("should contain vertex 2", edgeset_contains_vertex(edgeset, make_p_vertex(2)));
    mu_assert("should contain vertex 3", edgeset_contains_vertex(edgeset, make_p_vertex(3)));
    VertexSetPointer vertices = edgeset_vertices(edgeset);
    mu_assert("vertexset should also contain 2", vertexset_contains_vertex(*vertices, make_p_vertex(2)));
    mu_assert("vertexset should also contain 3", vertexset_contains_vertex(*vertices, make_p_vertex(3)));
    /* mu_assert("should not be able to add the same edge 'swapped'", */ 
    /*         push_edge(edgeset, make_edge(make_vertex(3), make_vertex(2))) == FAIL); */
    destroy_edgeset(edgeset);

    /* edgeset = init_edgeset(4); */
    /* VertexPointer x = make_p_vertex(0); */
    /* VertexPointer y = make_p_vertex(1); */
    /* VertexPointer a = make_p_vertex(2); */
    /* VertexPointer b = make_p_vertex(3); */
    /* push_edge(edgeset, make_edge(a, b)); */
    /* mu_assert("should have one neighbour", a->neighbors.nelements == 1); */
    /* mu_assert("should have one neighbour", b->neighbors.nelements == 1); */
    /* VertexPointer neighbor = get_element(&a->neighbors, 0); */
    /* mu_assert("neighbour should be b", neighbor->label == 3); */
    /* neighbor = get_element(&b->neighbors, 0); */
    /* mu_assert("neighbour should be a", neighbor->label == 2); */
    /* push_edge(edgeset, make_edge(a, x)); */
    /* mu_assert("should have two neighbour", a->neighbors.nelements == 2); */
    /* mu_assert("should have one neighbour", b->neighbors.nelements == 1); */
    /* mu_assert("should have one neighbour", x->neighbors.nelements == 1); */
    /* push_edge(edgeset, make_edge(y, b)); */
    /* mu_assert("should have two neighbour", a->neighbors.nelements == 2); */
    /* mu_assert("should have one neighbour", b->neighbors.nelements == 2); */
    /* mu_assert("should have one neighbour", x->neighbors.nelements == 1); */
    /* mu_assert("should have one neighbour", y->neighbors.nelements == 1); */

    return NULL;
}

char *utest_get_edge()
{
    EdgeSet edgeset;
    edgeset = init_edgeset(4);
    mu_assert("should fail", push_edge(edgeset, make_p_edge_label(77,77)) == FAIL);
    mu_assert("should succeed", push_edge(edgeset, make_p_edge_label(0, 1)) == SUCCESS);
    destroy_edgeset(edgeset);
    return NULL;
}

char *utest_edgeset_complement()
{
    EdgeSet edgeset_a = init_edgeset(4);
    EdgeSet edgeset_b = init_edgeset(4);
    push_edge(edgeset_a, make_p_edge_label(0, 1));
    push_edge(edgeset_a, make_p_edge_label(1, 2));
    push_edge(edgeset_a, make_p_edge_label(2, 3));
    push_edge(edgeset_b, make_p_edge_label(1, 2));
    EdgeSet edgeset_c, edgeset_d;
    edgeset_c = init_edgeset(4);
    edgeset_d = init_edgeset(4);
    edgeset_complement(edgeset_a, edgeset_b, &edgeset_c);
    edgeset_complement(edgeset_b, edgeset_a, &edgeset_d);
    mu_assert("should have length 16", edgeset_c.set->length == 16);
    mu_assert("should have 2 elements", edgeset_c.set->nelements == 2);
    mu_assert("and should be these edges", get_edge(edgeset_c, 0)->first->label == 0);
    mu_assert("and should be these edges", get_edge(edgeset_c, 0)->second->label == 1);
    mu_assert("and should be these edges", get_edge(edgeset_c, 1)->first->label == 2);
    mu_assert("and should be these edges", get_edge(edgeset_c, 1)->second->label == 3);
    mu_assert("should have length 16", edgeset_d.set->length == 16);
    mu_assert("should be empty", edgeset_d.set->nelements == 0);
    destroy_edgeset(edgeset_a);
    destroy_edgeset(edgeset_b);
    destroy_edgeset(edgeset_c);
    edgeset_a = init_edgeset(4);
    edgeset_b = init_edgeset(4);
    edgeset_c = init_edgeset(4);
    edgeset_complement(edgeset_a, edgeset_b, &edgeset_c);
    mu_assert("should be empty", edgeset_is_empty(edgeset_c));
    destroy_edgeset(edgeset_a);
    destroy_edgeset(edgeset_b);
    destroy_edgeset(edgeset_c);

    edgeset_a = init_edgeset(4);
    edgeset_b = init_edgeset(4);
    edgeset_c = init_edgeset(4);
    push_edge(edgeset_a, make_p_edge_label(1, 3));
    push_edge(edgeset_a, make_p_edge_label(3, 2));
    push_edge(edgeset_a, make_p_edge_label(2, 1));
    push_edge(edgeset_b, make_p_edge_label(1, 3));
    edgeset_complement(edgeset_b, edgeset_a, &edgeset_c);
    mu_assert("should be empty", edgeset_is_empty(edgeset_c));

    return NULL;
}

char *utest_symmetric_difference()
{
    EdgeSet graph = init_edgeset(8);
    EdgeSet matching = init_edgeset(8);
    EdgeSet path = init_edgeset(8);
    push_edge(graph, make_p_edge_label(0, 1));
    push_edge(graph, make_p_edge_label(1, 2));
    push_edge(graph, make_p_edge_label(2, 3));
    push_edge(graph, make_p_edge_label(3, 4));
    push_edge(graph, make_p_edge_label(2, 5));
    push_edge(graph, make_p_edge_label(2, 6));
    push_edge(graph, make_p_edge_label(6, 7));
    mu_assert("should not be a matching", !is_matching(graph));
    push_edge(matching, make_p_edge_label(0, 1));
    push_edge(matching, make_p_edge_label(2, 6));
    push_edge(matching, make_p_edge_label(3, 4));
    mu_assert("should be amatching", is_matching(matching));
    push_edge(path, make_p_edge_label(2, 5));
    push_edge(path, make_p_edge_label(2, 6));
    push_edge(path, make_p_edge_label(6, 7));
    EdgeSet augment = init_edgeset(8);
    mu_assert("should succeed", symmetric_difference(matching, path, &augment));
    mu_assert("should be amatching", is_matching(augment));
    mu_assert("should be of one larger size", augment.set->nelements == matching.set->nelements + 1);
    mu_assert("should contain this edge",
            edgeset_contains_edge(augment, make_p_edge_label(6, 7)));
    mu_assert("should contain this edge", 
            edgeset_contains_edge(augment, make_p_edge_label(2, 5)));
    mu_assert("should contain this edge", 
            edgeset_contains_edge(augment, make_p_edge_label(3, 4)));
    mu_assert("should contain this edge", 
            edgeset_contains_edge(augment, make_p_edge_label(0, 1)));

    return NULL;
}


char *utest_edgeset_union()
{
    EdgeSet edgeset_a = init_edgeset(4);
    EdgeSet edgeset_b = init_edgeset(4);
    push_edge(edgeset_a, make_p_edge_label(0, 1));
    push_edge(edgeset_a, make_p_edge_label(1, 2));
    push_edge(edgeset_a, make_p_edge_label(2, 3));
    push_edge(edgeset_b, make_p_edge_label(1, 2));
    EdgeSet edgeset_c = init_edgeset(4);
    edgeset_union(edgeset_a, edgeset_b, &edgeset_c);
    mu_assert("should have length 16", edgeset_c.set->length == 16);
    mu_assert("should have 2 elements", edgeset_c.set->nelements == 3);
    mu_assert("and should be these edges", get_edge(edgeset_c, 0)->first->label == 0);
    mu_assert("and should be these edges", get_edge(edgeset_c, 0)->second->label == 1);
    mu_assert("and should be these edges", get_edge(edgeset_c, 1)->first->label == 1);
    mu_assert("and should be these edges", get_edge(edgeset_c, 1)->second->label == 2);
    mu_assert("and should be these edges", get_edge(edgeset_c, 2)->first->label == 2);
    mu_assert("and should be these edges", get_edge(edgeset_c, 2)->second->label == 3);
    destroy_edgeset(edgeset_a);
    destroy_edgeset(edgeset_b);
    destroy_edgeset(edgeset_c);
    edgeset_a = init_edgeset(4);
    edgeset_b = init_edgeset(4);
    edgeset_c = init_edgeset(4);
    edgeset_complement(edgeset_a, edgeset_b, &edgeset_c);
    mu_assert("should be empty", edgeset_is_empty(edgeset_c));
    destroy_edgeset(edgeset_a);
    destroy_edgeset(edgeset_b);
    destroy_edgeset(edgeset_c);
    return NULL;
}

char *utest_edgeset_contains_edge()
{
    EdgeSet edgeset = init_edgeset(3);
    EdgePointer a = make_p_edge_label(0, 1);
    EdgePointer b = make_p_edge_label(0, 2);
    EdgePointer c = make_p_edge_label(1, 2);
    EdgePointer d = make_p_edge_label(0, 3);
    push_edge(edgeset, a);
    push_edge(edgeset, b);
    push_edge(edgeset, c);
    mu_assert("1 should have this edge", edgeset_contains_edge(edgeset, a));
    mu_assert("2 should have this edge", edgeset_contains_edge(edgeset, b));
    mu_assert("3 should have this edge", edgeset_contains_edge(edgeset, c));
    mu_assert("4 should not be able to add this edge", push_edge(edgeset, d) == FAIL);
    mu_assert("5 should have this edge", edgeset_contains_edge(edgeset, make_p_edge_edge(swapped(*a))));
    mu_assert("6 should have this edge", edgeset_contains_edge(edgeset, make_p_edge_edge(swapped(*b))));
    mu_assert("7 should have this edge", edgeset_contains_edge(edgeset, make_p_edge_edge(swapped(*c))));
    destroy_edgeset(edgeset);
    edgeset = init_edgeset(16);
    TokenTablePointer table = init_tokentable();
    make_tokentable("data/graphs/queen4_4.dmx", table);
    VertexSet vertexset = init_vertexset(16);
    parse_vertices(vertexset);
    mu_assert("should work", parse_edges(table, edgeset, NULL, vertexset));
    mu_assert("8 should have this edge", edgeset_contains_edge(edgeset, make_p_edge_label(13, 7)));
    mu_assert("9 should have this edge", edgeset_contains_edge(edgeset, make_p_edge_label(14, 8)));
    mu_assert("10 should have this edge", 
            edgeset_contains_edge(edgeset, make_p_edge_label(8, 14)));
    mu_assert("11 should have this edge", 
            edgeset_contains_edge(edgeset, make_p_edge_label(10, 15)));
    mu_assert("should have this edge", 
            edgeset_contains_edge(edgeset, make_p_edge_label(10, 11)));
    destroy_edgeset(edgeset);
    return NULL;
}

char *utest_covered_by()
{
    EdgeSet edgeset = init_edgeset(5);
    EdgePointer a = make_p_edge_label(0, 1);
    EdgePointer b = make_p_edge_label(1, 2);
    EdgePointer c = make_p_edge_label(2, 3);
    EdgePointer d = make_p_edge_label(1, 2);
    EdgePointer e = make_p_edge_label(3, 4);
    push_edge(edgeset, a);
    push_edge(edgeset, b);
    push_edge(edgeset, c);
    push_edge(edgeset, d);
    push_edge(edgeset, e);
    EdgePointer ret = malloc(sizeof(Edge));
    covered_by(edgeset, make_p_vertex(1), &ret);
    mu_assert("should be", edges_equal(ret, make_p_edge_label(0, 1)));
    covered_by(edgeset, make_p_vertex(2), &ret);
    mu_assert("should be", edges_equal(ret, make_p_edge_label(1, 2)));
    covered_by(edgeset, make_p_vertex(3), &ret);
    mu_assert("should be", edges_equal(ret, make_p_edge_label(2, 3)));
    mu_assert("should succeed", SUCCESS == covered_by(edgeset, make_p_vertex(4), &ret));
    mu_assert("should be", edges_equal(ret, make_p_edge_label(3, 4)));
    mu_assert("should fail", FAIL == covered_by(edgeset, make_p_vertex(5), &ret));
    return NULL;
}

char *test_edgeset() {
    mu_message(UNIT, "push_edge\n");
    mu_run_utest(utest_push_edge);
    mu_message(UNIT, "init_edgeset\n");
    mu_run_utest(utest_init_edgeset);
    mu_message(UNIT, "edgeset_complement\n");
    mu_run_utest(utest_edgeset_complement);
    mu_message(UNIT, "edgeset_union\n");
    mu_run_utest(utest_edgeset_union);
    mu_message(UNIT, "symmetric difference\n");
    mu_run_utest(utest_symmetric_difference);
    mu_message(UNIT, "destroy_edgeset\n");
    mu_run_utest(utest_destroy_edgeset);
    mu_message(UNIT, "get_edge\n");
    mu_run_utest(utest_get_edge);
    mu_message(UNIT, "edgeset_contains_edge\n");
    mu_run_utest(utest_edgeset_contains_edge);
    mu_message(UNIT, "Covered_by\n");
    mu_run_utest(utest_covered_by);
    return NULL;
}
