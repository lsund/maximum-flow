
#include <stdlib.h>
#include "test.h"

char *utest_edgeset_init()
{
    EdgeSet edgeset = edgeset_init(3);
    mu_assert("should have length 9", edgeset.set->capacity == 3);
    mu_assert("should not contain any vertex", !edgeset_contains_vertex(edgeset, vertex_p_make(0)));
    mu_assert("should not contain any vertex", !edgeset_contains_vertex(edgeset, vertex_p_make(1)));
    return NULL;
}

char *utest_edgeset_destroy()
{
    EdgeSet edgeset = edgeset_init(2);
    mu_assert("should succeed", edgeset_destroy(edgeset) == SUCCESS);
    edgeset = edgeset_init(2);
    edgeset.set->head = NULL;
    mu_assert("should succeed", edgeset_destroy(edgeset) == SUCCESS);
    return NULL;
}

char *utest_edgeset_push()
{
    EdgeSet edgeset;
    edgeset = edgeset_init(4);
    mu_assert("should not contain vertex 2", !edgeset_contains_vertex(edgeset, vertex_p_make(2)));
    mu_assert("1 should succeed", edgeset_push(edgeset, edge_p_make_label(2, 3)) == SUCCESS);
    mu_assert("should be 2", edgeset_get(edgeset, 0)->first->label == 2);
    mu_assert("should contain vertex 2", edgeset_contains_vertex(edgeset, vertex_p_make(2)));
    mu_assert("should contain vertex 3", edgeset_contains_vertex(edgeset, vertex_p_make(3)));
    VertexSet vertices = edgeset_vertices(edgeset);
    mu_assert("vertexset should also contain 2", vertexset_contains_label(vertices, 2));
    mu_assert("vertexset should also contain 3", vertexset_contains_label(vertices, 3));
    /* mu_assert("should not be able to add the same edge 'edge_edge_swapped'", */ 
    /*         edgeset_push(edgeset, edge_make(vertex_make(3), vertex_make(2))) == FAIL); */
    edgeset_destroy(edgeset);

    /* edgeset = edgeset_init(4); */
    /* VertexPointer x = vertex_p_make(0); */
    /* VertexPointer y = vertex_p_make(1); */
    /* VertexPointer a = vertex_p_make(2); */
    /* VertexPointer b = vertex_p_make(3); */
    /* edgeset_push(edgeset, edge_make(a, b)); */
    /* mu_assert("should have one neighbour", a->neighbors.length == 1); */
    /* mu_assert("should have one neighbour", b->neighbors.length == 1); */
    /* VertexPointer neighbor = array_get(&a->neighbors, 0); */
    /* mu_assert("neighbour should be b", neighbor->label == 3); */
    /* neighbor = array_get(&b->neighbors, 0); */
    /* mu_assert("neighbour should be a", neighbor->label == 2); */
    /* edgeset_push(edgeset, edge_make(a, x)); */
    /* mu_assert("should have two neighbour", a->neighbors.length == 2); */
    /* mu_assert("should have one neighbour", b->neighbors.length == 1); */
    /* mu_assert("should have one neighbour", x->neighbors.length == 1); */
    /* edgeset_push(edgeset, edge_make(y, b)); */
    /* mu_assert("should have two neighbour", a->neighbors.length == 2); */
    /* mu_assert("should have one neighbour", b->neighbors.length == 2); */
    /* mu_assert("should have one neighbour", x->neighbors.length == 1); */
    /* mu_assert("should have one neighbour", y->neighbors.length == 1); */

    return NULL;
}

char *utest_edgeset_get()
{
    EdgeSet edgeset;
    edgeset = edgeset_init(4);
    mu_assert("should succeed", edgeset_push(edgeset, edge_p_make_label(0, 1)) == SUCCESS);
    edgeset_destroy(edgeset);
    return NULL;
}

char *utest_edgeset_complement()
{
    EdgeSet edgeset_a = edgeset_init(4);
    EdgeSet edgeset_b = edgeset_init(4);
    edgeset_push(edgeset_a, edge_p_make_label(0, 1));
    edgeset_push(edgeset_a, edge_p_make_label(1, 2));
    edgeset_push(edgeset_a, edge_p_make_label(2, 3));
    edgeset_push(edgeset_b, edge_p_make_label(1, 2));
    EdgeSet edgeset_c, edgeset_d;
    edgeset_c = edgeset_init(4);
    edgeset_d = edgeset_init(4);
    edgeset_complement(edgeset_a, edgeset_b, &edgeset_c);
    edgeset_complement(edgeset_b, edgeset_a, &edgeset_d);
    mu_assert("should have length 4", edgeset_c.set->capacity == 4);
    mu_assert("should have 2 elements", edgeset_c.set->length == 2);
    mu_assert("and should be these edges", edgeset_get(edgeset_c, 0)->first->label == 0);
    mu_assert("and should be these edges", edgeset_get(edgeset_c, 0)->second->label == 1);
    mu_assert("and should be these edges", edgeset_get(edgeset_c, 1)->first->label == 2);
    mu_assert("and should be these edges", edgeset_get(edgeset_c, 1)->second->label == 3);
    mu_assert("should have length 4", edgeset_d.set->capacity == 4);
    mu_assert("should be empty", edgeset_d.set->length == 0);
    edgeset_destroy(edgeset_a);
    edgeset_destroy(edgeset_b);
    edgeset_destroy(edgeset_c);
    edgeset_a = edgeset_init(4);
    edgeset_b = edgeset_init(4);
    edgeset_c = edgeset_init(4);
    edgeset_complement(edgeset_a, edgeset_b, &edgeset_c);
    mu_assert("should be empty", edgeset_is_empty(edgeset_c));
    edgeset_destroy(edgeset_a);
    edgeset_destroy(edgeset_b);
    edgeset_destroy(edgeset_c);

    edgeset_a = edgeset_init(4);
    edgeset_b = edgeset_init(4);
    edgeset_c = edgeset_init(4);
    edgeset_push(edgeset_a, edge_p_make_label(1, 3));
    edgeset_push(edgeset_a, edge_p_make_label(3, 2));
    edgeset_push(edgeset_a, edge_p_make_label(2, 1));
    edgeset_push(edgeset_b, edge_p_make_label(1, 3));
    edgeset_complement(edgeset_b, edgeset_a, &edgeset_c);
    mu_assert("should be empty", edgeset_is_empty(edgeset_c));

    return NULL;
}

char *utest_edgeset_symmetric_difference()
{
    EdgeSet graph = edgeset_init(8);
    EdgeSet matching = edgeset_init(8);
    EdgeSet path = edgeset_init(8);
    edgeset_push(graph, edge_p_make_label(0, 1));
    edgeset_push(graph, edge_p_make_label(1, 2));
    edgeset_push(graph, edge_p_make_label(2, 3));
    edgeset_push(graph, edge_p_make_label(3, 4));
    edgeset_push(graph, edge_p_make_label(2, 5));
    edgeset_push(graph, edge_p_make_label(2, 6));
    edgeset_push(graph, edge_p_make_label(6, 7));
    mu_assert("should not be a matching", !is_matching(graph));
    edgeset_push(matching, edge_p_make_label(0, 1));
    edgeset_push(matching, edge_p_make_label(2, 6));
    edgeset_push(matching, edge_p_make_label(3, 4));
    mu_assert("should be amatching", is_matching(matching));
    edgeset_push(path, edge_p_make_label(2, 5));
    edgeset_push(path, edge_p_make_label(2, 6));
    edgeset_push(path, edge_p_make_label(6, 7));
    EdgeSet matching_augment = edgeset_init(8);
    mu_assert("should succeed", edgeset_symmetric_difference(matching, path, &matching_augment));
    mu_assert("should be amatching", is_matching(matching_augment));
    mu_assert("should be of one larger size", matching_augment.set->length == matching.set->length + 1);
    mu_assert("should contain this edge",
            edgeset_contains_edge(matching_augment, edge_p_make_label(6, 7)));
    mu_assert("should contain this edge", 
            edgeset_contains_edge(matching_augment, edge_p_make_label(2, 5)));
    mu_assert("should contain this edge", 
            edgeset_contains_edge(matching_augment, edge_p_make_label(3, 4)));
    mu_assert("should contain this edge", 
            edgeset_contains_edge(matching_augment, edge_p_make_label(0, 1)));

    return NULL;
}


char *utest_edgeset_union()
{
    EdgeSet edgeset_a = edgeset_init(4);
    EdgeSet edgeset_b = edgeset_init(4);
    edgeset_push(edgeset_a, edge_p_make_label(0, 1));
    edgeset_push(edgeset_a, edge_p_make_label(1, 2));
    edgeset_push(edgeset_a, edge_p_make_label(2, 3));
    edgeset_push(edgeset_b, edge_p_make_label(1, 2));
    EdgeSet edgeset_c = edgeset_init(4);
    edgeset_union(edgeset_a, edgeset_b, &edgeset_c);
    mu_assert("should have length 4", edgeset_c.set->capacity == 4);
    mu_assert("should have 3 elements", edgeset_c.set->length == 3);
    mu_assert("and should be these edges", edgeset_get(edgeset_c, 0)->first->label == 0);
    mu_assert("and should be these edges", edgeset_get(edgeset_c, 0)->second->label == 1);
    mu_assert("and should be these edges", edgeset_get(edgeset_c, 1)->first->label == 1);
    mu_assert("and should be these edges", edgeset_get(edgeset_c, 1)->second->label == 2);
    mu_assert("and should be these edges", edgeset_get(edgeset_c, 2)->first->label == 2);
    mu_assert("and should be these edges", edgeset_get(edgeset_c, 2)->second->label == 3);
    edgeset_destroy(edgeset_a);
    edgeset_destroy(edgeset_b);
    edgeset_destroy(edgeset_c);
    edgeset_a = edgeset_init(4);
    edgeset_b = edgeset_init(4);
    edgeset_c = edgeset_init(4);
    edgeset_complement(edgeset_a, edgeset_b, &edgeset_c);
    mu_assert("should be empty", edgeset_is_empty(edgeset_c));
    edgeset_destroy(edgeset_a);
    edgeset_destroy(edgeset_b);
    edgeset_destroy(edgeset_c);
    return NULL;
}

char *utest_edgeset_contains_edge()
{
    EdgeSet edgeset = edgeset_init(3);
    EdgePointer a = edge_p_make_label(0, 1);
    EdgePointer b = edge_p_make_label(0, 2);
    EdgePointer c = edge_p_make_label(1, 2);
    EdgePointer d = edge_p_make_label(0, 3);
    edgeset_push(edgeset, a);
    edgeset_push(edgeset, b);
    edgeset_push(edgeset, c);
    mu_assert("1 should have this edge", edgeset_contains_edge(edgeset, a));
    mu_assert("2 should have this edge", edgeset_contains_edge(edgeset, b));
    mu_assert("3 should have this edge", edgeset_contains_edge(edgeset, c));
    mu_assert("4 should not be able to add this edge", edgeset_push(edgeset, d) == SUCCESS);
    edgeset_destroy(edgeset);
    edgeset = edgeset_init(16);
    TokenTablePointer table = init_tokentable();
    make_tokentable("data/graphs/queen4_4.dmx", table);
    VertexSet vertexset = vertexset_init(16);
    parse_vertices(vertexset);
    mu_assert("should work", parse_edges(table, edgeset, NULL, vertexset));
    mu_assert("8 should have this edge", edgeset_contains_edge(edgeset, edge_p_make_label(13, 7)));
    mu_assert("9 should have this edge", edgeset_contains_edge(edgeset, edge_p_make_label(14, 8)));
    mu_assert("10 should have this edge", 
            edgeset_contains_edge(edgeset, edge_p_make_label(8, 14)));
    mu_assert("11 should have this edge", 
            edgeset_contains_edge(edgeset, edge_p_make_label(10, 15)));
    mu_assert("should have this edge", 
            edgeset_contains_edge(edgeset, edge_p_make_label(10, 11)));
    edgeset_destroy(edgeset);
    return NULL;
}

char *utest_edgeset_covered_by()
{
    EdgeSet edgeset = edgeset_init(5);
    EdgePointer a = edge_p_make_label(0, 1);
    EdgePointer b = edge_p_make_label(1, 2);
    EdgePointer c = edge_p_make_label(2, 3);
    EdgePointer d = edge_p_make_label(1, 2);
    EdgePointer e = edge_p_make_label(3, 4);
    edgeset_push(edgeset, a);
    edgeset_push(edgeset, b);
    edgeset_push(edgeset, c);
    edgeset_push(edgeset, d);
    edgeset_push(edgeset, e);
    EdgePointer ret = malloc(sizeof(Edge));
    edgeset_covered_by(edgeset, vertex_p_make(1), &ret);
    mu_assert("should be", edge_equals(ret, edge_p_make_label(0, 1)));
    edgeset_covered_by(edgeset, vertex_p_make(2), &ret);
    mu_assert("should be", edge_equals(ret, edge_p_make_label(1, 2)));
    edgeset_covered_by(edgeset, vertex_p_make(3), &ret);
    mu_assert("should be", edge_equals(ret, edge_p_make_label(2, 3)));
    mu_assert("should succeed", SUCCESS == edgeset_covered_by(edgeset, vertex_p_make(4), &ret));
    mu_assert("should be", edge_equals(ret, edge_p_make_label(3, 4)));
    return NULL;
}

char *test_edgeset() {
    mu_message(UNIT, "edgeset_push\n");
    mu_run_utest(utest_edgeset_push);
    mu_message(UNIT, "edgeset_init\n");
    mu_run_utest(utest_edgeset_init);
    mu_message(UNIT, "edgeset_complement\n");
    mu_run_utest(utest_edgeset_complement);
    mu_message(UNIT, "edgeset_union\n");
    mu_run_utest(utest_edgeset_union);
    mu_message(UNIT, "symmetric difference\n");
    mu_run_utest(utest_edgeset_symmetric_difference);
    mu_message(UNIT, "edgeset_destroy\n");
    mu_run_utest(utest_edgeset_destroy);
    mu_message(UNIT, "edgeset_get\n");
    mu_run_utest(utest_edgeset_get);
    mu_message(UNIT, "edgeset_contains_edge\n");
    mu_run_utest(utest_edgeset_contains_edge);
    mu_message(UNIT, "Covered_by\n");
    mu_run_utest(utest_edgeset_covered_by);
    return NULL;
}
