
#include <stdlib.h>
#include "test.h"

char *utest_tokenize() 
{

    TokenTablePointer table;
    ssize_t res;

    table = tokentable_init();
    res = tokenize("/home/lsund/Data/graphs/data/matchings/graphs/K2.dmx", table);
    mu_assert("should not fail", res == SUCCESS); 
    mu_assert("table has 2 rows", table->populated_rows == 2); 
    tokentable_destroy(table);

    table = tokentable_init();
    res = tokenize("/home/lsund/Data/graphs/data/matchings/graphs/K3.dmx", table);
    mu_assert("table has 4 rows", table->populated_rows == 4); 
    mu_assert("should not fail", res == SUCCESS); 
    tokentable_destroy(table);

    table = tokentable_init();
    res = tokenize("/home/lsund/Data/graphs/data/matchings/graphs/lu980.dmx", table);
    mu_assert("should not fail", res == SUCCESS); 
    mu_assert("table has 2555 rows", table->populated_rows == 7228); 
    tokentable_destroy(table);

    table = tokentable_init();
    res = tokenize(TEST_GRAPH, table);
    mu_assert("should be c", strcmp(tokentable_get(table, 0, 0), "c") == 0);
    mu_assert("should be c", strcmp(tokentable_get(table, 0, 0), "C") != 0);
    mu_assert("should be c", strcmp(tokentable_get(table, 0, 1), "c") != 0);
    mu_assert("should be c", strcmp(tokentable_get(table, 3, 2), "s") == 0);
    mu_assert("should be c", strcmp(tokentable_get(table, 11, 3), "10") == 0);
    mu_assert("should be null", tokentable_get(table, 12, 3) == NULL);
    tokentable_destroy(table);
    
    return NULL;
}

char *test_tokenizer() 
{
    mu_message(UNIT, "tokenize\n");
    mu_run_utest(utest_tokenize);

    return NULL;
}

