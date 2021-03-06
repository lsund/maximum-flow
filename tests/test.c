/*****************************************************************************

* File Name: test.c

* Author: Ludvig Sundström

* Description: 

* Creation Date: 16-07-2015

*****************************************************************************/

#include "test.h"

#ifndef TEST
#define TEST 0
#endif

int entry_index;
int tests_run, utests_run;

static char *test()
{
	mu_message(MODULE,"collection\n");
    mu_run_test(test_collection);
	mu_message(MODULE,"vertex\n");
    mu_run_test(test_vertex);
	mu_message(MODULE,"vertexcollection\n");
    mu_run_test(test_vertexcollection);
	mu_message(MODULE,"tree\n");
    mu_run_test(test_tree);
	mu_message(MODULE,"tokentable\n");
    mu_run_test(test_tokentable);
	mu_message(MODULE,"tokenizer\n");
    mu_run_test(test_tokenizer);
	mu_message(MODULE,"parser\n");
    mu_run_test(test_parser);
	mu_message(MODULE,"network\n");
    mu_run_test(test_network);
	mu_message(MODULE,"util\n");
    mu_run_test(test_util);
    mu_message(MODULE, "pseudoflow\n");
    mu_run_test(test_pseudoflow);
    mu_message(MODULE, "goldberg_tarjan\n");
    mu_run_test(test_goldberg_tarjan_algorithm);
    mu_message(MODULE, "pseudoflow algorithm\n");
    mu_run_test(test_pseudoflow_algorithm);
    return 0;
}

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
            fprintf(stdout, ANSI_COLOR_GREY   "\t%s" ANSI_COLOR_RESET, s); 
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


static char *one_test(const char *module)
{
    if (strcmp(module, "tree") == 0) {
        mu_run_test(test_tree);
    } else if (strcmp(module, "pseudoflow") == 0) {
        mu_run_test(test_pseudoflow);
    } else if (strcmp(module, "collection") == 0) {
        mu_run_test(test_collection);
    } else if (strcmp(module, "vertexcollection") == 0) {
        mu_run_test(test_vertexcollection);
    } else if (strcmp(module, "extensive") == 0) {
        mu_run_test(test_extensive);
    } else if (strcmp(module, "interop") == 0) {
        mu_run_test(test_interop);
    } else if (strcmp(module, "ps_alg") == 0) {
        mu_run_test(test_pseudoflow_algorithm);
    }
    return 0;
}


static char *all_tests() {
    char *result; 
    if ((result = test())) { return result; }

    return 0;
}

int main(int argc, char **argv) {
    entry_index = -1;
    char *result;
    char buf1[128], buf2[128];
    tests_run = 0;
    utests_run = 0;
    if (argc == 2) {
        if (strcmp(argv[1], "edgecollection") == 0) {
            result = one_test("edgecollection");
        } else if (strcmp(argv[1], "tree") == 0) {
            result = one_test("tree");
        } else if (strcmp(argv[1], "pseudoflow") == 0) {
            result = one_test("pseudoflow");
        } else if (strcmp(argv[1], "collection") == 0) {
            result = one_test("collection");
        } else if (strcmp(argv[1], "vertexcollection") == 0) {
            result = one_test("vertexcollection");
        } else if (strcmp(argv[1], "extensive") == 0) {
            result = one_test("extensive");
        } else if (strcmp(argv[1], "ps_alg") == 0) {
            result = one_test("ps_alg");
        } else if (strcmp(argv[1], "interop") == 0) {
            result = one_test("interop");
        } else {
            result = NULL;
            runtime_error("invalid argument to test");
        }
    } else if (argc == 3) {
        int index = strtol(argv[2], NULL, 10);
        if (strcmp(argv[1], "perfect") == 0) {
            entry_index = index;
            result = one_test("perfect");
        } else {
            result = "";
            runtime_error("wrong arguments to test");
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

