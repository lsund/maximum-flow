
#include <stdlib.h>
#include "test.h"

char *utest_graph_make() 
{
    VertexCollection vertexcollection = vertexcollection_init(2);
    EdgeCollection edgecollection = edgecollection_init(1);
    vertexcollection_push(vertexcollection, vertex_p_make(0));
    vertexcollection_push(vertexcollection, vertex_p_make(1));
    edgecollection_push(edgecollection, edge_p_make_label(0, 1));
    GraphPointer graph = graph_make(vertexcollection, edgecollection);
    mu_assert("should not be null", vertexcollection_get(graph->vertices, 0));
    mu_assert("should not be null", edgecollection_get(graph->edges, 0));
    mu_assert("should be 1", edgecollection_get(graph->edges, 0)->first->label == 0);
    return NULL;
}

char *test_graph() {
    mu_message(UNIT, "graph_make\n");
    mu_run_utest(utest_graph_make);
    return NULL;
}
