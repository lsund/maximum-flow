
#include "test.h"

char *test_main()
{
    TokenTablePointer table = tokentable_init();
    mu_assert("should be able to load table", make_tokentable("data/networks/small.dmx", table) == SUCCESS);
    NetworkPointer network = malloc(sizeof(Network));
    mu_assert("should be able to parse table", parse(table, network) == SUCCESS);
    mu_assert("should have 6 vertices", network->graph->vertexset.set->length == 6);
    mu_assert("should have 7 edges", network->graph->edgeset.set->length == 7);
    return NULL;
}
