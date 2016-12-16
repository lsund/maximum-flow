
#include "network.h"

NetworkPointer network_init()
{
    // TODO
    NetworkPointer ret   = malloc(sizeof(Network));
    ret->graph           = NULL;
    ret->source          = NULL;
    ret->sink            = NULL;
    ret->capacities      = NULL;
    ret->flows           = NULL;
    ret->distance_labels = NULL;
    return ret;
}

unsigned int network_edge_capacity(const NetworkPointer network, const EdgePointer edge)
{
    unsigned int index = edgecollection_index_of(network->graph->edges, edge);
    return *(network->capacities + index);
}

unsigned int network_edge_flow(const NetworkPointer network, const EdgePointer edge)
{
    unsigned int index = edgecollection_index_of(network->graph->edges, edge);
    return *(network->flows + index);
}

unsigned int network_vertex_exflow(const NetworkPointer network, const VertexPointer vertex)
{
    unsigned int inflow, outflow;
    inflow = 0;
    outflow = 0;
    size_t i;
    for (i = 0; i < edgecollection_length(network->graph->edges); i++) {
        EdgePointer edge = edgecollection_get(network->graph->edges, i);
        if (vertex_equals(edge->first, vertex)) {
            outflow += network_edge_flow(network, edge);
        } else if (vertex_equals(edge->second, vertex)) {
            inflow += network_edge_flow(network, edge);
        }
    }
    return inflow - outflow;
}

bool network_vertex_is_active(const NetworkPointer network, const VertexPointer vertex)
{
    return network_vertex_exflow(network, vertex) > 0;
}

VertexPointer network_active_vertex(const NetworkPointer network)
{
    size_t i;
    for (i = 0; i < vertexcollection_length(network->graph->vertices); i++) {
        VertexPointer vertex = vertexcollection_get(network->graph->vertices, 0); 
        if (network_vertex_is_active(network, vertex)) {
            return vertex;
        }
    }
    return NULL;
}

bool network_edge_is_residual(const NetworkPointer network, const EdgePointer edge)
{
    // TODO
    return true;
}

void network_vertex_set_flow(const NetworkPointer network, const VertexPointer vertex)
{
    // TODO
    return;
}

bool network_edge_is_admissable(const NetworkPointer network, const EdgePointer edge)
{
    unsigned int label_first, label_second;
    label_first = network_vertex_distance_label(network, edge->first);
    label_second = network_vertex_distance_label(network, edge->second);
    bool cond_a = label_first == label_second + 1;
    bool cond_b = network_edge_is_residual(network, edge);
    return cond_a && cond_b;
}

Label network_vertex_distance_label(const NetworkPointer network, const VertexPointer vertex)
{
    // TODO
    return 0;
}

void network_set_edge_flow(
        const NetworkPointer network, 
        const EdgePointer edge, 
        unsigned int flow
    )
{
    unsigned int index = edgecollection_index_of(network->graph->edges, edge);
    *(network->flows + index) = flow;
}

void network_set_edge_capacity(
        const NetworkPointer network, 
        const EdgePointer edge, 
        unsigned int capacity
    )
{
    unsigned int index = edgecollection_index_of(network->graph->edges, edge);
    *(network->capacities + index) = capacity;
}

bool network_edge_is_reverse(const NetworkPointer network, const EdgePointer edge)
{
    // TODO
    return 0;
}


