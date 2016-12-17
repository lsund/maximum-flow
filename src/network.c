
#include "network.h"

NetworkPointer network_init()
{
    NetworkPointer ret   = malloc(sizeof(Network));
    ret->graph           = NULL;
    ret->source          = NULL;
    ret->sink            = NULL;
    ret->capacities      = NULL;
    ret->flows           = NULL;
    ret->distance_labels = NULL;
    return ret;
}

Label network_vertex_distance_label(const NetworkPointer network, const VertexPointer vertex)
{
    unsigned int index = vertexcollection_index_of(network->graph->vertices, vertex);
    return *(network->distance_labels + index);
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

unsigned int network_vertex_inflow(const NetworkPointer network, const VertexPointer vertex)
{
    unsigned int inflow;
    inflow = 0;
    size_t i;
    for (i = 0; i < edgecollection_length(network->graph->edges); i++) {
        EdgePointer edge = edgecollection_get(network->graph->edges, i);
        if (vertex_equals(edge->second, vertex)) {
            inflow += network_edge_flow(network, edge);
        }
    }
    return inflow;
}

int network_vertex_exflow(const NetworkPointer network, const VertexPointer vertex)
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
    if (vertex_equals(network->source, vertex) || vertex_equals(network->sink, vertex)) {
        return false;
    }
    return network_vertex_exflow(network, vertex) > 0;
}

VertexPointer network_active_vertex(const NetworkPointer network)
{
    size_t i;
    for (i = 0; i < vertexcollection_length(network->graph->vertices); i++) {
        VertexPointer vertex = vertexcollection_get(network->graph->vertices, i); 
        if (network_vertex_is_active(network, vertex)) {
            return vertex;
        }
    }
    return NULL;
}

EdgePointer network_admissable_edge(const NetworkPointer network, const EdgeCollection edges)
{
    size_t i;
    for (i = 0; i < edgecollection_length(edges); i++) {
        EdgePointer edge = edgecollection_get(edges, i);
        if (network_edge_is_admissable(network, edge)) {
            return edge;
        }
    }
    return NULL;
}

unsigned int network_flow(const NetworkPointer network)
{
    return network_vertex_inflow(network, network->sink);
}

bool network_edge_is_residual(const NetworkPointer network, const EdgePointer edge)
{
    unsigned int edge_flow, edge_capacity, residual_capacity;
    if (network_edge_is_reverse(network, edge)) {
        Edge reverse_edge = edge_swapped(*edge);
        edge_flow = network_edge_flow(network, &reverse_edge);
        residual_capacity = edge_flow;
    } else {
        edge_flow = network_edge_flow(network, edge);
        edge_capacity = network_edge_capacity(network, edge);
        residual_capacity = edge_capacity - edge_flow;
    }
    return residual_capacity > 0;
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

bool network_edge_is_reverse(const NetworkPointer network, const EdgePointer edge)
{
    size_t i;
    for (i = 0; i < edgecollection_length(network->graph->edges); i++) {
        EdgePointer current = edgecollection_get(network->graph->edges, i);
        if (edge_equals_reverse(edge, current)) {
            return true;
        } else if (edge_equals(edge, current)) {
            return false;
        }
    }
    runtime_error("network_edge_is_reverse: the edge is neither forward or backward");
    return false;
}

void network_augment_edge(const NetworkPointer network, const EdgePointer edge, const unsigned int added_flow)
{
    int flow = network_edge_flow(network, edge);
    if (flow + added_flow > network_edge_capacity(network, edge)) {
        runtime_error("network_augment_edge: flow exeeds capacity");
    }
    network_set_edge_flow(network, edge, flow + added_flow);
}

void network_set_edge_flow(
        const NetworkPointer network, 
        const EdgePointer edge, 
        int flow
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

void network_vertex_set_distance_label(const NetworkPointer network, const VertexPointer vertex, const unsigned int label)
{
    if (!vertex || !network) {
        runtime_error("network_vertex_set_distance_label: null argument");
    }
    unsigned int index = vertexcollection_index_of(network->graph->vertices, vertex);
    *(network->distance_labels + index) = label; 
}

/* void network_vertex_set_flow(const NetworkPointer network, const VertexPointer vertex) */
/* { */
/*     // TODO */
/*     return; */
/* } */


