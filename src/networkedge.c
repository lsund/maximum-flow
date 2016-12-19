#include "networkedge.h"

unsigned int networkedge_capacity(const NetworkPointer network, const EdgePointer edge)
{
    unsigned int index, capacity;
    index = edgecollection_index_of(network->graph.edges, edge);
    capacity = *(network->capacities + index);
    return capacity;
}

unsigned int networkedge_residual_capacity(const NetworkPointer network, const EdgePointer edge)
{
    unsigned int index, capacity, flow;
    if (networkedge_is_reverse(network, edge)) {
        Edge reverse_edge = edge_swapped(*edge);
        index = edgecollection_index_of(network->graph.edges, &reverse_edge);
        flow = *(network->flows + index);
        return flow;
    } else {
        index = edgecollection_index_of(network->graph.edges, edge);
        capacity = *(network->capacities + index);
        flow = *(network->flows + index);
        return capacity - flow;
    }
}

unsigned int networkedge_flow(const NetworkPointer network, const EdgePointer edge)
{
    unsigned int index = edgecollection_index_of(network->graph.edges, edge);
    return *(network->flows + index);
}

static bool networkedge_is_admissable(
        const NetworkPointer network, 
        const EdgePointer edge, 
        GraphPointer residual_graph
    )
{
    unsigned int label_first, label_second;
    label_first = networkvertex_distance_label(network, edge->first);
    label_second = networkvertex_distance_label(network, edge->second);
    bool cond_a = label_first == label_second + 1;
    network_residual_graph(network, residual_graph);
    bool cond_b = edgecollection_contains_edge(residual_graph->edges, edge);
    return cond_a && cond_b;
}

EdgePointer networkedge_admissable(
        const NetworkPointer network, 
        const EdgeCollection edges, 
        GraphPointer residual_graph
    )
{
    size_t i;
    for (i = 0; i < edgecollection_length(edges); i++) {
        EdgePointer edge = edgecollection_get(edges, i);
        if (networkedge_is_admissable(network, edge, residual_graph)) {
            return edge;
        } 
    }
    return NULL;
}

bool networkedge_is_reverse(const NetworkPointer network, const EdgePointer edge)
{
    size_t i;
    for (i = 0; i < edgecollection_length(network->graph.edges); i++) {
        EdgePointer current = edgecollection_get(network->graph.edges, i);
        if (edge_equals_reverse(edge, current)) {
            return true;
        } else if (edge_equals(edge, current)) {
            return false;
        }
    }
    runtime_error("networkedge_is_reverse: the edge is neither forward or backward");
    return false;
}

EdgePointer networkedge_reverse(const NetworkPointer network, const EdgePointer edge)
{
    size_t i;
    for (i = 0; i < edgecollection_length(network->graph.edges); i++) {
        EdgePointer current = edgecollection_get(network->graph.edges, i);
        if (edge_equals_reverse(edge, current)) {
            return current;
        } else if (edge_equals(edge, current)) {
            return NULL;
        }
    }
    runtime_error("networkedge_is_reverse: the edge is neither forward or backward");
    return NULL;
}

void networkedge_augment(const NetworkPointer network, const EdgePointer edge, const unsigned int added_flow)
{
    EdgePointer reverse_edge = networkedge_reverse(network, edge);
    if (!reverse_edge) {
        int flow = networkedge_flow(network, edge);
        networkedge_set_flow(network, edge, flow + added_flow);
    } else {
        int flow = networkedge_flow(network, reverse_edge);
        networkedge_set_flow(network, reverse_edge, flow - added_flow);
    }
}

void networkedge_set_flow(
        const NetworkPointer network, 
        const EdgePointer edge, 
        int flow
    )
{
    unsigned int index = edgecollection_index_of(network->graph.edges, edge);
    *(network->flows + index) = flow;
}

void networkedge_set_capacity(
        const NetworkPointer network, 
        const EdgePointer edge, 
        unsigned int capacity
    )
{
    unsigned int index = edgecollection_index_of(network->graph.edges, edge);
    *(network->capacities + index) = capacity;
}

