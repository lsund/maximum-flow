

#include <stdlib.h>
#include "test.h"

char * utest_edge_init()
{
    Edge e = edge_init();
    mu_assert("should be null", e.first == NULL);
    mu_assert("should be null", e.second == NULL);
    return NULL;
}

char *utest_edge_make()
{
    Edge e = edge_make_vertices(vertex_p_make(8), vertex_p_make(7));
    mu_assert("should be null", e.first->label == 8);
    mu_assert("should be null", e.second->label == 7);
    return NULL;
}

char *utest_edge_make_label()
{
    Edge e = edge_make_label(8, 7);
    mu_assert("should be null", e.first->label == 8);
    mu_assert("should be null", e.second->label == 7);
    return NULL;
}

char *utest_edge_p_make_vertices()
{
    EdgePointer e = edge_p_make_vertices(vertex_p_make(8), vertex_p_make(7));
    mu_assert("should be null", e->first->label == 8);
    mu_assert("should be null", e->second->label == 7);
    return NULL;
}

char *utest_edge_p_make_edge()
{
    Edge e = edge_make_label(8, 7);
    EdgePointer edge = edge_p_make_edge(e);
    mu_assert("should be null", edge->first->label == 8);
    mu_assert("should be null", edge->second->label == 7);
    return NULL;
}

char *utest_edge_p_make_label()
{
    EdgePointer e = edge_p_make_label(8, 7);
    mu_assert("should be null", e->first->label == 8);
    mu_assert("should be null", e->second->label == 7);
    return NULL;
}

char *utest_edge_swapped()
{
    Edge e = edge_make_label(8, 7);
    mu_assert("should be 7", edge_swapped(e).first->label == 7);
    mu_assert("should be 8", edge_swapped(e).second->label == 8);
    return NULL;
}

char *utest_edge_get_adjacent()
{
    EdgePointer e = edge_p_make_label(8, 7);
    Vertex x = vertex_make(8);
    Vertex y = vertex_make(7);
    Vertex z = vertex_make(6);
    VertexPointer ret = edge_get_adjacent(e, &x);
    mu_assert("should be 7", ret->label == 7);
    ret = edge_get_adjacent(e, &y);
    mu_assert("should be 8", ret->label == 8);
    mu_assert("should fail", edge_get_adjacent(e, &z) == NULL);
    return NULL;
}

char *utest_edge_swap()
{
    EdgePointer e = edge_p_make_label(8, 7);
    edge_swap(e);
    mu_assert("should be 7", e->first->label == 7);
    mu_assert("should be 8", e->second->label == 8);
    return NULL;
}

char *utest_edge_equals()
{
    EdgePointer e = edge_p_make_label(8, 7);
    EdgePointer e2 = edge_p_make_label(8, 7);
    mu_assert("should equal", edge_equals(e, e2));;
    edge_swap(e);
    mu_assert("should not equal", !edge_equals(e, e2));;
    e->first = NULL;
    mu_assert("should not equal", !edge_equals(e, e2));;
    return NULL;
}

char *utest_edge_incident_with()
{
    VertexPointer x = vertex_p_make(8);
    VertexPointer y = vertex_p_make(7);
    VertexPointer z = vertex_p_make(6);
    EdgePointer e = edge_p_make_label(8, 7);
    mu_assert("should be", edge_incident_with(e, x));
    mu_assert("should be", edge_incident_with(e, y));
    mu_assert("should not be", !edge_incident_with(e, z));
    return NULL;
}

char *test_edge() {
    mu_message(UNIT, "edge_init\n");
    mu_run_utest(utest_edge_init);
    mu_message(UNIT, "edge_make_vertices\n");
    mu_run_utest(utest_edge_make);
    mu_message(UNIT, "make_labe\n");
    mu_run_utest(utest_edge_make_label);
    mu_message(UNIT, "p_make_vertices\n");
    mu_run_utest(utest_edge_p_make_vertices);
    mu_message(UNIT, "p_edge_make\n");
    mu_run_utest(utest_edge_p_make_edge);
    mu_message(UNIT, "p_make_label\n");
    mu_run_utest(utest_edge_p_make_label);
    mu_message(UNIT, "edge_swapped\n");
    mu_run_utest(utest_edge_swapped);
    mu_message(UNIT, "edge_get_adjacent\n");
    mu_run_utest(utest_edge_get_adjacent);
    mu_message(UNIT, "edge_swap\n");
    mu_run_utest(utest_edge_swap);
    mu_message(UNIT, "edge_equals\n");
    mu_run_utest(utest_edge_equals);
    mu_message(UNIT, "edge_incident_with\n");
    mu_run_utest(utest_edge_incident_with);
    return NULL;
}
