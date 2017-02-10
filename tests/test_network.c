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
    mu_assert("should be the reversed version", edge_equals_reverse(*edge, *edger));
    mu_assert("should be the reversed version", edge_equals_reverse(*edge2, *edge2r));
    NetworkPointer network;
    network = parse(TEST_GRAPH, PR);
    mu_assert("should have 24 edges", edgecollection_length(network->graph.edges) == 24);
    mu_assert("should contain", edgecollection_contains_edge(network->graph.edges, *edge2)); 
    networkvertex_set_distance_label(network, vertex_make(1), 1);
    networkvertex_set_distance_label(network, vertex_make(2), 0);
    mu_assert("should be reverse", networkedge_is_reverse(network, *edger));
    mu_assert("should be reverse", networkedge_is_reverse(network, *edge2r));
    mu_assert("edge should not be reverse", !networkedge_is_reverse(network, *edge));
    mu_assert("edge2 should not be reverse", !networkedge_is_reverse(network, *edge2));
    return NULL;
}

char *utest_networkvertex_is_active()
{
    /* NetworkPointer network = network_init(); */
    /* parse(TEST_GRAPH, network); */
    /* network->inflows = calloc(10, sizeof(unsigned int)); */
    /* network->outflows = calloc(10, sizeof(unsigned int)); */
    /* networkedge_set_flow(network, edge_p_make_label(1, 2), 8); */
    /* mu_assert("should be active", networkvertex_is_active(network, vertex_make(2))); */
    /* mu_assert("should be 0", networkvertex_is_active(network, vertex_make(4)) == false); */
    /* mu_assert("source should not be active", !networkvertex_is_active(network, network->source)); */
    /* mu_assert("source should not be active", !networkvertex_is_active(network, network->sink)); */
    return NULL;
}

char *utest_networkvertex_exflow()
{
    /* NetworkPointer network = network_init(); */
    /* parse(TEST_GRAPH, network); */
    /* network->flows = calloc(10, sizeof(unsigned int)); */
    /* network->inflows = calloc(10, sizeof(unsigned int)); */
    /* network->outflows = calloc(10, sizeof(unsigned int)); */
    /* networkedge_set_flow(network, edge_p_make_label(1, 2), 10); */
    /* networkedge_set_flow(network, edge_p_make_label(1, 3), 10); */
    /* networkedge_set_flow(network, edge_p_make_label(2, 4), 0); */
    /* networkedge_set_flow(network, edge_p_make_label(2, 4), 0); */
    /* mu_assert("should be 10", networkvertex_exflow(network, vertex_make(2)) == 10); */
    /* mu_assert("should be 0", networkvertex_exflow(network, vertex_make(6)) == 0); */
    return NULL; 
}


char *test_network()
{
    mu_message(UNIT, "networkvertex_is_active\n");
    mu_run_utest(utest_networkvertex_is_active);
    mu_message(UNIT, "networkvertex_exflow\n");
    mu_run_utest(utest_networkvertex_exflow);
    return NULL;
}

