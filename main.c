
#include <stdio.h>
#include <stddef.h>
#include <time.h>

#include "parser.h"
#include "algorithms.h"
#include "map.h"

int main(int argc, char *argv[]) 
{
    NetworkPointer network = network_init();
    if (argc == 2) {
        parse(argv[1], network);
    } else {
        // 20x20 3.5s
        /* parse("/home/lsund/Data/graphs/data/networks/set/gen2x2.dmx", network); */
        parse("/home/lsund/Data/graphs/data/networks/set/gen20x20.dmx", network);
    }
    clock_t start = clock(), diff;
    push_relabel(network);
    diff = clock() - start;
    int msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);
    printf("flow: %u\n", network_flow(network));
    network_destroy(network);
    return 0;
}

