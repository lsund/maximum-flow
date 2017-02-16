
#include <stdlib.h>
#include "test.h"

char *utest_parse() {
    NetworkPointer network;
    network = parse(TEST_GRAPH, PR);
    mu_assert("first vertex should be 1", vertexcollection_get(network->graph.vertices, 0)->label == 1);
    mu_assert("source should be 0", network->source->label == 1);
    size_t i;
    for (i = 0; i < edgecollection_length(network->graph.edges); i++) {
        EdgePointer edge = edgecollection_get(network->graph.edges, i);
        mu_assert("should be 0", edge_flow(edge) == 0);
    }
    return NULL;
}

char *test_parser() {
    mu_message(UNIT, "parse\n");
    mu_run_utest(utest_parse);
    return NULL;
}
