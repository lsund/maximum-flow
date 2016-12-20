
#include <stdlib.h>
#include "test.h"

char *utest_graph_incident_with()
{
    /* VertexCollection vertices = vertexcollection_init(6); */
    /* EdgeCollection edges = edgecollection_init(7); */
    /* vertexcollection_push(vertices, vertex_p_make(0)); */
    /* vertexcollection_push(vertices, vertex_p_make(1)); */
    /* vertexcollection_push(vertices, vertex_p_make(2)); */
    /* vertexcollection_push(vertices, vertex_p_make(3)); */
    /* vertexcollection_push(vertices, vertex_p_make(4)); */
    /* vertexcollection_push(vertices, vertex_p_make(5)); */
    /* edgecollection_push(edges, edge_p_make_label(0, 1)); */
    /* edgecollection_push(edges, edge_p_make_label(0, 2)); */
    /* edgecollection_push(edges, edge_p_make_label(1, 3)); */
    /* edgecollection_push(edges, edge_p_make_label(1, 4)); */
    /* edgecollection_push(edges, edge_p_make_label(2, 4)); */
    /* edgecollection_push(edges, edge_p_make_label(3, 5)); */
    /* edgecollection_push(edges, edge_p_make_label(4, 5)); */
    /* GraphPointer graph = graph_make(vertices, edges); */
    /* EdgeCollection incident = graph_incident_with(graph, vertex_p_make(0)); */
    /* mu_assert("should be of length 7", edgecollection_length(graph.edges) == 7); */ 
    /* mu_assert("should be of length 2", edgecollection_length(incident) == 2); */ 
    /* mu_assert("should contain", edgecollection_contains_edge(incident, edge_p_make_label(0, 1))); */
    /* mu_assert("should contain", edgecollection_contains_edge(incident, edge_p_make_label(0, 2))); */
    /* mu_assert("should contain", !edgecollection_contains_edge(incident, edge_p_make_label(1, 2))); */
    /* incident = graph_incident_with(graph, vertex_p_make(2)); */
    /* mu_assert("should be of length 2", edgecollection_length(incident) == 2); */ 
    return NULL;
}

char *utest_graph_make() 
{
    VertexCollection vertexcollection = vertexcollection_init(2);
    EdgeCollection edgecollection = edgecollection_init(1);
    vertexcollection_push(vertexcollection, vertex_p_make(0));
    vertexcollection_push(vertexcollection, vertex_p_make(1));
    edgecollection_push(edgecollection, edge_p_make_label(0, 1));
    Graph graph = graph_make(vertexcollection, edgecollection);
    mu_assert("should not be null", vertexcollection_get(graph.vertices, 0));
    mu_assert("should not be null", edgecollection_get(graph.edges, 0));
    mu_assert("should be 1", edgecollection_get(graph.edges, 0)->first.label == 0);
    return NULL;
}

char *test_graph() {
    mu_message(UNIT, "graph_incident_with\n");
    mu_run_utest(utest_graph_incident_with);
    mu_message(UNIT, "graph_make\n");
    mu_run_utest(utest_graph_make);
    return NULL;
}

