
#include "test.h"

char *test_main()
{
    NetworkPointer network = network_init();
    mu_assert("should be able to parse table", parse(TEST_GRAPH, network) == SUCCESS);
    mu_assert("should have 6 vertices", vertexcollection_length(network->graph->vertices) == 6);
    mu_assert("should have 7 edges", edgecollection_length(network->graph->edges) == 7);
    return NULL;
}
