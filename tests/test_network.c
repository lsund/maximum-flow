#include "test.h"

char *utest_network_active_vertex()
{
    return NULL;
}

char *utest_networkedge_is_reverse()
{
    EdgePointer edge = edge_p_make_label(1, 2);
    EdgePointer edger = edge_p_make_label(2, 1);
    EdgePointer edge2 = edge_p_make_label(1, 3);
    EdgePointer edge2r = edge_p_make_label(3, 1);
    mu_assert("should be the reversed version", edge_equals_reverse(edge, edger));
    mu_assert("should be the reversed version", edge_equals_reverse(edge2, edge2r));
    NetworkPointer network = network_init();
    parse(TEST_GRAPH, network);
    mu_assert("should have 7 edge", edgecollection_length(network->graph.edges) == 7);
    mu_assert("should contain", edgecollection_contains_edge(network->graph.edges, edge2)); 
    networkvertex_set_distance_label(network, vertex_p_make(1), 1);
    networkvertex_set_distance_label(network, vertex_p_make(2), 0);
    mu_assert("should be reverse", networkedge_is_reverse(network, edger));
    mu_assert("should be reverse", networkedge_is_reverse(network, edge2r));
    mu_assert("edge should not be reverse", !networkedge_is_reverse(network, edge));
    mu_assert("edge2 should not be reverse", !networkedge_is_reverse(network, edge2));
    return NULL;
}

char *utest_networkedge_is_admissable()
{
    NetworkPointer network = network_init();
    parse(TEST_GRAPH, network);
    EdgePointer edge = edge_p_make_label(1, 2);
    EdgePointer edge2 = edge_p_make_label(1, 3);
    EdgePointer edge3 = edge_p_make_label(2, 4);
    networkedge_set_flow(network, edge, 10);
    networkedge_set_flow(network, edge2, 10);
    networkvertex_set_distance_label(network, vertex_p_make(2), 4);
    networkvertex_set_distance_label(network, vertex_p_make(4), 3);
    mu_assert("should not be admissable", !networkedge_is_admissable(network, edge));
    mu_assert("should not be admissable", !networkedge_is_admissable(network, edge2));
    mu_assert("should be admissable", networkedge_is_admissable(network, edge3));
    return NULL;
}

char *utest_networkvertex_is_active()
{
    NetworkPointer network = network_init();
    parse(TEST_GRAPH, network);
    networkedge_set_flow(network, edge_p_make_label(1, 2), 8);
    mu_assert("should be active", networkvertex_is_active(network, vertex_p_make(2)));
    mu_assert("should be 0", networkvertex_is_active(network, vertex_p_make(4)) == false);
    mu_assert("source should not be active", !networkvertex_is_active(network, network->source));
    mu_assert("source should not be active", !networkvertex_is_active(network, network->sink));
    return NULL;
}

char *utest_networkvertex_exflow()
{
    NetworkPointer network = network_init();
    parse(TEST_GRAPH, network);
    networkedge_set_flow(network, edge_p_make_label(1, 2), 10);
    networkedge_set_flow(network, edge_p_make_label(1, 3), 10);
    networkedge_set_flow(network, edge_p_make_label(2, 4), 0);
    networkedge_set_flow(network, edge_p_make_label(2, 4), 0);
    mu_assert("should be 10", networkvertex_exflow(network, vertex_p_make(2)) == 10);
    mu_assert("should be 0", networkvertex_exflow(network, vertex_p_make(6)) == 0);
    return NULL; 
}


char *utest_networkvertex_set_distance_label()
{
    NetworkPointer network = network_init();
    VertexCollection vertices = vertexcollection_init(8);
    EdgeCollection edges = edgecollection_init(8);
    vertexcollection_push(vertices, vertex_p_make(0));
    network->graph = graph_make(vertices, edges);
    network->distance_labels = calloc(8, sizeof(Label));
    mu_assert("should be 0", *network->distance_labels == 0);
    networkvertex_set_distance_label(network, vertexcollection_get(network->graph.vertices, 0), 77);
    mu_assert("should be 77", *network->distance_labels == 77);
    return NULL;
}

char *utest_networkvertex_distance_label()
{
    NetworkPointer network = network_init();
    VertexCollection vertices = vertexcollection_init(8);
    EdgeCollection edges = edgecollection_init(8);
    vertexcollection_push(vertices, vertex_p_make(0));
    network->graph = graph_make(vertices, edges);
    network->distance_labels = calloc(8, sizeof(Label));
    networkvertex_set_distance_label(network, vertexcollection_get(network->graph.vertices, 0), 77);
    mu_assert("should be 77", networkvertex_distance_label(network, vertexcollection_get(network->graph.vertices, 0)) == 77);
    return NULL;
}

char *utest_networkedge_set_flow()
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
    networkedge_set_flow(network, edge, 10);
    mu_assert("should be 10", networkedge_flow(network, edge) == 10);
    return NULL;
    return NULL;
}

char *utest_networkedge_set_capacity()
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
    networkedge_set_capacity(network, edge, 10);
    mu_assert("should be 10", networkedge_capacity(network, edge) == 10);
    return NULL;
}

char *test_network()
{
    mu_message(UNIT, "network_set_distance_label\n");
    mu_run_utest(utest_networkvertex_set_distance_label);
    mu_message(UNIT, "networkvertex_distance_labe\n");
    mu_run_utest(utest_networkvertex_distance_label);
    mu_message(UNIT, "networkedge_set_capacity\n");
    mu_run_utest(utest_networkedge_set_capacity);
    mu_message(UNIT, "networkedge_is_reverse\n");
    mu_run_utest(utest_networkedge_is_reverse);
    mu_message(UNIT, "networkedge_set_flow\n");
    mu_run_utest(utest_networkedge_set_flow);
    mu_message(UNIT, "networkvertex_is_active\n");
    mu_run_utest(utest_networkvertex_is_active);
    mu_message(UNIT, "networkvertex_exflow\n");
    mu_run_utest(utest_networkvertex_exflow);
    mu_message(UNIT, "networkedge_is_admissable\n");
    mu_run_utest(utest_networkedge_is_admissable);
    return NULL;
}

