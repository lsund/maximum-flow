#include "networkedge.h"

unsigned int networkedge_capacity(const NetworkPointer network, const EdgePointer edge)
{
    unsigned int index, capacity;
    index = edgecollection_index_of(network->graph.edges, edge);
    capacity = *(network->capacities + index);
    return capacity;
}

unsigned int networkedge_residual_capacity(
        const NetworkPointer network, 
        const EdgePointer edge
    )
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
        const EdgePointer edge
    )
{
    unsigned int label_first, label_second;
    label_first = networkvertex_distance_label(network, edge->first);
    label_second = networkvertex_distance_label(network, edge->second);
    bool cond_a = label_first == label_second + 1;
    return cond_a;
}

EdgePointer networkedge_admissable(
        const NetworkPointer network, 
        const Vertex active
    )
{
    EdgeCollection edges = *(network->residual_edges + active.label);
    size_t i;
    for (i = 0; i < edgecollection_length(edges); i++) {
        EdgePointer edge = edgecollection_get(edges, i);
        if (networkedge_is_admissable(network, edge)) {
            return edge;
        } 
    }
    return NULL;
}

bool networkedge_is_reverse(const NetworkPointer network, const EdgePointer edge)
{
    unsigned int key = edge_hash(edge);
    return map_get(network->is_reverse, key) == 1;
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
    EdgePointer back_edge;
    Edge back_edge_val = edge_swapped(*edge);
    int index;
    index = edgecollection_index_of(network->reverse_edges, &back_edge_val);
    if (index == -1) {
        index = edgecollection_index_of(network->graph.edges, &back_edge_val);
        back_edge = edgecollection_get(network->graph.edges, index);
    } else {
        back_edge = edgecollection_get(network->reverse_edges, index);
    }

    unsigned int residual_capacity = networkedge_residual_capacity(network, edge);
    unsigned int residual_back_capacity = networkedge_residual_capacity(network, back_edge);
    if (residual_capacity - added_flow == 0) {
        edgecollection_remove((network->residual_edges + edge->first.label), edge); 
    }
    if (residual_back_capacity == 0) {
        edgecollection_push(*(network->residual_edges + edge->second.label), back_edge); 
    }
    EdgePointer reverse_edge = networkedge_reverse(network, edge);
    if (!reverse_edge) {
        networkedge_add_flow(network, edge, added_flow);
    } else {
        networkedge_add_flow(network, reverse_edge, -added_flow);
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

void networkedge_add_flow(
        const NetworkPointer network, 
        const EdgePointer edge, 
        int added_flow
    )
{
    int flow = networkedge_flow(network, edge);
    unsigned int index = edgecollection_index_of(network->graph.edges, edge);
    *(network->flows + index) = flow + added_flow;
    *(network->inflows + edge->second.label) += added_flow;
    *(network->outflows + edge->first.label) += added_flow;
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

