
#include <stdlib.h>
#include "test.h"

char *utest_tokentable_init() {
    TokenTablePointer table;
    FILE *fp;
    fp = fopen("/home/lsund/Data/graphs/data/matchings/graphs/K2.dmx", "r");
    table = tokentable_init();
    mu_assert("table has a capacity of MAX_LINES", table->rows == MAX_LINES); 
    mu_assert("no rows are populated", table->populated_rows == 0); 
    mu_assert("tokens are not initialized", table->tokens != 0); 
    fclose(fp);
    tokentable_destroy(table);
    return NULL;
}

char *utest_tokentable_destroy() {
    FILE *fp;
    TokenTablePointer table;
    fp = fopen("/home/lsund/Data/graphs/data/matchings/graphs/K2.dmx", "r");
    table = tokentable_init();
    fclose(fp);
    tokentable_destroy(table);
    mu_assert("tokens are not null", table->tokens == NULL); 
    return NULL;
}

char *utest_tokentable_get() {
    TokenTablePointer table;
    table = tokentable_init();
    tokenize("/home/lsund/Data/graphs/data/matchings/graphs/myciel7.mwis.dmx", table);
    mu_assert("r0c0 should be c", strcmp(tokentable_get(table, 0, 0), "c") == 0);
    mu_assert("r4c2 should be 2", strcmp(tokentable_get(table, 4, 2) , "2") == 0);
    mu_assert("r2c8 should be defines", strcmp(tokentable_get(table, 2, 8) , "defines") == 0);
    tokentable_destroy(table);
    return NULL;
}

char *utest_tokentable_graph_dimension() {
    TokenTablePointer table;
    table = tokentable_init();
    tokenize("/home/lsund/Data/graphs/data/matchings/graphs/myciel7.mwis.dmx", table);
    mu_assert("nedges should be 2360", tokentable_graph_dimension(table).y == 2360);
    tokentable_destroy(table);

    return NULL;
}

char *test_tokentable()
{
    mu_message(UNIT, "tokentable_init\n");
    mu_run_utest(utest_tokentable_init);

    mu_message(UNIT, "tokentable_destroy\n");
    mu_run_utest(utest_tokentable_destroy);

    mu_message(UNIT, "tokentable_get\n");
    mu_run_utest(utest_tokentable_get);

    mu_message(UNIT, "nedges_in_table\n");
    mu_run_utest(utest_tokentable_graph_dimension);
    return NULL;
}
