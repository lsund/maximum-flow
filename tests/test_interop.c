
#include "test.h"

char *test_interop()
{
    NetworkPointer pr_network, ps_network;

    pr_network = network_init(PR);
    ps_network = network_init(PS);
    parse("/home/lsund/Data/graphs/data/networks/set/gen2x2.dmx", pr_network);
    parse("/home/lsund/Data/graphs/data/networks/set/gen2x2.dmx", ps_network);
    pseudoflow(ps_network);
    push_relabel(pr_network);
    mu_assert("flow should be equal", network_flow(pr_network) == network_flow(ps_network));
    network_destroy(pr_network);
    network_destroy(ps_network);

    /* pr_network = network_init(PR); */
    /* ps_network = network_init(PS); */
    /* parse("/home/lsund/Data/graphs/data/networks/set/gen3x3.dmx", pr_network); */
    /* parse("/home/lsund/Data/graphs/data/networks/set/gen3x3.dmx", ps_network); */
    /* pseudoflow(ps_network); */
    /* push_relabel(pr_network); */
    /* mu_assert("flow should be equal", network_flow(pr_network) == network_flow(ps_network)); */
    /* network_destroy(pr_network); */
    /* network_destroy(ps_network); */

    return NULL;
}
