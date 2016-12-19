
#include "graph.h"

Graph graph_init()
{
    Graph ret;
    ret.vertices = vertexcollection_init(ARRAY_MIN_SIZE);
    ret.edges = edgecollection_init(ARRAY_MIN_SIZE);
    return ret;
}

Graph graph_make(const VertexCollection vertexcollection, const EdgeCollection edgecollection)
{
    Graph ret;
    ret.vertices = vertexcollection;
    ret.edges = edgecollection;
    return ret;
}

void graph_reset(Graph graph)
{
    vertexcollection_reset(graph.vertices);
    edgecollection_reset(graph.edges);
}

VertexCollection graph_neighbors_of(const Graph graph, const VertexPointer vertex)
{
    VertexCollection ret = vertexcollection_init(vertexcollection_length(graph.vertices));
    size_t i;
    for (i = 0; i < edgecollection_length(graph.edges); i++) {
        EdgePointer edge = edgecollection_get(graph.edges, i);
        if (edge_incident_with(edge, vertex)) {
            vertexcollection_push(ret, edge_get_adjacent(edge, vertex));
        }
    }
    return ret;
}

void graph_out_edges_from(
        const Graph graph, 
        const VertexPointer vertex,
        EdgeCollectionPointer ret)
{
    edgecollection_reset(*ret);
    size_t i;
    for (i = 0; i < edgecollection_length(graph.edges); i++) {
        EdgePointer edge = edgecollection_get(graph.edges, i);
        if (vertex_equals(edge->first, vertex)) {
            edgecollection_push(*ret, edge);
        }
    }
}

Result graph_destroy(Graph graph)
{
    vertexcollection_destroy(graph.vertices);
    edgecollection_destroy(graph.edges);
    return SUCCESS;
}

