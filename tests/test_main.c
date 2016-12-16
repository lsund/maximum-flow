
#include "test.h"

char *test_main()
{
    NetworkPointer network = network_init();
    parse(TEST_GRAPH, network);
    push_relabel(network);
    mu_assert("should be 17", network_vertex_inflow(network, network->sink));
    return NULL;
}
