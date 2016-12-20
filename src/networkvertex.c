#include "networkvertex.h"

Label networkvertex_distance_label(const NetworkPointer network, const Vertex vertex)
{
    unsigned int index = vertexcollection_index_of(network->graph.vertices, vertex);
    return *(network->distance_labels + index);
}

unsigned int networkvertex_inflow(const NetworkPointer network, const Vertex vertex)
{
    unsigned int inflow;
    inflow = 0;
    size_t i;
    for (i = 0; i < edgecollection_length(network->graph.edges); i++) {
        EdgePointer edge = edgecollection_get(network->graph.edges, i);
        if (vertex_equals(edge->second, vertex)) {
            inflow += networkedge_flow(network, edge);
        }
    }
    return inflow;
}

int networkvertex_exflow(const NetworkPointer network, const Vertex vertex)
{
    unsigned int inflow, outflow;
    inflow = 0;
    outflow = 0;
    size_t i;
    EdgeCollection in_edges = *(network->in_edges + vertex.label);
    EdgeCollection out_edges = *(network->out_edges + vertex.label);
    for (i = 0; i < edgecollection_length(in_edges); i++) {
            EdgePointer edge = edgecollection_get(*(network->in_edges + vertex.label), i);
            inflow += networkedge_flow(network, edge);
    }
    for (i = 0; i < edgecollection_length(out_edges); i++) {
            EdgePointer edge = edgecollection_get(*(network->out_edges + vertex.label), i);
            outflow += networkedge_flow(network, edge);
    }
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

