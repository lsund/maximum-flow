#include "networkedge.h"

EdgePointer networkedge_get_source_edge(
        const NetworkPointer network,
        const VertexPointer vertex
    )
{
    EdgeCollection edges = network->source_edges;
    size_t i;
    for (i = 0; i < edgecollection_length(edges); i++) {
        EdgePointer edge = edgecollection_get(edges, i);
        if (vertex_equals(edge->second, *vertex)) {
            return edge;
        }
    }
    runtime_error("networkedge_get_source_edge: vertex not adjacent to source");
    return NULL;
}

EdgePointer networkedge_get_sink_edge(
        const NetworkPointer network,
        const VertexPointer vertex
    )
{
    EdgeCollection edges = network->sink_edges;
    size_t i;
    for (i = 0; i < edgecollection_length(edges); i++) {
        EdgePointer edge = edgecollection_get(edges, i);
        if (vertex_equals(edge->first, *vertex)) {
            return edge;
        }
    }
    runtime_error("networkedge_get_sink_edge: vertex not adjacent to sink");
    return NULL;
}

unsigned int networkedge_capacity(
        const NetworkPointer network, 
        const Edge edge
    )
{
    unsigned int index, capacity;
    index = edgecollection_index_of(network->graph.edges, edge);
    if (index > edgecollection_length(network->graph.edges) + 2) {
        runtime_error("networkedge_capacity: index out of bounds");
    }
    capacity = *(network->capacities + index);
    return capacity;
}

unsigned int networkedge_residual_capacity(
        const NetworkPointer network, 
        const Edge edge
    )
{
    unsigned int index, capacity, flow;
    if (networkedge_is_reverse(network, edge)) {
        Edge reverse_edge = edge_swapped(edge);
        index = edgecollection_index_of(network->graph.edges, reverse_edge);
        flow = *(network->flows + index);
        return flow;
    } else {
        index = edgecollection_index_of(network->graph.edges, edge);
        capacity = *(network->capacities + index);
        flow = *(network->flows + index);
        return capacity - flow;
    }
}

unsigned int networkedge_flow(const NetworkPointer network, const Edge edge)
{
    unsigned int index;
    index = edgecollection_index_of(network->graph.edges, edge);
    return *(network->flows + index);
}

bool networkedge_is_reverse(const NetworkPointer network, const Edge edge)
{
    unsigned int key = edge_hash(edge);
    return map_get(network->is_reverse, key) == 1;
}

void networkedge_augment(const NetworkPointer network, const Edge edge, const unsigned int added_flow)
{
    EdgePointer back_edge;
    Edge back_edge_val = edge_swapped(edge);
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
    residual_back_capacity = networkedge_residual_capacity(network, *back_edge);
    if (residual_capacity - added_flow == 0) {
        edgecollection_remove((network->residual_edges + edge.first.label), edge); 
    }
    if (residual_back_capacity == 0) {
        edgecollection_push(*(network->residual_edges + edge.second.label), back_edge); 
    }
    bool is_reverse = edgecollection_contains_edge(network->reverse_edges, edge);
    if (!is_reverse) {
        networkedge_add_flow(network, edge, added_flow);
    } else {
        networkedge_add_flow(network, *back_edge, -added_flow);
    }
}

void networkedge_fill_flow(
        const NetworkPointer network,
        const Edge edge,
        const unsigned int capacity,
        const EdgeType type
    )
{
    int index, flow, increased_flow;
    if (type == FORWARD)
    {
        index = edgecollection_index_of(network->graph.edges, edge);
        flow = *(network->flows + index);
        increased_flow = capacity - flow;
        networkedge_set_flow(network, edge, capacity);
        *(network->excesses + edge.first.label) -= increased_flow;
        *(network->excesses + edge.second.label) += increased_flow;
    } else {
        Edge reverse_edge;
        EdgePointer reverse_edge_p;
        reverse_edge = edge_swapped(edge);
        index        = edgecollection_index_of(
                                network->graph.edges,
                                reverse_edge
                            );
        reverse_edge_p = edgecollection_get_reference(
                                network->graph.edges, 
                                reverse_edge
                            );
        int flow = *(network->flows + index);
        networkedge_set_flow(network, reverse_edge, flow - capacity);
        increased_flow = capacity;
        *(network->excesses + reverse_edge_p->first.label) += increased_flow;
        *(network->excesses + reverse_edge_p->second.label) -= increased_flow;
    }
}


void networkedge_set_flow(
        const NetworkPointer network, 
        const Edge edge, 
        int flow
    )
{
    unsigned int index;
    index = edgecollection_index_of(network->graph.edges, edge);
    if (index > edgecollection_length(network->graph.edges) + 2) {
        runtime_error("networkedge_set_flow: index out of bounds");
    }
    *(network->flows + index) = flow;
}

void networkedge_add_flow(
        NetworkPointer network,
        const Edge edge,
        int added_flow
    )
{
    unsigned int index;
    int flow;
    index = edgecollection_index_of(network->graph.edges, edge);
    flow = networkedge_flow(network, edge);
    if (network->type == PR) {
        unsigned int first_exflow_before, second_exflow_before;
        first_exflow_before = networkvertex_exflow_pr(network, edge.first);
        second_exflow_before = networkvertex_exflow_pr(network, edge.second);

        *(network->flows + index) = flow + added_flow;
        *(network->inflows + edge.second.label) += added_flow;
        *(network->outflows + edge.first.label) += added_flow;

        unsigned int first_exflow, second_exflow;
        first_exflow = networkvertex_exflow_pr(network, edge.first);
        second_exflow = networkvertex_exflow_pr(network, edge.second);
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
        const Edge edge, 
        unsigned int capacity
    )
{
    unsigned int index;
    index = edgecollection_index_of(network->graph.edges, edge);
    if (index > edgecollection_length(network->graph.edges) + 2) {
        runtime_error("networkedge_set_capacity: index out of bounds");
    }
    *(network->capacities + index) = capacity;
}

