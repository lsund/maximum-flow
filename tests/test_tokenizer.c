
#include <stdlib.h>
#include "test.h"

char *utest_tokenize() 
{

    TokenTablePointer table;
    ssize_t res;

    table = tokentable_init();
    res = tokenize_dimacs("/home/lsund/Data/graphs/data/matchings/graphs/K2.dmx", table);
    mu_assert("should not fail", res == SUCCESS); 
    mu_assert("table has 2 rows", table->populated_rows == 2); 
    tokentable_destroy(table);

    table = tokentable_init();
    res = tokenize_dimacs("/home/lsund/Data/graphs/data/matchings/graphs/K3.dmx", table);
    mu_assert("table has 4 rows", table->populated_rows == 4); 
    mu_assert("should not fail", res == SUCCESS); 
    tokentable_destroy(table);

    table = tokentable_init();
    res = tokenize_dimacs("/home/lsund/Data/graphs/data/matchings/graphs/lu980.dmx", table);
    mu_assert("should not fail", res == SUCCESS); 
    mu_assert("table has 2555 rows", table->populated_rows == 7228); 
    tokentable_destroy(table);

    return NULL;
}

char *test_tokenizer() 
{
    mu_message(UNIT, "tokenize_dimacs\n");
    mu_run_utest(utest_tokenize);

    return NULL;
}

