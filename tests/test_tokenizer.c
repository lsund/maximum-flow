
#include <stdlib.h>
#include "test.h"

char *utest_init_tokentable() {
    TokenTablePointer table;
    FILE *fp;
    fp = fopen("data/instances/K2.dmx", "r");
    table = init_tokentable();
    mu_assert("table has a capacity of MAX_LINES", table->rows == 3000); 
    mu_assert("no rows are populated", table->populated_rows == 0); 
    mu_assert("tokens are not initialized", table->tokens != 0); 
    fclose(fp);
    destroy_tokentable(table);
    return NULL;
}

char *utest_destroy_tokentable() {
    FILE *fp;
    TokenTablePointer table;
    fp = fopen("data/instances/K2.dmx", "r");
    table = init_tokentable();
    fclose(fp);
    destroy_tokentable(table);
    mu_assert("tokens are not null", table->tokens == NULL); 
    return NULL;
}

char *utest_make_tokentable() 
{

    TokenTablePointer table;
    ssize_t res;

    table = init_tokentable();
    res = make_tokentable("data/instances/K2.dmx", table);
    mu_assert("should not fail", res == SUCCESS); 
    mu_assert("table has 2 rows", table->populated_rows == 2); 
    destroy_tokentable(table);

    table = init_tokentable();
    res = make_tokentable("data/instances/K3.dmx", table);
    mu_assert("table has 5 rows", table->populated_rows == 5); 
    mu_assert("should not fail", res == SUCCESS); 
    destroy_tokentable(table);

    table = init_tokentable();
    res = make_tokentable("data/instances/myciel7.mwis.dmx", table);
    mu_assert("should not fail", res == SUCCESS); 
    mu_assert("table has 2555 rows", table->populated_rows == 2555); 
    destroy_tokentable(table);

    table = init_tokentable();
    res = make_tokentable("data/instances/malformed.dmx", table);
    mu_assert("should fail because file is malformed", res == FAIL); 
    destroy_tokentable(table);
    
    return NULL;
}

char *utest_get_token() {
    TokenTablePointer table;
    table = init_tokentable();
    make_tokentable("data/instances/myciel7.mwis.dmx", table);
    mu_assert("r0c0 should be c", strcmp(get_token(table, 0, 0), "c") == 0);
    mu_assert("r4c2 should be 2", strcmp(get_token(table, 4, 2) , "2") == 0);
    mu_assert("r2c8 should be defines", strcmp(get_token(table, 2, 8) , "defines") == 0);
    destroy_tokentable(table);
    return NULL;
}

char *utest_graph_cardinality() {
    TokenTablePointer table;
    table = init_tokentable();
    make_tokentable("data/instances/myciel7.mwis.dmx", table);
    mu_assert("nedges should be 2360", graph_cardinality(table).y == 2360);
    destroy_tokentable(table);

    table = init_tokentable();
    make_tokentable("data/instances/malformed2.dmx", table);
    mu_assert("nedges should fail", graph_cardinality(table).y == -1);
    destroy_tokentable(table);
    return NULL;
    return NULL;
}

char *test_tokenizer() 
{
    mu_message(UNIT, "init_tokentable\n");
    mu_run_utest(utest_init_tokentable);

    mu_message(UNIT, "destroy_tokentable\n");
    mu_run_utest(utest_destroy_tokentable);

    mu_message(UNIT, "make_tokentable\n");
    mu_run_utest(utest_make_tokentable);

    mu_message(UNIT, "get_token\n");
    mu_run_utest(utest_get_token);

    mu_message(UNIT, "nedges_in_table\n");
    mu_run_utest(utest_graph_cardinality);

    return NULL;
}

