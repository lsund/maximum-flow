
#include <stdlib.h>
#include "test.h"

char *utest_edgeset_empty()
{
    EdgeSet edgeset = edgeset_empty();
    mu_assert("should be null", edgeset_is_empty(edgeset));
    return NULL;
}

char *utest_edgeset_init()
{
    EdgeSet edgeset = edgeset_init(3);
    mu_assert("should have length 9", edgeset.set->capacity == 3);
    mu_assert("should be empty", edgeset_is_empty(edgeset));
    mu_assert("should not contain any vertex", !edgeset_contains_vertex(edgeset, vertex_p_make(0)));
    mu_assert("should not contain any vertex", !edgeset_contains_vertex(edgeset, vertex_p_make(1)));
    return NULL;
}

char *utest_edgeset_p_init()
{
    EdgeSetPointer edgeset = edgeset_p_init(3);
    mu_assert("should have length 9", edgeset->set->capacity == 3);
    mu_assert("should be empty", edgeset_is_empty(*edgeset));
    mu_assert("should not contain any vertex", !edgeset_contains_vertex(*edgeset, vertex_p_make(0)));
    mu_assert("should not contain any vertex", !edgeset_contains_vertex(*edgeset, vertex_p_make(1)));
    return NULL;
}

char *utest_edgeset_get()
{
    EdgeSet edgeset;
    edgeset = edgeset_init(4);
    mu_assert("should succeed", edgeset_push(edgeset, edge_p_make_label(0, 1)) == SUCCESS);
    EdgePointer edge = edgeset_get(edgeset, 0);
    mu_assert("should be 0", edge->first->label == 0);
    mu_assert("should be 1", edge->second->label == 1);
    edge = edgeset_get(edgeset, 1);
    mu_assert("should be null", !edge);
    edgeset_destroy(edgeset);
    return NULL;
}

char *utest_edgeset_vertex_count()
{
    EdgeSet edgeset;
    edgeset = edgeset_init(4);
    edgeset_push(edgeset, edge_p_make_label(0, 1));
    edgeset_push(edgeset, edge_p_make_label(2, 1));
    edgeset_push(edgeset, edge_p_make_label(1, 2));
    edgeset_push(edgeset, edge_p_make_label(3, 4));
    mu_assert("should have 5 vertices", edgeset_vertex_count(edgeset) == 5);
    return NULL;
}

char *utest_edgeset_vertices()
{
    EdgeSet edgeset;
    edgeset = edgeset_init(4);
    edgeset_push(edgeset, edge_p_make_label(0, 2));
    edgeset_push(edgeset, edge_p_make_label(2, 1));
    edgeset_push(edgeset, edge_p_make_label(1, 2));
    edgeset_push(edgeset, edge_p_make_label(3, 4));
    VertexSet vertexset = edgeset_vertices(edgeset);
    mu_assert("should be", vertexset_get(vertexset, 0)->label == 0);
    mu_assert("should be", vertexset_get(vertexset, 1)->label == 2);
    mu_assert("should be", vertexset_get(vertexset, 2)->label == 1);
    mu_assert("should be", vertexset_get(vertexset, 3)->label == 3);
    mu_assert("should be", vertexset_get(vertexset, 4)->label == 4);
    return NULL;
}

char *utest_edgeset_set()
{
    EdgeSet edgeset;
    edgeset = edgeset_init(4);
    edgeset_push(edgeset, edge_p_make_label(0, 2));
    edgeset_push(edgeset, edge_p_make_label(2, 1));
    edgeset_push(edgeset, edge_p_make_label(1, 2));
    edgeset_push(edgeset, edge_p_make_label(3, 4));
    EdgePointer e = edge_p_make_label(77, 78);
    edgeset_set(edgeset, NULL, 0);
    edgeset_set(edgeset, e, 1);
    mu_assert("should be null", edge_equals(edgeset_get(edgeset, 0), NULL));
    mu_assert("should be null", edge_equals(edgeset_get(edgeset, 1), e));
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
    mu_assert("capacity still 4", edgeset.set->capacity == 4);
    mu_assert("length 1", edgeset.set->length == 1);
    return NULL;
}

char *utest_edgeset_is_empty()
{
    EdgeSet edgeset = edgeset_empty();
    mu_assert("should be empty", edgeset_is_empty(edgeset));
    return NULL;
}

char *utest_edgeset_equals()
{
    EdgeSet edgeset, edgeset2;
    edgeset = edgeset_init(5);
    edgeset2 = edgeset_init(5);
    edgeset_push(edgeset, edge_p_make_label(0, 2));
    edgeset_push(edgeset, edge_p_make_label(2, 1));
    edgeset_push(edgeset, edge_p_make_label(1, 2));
    edgeset_push(edgeset, edge_p_make_label(3, 4));
    edgeset_push(edgeset2, edge_p_make_label(0, 2));
    edgeset_push(edgeset2, edge_p_make_label(2, 1));
    edgeset_push(edgeset2, edge_p_make_label(1, 2));
    edgeset_push(edgeset2, edge_p_make_label(3, 4));
    mu_assert("should equal", edgeset_equals(edgeset, edgeset2));
    edgeset_push(edgeset2, edge_p_make_label(5, 6));
    mu_assert("should not equal", !edgeset_equals(edgeset, edgeset2));
    edgeset_push(edgeset, edge_p_make_label(5, 6));
    mu_assert("should equal", edgeset_equals(edgeset, edgeset2));
    edgeset.set->capacity = 10;
    mu_assert("should not equal", !edgeset_equals(edgeset, edgeset2));
    return NULL;
}

char *utest_edgeset_is_super()
{
    EdgeSet edgeset, edgeset2;
    edgeset = edgeset_init(5);
    edgeset2 = edgeset_init(5);
    edgeset_push(edgeset, edge_p_make_label(0, 2));
    edgeset_push(edgeset, edge_p_make_label(2, 1));
    edgeset_push(edgeset, edge_p_make_label(1, 2));
    edgeset_push(edgeset, edge_p_make_label(3, 4));
    edgeset_push(edgeset2, edge_p_make_label(0, 2));
    edgeset_push(edgeset2, edge_p_make_label(2, 1));
    edgeset_push(edgeset2, edge_p_make_label(1, 2));
    edgeset_push(edgeset2, edge_p_make_label(3, 4));
    mu_assert("1: should be super", edgeset_is_super(edgeset, edgeset2));
    edgeset_push(edgeset2, edge_p_make_label(5, 6));
    mu_assert("2: should be super", edgeset_is_super(edgeset2, edgeset));
    mu_assert("should not be super", !edgeset_is_super(edgeset, edgeset2));
    mu_assert("3: should be super", edgeset_is_super(edgeset_empty(), edgeset_empty()));
    mu_assert("4: should be super", edgeset_is_super(edgeset, edgeset_empty()));
    return NULL;
}

char *utest_edgeset_is_sub()
{
    EdgeSet edgeset, edgeset2;
    edgeset = edgeset_init(5);
    edgeset2 = edgeset_init(5);
    edgeset_push(edgeset, edge_p_make_label(0, 2));
    edgeset_push(edgeset, edge_p_make_label(2, 1));
    edgeset_push(edgeset, edge_p_make_label(1, 2));
    edgeset_push(edgeset, edge_p_make_label(3, 4));
    edgeset_push(edgeset2, edge_p_make_label(0, 2));
    edgeset_push(edgeset2, edge_p_make_label(2, 1));
    edgeset_push(edgeset2, edge_p_make_label(1, 2));
    edgeset_push(edgeset2, edge_p_make_label(3, 4));
    mu_assert("1: should be sub", edgeset_is_sub(edgeset, edgeset2));
    edgeset_push(edgeset2, edge_p_make_label(5, 6));
    mu_assert("2: should be sub", edgeset_is_sub(edgeset, edgeset2));
    mu_assert("should not be super", !edgeset_is_sub(edgeset2, edgeset));
    mu_assert("3: should be sub", edgeset_is_sub(edgeset_empty(), edgeset_empty()));
    mu_assert("4: should be sub", !edgeset_is_sub(edgeset, edgeset_empty()));
    mu_assert("5: should be sub", edgeset_is_sub(edgeset_empty(), edgeset));
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
    mu_assert("3 should have this edge", !edgeset_contains_edge(edgeset, edge_p_make_label(0, 5)));
    mu_assert("3 should have this edge", edgeset_contains_edge(edgeset, edge_p_make_label(0, 3)));
    edgeset_destroy(edgeset);
    return NULL;
}

char *utest_edgeset_contains_vertex()
{
    EdgeSet edgeset;
    edgeset = edgeset_init(4);
    edgeset_push(edgeset, edge_p_make_label(0, 2));
    edgeset_push(edgeset, edge_p_make_label(2, 1));
    edgeset_push(edgeset, edge_p_make_label(1, 2));
    edgeset_push(edgeset, edge_p_make_label(3, 4));
    mu_assert("should contain", edgeset_contains_vertex(edgeset, vertex_p_make(0)));
    mu_assert("should contain", edgeset_contains_vertex(edgeset, vertex_p_make(1)));
    mu_assert("should contain", edgeset_contains_vertex(edgeset, vertex_p_make(2)));
    mu_assert("should contain", edgeset_contains_vertex(edgeset, vertex_p_make(3)));
    mu_assert("should contain", edgeset_contains_vertex(edgeset, vertex_p_make(4)));
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

char *utest_is_matching() 
{
    EdgeSet edgeset = edgeset_init(4);
    edgeset_push(edgeset, edge_p_make_label(0, 1));
    edgeset_push(edgeset, edge_p_make_label(2, 3));
    mu_assert("1: should be a matching", is_matching(edgeset) == true); 

    edgeset_push(edgeset, edge_p_make_label(0, 1));
    edgeset_push(edgeset, edge_p_make_label(1, 3));
    mu_assert("2: should not be a matching", !is_matching(edgeset)); 

    edgeset_push(edgeset, edge_p_make_label(0, 1));
    edgeset_push(edgeset, edge_p_make_label(2, 0));
    mu_assert("should not be a matching", !is_matching(edgeset)); 

    edgeset_push(edgeset, edge_p_make_label(0, 1));
    edgeset_push(edgeset, edge_p_make_label(0, 1));
    mu_assert("should not be a matching", !is_matching(edgeset)); 

    edgeset_destroy(edgeset);
    return NULL;
}

char *test_edgeset() {
    mu_message(UNIT, "edgeset_empty\n");
    mu_run_utest(utest_edgeset_empty);
    mu_message(UNIT, "edgeset_is_empty\n");
    mu_run_utest(utest_edgeset_is_empty);
    mu_message(UNIT, "edgeset_equals\n");
    mu_run_utest(utest_edgeset_equals);
    mu_message(UNIT, "edgeset_vertex_count\n");
    mu_run_utest(utest_edgeset_vertex_count);
    mu_message(UNIT, "edgeset_vertices\n");
    mu_run_utest(utest_edgeset_vertices);
    mu_message(UNIT, "edgeset_set\n");
    mu_run_utest(utest_edgeset_set);
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
    mu_message(UNIT, "is_super\n");
    mu_run_utest(utest_edgeset_is_super);
    mu_message(UNIT, "is_sub\n");
    mu_run_utest(utest_edgeset_is_sub);
    mu_message(UNIT, "contains_vertex\n");
    mu_run_utest(utest_edgeset_contains_vertex);
    mu_message(UNIT, "is_matching\n");
    mu_run_utest(utest_is_matching);
    return NULL;
}
