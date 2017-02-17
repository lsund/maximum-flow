
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

// The type of network that will be used
// Change this to PR if you want to use the push_relabel
// algorithm instead of the pseudoflow algorithm
#define NETWORK_TYPE PR
// The file that will be used as input given that no argement
// is given the program
#define FILE_NAME "sample_data/25x25.dmx"

// Type synonym
typedef unsigned int Label; 

#define MAX_VERTICES 10000
#define MAX_EDGES 10000
#define TKN_MAX_LEN 64
#define LINE_MAX_TKNS 64
#define MAX_LINES 50000

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_GREY    "\x1b[37m"
#define ANSI_COLOR_RESET   "\x1b[0m"

