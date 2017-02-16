
#include <time.h>

#include "parser.h"
#include "push_relabel.h"
#include "pseudoflow.h"

// The type of network that will be used
// Change this to PR if you want to use the push_relabel
// algorithm instead of the pseudoflow algorithm
#define NETWORK_TYPE PR
// The file that will be used as input given that no argement
// is given the program
#define FILE_NAME "sample_data/25x25.dmx"

int main(int argc, char *argv[]) 
{
    char *filename;
    NetworkType type;
    if (argc == 3) {
        filename = argv[1];
        if (strcmp(argv[2], "pr") == 0) {
            type = PR; 
        } else if (strcmp(argv[2], "ps") == 0) {
            type = PS;
        } else {
            type = NETWORK_TYPE;
        }
    } else if (argc == 2) {
        filename = argv[1];
        type = NETWORK_TYPE;
    } else {
        filename = FILE_NAME;
        type = NETWORK_TYPE;
    }
    printf("type 0 = push relabel network\ntype 1 = pseudoflow network\n");
    printf("Computing flow of the network in file %s using network type %d\n", filename, type);
    NetworkPointer network = parse(filename, type);
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

