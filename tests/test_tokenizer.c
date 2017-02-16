
#include <stdlib.h>
#include "test.h"

char *utest_tokenize() 
{

    TokenTablePointer table;

    table = tokenize_dimacs("/home/lsund/Data/graphs/data/matchings/graphs/K2.dmx");
    mu_assert("should not fail", table); 
    mu_assert("table has 2 rows", table->populated_rows == 2); 
    tokentable_destroy(table);

    table = tokenize_dimacs("/home/lsund/Data/graphs/data/matchings/graphs/K3.dmx");
    mu_assert("table has 4 rows", table->populated_rows == 4); 
    mu_assert("should not fail", table); 
    tokentable_destroy(table);

    table = tokenize_dimacs("/home/lsund/Data/graphs/data/matchings/graphs/lu980.dmx");
    mu_assert("should not fail", table); 
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

