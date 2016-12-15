
#include "test.h"

char *test_main()
{
    TokenTablePointer table = tokentable_init();
    mu_assert("should be able to load table", make_tokentable("/home/lsund/Data/graphs/data/networks/small.dmx", table) == SUCCESS);
    NetworkPointer network = malloc(sizeof(Network));
    mu_assert("should be able to parse table", parse(table, network) == SUCCESS);
    mu_assert("should have 6 vertices", vertexcollection_length(network->graph->vertices) == 6);
    mu_assert("should have 7 edges", edgecollection_length(network->graph->edges) == 7);
    return NULL;
}
