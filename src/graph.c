
#include "graph.h"

GraphPointer graph_make(const VertexCollection vertexcollection, const EdgeCollection edgecollection)
{
    GraphPointer ret = malloc(sizeof(Graph));
    ret->vertices = vertexcollection;
    ret->edges = edgecollection;
    return ret;
}

Result graph_destroy(GraphPointer graph)
{
    if (!graph || !graph->edges.members || !graph->vertices.members) {
        errno = EFAULT;
        return FAIL;
    }
    if (!graph->edges.members->head || !graph->vertices.members->head) {
        errno = EFAULT;
        return FAIL;
    }
    vertexcollection_destroy(graph->vertices);
    edgecollection_destroy(graph->edges);
    free(graph);
    graph = NULL;
    return SUCCESS;
}

