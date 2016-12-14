
#include <stdio.h>
#include <stddef.h>

#include "parser.h"

int main(int argc, char *argv[]) 
{
    argc = 0;
    argv = NULL;
    TokenTablePointer table = tokentable_init();
    make_tokentable("data/instances/K2.dmx", table);
    NetworkPointer network = malloc(sizeof(Network));
    parse(table, network);
    
    return 0;
}

