
#include <stdio.h>
#include <stddef.h>

#include "parser.h"
#include "algorithms.h"

int main(int argc, char *argv[]) 
{
    NetworkPointer network = network_init();
    if (argc == 2) {
        parse(argv[1], network);
    } else {
        parse("/home/lsund/Data/graphs/data/networks/small.dmx", network);
    }
    push_relabel(network);
    printf("%u\n", network_flow(network));
    network_destroy(network);
    return 0;
}

