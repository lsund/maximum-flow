
#include "test.h"

char *utest_network_make()
{
    return NULL;
}

char *utest_network_get_vertex_distance_label()
{
    return NULL;
}

char *utest_network_get_edge_flow()
{
    return NULL;
}

char *utest_network_get_edge_capacity()
{
    return NULL;
}

char *utest_network_set_edge_capacity()
{
    return NULL;
}

char *utest_network_edge_is_reverse()
{
    return NULL;
}

char *utest_network_residual()
{
    return NULL;
}

char *test_network()
{
    mu_run_utest(utest_network_make);
    mu_run_utest(utest_network_get_vertex_distance_label);
    mu_run_utest(utest_network_get_edge_flow);
    mu_run_utest(utest_network_get_edge_capacity);
    mu_run_utest(utest_network_edge_is_reverse);
    mu_run_utest(utest_network_residual);
    mu_run_utest(test_network);
    return NULL;
}

