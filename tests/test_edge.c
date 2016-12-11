

#include <stdlib.h>
#include "test.h"

char *test_edges_equal()
{
    return NULL;
}

char *test_edge() {
    mu_message(UNIT, "edges_equal\n");
    mu_run_utest(test_edges_equal);
    return NULL;
}
