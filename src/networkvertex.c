#include "networkvertex.h"

Label networkvertex_distance_label(const NetworkPointer network, const Vertex vertex)
{
    unsigned int index = vertexcollection_index_of(network->graph.vertices, vertex);
    return *(network->distance_labels + index);
}

unsigned int networkvertex_inflow(const NetworkPointer network, const Vertex vertex)
{
    return *(network->inflows + vertex.label);
}

int networkvertex_exflow(const NetworkPointer network, const Vertex vertex)
{
    unsigned int inflow, outflow;
    inflow = *(network->inflows + vertex.label);
    outflow = *(network->outflows + vertex.label);
    return inflow - outflow;
}

bool networkvertex_is_active(const NetworkPointer network, const Vertex vertex)
{
    if (vertex_equals(network->source, vertex) || vertex_equals(network->sink, vertex)) {
        return false;
    }
    return networkvertex_exflow(network, vertex) > 0;
}

Result networkvertex_active(const NetworkPointer network, VertexPointer vertex)
{
    size_t i;
    for (i = 0; i < vertexcollection_length(network->graph.vertices); i++) {
        VertexPointer current = vertexcollection_get(network->graph.vertices, i); 
        if (networkvertex_is_active(network, *current)) {
            *vertex = *current;
            return SUCCESS;
        }
    }
    return FAIL;
}

void networkvertex_set_distance_label(const NetworkPointer network, const Vertex vertex, const unsigned int label)
{
    if (!network) {
        runtime_error("networkvertex_set_distance_label: null argument");
    }
    unsigned int index = vertexcollection_index_of(network->graph.vertices, vertex);
    *(network->distance_labels + index) = label; 
}

