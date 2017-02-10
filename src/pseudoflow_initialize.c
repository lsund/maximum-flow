
#include "pseudoflow_initialize.h"

static void initialize_source_sink_vertex(
        const NetworkPointer network, 
        const VertexPointer vertex,
        const Edge edge,
        const VertexType type
    )
{
    unsigned int capacity;
    capacity = networkedge_capacity(network, edge);
    networkedge_augment(network, edge, capacity);
    if (type == SOURCE) {
        *(network->excesses + vertex->label) = capacity;
    } else {
        *(network->excesses + vertex->label) = -capacity;
    }
}

static void initialize_vertex(
        const NetworkPointer network, 
        const VertexPointer vertex,
        const Edge edge,
        const VertexType type
    )
{
    if (type == SOURCE || type == SINK) {
        initialize_source_sink_vertex(network, vertex, edge, type);
    } else {
        *(network->excesses + vertex->label) = 0;
    }
    tree_merge(network->root, vertex);
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
            bool is_source_vertex = vertexcollection_contains_label(
                                            network->source_neighbours, 
                                            vertex->label
                                        );
            bool is_sink_vertex   = vertexcollection_contains_label(
                                            network->sink_neighbours,
                                            vertex->label
                                        );
            EdgePointer edge;
            if (is_source_vertex) {
                edge = networkedge_get_source_edge(network, vertex);
                initialize_vertex(network, vertex, *edge, SOURCE);
            } else if (is_sink_vertex) {
                edge = networkedge_get_sink_edge(network, vertex);
                initialize_vertex(network, vertex, *edge, SINK);
            } else {
                initialize_vertex(network, vertex, edge_make_label(-1, -1), NONE);
            }
        }
    }
}

