
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

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
    int opt;
    int i = 1;
    while ((opt = getopt(argc, argv, "fto")) != 1) {
        i++;
        switch (opt) {
            case 'f': 
                filename = argv[i];
                i++;
                break;
            case 't': 
                type = strcmp("pr", argv[i]) == 0 ? PR : PS;
                i++;
                break;
            case 'o': 
                printf("%s\n", argv[i]);
                i++;
                break;
            case -1:
                return;
            default: 
                printf("%d\n", opt);
                fprintf(stderr, "Usage : %s [ilw] \n", argv[0]);
                exit(EXIT_FAILURE);
        }
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

