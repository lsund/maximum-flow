#include "networkedge.h"

unsigned int networkedge_capacity(
        const NetworkPointer network, 
        const EdgePointer edge
    )
{
    unsigned int index, capacity;
    index = edgecollection_index_of(network->graph.edges, *edge);
    capacity = *(network->capacities + index);
    return capacity;
}

unsigned int networkedge_residual_capacity(
        const NetworkPointer network, 
        const EdgePointer edge
    )
{
    unsigned int index, capacity, flow;
    /* if (network->type == PS && vertex_equals(edge->second, *network->root)) { */
    /*     index = edgecollection_index_of(network->graph.edges, *edge); */
    /* } */
    if (networkedge_is_reverse(network, edge)) {
        Edge reverse_edge = edge_swapped(*edge);
        index = edgecollection_index_of(network->graph.edges, reverse_edge);
        flow = *(network->flows + index);
        return flow;
    } else {
        index = edgecollection_index_of(network->graph.edges, *edge);
        capacity = *(network->capacities + index);
        flow = *(network->flows + index);
        return capacity - flow;
    }
}

unsigned int networkedge_flow(const NetworkPointer network, const EdgePointer edge)
{
    unsigned int index;
    index = edgecollection_index_of(network->graph.edges, *edge);
    return *(network->flows + index);
}

bool networkedge_is_reverse(const NetworkPointer network, const EdgePointer edge)
{
    unsigned int key = edge_p_hash(edge);
    return map_get(network->is_reverse, key) == 1;
}

void networkedge_augment(const NetworkPointer network, const EdgePointer edge, const unsigned int added_flow)
{
    EdgePointer back_edge;
    Edge back_edge_val = edge_swapped(*edge);
    int index;
    index = edgecollection_index_of(network->reverse_edges, back_edge_val);
    if (index == -1) {
        index = edgecollection_index_of(network->graph.edges, back_edge_val);
        back_edge = edgecollection_get(network->graph.edges, index);
    } else {
        back_edge = edgecollection_get(network->reverse_edges, index);
    }
    
    unsigned int residual_capacity, residual_back_capacity;
    residual_capacity = networkedge_residual_capacity(network, edge);
    residual_back_capacity = networkedge_residual_capacity(network, back_edge);
    if (residual_capacity - added_flow == 0) {
        edgecollection_remove((network->residual_edges + edge->first.label), edge); 
    }
    if (residual_back_capacity == 0) {
        edgecollection_push(*(network->residual_edges + edge->second.label), back_edge); 
    }
    bool is_reverse = edgecollection_contains_edge(network->reverse_edges, edge);
    if (!is_reverse) {
        networkedge_add_flow(network, edge, added_flow);
    } else {
        networkedge_add_flow(network, back_edge, -added_flow);
    }
}

void networkedge_set_flow(
        const NetworkPointer network, 
        const EdgePointer edge, 
        int flow
    )
{
    unsigned int index;
    index = edgecollection_index_of(network->graph.edges, *edge);
    *(network->flows + index) = flow;
}

void networkedge_add_flow(
        NetworkPointer network,
        const EdgePointer edge,
        int added_flow
    )
{
    unsigned int index;
    int flow;
    index = edgecollection_index_of(network->graph.edges, *edge);
    flow = networkedge_flow(network, edge);
    if (network->type == PR) {
        unsigned int first_exflow, second_exflow;
        unsigned int first_exflow_before, second_exflow_before;
        first_exflow_before = networkvertex_exflow(network, edge->first);
        second_exflow_before = networkvertex_exflow(network, edge->second);

        *(network->flows + index) = flow + added_flow;
        *(network->inflows + edge->second.label) += added_flow;
        *(network->outflows + edge->first.label) += added_flow;

        first_exflow = networkvertex_exflow(network, edge->first);
        second_exflow = networkvertex_exflow(network, edge->second);
        activate_vertices(
                network,
                edge,
                first_exflow_before, 
                second_exflow_before, 
                first_exflow, 
                second_exflow
            );
    } else if (network->type == PS) {
        *(network->flows + index) = flow + added_flow;
    }
}

void networkedge_set_capacity(
        const NetworkPointer network, 
        const EdgePointer edge, 
        unsigned int capacity
    )
{
    unsigned int index;
    index = edgecollection_index_of(network->graph.edges, *edge);
    *(network->capacities + index) = capacity;
}

