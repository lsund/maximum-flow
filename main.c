
#include <time.h>

#include "parser.h"
#include "push_relabel.h"
#include "pseudoflow.h"

// The type of network that will be used
// Change this to PR if you want to use the push_relabel
// algorithm instead of the pseudoflow algorithm
#define NETWORK_TYPE PS 
// The file that will be used as input given that no argement
// is given the program
#define FILE_NAME "sample_data/10x10.dmx"

int main(int argc, char *argv[]) 
{
    NetworkPointer network = network_init(NETWORK_TYPE);
    char *filename;
    if (argc == 2) {
        filename = argv[1];
    } else {
        filename = FILE_NAME;
    }
    printf("Computing flow of the network in file %s\n", filename);
    parse(filename, network);
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

