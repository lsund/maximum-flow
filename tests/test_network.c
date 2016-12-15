
#include "test.h"

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
    mu_message(UNIT, "network_set_edge_capacity\n");
    mu_run_utest(utest_network_set_edge_capacity);
    mu_message(UNIT, "network_set_edge_flow\n");
    mu_run_utest(utest_network_set_edge_flow);
    return NULL;
}

