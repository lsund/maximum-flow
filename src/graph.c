
#include "graph.h"

GraphPointer graph_make(const VertexSet vertexset, const EdgeSet edgeset)
{
    GraphPointer ret = malloc(sizeof(Graph));
    ret->vertexset = vertexset;
    ret->edgeset = edgeset;
    return ret;
}

Result graph_make_reversed(const Graph graph, GraphPointer reversed)
{
    reversed->vertexset = graph.vertexset;  
    EdgeSet reversed_edgeset = edgeset_init(graph.edgeset.set->length);
    size_t i;
    for (i = 0; i < graph.edgeset.set->length; i++) {
        Edge graph_edge = *edgeset_get(graph.edgeset, i);
        EdgePointer reversed_edge = edge_p_make_edge(edge_swapped(graph_edge));
        edgeset_push(reversed_edgeset, reversed_edge);
    }
    reversed->edgeset = reversed_edgeset;
    return SUCCESS;
}

Result graph_destroy(GraphPointer graph)
{
    if (!graph || !graph->edgeset.set || !graph->vertexset.set) {
        errno = EFAULT;
        return FAIL;
    }
    if (!graph->edgeset.set->head || !graph->vertexset.set->head) {
        errno = EFAULT;
        return FAIL;
    }
    vertexset_destroy(graph->vertexset);
    edgeset_destroy(graph->edgeset);
    free(graph);
    graph = NULL;
    return SUCCESS;
}

