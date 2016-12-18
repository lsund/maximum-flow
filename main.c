
#include <stdio.h>
#include <stddef.h>

#include "parser.h"
#include "algorithms.h"

int main(int argc, char *argv[]) 
{
    argc = 0;
    NetworkPointer network = network_init();
    parse(argv[1], network);
    push_relabel(network);
    printf("%u\n", network_flow(network));
    return 0;
}

