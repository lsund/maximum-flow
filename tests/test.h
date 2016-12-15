
#ifndef TEST_H
#define TEST_H

#include "parser.h"
#include "tokenizer.h"
#include "minunit.h"
#include "graph.h"
#include "edgeset.h"
#include "vertexset.h"
#include "tree.h"
#include "disjointset.h"
#include "network.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_GREY    "\x1b[37m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define TEST_GRAPH "/home/lsund/Data/graphs/data/networks/small.dmx"

char *test_parser();
char *test_tokenizer();
char *test_graph();
char *test_util();
char *test_edgeset(); 
char *test_vertexset(); 
char *test_array();
char *test_tree();
char *test_vertex();
char *test_edge();
char *test_matching();
char *test_disjointset();
char *test_network();
char *test_main();


enum MessageOption { 
    MODULE,
    UNIT,
    DATA,
    STATISTICS,
    PASSING,
    PREPEND,
    ERROR,
    TESTSPASSED 
};

void mu_message(enum MessageOption, const char *s);

extern int tests_run;
extern int utests_run;

// Testing works the following way: Each public function in each module is
// tested. private functions are tested indirectly, because of the testing of
// the public functions. The public functions are tested for abilities to handle
// all inputs and that the outputs make sense.

#endif
