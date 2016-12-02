/*****************************************************************************

* File Name: test.c

* Author: Ludvig Sundström

* Description: 

* Creation Date: 16-07-2015

*****************************************************************************/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include "test.h"
#include "minunit.h"
#include <string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_GREY    "\x1b[37m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#ifndef TEST
#define TEST 0
#endif

int tests_run, utests_run;

char *test_parser();
char *test_tokenizer();
char *test_graph();
char *test_util();
char *test_edgeset(); 
char *test_vertexset(); 
char *test_array();
char *test_vertex();
char *test_edge();

void mu_message(enum MessageOption option, const char *s) 
{
    switch (option) {
        case MODULE:
            fprintf(stdout, ANSI_COLOR_YELLOW "Testing Module: %s" ANSI_COLOR_RESET, s); 
            break;
        case UNIT:
            fprintf(stdout, ANSI_COLOR_CYAN   "\tTesting Unit: %s" ANSI_COLOR_RESET, s); 
            break;
        case DATA:
            fprintf(stdout, ANSI_COLOR_GREY   "\t\t%s" ANSI_COLOR_RESET, s); 
            break;
        case PASSING:
            fprintf(stdout, ANSI_COLOR_GREEN  "\t\tPassed" ANSI_COLOR_RESET "\n"); 
            break;
        case STATISTICS:
            fprintf(stdout, ANSI_COLOR_RESET "%s" ANSI_COLOR_RESET, s); 
            break;
        case PREPEND:
            fprintf(stdout, ANSI_COLOR_GREY "%s" ANSI_COLOR_RESET, s); 
            break;
        case ERROR:
            fprintf(stdout, ANSI_COLOR_RED   "Error >> %s" ANSI_COLOR_RESET "\n", s); 
            break;
        case TESTSPASSED:
            fprintf(stdout, ANSI_COLOR_GREEN "ALL TESTS PASSED" ANSI_COLOR_RESET "\n"); 
            break;
    }
}

static char *test()
{
	mu_message(MODULE,"set\n");
    mu_run_test(test_array);
	mu_message(MODULE,"vertex\n");
    mu_run_test(test_vertex);
	mu_message(MODULE,"edge\n");
    mu_run_test(test_edge);
	mu_message(MODULE,"vertexset\n");
    mu_run_test(test_vertexset);
	mu_message(MODULE,"edgeset\n");
    mu_run_test(test_edgeset);
	mu_message(MODULE,"tokenizer\n");
    mu_run_test(test_tokenizer);
	mu_message(MODULE,"parser\n");
    mu_run_test(test_parser);
	mu_message(MODULE,"graph\n");
    mu_run_test(test_graph);
	mu_message(MODULE,"util\n");
    mu_run_test(test_util);
    return 0;
}

static char *one_test(const char *module)
{
    if (strcmp(module, "edgeset") == 0) {
        mu_run_test(test_edgeset);
    }
    return 0;
}


static char *all_tests() {
    char *result; 
    if ((result = test())) { return result; }
    return 0;
}

int main(int argc, char **argv) {
    char *result;
    char buf1[128], buf2[128];
    tests_run = 0;
    utests_run = 0;
    if (argc == 2) {
        if (strcmp(argv[1], "edgeset") == 0) {
            result = one_test("edgeset");
        } else if (strcmp(argv[1], "tree") == 0) {
            result = one_test("tree");
        } else {
            result = NULL;
            runtime_error("invalid argument to test");
        }
    } else {
        result = all_tests();
    }
    if (result != 0) {
        mu_message(ERROR, result);
    }
    else {
        sprintf(buf1, "Modules tested: %d\n", tests_run);
        sprintf(buf2, "Unit tests run: %d\n", utests_run);
        mu_message(STATISTICS, buf1);
        mu_message(STATISTICS, buf2);
        mu_message(TESTSPASSED, "");
    }
    return result != 0;
}

