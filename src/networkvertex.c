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
    return networkvertex_exflow(network, vertex) > 0;
}

Result networkvertex_active(const NetworkPointer network, VertexPointer vertex)
{
    VertexPointer first_active = vertexcollection_get_first(network->active_vertices);
    if (first_active) {
        *vertex = *first_active;
        return SUCCESS;
    } else {
        return FAIL;
    }
}

void networkvertex_set_distance_label(const NetworkPointer network, const Vertex vertex, const unsigned int label)
{
    if (!network) {
        runtime_error("networkvertex_set_distance_label: null argument");
    }
    unsigned int index = vertexcollection_index_of(network->graph.vertices, vertex);
    *(network->distance_labels + index) = label; 
}

