
#include <time.h>

#include "parser.h"
#include "goldberg_tarjan.h"
#include "pseudoflow.h"

char *filename;
NetworkType type;

static void print_before(const char *filename, const NetworkType type)
{
    printf("type 0 = push relabel network\ntype 1 = pseudoflow network\n");
    printf(
            "Computing flow of the network in file %s using network type %d\n", 
            filename,
            type
        );
}

static void print_after(const NetworkPointer network, const int msec)
{
    printf("Time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);
    printf("flow: %u\n", recover_flow(network));
}

static void parse_arguments(int argc, char *argv[])
{
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
}

int main(int argc, char *argv[]) 
{
    parse_arguments(argc, argv);
    NetworkPointer network = parse(filename, type);
    print_before(filename, type);
    clock_t start = clock(), diff;
    if (network->type == PR) {
        goldberg_tarjan(network);
    } else {
        pseudoflow(network);
    }
    diff = clock() - start;
    int msec = diff * 1000 / CLOCKS_PER_SEC;
    print_after(network, msec);
    network_destroy(network);

    return 0;
}

