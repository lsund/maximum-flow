
#include "graph.h"

GraphPointer graph_make(const VertexCollection vertexcollection, const EdgeCollection edgecollection)
{
    GraphPointer ret = malloc(sizeof(Graph));
    ret->vertices = vertexcollection;
    ret->edges = edgecollection;
    return ret;
}

VertexCollection graph_neighbors_of(const GraphPointer graph, const VertexPointer vertex)
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

EdgeCollection graph_incident_with(const GraphPointer graph, const VertexPointer vertex)
{
    EdgeCollection ret = edgecollection_init(edgecollection_length(graph->edges));
    size_t i;
    for (i = 0; i < edgecollection_length(graph->edges); i++) {
        EdgePointer edge = edgecollection_get(graph->edges, i);
        if (edge_incident_with(edge, vertex)) {
            edgecollection_push(ret, edge);
        }
    }
    return ret;
}

EdgeCollection graph_out_edges_from(const GraphPointer graph, const VertexPointer vertex)
{
    EdgeCollection ret = edgecollection_init(edgecollection_length(graph->edges));
    size_t i;
    for (i = 0; i < edgecollection_length(graph->edges); i++) {
        EdgePointer edge = edgecollection_get(graph->edges, i);
        if (vertex_equals(edge->first, vertex)) {
            edgecollection_push(ret, edge);
        }
    }
    return ret;
}

Result graph_destroy(GraphPointer graph)
{
    if (!graph || !graph->edges.members || !graph->vertices.members) {
        return FAIL;
    }
    if (!graph->edges.members->head || !graph->vertices.members->head) {
        return FAIL;
    }
    vertexcollection_destroy(graph->vertices);
    edgecollection_destroy(graph->edges);
    free(graph);
    graph = NULL;
    return SUCCESS;
}

