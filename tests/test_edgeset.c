
#include <stdlib.h>
#include "test.h"

char *utest_init_edgeset()
{
    EdgeSet edgeset = init_edgeset(110);
    mu_assert("Too large input should give null", edgeset.set == NULL);
    edgeset = init_edgeset(3);
    mu_assert("should have length 9", edgeset.set->length == 9);
    mu_assert("vertexset should be initialized ", edgeset.vertices.set);
    mu_assert("vertexset should be initialized ", edgeset.vertices.set->head);
    mu_assert("vertexset should be initialized with a length", edgeset.vertices.set->length == 4);
    mu_assert("vertexset should not be unit ", vertexset_is_empty(edgeset.vertices));
    mu_assert("should not contain any vertex", !edgeset_contains_vertex(edgeset, make_vertex(0)));
    mu_assert("should not contain any vertex", !edgeset_contains_vertex(edgeset, make_vertex(1)));
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

char *utest_get_edge_at_position()
{
    EdgeSet edgeset;
    edgeset = init_edgeset(4);
    mu_assert("should fail", add_edge(edgeset, make_edge(make_vertex(77),make_vertex(77))) == FAIL);
    mu_assert("should succeed", add_edge(edgeset, make_edge(make_vertex(0),make_vertex(1))) == SUCCESS);
    destroy_edgeset(edgeset);
    return NULL;
}

char *utest_edgeset_complement()
{
    EdgeSet edgeset_a = init_edgeset(4);
    EdgeSet edgeset_b = init_edgeset(4);
    add_edge(edgeset_a, make_edge(make_vertex(0), make_vertex(1)));
    add_edge(edgeset_a, make_edge(make_vertex(1), make_vertex(2)));
    add_edge(edgeset_a, make_edge(make_vertex(2), make_vertex(3)));
    add_edge(edgeset_b, make_edge(make_vertex(1), make_vertex(2)));
    EdgeSet edgeset_c, edgeset_d;
    edgeset_c = init_edgeset(4);
    edgeset_d = init_edgeset(4);
    edgeset_complement(edgeset_a, edgeset_b, &edgeset_c);
    edgeset_complement(edgeset_b, edgeset_a, &edgeset_d);
    mu_assert("should have length 16", edgeset_c.set->length == 16);
    mu_assert("should have 2 elements", edgeset_c.set->nelements == 2);
    mu_assert("and should be these edges", get_edge_at_position(edgeset_c, 0)->first.label == 0);
    mu_assert("and should be these edges", get_edge_at_position(edgeset_c, 0)->second.label == 1);
    mu_assert("and should be these edges", get_edge_at_position(edgeset_c, 1)->first.label == 2);
    mu_assert("and should be these edges", get_edge_at_position(edgeset_c, 1)->second.label == 3);
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
    return NULL;
}

char *utest_symmetric_difference()
{
    EdgeSet graph = init_edgeset(8);
    EdgeSet matching = init_edgeset(8);
    EdgeSet path = init_edgeset(8);
    add_edge(graph, make_edge(make_vertex(0), make_vertex(1)));
    add_edge(graph, make_edge(make_vertex(1), make_vertex(2)));
    add_edge(graph, make_edge(make_vertex(2), make_vertex(3)));
    add_edge(graph, make_edge(make_vertex(3), make_vertex(4)));
    add_edge(graph, make_edge(make_vertex(2), make_vertex(5)));
    add_edge(graph, make_edge(make_vertex(2), make_vertex(6)));
    add_edge(graph, make_edge(make_vertex(6), make_vertex(7)));
    add_edge(matching, make_edge(make_vertex(0), make_vertex(1)));
    add_edge(matching, make_edge(make_vertex(2), make_vertex(6)));
    add_edge(matching, make_edge(make_vertex(3), make_vertex(4)));
    add_edge(path, make_edge(make_vertex(2), make_vertex(5)));
    add_edge(path, make_edge(make_vertex(2), make_vertex(6)));
    add_edge(path, make_edge(make_vertex(6), make_vertex(7)));
    EdgeSet augment = init_edgeset(8);
    symmetric_difference(matching, path, &augment);
    mu_assert("should be of one larger size", augment.set->nelements == matching.set->nelements + 1);
    mu_assert("should contain this edge",
            edgeset_contains_edge(augment, make_edge(make_vertex(6), make_vertex(7))));
    mu_assert("should contain this edge", 
            edgeset_contains_edge(augment, make_edge(make_vertex(2), make_vertex(5))));
    mu_assert("should contain this edge", 
            edgeset_contains_edge(augment, make_edge(make_vertex(3), make_vertex(4))));
    mu_assert("should contain this edge", 
            edgeset_contains_edge(augment, make_edge(make_vertex(0), make_vertex(1))));
    return NULL;
}


char *utest_edgeset_union()
{
    EdgeSet edgeset_a = init_edgeset(4);
    EdgeSet edgeset_b = init_edgeset(4);
    add_edge(edgeset_a, make_edge(make_vertex(0), make_vertex(1)));
    add_edge(edgeset_a, make_edge(make_vertex(1), make_vertex(2)));
    add_edge(edgeset_a, make_edge(make_vertex(2), make_vertex(3)));
    add_edge(edgeset_b, make_edge(make_vertex(1), make_vertex(2)));
    EdgeSet edgeset_c = init_edgeset(4);
    edgeset_union(edgeset_a, edgeset_b, &edgeset_c);
    mu_assert("should have length 16", edgeset_c.set->length == 16);
    mu_assert("should have 2 elements", edgeset_c.set->nelements == 3);
    mu_assert("and should be these edges", get_edge_at_position(edgeset_c, 0)->first.label == 0);
    mu_assert("and should be these edges", get_edge_at_position(edgeset_c, 0)->second.label == 1);
    mu_assert("and should be these edges", get_edge_at_position(edgeset_c, 1)->first.label == 1);
    mu_assert("and should be these edges", get_edge_at_position(edgeset_c, 1)->second.label == 2);
    mu_assert("and should be these edges", get_edge_at_position(edgeset_c, 2)->first.label == 2);
    mu_assert("and should be these edges", get_edge_at_position(edgeset_c, 2)->second.label == 3);
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

char *utest_add_edge()
{
    EdgeSet edgeset;
    edgeset = init_edgeset(4);
    mu_assert("should fail", add_edge(edgeset, make_edge(make_vertex(2), make_vertex(2))) == FAIL);
    mu_assert("should not contain vertex 2", !edgeset_contains_vertex(edgeset, make_vertex(2)));
    mu_assert("1 should succeed", add_edge(edgeset, make_edge(make_vertex(2), make_vertex(3))) == SUCCESS);
    mu_assert("should fail", add_edge(edgeset, make_edge(make_vertex(77),make_vertex(77))) == FAIL);
    mu_assert("should be 2", get_edge_at_position(edgeset, 0)->first.label == 2);
    mu_assert("should contain vertex 2", edgeset_contains_vertex(edgeset, make_vertex(2)));
    mu_assert("should contain vertex 3", edgeset_contains_vertex(edgeset, make_vertex(3)));
    mu_assert("vertexset should also contain 2", vertexset_contains_vertex(edgeset.vertices, make_vertex(2)));
    mu_assert("vertexset should also contain 3", vertexset_contains_vertex(edgeset.vertices, make_vertex(3)));
    /* mu_assert("should not be able to add the same edge 'swapped'", */ 
    /*         add_edge(edgeset, make_edge(make_vertex(3), make_vertex(2))) == FAIL); */
    destroy_edgeset(edgeset);
    return NULL;
}

char *utest_edgeset_contains_edge()
{
    EdgeSet edgeset = init_edgeset(3);
    Edge a = make_edge(make_vertex(0), make_vertex(1));
    Edge b = make_edge(make_vertex(0), make_vertex(2));
    Edge c = make_edge(make_vertex(1), make_vertex(2));
    Edge d = make_edge(make_vertex(0), make_vertex(3));
    add_edge(edgeset, a);
    add_edge(edgeset, b);
    add_edge(edgeset, c);
    mu_assert("should have this edge", edgeset_contains_edge(edgeset, a));
    mu_assert("should have this edge", edgeset_contains_edge(edgeset, b));
    mu_assert("should have this edge", edgeset_contains_edge(edgeset, c));
    mu_assert("should not be able to add this edge", add_edge(edgeset, d) == FAIL);
    destroy_edgeset(edgeset);
    edgeset = init_edgeset(16);
    TokenTablePointer table = init_tokentable();
    make_tokentable("data/instances/queen4_4.dmx", table);
    VertexSet vertexset = init_vertexset(16);
    parse_vertices(vertexset);
    parse_edges(table, edgeset, NULL, vertexset);
    mu_assert("should have this edge", edgeset_contains_edge(edgeset, make_edge(make_vertex(13), make_vertex(7))));
    mu_assert("should have this edge", edgeset_contains_edge(edgeset, make_edge(make_vertex(14), make_vertex(8))));
    mu_assert("should have this edge", 
            edgeset_contains_edge(edgeset, make_edge(make_vertex(10), make_vertex(15))));
    mu_assert("should have this edge", 
            edgeset_contains_edge(edgeset, make_edge(make_vertex(10), make_vertex(11))));
    destroy_edgeset(edgeset);
    return NULL;
}

char *utest_edgepath_from_vertexset()
{
    VertexSet vertexset = init_vertexset(8);
    mu_assert("should work", add_vertex(vertexset, make_vertex(8)));
    mu_assert("should work", add_vertex(vertexset, make_vertex(5)));
    mu_assert("should work", add_vertex(vertexset, make_vertex(2)));
    mu_assert("should work", add_vertex(vertexset, make_vertex(0)));
    mu_assert("vertexset should now have 4 elements", vertexset.set->nelements == 4);
    Edge edges[] = { 
        make_edge(make_vertex(8), make_vertex(5)), 
        make_edge(make_vertex(5), make_vertex(2)), 
        make_edge(make_vertex(2), make_vertex(0))
    };
    Edge edges2[] = { };
    EdgeSet p = init_edgeset(9);
    edgepath_from_vertexset(vertexset, &p);
    mu_assert("should be true", edgeset_contains_edges(p, edges, 3));
    destroy_edgeset(p);
    p = init_edgeset(8);
    mu_assert("should be true", edgeset_contains_edges(p, edges2, 0));
    destroy_vertexset(vertexset);
    destroy_edgeset(p);
    p = init_edgeset(8);
    edgepath_from_vertexset(init_vertexset(0), &p);
    mu_assert("should be empty", edgeset_is_empty(p));
    destroy_edgeset(p);
    vertexset = init_vertexset(2);
    add_vertex(vertexset, make_vertex(0));
    p = init_edgeset(8);
    edgepath_from_vertexset(vertexset, &p);
    mu_assert("should be empty", edgeset_is_empty(p));
    destroy_edgeset(p);
    p = init_edgeset(8);
    add_vertex(vertexset, make_vertex(1));
    edgepath_from_vertexset(vertexset, &p);
    mu_assert("should not be empty anymore", !edgeset_is_empty(p));
    return NULL;
}

char *test_edgeset() {
    mu_message(UNIT, "add_edge\n");
    mu_run_utest(utest_add_edge);
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
    mu_message(UNIT, "get_edge_at_position\n");
    mu_run_utest(utest_get_edge_at_position);
    mu_message(UNIT, "edgeset_contains_edge\n");
    mu_run_utest(utest_edgeset_contains_edge);
    mu_message(UNIT, "edgepath_from_vertexset\n");
    mu_run_utest(utest_edgepath_from_vertexset);
    return NULL;
}
