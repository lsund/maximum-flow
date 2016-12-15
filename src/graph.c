
#include "graph.h"

GraphPointer graph_make(const VertexSet vertexset, const EdgeSet edgeset)
{
    GraphPointer ret = malloc(sizeof(Graph));
    ret->vertexset = vertexset;
    ret->edgeset = edgeset;
    return ret;
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

