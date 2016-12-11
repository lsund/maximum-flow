

#include <stdlib.h>
#include "test.h"

char *test_edge_equals()
{
    return NULL;
}

char *test_edge() {
    mu_message(UNIT, "edge_equals\n");
    mu_run_utest(test_edge_equals);
    return NULL;
}
