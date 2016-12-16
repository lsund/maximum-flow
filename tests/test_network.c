#include "test.h"

char *utest_network_vertex_set_distance_label()
{
    NetworkPointer network = network_init();
    VertexCollection vertices = vertexcollection_init(8);
    EdgeCollection edges = edgecollection_init(8);
    vertexcollection_push(vertices, vertex_p_make(0));
    network->graph = graph_make(vertices, edges);
    network->distance_labels = calloc(8, sizeof(Label));
    mu_assert("should be 0", *network->distance_labels == 0);
    network_vertex_set_distance_label(network, vertexcollection_get(network->graph->vertices, 0), 77);
    mu_assert("should be 77", *network->distance_labels == 77);
    return NULL;
}

char *utest_network_vertex_distance_label()
{
    NetworkPointer network = network_init();
    VertexCollection vertices = vertexcollection_init(8);
    EdgeCollection edges = edgecollection_init(8);
    vertexcollection_push(vertices, vertex_p_make(0));
    network->graph = graph_make(vertices, edges);
    network->distance_labels = calloc(8, sizeof(Label));
    network_vertex_set_distance_label(network, vertexcollection_get(network->graph->vertices, 0), 77);
    mu_assert("should be 77", network_vertex_distance_label(network, vertexcollection_get(network->graph->vertices, 0)) == 77);
    return NULL;
}

char *utest_network_set_edge_flow()
{
    NetworkPointer network = network_init();
    VertexCollection vertices = vertexcollection_init(8);
    vertexcollection_push(vertices, vertex_p_make(0));
    vertexcollection_push(vertices, vertex_p_make(1));
    EdgeCollection edges = edgecollection_init(8);
    EdgePointer edge = edge_p_make_label(0, 1);
    edgecollection_push(edges, edge);
    network->graph = graph_make(vertices, edges);
    network->flows = calloc(8, sizeof(unsigned int));
    network_set_edge_flow(network, edge, 10);
    mu_assert("should be 10", network_edge_flow(network, edge) == 10);
    return NULL;
    return NULL;
}

char *utest_network_set_edge_capacity()
{
    NetworkPointer network = network_init();
    VertexCollection vertices = vertexcollection_init(8);
    vertexcollection_push(vertices, vertex_p_make(0));
    vertexcollection_push(vertices, vertex_p_make(1));
    EdgeCollection edges = edgecollection_init(8);
    EdgePointer edge = edge_p_make_label(0, 1);
    edgecollection_push(edges, edge);
    network->graph = graph_make(vertices, edges);
    network->capacities = calloc(8, sizeof(unsigned int));
    network_set_edge_capacity(network, edge, 10);
    mu_assert("should be 10", network_edge_capacity(network, edge) == 10);
    return NULL;
}

char *test_network()
{
    mu_message(UNIT, "network_set_distance_label\n");
    mu_run_utest(utest_network_vertex_set_distance_label);
    mu_message(UNIT, "network_vertex_distance_labe\n");
    mu_run_utest(utest_network_vertex_distance_label);
    mu_message(UNIT, "network_set_edge_capacity\n");
    mu_run_utest(utest_network_set_edge_capacity);
    mu_message(UNIT, "network_set_edge_flow\n");
    mu_run_utest(utest_network_set_edge_flow);
    return NULL;
}

