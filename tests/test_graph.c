
#include <stdlib.h>
#include "test.h"

char *utest_graph_make() 
{
    VertexSet vertexset = vertexset_init(2);
    EdgeSet edgeset = edgeset_init(1);
    vertexset_push(vertexset, vertex_p_make(0));
    vertexset_push(vertexset, vertex_p_make(1));
    edgeset_push(edgeset, edge_p_make_label(0, 1));
    GraphPointer graph = graph_make(vertexset, edgeset);
    mu_assert("should not be null", vertexset_get(graph->vertexset, 0));
    mu_assert("should not be null", edgeset_get(graph->edgeset, 0));
    mu_assert("should be 1", edgeset_get(graph->edgeset, 0)->first->label == 0);
    return NULL;
}

char *test_graph() {
    mu_message(UNIT, "graph_make\n");
    mu_run_utest(utest_graph_make);
    return NULL;
}
