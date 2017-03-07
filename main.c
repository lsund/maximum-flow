
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#include "parser.h"
#include "goldberg_tarjan.h"
#include "pseudoflow.h"

char *file;
int output;
NetworkType type;

static void print_help_and_exit()
{
    fprintf(stderr, "\nUsage:\t./maxflow -f file -t type\n");
    fprintf(stderr, "\ntype:\t\n");
    fprintf(stderr, "\tpr:\trun push-relabel algorithm\n");
    fprintf(stderr, "\tps:\trun pseudoflow algorithm\n");
    fprintf(stderr, "\tboth:\tboth algorithms\n\n");
    exit(EXIT_FAILURE);
}

static void print_benchcmark(const NetworkPointer network, const int msec)
{
    char type_str[16];
    if (network->type == PR) {
        sprintf(type_str, "%s", "pr");
    } else if (network->type == PS) {
        sprintf(type_str, "%s", "ps");
    } else {
        runtime_error("print_benchcmark: invalid argument");
    }
    if (VERBOSE) {
        printf("File: %s, Network type: %s Msec: %d ", file, type_str, msec);
    } else {
        printf("%d ", msec);
    }
}

static void parse_arguments(int argc, char *argv[])
{
    bool specified_file, specified_type;
    specified_file    = false;
    specified_type    = false;
    int opt;
    int i   = 1;
    while ((opt = getopt(argc, argv, "ft")) != 1) {
        i++;
        switch (opt) {
            case 'f': 
                file = argv[i];
                i++;
                specified_file = true;
                break;
            case 't':
                if (strcmp("pr", argv[i]) == 0) {
                    type = PR;
                } else if (strcmp("ps", argv[i]) == 0) {
                    type = PS;
                } else {
                    type = NO_TYPE;
                }
                i++;
                specified_type = true;
                break;
            case -1:
                return;
            default:
                print_help_and_exit();
        }
    }
    if (!specified_file || !specified_type) {
        print_help_and_exit();
    }
}

static int benchmark(const NetworkPointer network)
{
    clock_t start, diff;
    start = clock();
    if (network->type == PR) {
        goldberg_tarjan(network);
    } else {
        pseudoflow(network);
    }
    diff = clock() - start;
    return diff * 1000 / CLOCKS_PER_SEC;
}

int main(int argc, char *argv[]) 
{
    NetworkPointer network;
    parse_arguments(argc, argv);
    int msec;
    if (type == NO_TYPE) {

        int msec_pr, msec_ps;

        network = parse(file, PR);
        printf("%zu ", vertexcollection_length(network->graph.vertices));
        msec_pr = benchmark(network);
        print_benchcmark(network, msec_pr);
        network_destroy(network);

        network = parse(file, PS);
        msec_ps = benchmark(network);
        print_benchcmark(network, msec_ps);
        network_destroy(network);

    } else {
        network = parse(file, type);
        printf("%zu ", vertexcollection_length(network->graph.vertices));
        msec = benchmark(network);
        print_benchcmark(network, msec);
        network_destroy(network);
    } 
    printf("\n");
    return 0;
}

