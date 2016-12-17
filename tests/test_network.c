#include "test.h"

char *utest_network_active_vertex()
{
    return NULL;
}

char *utest_network_edge_is_reverse()
{
    EdgePointer edge = edge_p_make_label(0, 1);
    EdgePointer edger = edge_p_make_label(1, 0);
    EdgePointer edge2 = edge_p_make_label(0, 2);
    EdgePointer edge2r = edge_p_make_label(2, 0);
    mu_assert("should be the reversed version", edge_equals_reverse(edge, edger));
    mu_assert("should be the reversed version", edge_equals_reverse(edge2, edge2r));
    NetworkPointer network = network_init();
    parse(TEST_GRAPH, network);
    mu_assert("should have 7 edge", edgecollection_length(network->graph->edges) == 7);
    mu_assert("should contain", edgecollection_contains_edge(network->graph->edges, edge2)); 
    network_vertex_set_distance_label(network, vertex_p_make(0), 1);
    network_vertex_set_distance_label(network, vertex_p_make(1), 0);
    mu_assert("should be reverse", network_edge_is_reverse(network, edger));
    mu_assert("should be reverse", network_edge_is_reverse(network, edge2r));
    mu_assert("edge should not be reverse", !network_edge_is_reverse(network, edge));
    mu_assert("edge2 should not be reverse", !network_edge_is_reverse(network, edge2));
    return NULL;
}

char *utest_network_edge_is_admissable()
{
    NetworkPointer network = network_init();
    parse(TEST_GRAPH, network);
    EdgePointer edge = edge_p_make_label(0, 1);
    EdgePointer edge2 = edge_p_make_label(0, 2);
    EdgePointer edge3 = edge_p_make_label(1, 3);
    network_set_edge_flow(network, edge, 10);
    network_set_edge_flow(network, edge2, 10);
    network_vertex_set_distance_label(network, vertex_p_make(1), 4);
    network_vertex_set_distance_label(network, vertex_p_make(3), 3);
    mu_assert("should not be admissable", !network_edge_is_admissable(network, edge));
    mu_assert("should not be admissable", !network_edge_is_admissable(network, edge2));
    mu_assert("should be admissable", network_edge_is_admissable(network, edge3));
    return NULL;
}

char *utest_network_vertex_is_active()
{
    NetworkPointer network = network_init();
    parse(TEST_GRAPH, network);
    network_set_edge_flow(network, edge_p_make_label(0, 1), 8);
    mu_assert("should be active", network_vertex_is_active(network, vertex_p_make(1)));
    mu_assert("should be 0", network_vertex_is_active(network, vertex_p_make(4)) == false);
    mu_assert("source should not be active", !network_vertex_is_active(network, network->source));
    mu_assert("source should not be active", !network_vertex_is_active(network, network->sink));
    return NULL;
}

char *utest_network_vertex_exflow()
{
    NetworkPointer network = network_init();
    parse(TEST_GRAPH, network);
    network_set_edge_flow(network, edge_p_make_label(0, 1), 8);
    mu_assert("should be 8", network_vertex_exflow(network, vertex_p_make(1)) == 8);
    /* mu_assert("should be 8", network_vertex_exflow(network, vertex_p_make(0)) == -8); */
    mu_assert("should be 0", network_vertex_exflow(network, vertex_p_make(4)) == 0);
    return NULL; 
}


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
    mu_message(UNIT, "network_edge_is_reverse\n");
    mu_run_utest(utest_network_edge_is_reverse);
    mu_message(UNIT, "network_set_edge_flow\n");
    mu_run_utest(utest_network_set_edge_flow);
    mu_message(UNIT, "network_vertex_is_active\n");
    mu_run_utest(utest_network_vertex_is_active);
    mu_message(UNIT, "network_vertex_exflow\n");
    mu_run_utest(utest_network_vertex_exflow);
    mu_message(UNIT, "network_edge_is_admissable\n");
    mu_run_utest(utest_network_edge_is_admissable);
    return NULL;
}

