
#include <stdio.h>
#include <stddef.h>
#include <time.h>

#include "parser.h"
#include "push_relabel.h"
#include "pseudoflow.h"
#include "map.h"

int main(int argc, char *argv[]) 
{
   NetworkPointer network = network_init(PR);
    /* NetworkPointer network = network_init(PS); */
    if (argc == 2) {
        parse(argv[1], network);
    } else {
        // 20x20 3.5s pr
        // 20x20 1801s ps
        /* parse("/home/lsund/Data/graphs/data/networks/set/gen2x2.dmx", network); */
        /* parse("/home/lsund/Data/graphs/data/networks/set/gen3x3.dmx", network); */
        /* parse("/home/lsund/Data/graphs/data/networks/set/gen5x5.dmx", network); */
        parse("/home/lsund/Data/graphs/data/networks/bigsets/8x8s/249.dmx", network);
        /* parse("/home/lsund/Data/graphs/data/networks/set/gen20x20.dmx", network); */
    }
    clock_t start = clock(), diff;
    if (network->type == PR) {
        push_relabel(network);
    } else {
        pseudoflow(network);
    }
    diff = clock() - start;
    int msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);
    printf("flow: %u\n", network_flow(network));
    network_destroy(network);
    return 0;
}

