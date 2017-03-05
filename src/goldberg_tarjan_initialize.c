
#include "goldberg_tarjan_initialize.h"

void goldberg_tarjan_initialize(NetworkPointer network)
{
    EdgePointer edge;
    unsigned int capacity;
    size_t i;
    for (i = 0; i < edgecollection_length(network->graph.edges); i++) {
        edge = edgecollection_get(network->graph.edges, i);
        if (vertex_equals(*edge->first, *network->source)) {
            capacity = edge_capacity(edge);
            edge_augment(edge, capacity);
        } 
    }
    size_t n_vertices = vertexcollection_length(network->graph.vertices);
    vertex_set_distance_label(network->source, n_vertices);
}

