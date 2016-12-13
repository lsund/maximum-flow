
#include <stdlib.h>
#include "test.h"

char *utest_graph_init() 
{
    return NULL;
}

char *utest_graph_make() 
{
    return NULL;
}
char *utest_graph_destroy() 
{
    return NULL;
}

char *test_graph() {
    mu_message(UNIT, "graph_init\n");
    mu_run_utest(utest_graph_init);
    mu_message(UNIT, "graph_make\n");
    mu_run_utest(utest_graph_make);
    mu_message(UNIT, "graph_destroy\n");
    mu_run_utest(utest_graph_destroy);
    return NULL;
}
