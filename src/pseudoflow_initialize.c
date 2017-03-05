
#include "pseudoflow_initialize.h"

static void initialize_source_sink_vertex(
        const VertexPointer vertex,
        const EdgePointer edge,
        const VertexType type
    )
{
    unsigned int capacity;
    capacity = edge_capacity(edge);
    edge_augment(edge, capacity);
    if (type == SOURCE) {
        vertex->excess = capacity;
    } else {
        vertex->excess = -capacity;
    }
}

static void initialize_vertex(
        const NetworkPointer network, 
        const VertexPointer vertex,
        const EdgePointer edge,
        const VertexType type
    )
{
    if (type == SOURCE || type == SINK) {
        initialize_source_sink_vertex(vertex, edge, type);
    } else {
    }
    tree_merge(network->root, vertex);
}

static bool is_neighbour_to(
        const NetworkPointer network,
        const Vertex vertex_a,
        const Vertex vertex_b
    )
{
    EdgeCollection out_edges = network_get_out_edges(network, vertex_a);
    size_t i;
    for (i = 0; i < edgecollection_length(out_edges); i++) {
        EdgePointer edge = edgecollection_get(out_edges, i);
        if (vertex_equals(*edge->second, vertex_b)) {
            return true;
        }
    }
    return false;
}

void pseudoflow_initialize(const NetworkPointer network)
{
    VertexPointer vertex;
    size_t i;
    for (i = 0; i < vertexcollection_length(network->graph.vertices); i++) {
        vertex = vertexcollection_get(network->graph.vertices, i);
        bool is_source = vertex_equals(*vertex, *network->source);
        bool is_sink = vertex_equals(*vertex, *network->sink);
        if (!is_source && !is_sink) {
            bool is_source_vertex = is_neighbour_to(network, *network->source, *vertex);
            bool is_sink_vertex = is_neighbour_to(network, *vertex, *network->sink);
            EdgePointer edge;
            if (is_source_vertex) {
                edge = network_get_out_edge(network, *network->source, *vertex);
                initialize_vertex(network, vertex, edge, SOURCE);
            } else if (is_sink_vertex) {
                edge = network_get_out_edge(network, *vertex, *network->sink);
                initialize_vertex(network, vertex, edge, SINK);
            } else {
                initialize_vertex(network, vertex, NULL, NONE);
            }
        }
    }
}

