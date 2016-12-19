#include "networkvertex.h"

Label networkvertex_distance_label(const NetworkPointer network, const VertexPointer vertex)
{
    unsigned int index = vertexcollection_index_of(network->graph->vertices, vertex);
    return *(network->distance_labels + index);
}

unsigned int networkvertex_inflow(const NetworkPointer network, const VertexPointer vertex)
{
    unsigned int inflow;
    inflow = 0;
    size_t i;
    for (i = 0; i < edgecollection_length(network->graph->edges); i++) {
        EdgePointer edge = edgecollection_get(network->graph->edges, i);
        if (vertex_equals(edge->second, vertex)) {
            inflow += networkedge_flow(network, edge);
        }
    }
    return inflow;
}

int networkvertex_exflow(const NetworkPointer network, const VertexPointer vertex)
{
    unsigned int inflow, outflow;
    inflow = 0;
    outflow = 0;
    size_t i;
    for (i = 0; i < edgecollection_length(network->graph->edges); i++) {
        EdgePointer edge = edgecollection_get(network->graph->edges, i);
        if (vertex_equals(edge->first, vertex)) {
            outflow += networkedge_flow(network, edge);
        } else if (vertex_equals(edge->second, vertex)) {
            inflow += networkedge_flow(network, edge);
        }
    }
    return inflow - outflow;
}

bool networkvertex_is_active(const NetworkPointer network, const VertexPointer vertex)
{
    if (vertex_equals(network->source, vertex) || vertex_equals(network->sink, vertex)) {
        return false;
    }
    return networkvertex_exflow(network, vertex) > 0;
}

VertexPointer network_active_vertex(const NetworkPointer network)
{
    size_t i;
    for (i = 0; i < vertexcollection_length(network->graph->vertices); i++) {
        VertexPointer vertex = vertexcollection_get(network->graph->vertices, i); 
        if (networkvertex_is_active(network, vertex)) {
            return vertex;
        }
    }
    return NULL;
}

void networkvertex_set_distance_label(const NetworkPointer network, const VertexPointer vertex, const unsigned int label)
{
    if (!vertex || !network) {
        runtime_error("networkvertex_set_distance_label: null argument");
    }
    unsigned int index = vertexcollection_index_of(network->graph->vertices, vertex);
    *(network->distance_labels + index) = label; 
}

