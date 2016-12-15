
#include "graph.h"

GraphPointer graph_make(const VertexCollection vertexcollection, const EdgeCollection edgecollection)
{
    GraphPointer ret = malloc(sizeof(Graph));
    ret->vertices = vertexcollection;
    ret->edges = edgecollection;
    return ret;
}

VertexCollection graph_neighbours_of(const GraphPointer graph, const VertexPointer vertex)
{
    VertexCollection ret = vertexcollection_init(vertexcollection_length(graph->vertices));
    size_t i;
    for (i = 0; i < edgecollection_length(graph->edges); i++) {
        EdgePointer edge = edgecollection_get(graph->edges, i);
        if (edge_incident_with(edge, vertex)) {
            vertexcollection_push(ret, edge_get_adjacent(edge, vertex));
        }
    }
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

