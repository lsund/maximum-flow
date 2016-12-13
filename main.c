
#include <stdio.h>
#include <stddef.h>
#include "network.h"

int main(int argc, char *argv[]) 
{
    argc = 0;
    argv = NULL;
    TokenTablePointer table = init_tokentable();
    make_tokentable("data/instances/K2.dmx", table);
    /* NetworkPointer network = malloc(sizeof(Network)); */
    /* network_make(graph, 0, 1, network); */
    
    return 0;
}

