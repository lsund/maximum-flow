
#include <stdlib.h>
#include "test.h"

char *utest_make_network()
{
    NetworkPointer network = malloc(sizeof(Network));
    TokenTablePointer table = init_tokentable();
    make_tokentable("data/instances/K2.dmx", table);
    GraphPointer graph = init_graph();
    make_graph(table, graph);
    mu_assert("should fail", make_network(graph, 0, 1, network) == FAIL);
    mu_assert("should work", make_network(graph, 1, 2, network) == SUCCESS);
    mu_assert("network should exist", network);
    mu_assert("reversed network should exist", network->rev_graph);
    mu_assert("should have an edgeset", network->rev_graph->edgeset.set); 
    mu_assert("should have length 4", network->rev_graph->edgeset.set->length == 9); 
    mu_assert("should have an element", network->rev_graph->edgeset.set->nelements == 1); 
    EdgePointer rev_edge = get_edge_at_position(network->rev_graph->edgeset, 0); 
    mu_assert("should exist", rev_edge);
    mu_assert("should be 2", rev_edge->first.label == 2);
    mu_assert("should be 1", rev_edge->second.label == 1);

    return NULL;
}

char *test_network() {
    mu_message(UNIT, "make_network\n");
    mu_run_utest(utest_make_network);
    return NULL;
}
