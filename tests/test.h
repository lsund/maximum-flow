
#ifndef TEST_H
#define TEST_H

#include "parser.h"
#include "tokenizer.h"
#include "minunit.h"
#include "graph.h"
#include "edgeset.h"
#include "vertexset.h"
#include "tree.h"
#include "matching.h"
#include "disjointset.h"

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
char *test_bipartite_perfect_matching();
char *test_perfect_matching();


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
