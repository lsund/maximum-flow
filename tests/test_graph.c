
#include <stdlib.h>
#include "test.h"

char *utest_init_graph() 
{
    return NULL;
}

char *utest_make_graph() 
{
    TokenTablePointer table;
    table = init_tokentable();
    make_tokentable("data/instances/K2.dmx", table);
    GraphPointer graph;
    graph = init_graph();
    Result res = make_graph(table, graph);
    mu_assert("make_graph: should succed", res == SUCCESS);
    mu_assert("should have potential for 4 edges", graph->edgeset.set->length == 9);
    mu_assert("graph should not be null", graph != NULL);
    mu_assert("vs should not be null", graph->vertexset.set->head != NULL);
    mu_assert("es should not be null", graph->edgeset.set->head != NULL);
    res = make_graph(NULL, graph);
    mu_assert("make_graph: should fail", res == FAIL);
    res = make_graph(table, NULL);
    mu_assert("make_graph: should fail", res == FAIL);

    return NULL;
}
char *utest_destroy_graph() 
{
    TokenTablePointer table;
    table = init_tokentable();
    make_tokentable("data/instances/K2.dmx", table);
    GraphPointer graph;
    graph = init_graph();
    make_graph(table, graph);
    ssize_t res = destroy_graph(graph);
    mu_assert("should succeed", res == SUCCESS);
    res = destroy_graph(NULL);
    mu_assert("should fail", res == FAIL);
    return NULL;
}

char *test_graph() {
    mu_message(UNIT, "init_graph\n");
    mu_run_utest(utest_init_graph);
    mu_message(UNIT, "make_graph\n");
    mu_run_utest(utest_make_graph);
    mu_message(UNIT, "destroy_graph\n");
    mu_run_utest(utest_destroy_graph);
    return NULL;
}
