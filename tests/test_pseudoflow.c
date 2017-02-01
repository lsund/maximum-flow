#include "test.h"

NetworkPointer create_test_network()
{
    return NULL;
}

char *utest_psuedoflow_initialize()
{
    return NULL;
}

char *utest_merger_edge()
{
    return NULL;
}

char *utest_pseudoflow() {

    return NULL;
}

char *test_pseudoflow()
{
    mu_message(UNIT, "pseudoflow_initialize\n");
    mu_run_utest(utest_psuedoflow_initialize);
    mu_message(UNIT, "merger_edge\n");
    mu_run_utest(utest_merger_edge);
    mu_message(UNIT, "pseudoflow\n");
    mu_run_utest(utest_pseudoflow);
    return NULL;
}
