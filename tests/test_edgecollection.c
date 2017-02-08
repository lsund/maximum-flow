
#include <stdlib.h>
#include "test.h"
#include "collection.h"

bool edgecollection_contains_vertex(
        const EdgeCollection edges,
        const VertexPointer vertex
    )
{
    VertexCollection vertices = edgecollection_vertices(edges);
    bool contains = vertexcollection_contains_label(vertices, vertex->label);
    vertexcollection_destroy(vertices);
    return contains;
}


char *utest_edgecollection_remove()
{
    EdgePointer a = edge_p_make_label(0, 1);
    EdgePointer b = edge_p_make_label(1, 2);
    EdgePointer c = edge_p_make_label(2, 3);
    EdgeCollection edgecollection = edgecollection_init_min();
    edgecollection_push(edgecollection, a);
    edgecollection_push(edgecollection, b);
    edgecollection_push(edgecollection, c);
    edgecollection_remove(&edgecollection, b);

    mu_assert("should have a", edgecollection_contains_edge(edgecollection, a));
    mu_assert("should not have b", !edgecollection_contains_edge(edgecollection, b));
    mu_assert("should have c", edgecollection_contains_edge(edgecollection, c));
    edgecollection_remove(&edgecollection, c);
    mu_assert("should not have c", !edgecollection_contains_edge(edgecollection, c));
    mu_assert("should have a", edgecollection_contains_edge(edgecollection, a));
    edgecollection_remove(&edgecollection, a);
    mu_assert("should not have a", !edgecollection_contains_edge(edgecollection, a));
    edgecollection_push(edgecollection, a);
    edgecollection_push(edgecollection, b);
    edgecollection_push(edgecollection, c);
    mu_assert("should have a", edgecollection_contains_edge(edgecollection, a));
    mu_assert("should have b", edgecollection_contains_edge(edgecollection, b));
    mu_assert("should have c", edgecollection_contains_edge(edgecollection, c));
    edgecollection_remove(&edgecollection, a);
    mu_assert("should not have a", !edgecollection_contains_edge(edgecollection, a));
    mu_assert("should have b", edgecollection_contains_edge(edgecollection, b));
    mu_assert("should have c", edgecollection_contains_edge(edgecollection, c));

    return NULL;
}

char *utest_edgecollection_init()
{
    EdgeCollection edgecollection = edgecollection_init(3);
    mu_assert("should have length 9", edgecollection.members->capacity == 3);
    mu_assert("should not contain any vertex", !edgecollection_contains_vertex(edgecollection, vertex_p_make(0)));
    mu_assert("should not contain any vertex", !edgecollection_contains_vertex(edgecollection, vertex_p_make(1)));
    return NULL;
}

char *utest_edgecollection_get()
{
    EdgeCollection edgecollection;
    edgecollection = edgecollection_init(4);
    mu_assert("should succeed", edgecollection_push(edgecollection, edge_p_make_label(0, 1)) == SUCCESS);
    EdgePointer edge = edgecollection_get(edgecollection, 0);
    mu_assert("should be 0", edge->first.label == 0);
    mu_assert("should be 1", edge->second.label == 1);
    edge = edgecollection_get(edgecollection, 1);
    mu_assert("should be null", !edge);
    edgecollection_destroy(edgecollection);
    return NULL;
}

char *utest_edgecollection_vertices()
{
    EdgeCollection edgecollection;
    edgecollection = edgecollection_init(4);
    edgecollection_push(edgecollection, edge_p_make_label(0, 2));
    edgecollection_push(edgecollection, edge_p_make_label(2, 1));
    edgecollection_push(edgecollection, edge_p_make_label(1, 2));
    edgecollection_push(edgecollection, edge_p_make_label(3, 4));
    VertexCollection vertexcollection = edgecollection_vertices(edgecollection);
    mu_assert("should be", vertexcollection_get(vertexcollection, 0)->label == 0);
    mu_assert("should be", vertexcollection_get(vertexcollection, 1)->label == 2);
    mu_assert("should be", vertexcollection_get(vertexcollection, 2)->label == 1);
    mu_assert("should be", vertexcollection_get(vertexcollection, 3)->label == 3);
    mu_assert("should be", vertexcollection_get(vertexcollection, 4)->label == 4);
    return NULL;
}

char *utest_edgecollection_push()
{
    EdgeCollection edgecollection;
    edgecollection = edgecollection_init(4);
    EdgePointer a = edge_p_make_label(2, 3);
    EdgePointer b = edge_p_make_label(2, 4);
    mu_assert("should not contain vertex 2", !edgecollection_contains_vertex(edgecollection, vertex_p_make(2)));
    mu_assert("1 should succeed", edgecollection_push(edgecollection, a) == SUCCESS);
    mu_assert("should get 0 as index", edgecollection_index_of(edgecollection, *a) == 0);
    mu_assert("should be 2", edgecollection_get(edgecollection, 0)->first.label == 2);
    mu_assert("should contain vertex 2", edgecollection_contains_vertex(edgecollection, vertex_p_make(2)));
    mu_assert("should contain vertex 3", edgecollection_contains_vertex(edgecollection, vertex_p_make(3)));
    VertexCollection vertices = edgecollection_vertices(edgecollection);
    mu_assert("vertexcollection should also contain 2", vertexcollection_contains_label(vertices, 2));
    mu_assert("vertexcollection should also contain 3", vertexcollection_contains_label(vertices, 3));
    mu_assert("capacity still 4", edgecollection.members->capacity == 4);
    mu_assert("length 1", edgecollection.members->length == 1);
    mu_assert("1 should succeed", edgecollection_push(edgecollection, b) == SUCCESS);
    mu_assert("b should get 1 as index", edgecollection_index_of(edgecollection, *b) == 1);
    return NULL;
}

char *utest_edgecollection_contains_edge()
{
    EdgeCollection edgecollection = edgecollection_init(3);
    EdgePointer a = edge_p_make_label(0, 1);
    EdgePointer b = edge_p_make_label(0, 2);
    EdgePointer c = edge_p_make_label(1, 2);
    EdgePointer d = edge_p_make_label(0, 3);
    edgecollection_push(edgecollection, a);
    edgecollection_push(edgecollection, b);
    edgecollection_push(edgecollection, c);
    mu_assert("1 should have this edge", edgecollection_contains_edge(edgecollection, a));
    mu_assert("2 should have this edge", edgecollection_contains_edge(edgecollection, b));
    mu_assert("3 should have this edge", edgecollection_contains_edge(edgecollection, c));
    mu_assert("4 should not be able to add this edge", edgecollection_push(edgecollection, d) == SUCCESS);
    mu_assert("3 should have this edge", !edgecollection_contains_edge(edgecollection, edge_p_make_label(0, 5)));
    mu_assert("3 should have this edge", edgecollection_contains_edge(edgecollection, edge_p_make_label(0, 3)));
    edgecollection_destroy(edgecollection);
    return NULL;
}

char *utest_edgecollection_contains_vertex()
{
    EdgeCollection edgecollection;
    edgecollection = edgecollection_init(4);
    edgecollection_push(edgecollection, edge_p_make_label(0, 2));
    edgecollection_push(edgecollection, edge_p_make_label(2, 1));
    edgecollection_push(edgecollection, edge_p_make_label(1, 2));
    edgecollection_push(edgecollection, edge_p_make_label(3, 4));
    mu_assert("should contain", edgecollection_contains_vertex(edgecollection, vertex_p_make(0)));
    mu_assert("should contain", edgecollection_contains_vertex(edgecollection, vertex_p_make(1)));
    mu_assert("should contain", edgecollection_contains_vertex(edgecollection, vertex_p_make(2)));
    mu_assert("should contain", edgecollection_contains_vertex(edgecollection, vertex_p_make(3)));
    mu_assert("should contain", edgecollection_contains_vertex(edgecollection, vertex_p_make(4)));
    return NULL;
}

char *test_edgecollection() {
    mu_message(UNIT, "edgecollection_vertices\n");
    mu_run_utest(utest_edgecollection_vertices);
    mu_message(UNIT, "edgecollection_push\n");
    mu_run_utest(utest_edgecollection_push);
    mu_message(UNIT, "edgecollection_init\n");
    mu_run_utest(utest_edgecollection_init);
    mu_message(UNIT, "edgecollection_get\n");
    mu_run_utest(utest_edgecollection_get);
    mu_message(UNIT, "edgecollection_contains_edge\n");
    mu_run_utest(utest_edgecollection_contains_edge);
    mu_message(UNIT, "contains_vertex\n");
    mu_run_utest(utest_edgecollection_contains_vertex);
    mu_message(UNIT, "edgecollection_remove\n");
    mu_run_utest(utest_edgecollection_remove);
    return NULL;
}
