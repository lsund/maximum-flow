
#include "test.h"

char *test_main()
{
    NetworkPointer network = network_init();
    parse(TEST_GRAPH, network);
    push_relabel(network);
    mu_assert("should be 17", network_flow(network) == 17);
    return NULL;
}
