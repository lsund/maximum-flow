
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#include "parser.h"
#include "goldberg_tarjan.h"
#include "pseudoflow.h"

char *file;
char *outfile;
int output;
NetworkType type;

static void print_before(const char *file, const NetworkType type)
{
    printf("type 0 = push relabel network\ntype 1 = pseudoflow network\n");
    printf(
            "Computing flow of the network in file %s using network type %d\n", 
            file,
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
    bool file, specified_type, specified_outfile;
    file              = false;
    specified_outfile = false;
    specified_type    = false;
    int opt;
    int i   = 1;
    while ((opt = getopt(argc, argv, "fto")) != 1) {
        i++;
        switch (opt) {
            case 'f': 
                file = argv[i];
                i++;
                file = true;
                break;
            case 't': 
                type = strcmp("pr", argv[i]) == 0 ? PR : PS;
                i++;
                type = true;
                break;
            case 'o': 
                outfile = argv[i];
                i++;
                specified_outfile = true;
                break;
            case -1:
                return;
            default: 
                fprintf(
                        stderr, "Usage : %s -f file [-t type] [-o outfile] \n",
                        argv[0]
                    );
                exit(EXIT_FAILURE);
        }
        if (!file) {
            fprintf(
                    stderr, "Usage : %s -f file [-t type] [-o outfile] \n",
                    argv[0]
                );
        }
        if (!type) {
            type = PR;
        }
    }
}

int main(int argc, char *argv[]) 
{
    parse_arguments(argc, argv);
    NetworkPointer network = parse(file, type);
    print_before(file, type);
    clock_t start = clock(), diff;
    if (network->type == PR) {
        goldberg_tarjan(network);
    } else {
        pseudoflow(network);
    }
    diff = clock() - start;
    int msec = diff * 1000 / CLOCKS_PER_SEC;
    if (outfile) {
        /* print_file(network, outfile); */
    } else {
        print_after(network, msec);
    }
    network_destroy(network);

    return 0;
}

