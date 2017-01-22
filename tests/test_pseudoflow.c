#include "test.h"

NetworkPointer create_test_network()
{
    NetworkPointer ret = network_init(PS);
    parse("/home/lsund/Data/graphs/data/networks/test.dmx", ret);
    return ret;
}

char *utest_psuedoflow_initialize()
{
    NetworkPointer network = network_init(PS);
    parse("/home/lsund/Data/graphs/data/networks/set/gen2x2.dmx", network);
    pseudoflow_initialize(network);
    network = network_init(PS);
    parse("/home/lsund/Data/graphs/data/networks/set/gen20x20.dmx", network);
    pseudoflow_initialize(network);
    network = network_init(PS);
    parse("/home/lsund/Data/graphs/data/networks/set/gen3x3.dmx", network);
    pseudoflow_initialize(network);
    mu_assert("number of weak vertices should be 6", 
            vertexcollection_length(network->weak_vertices) == 6);
    mu_assert("number of strong vertices should be 3", 
            vertexcollection_length(network->strong_vertices) == 3);
    return NULL;
}

char *utest_merger_edge()
{
    Edge check = edge_make_label(2, 4);
    NetworkPointer network = network_init(PS);
    parse("/home/lsund/Data/graphs/data/networks/set/gen2x2.dmx", network);
    pseudoflow_initialize(network);
    EdgePointer mergeredge = merger_edge(network);
    mu_assert("first found merger_edge should be (2,4)", edge_equals(mergeredge, &check));
    return NULL;
}

char *utest_pseudoflow() {
    NetworkPointer network = create_test_network();
    pseudoflow_initialize(network);
    mu_assert("should have label 1", network->source->label == 1);
    mu_assert("should have label 4", network->sink->label == 4);
    EdgePointer e1 = edgecollection_get(network->graph.edges, 0);
    EdgePointer e2 = edgecollection_get(network->graph.edges, 1);
    EdgePointer e3 = edgecollection_get(network->graph.edges, 2);

    EdgePointer be1 = edgecollection_get(network->reverse_edges, 0);
    EdgePointer be2 = edgecollection_get(network->reverse_edges, 1);
    EdgePointer be3 = edgecollection_get(network->reverse_edges, 2);

    Edge e1v = edge_make_label(1, 2);
    Edge e2v = edge_make_label(2, 3);
    Edge e3v = edge_make_label(3, 4);

    mu_assert("should be (1, 2)", edge_equals(e1, &e1v));
    mu_assert("should be (2, 3)", edge_equals(e2, &e2v));
    mu_assert("should be (3, 4)", edge_equals(e3, &e3v));

    mu_assert("should have flow 30", networkedge_flow(network, e1) == 30);
    mu_assert("should have flow 0", networkedge_flow(network, e2) == 0);
    mu_assert("should have flow 30", networkedge_flow(network, e3) == 30);

    mu_assert("should have capacity 30", networkedge_capacity(network, e1) == 30);
    mu_assert("should have capacity 30", networkedge_capacity(network, e2) == 10);
    mu_assert("should have capacity 30", networkedge_capacity(network, e3) == 30);

    mu_assert("should have residual capacity 0", networkedge_residual_capacity(network, e1) == 0);
    mu_assert("should have residual capacity 10", networkedge_residual_capacity(network, e2) == 10);
    mu_assert("should have residual capacity 0", networkedge_residual_capacity(network, e3) == 0);

    mu_assert("should have residual capacity 30", networkedge_residual_capacity(network, be1) == 30);
    mu_assert("should have residual capacity 0", networkedge_residual_capacity(network, be2) == 0);
    mu_assert("should have residual capacity 30", networkedge_residual_capacity(network, be3) == 30);
    
    EdgePointer merger = merger_edge(network);
    mu_assert("first merger edge should be (2, 3)", edge_equals(&e2v, merger));

    mu_assert("excess of the strong branch should be 30", *(network->excesses + 2) == 30);
    mu_assert("excess of the weak branch should be -30", *(network->excesses + 3) == -30);

    
    network = create_test_network();
    pseudoflow(network);
    mu_assert("flow should be 10", network_flow(network) == 10);

    network = network_init(PS);
    parse("/home/lsund/Data/graphs/data/networks/set/gen2x2.dmx", network);
    pseudoflow(network);
    return NULL;
}

char *test_pseudoflow()
{
    mu_message(UNIT, "pseudoflow_initialize\n");
    mu_run_utest(utest_psuedoflow_initialize);
    mu_message(UNIT, "merger_edge\n");
    mu_run_utest(utest_merger_edge);
    mu_message(UNIT, "pseudoflow\n");
    mu_run_utest(utest_pseudoflow);
    return NULL;
}
