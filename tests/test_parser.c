
#include <stdlib.h>
#include "test.h"

char *utest_parse() {
    NetworkPointer network = malloc(sizeof(Network));
    mu_assert("should succeed", parse(TEST_GRAPH, network));
    mu_assert("should not be empty", !edgecollection_is_empty(network->graph->edges));
    mu_assert("should not be empty", !vertexcollection_is_empty(network->graph->vertices));
    mu_assert("first vertex should be 1", vertexcollection_get(network->graph->vertices, 0)->label == 0);
    return NULL;
}

char *test_parser() {
    mu_message(UNIT, "parse\n");
    mu_run_utest(utest_parse);
    return NULL;
}
