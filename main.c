
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#include "parser.h"
#include "goldberg_tarjan.h"
#include "pseudoflow.h"

char *file;
int output;
NetworkType type;

static void print_after(const NetworkPointer network, const int msec)
{
    char type_str[16];
    if (network->type == PR) {
        sprintf(type_str, "%s", "pr");
    } else if (network->type == PS) {
        sprintf(type_str, "%s", "ps");
    } else {
        runtime_error("print_after: invalid argument");
    }
    printf("%s %d ", type_str, msec);
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
                fprintf(
                        stderr, "Usage : %s -f file [-t type]\n",
                        argv[0]
                    );
                exit(EXIT_FAILURE);
        }
        if (!specified_file) {
            fprintf(
                    stderr, "Usage : %s -f file [-t type]\n",
                    argv[0]
                );
            exit(EXIT_FAILURE);
        }
        if (!specified_type) {
            type = PR;
        }
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
        msec_pr = benchmark(network);
        print_after(network, msec_pr);
        network = parse(file, PS);
        msec_ps = benchmark(network);
        print_after(network, msec_ps);
    } else {
        network = parse(file, type);
        msec = benchmark(network);
        print_after(network, msec);
    } 
    printf("\n");
    network_destroy(network);
    return 0;
}

