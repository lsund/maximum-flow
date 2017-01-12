#include "test.h"

char *utest_psuedoflow_initialize()
{
    NetworkPointer network = network_init(PS);
    parse("/home/lsund/Data/graphs/data/networks/set/gen2x2.dmx", network);
    pseudoflow_initialize(network);
    mu_assert("should contain the same number of elements as the graph + 1",
            *network->tree.nvertices == 5);
    network = network_init(PS);
    parse("/home/lsund/Data/graphs/data/networks/set/gen20x20.dmx", network);
    pseudoflow_initialize(network);
    mu_assert("should contain the same number of elements as the graph + 1",
            *network->tree.nvertices == 401);
    network = network_init(PS);
    parse("/home/lsund/Data/graphs/data/networks/set/gen3x3.dmx", network);
    pseudoflow_initialize(network);
    mu_assert("should contain the same number of elements as the graph + 1",
            *network->tree.nvertices == 10);
    mu_assert("number of strong vertices should be 3",
            vertexcollection_length(network->strong_vertices) == 3);
    mu_assert("number of weak vertices should be 6",
            vertexcollection_length(network->weak_vertices) == 6);
    return NULL;
}

char *test_pseudoflow()
{
    mu_message(UNIT, "pseudoflow_initialize\n");
    mu_run_utest(utest_psuedoflow_initialize);
    return NULL;
}
