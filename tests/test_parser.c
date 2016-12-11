
#include <stdlib.h>
#include "test.h"

char *utest_parse() {
    TokenTablePointer table = init_tokentable();
    make_tokentable("data/graphs/K2.dmx", table);
    GraphPointer graph = init_graph();
    make_graph(table, graph);
    Result res = parse(table, graph);
    mu_assert("parse: should succeed", res == SUCCESS);
    
    *(*(table->tokens + 1) + 1) = NULL;
    res = parse(table, graph);
    mu_assert("corrupted table, should fail", res == FAIL);
    graph = NULL;
    res = parse(table, graph);
    mu_assert("should fail with null argument", res == FAIL);
    graph = init_graph();
    table = NULL;
    res = parse(table, graph);
    mu_assert("should fail with null argument", res == FAIL);
    destroy_graph(graph);
    destroy_tokentable(table);

    table = init_tokentable();
    make_tokentable("data/graphs/K2.dmx", table);
    graph = init_graph();
    make_graph(table, graph);
    res = parse(table, graph);

    return NULL;
}

char *utest_parse_vertices()
{
    VertexSet vertexset = init_vertexset(2);
    TokenTablePointer table = init_tokentable();
    make_tokentable("data/graphs/K2.dmx", table);
    VertexPointer flat_edges = malloc(4 * sizeof(Vertex));
    parse_edges(table, init_edgeset(2), flat_edges, vertexset);
    parse_vertices(vertexset);
    mu_assert("should have 2 vertices", vertexset.set->length == 3); 
    return NULL;
}

char *test_parser() {
    mu_message(UNIT, "parse_vertices\n");
    mu_run_utest(utest_parse_vertices);
    mu_message(UNIT, "parse\n");
    mu_run_utest(utest_parse);
    return NULL;
}
