
#include <stdlib.h>
#include "test.h"

char *utest_graph_init() 
{
    return NULL;
}

char *utest_graph_make() 
{
    TokenTablePointer table;
    table = init_tokentable();
    make_tokentable("data/graphs/K2.dmx", table);
    GraphPointer graph;
    graph = graph_init();
    Result res = graph_make(table, graph);
    mu_assert("graph_make: should succed", res == SUCCESS);
    mu_assert("should have potential for 4 edges", graph->edgeset.set->length == 9);
    mu_assert("graph should not be null", graph != NULL);
    mu_assert("vs should not be null", graph->vertexset.set->head != NULL);
    mu_assert("es should not be null", graph->edgeset.set->head != NULL);
    VertexPointer a = vertexset_get(graph->vertexset, 0);
    VertexPointer b = vertexset_get(graph->vertexset, 1);
    mu_assert("should exist", a && b); 
    mu_assert("should have 1 neighbour", a->neighbors.nelements == 1);
    mu_assert("should have 1 neighbour", b->neighbors.nelements == 1);

    res = graph_make(NULL, graph);
    mu_assert("graph_make: should fail", res == FAIL);
    res = graph_make(table, NULL);
    mu_assert("graph_make: should fail", res == FAIL);

    return NULL;
}
char *utest_graph_destroy() 
{
    TokenTablePointer table;
    table = init_tokentable();
    make_tokentable("data/graphs/K2.dmx", table);
    GraphPointer graph;
    graph = graph_init();
    graph_make(table, graph);
    ssize_t res = graph_destroy(graph);
    mu_assert("should succeed", res == SUCCESS);
    res = graph_destroy(NULL);
    mu_assert("should fail", res == FAIL);
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
