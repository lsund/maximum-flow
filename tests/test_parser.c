
#include <stdlib.h>
#include "test.h"

char *utest_parse() {
    TokenTablePointer table = tokentable_init();
    make_tokentable(TEST_GRAPH, table);
    NetworkPointer network = malloc(sizeof(Network));
    mu_assert("should succeed", parse(table, network));
    mu_assert("should not be empty", !edgeset_is_empty(network->graph->edgeset));
    mu_assert("should not be empty", !vertexset_is_empty(network->graph->vertexset));
    mu_assert("first vertex should be 1", vertexset_get(network->graph->vertexset, 0)->label == 0);
    return NULL;
}

char *test_parser() {
    mu_message(UNIT, "parse\n");
    mu_run_utest(utest_parse);
    return NULL;
}
