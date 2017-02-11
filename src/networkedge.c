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

bool networkedge_is_reverse(const NetworkPointer network, const EdgePointer edge)
{
    unsigned int key = edge_hash(*edge);
    return map_get(network->is_reverse, key) == 1;
}

void networkedge_augment(const NetworkPointer network, const EdgePointer edge, const unsigned int added_flow)
{
    EdgePointer reverse_edge;
    reverse_edge = edge->reverse;
    
    unsigned int residual_capacity, residual_back_capacity;
    residual_capacity = edge_residual_capacity(edge);
    residual_back_capacity = edge_residual_capacity(reverse_edge);
    if (residual_capacity - added_flow == 0) {
        edgecollection_remove((network->residual_edges + edge->first.label), edge); 
    }
    if (residual_back_capacity == 0) {
        edgecollection_push(*(network->residual_edges + edge->second.label), reverse_edge); 
    }
    if (!edge->is_reverse) {
        networkedge_add_flow(network, edge, added_flow);
    } else {
        networkedge_add_flow(network, reverse_edge, -added_flow);
    }
}

void networkedge_fill_flow(
        const NetworkPointer network,
        const EdgePointer edge,
        const unsigned int capacity,
        const EdgeType type
    )
{
    int flow, increased_flow;
    if (type == FORWARD)
    {
        flow = edge_flow(edge);
        increased_flow = capacity - flow;
        edge_set_flow(edge, capacity);
        *(network->excesses + edge->first.label) -= increased_flow;
        *(network->excesses + edge->second.label) += increased_flow;
    } else {
        EdgePointer reverse_edge_p;
        reverse_edge_p = edge->reverse;
        int flow = edge_flow(reverse_edge_p);
        edge_set_flow(reverse_edge_p, flow - capacity);
        increased_flow = capacity;
        *(network->excesses + reverse_edge_p->first.label) += increased_flow;
        *(network->excesses + reverse_edge_p->second.label) -= increased_flow;
    }
}

void networkedge_add_flow(
        NetworkPointer network,
        const EdgePointer edge,
        int added_flow
    )
{
    int flow;
    flow = edge_flow(edge);
    if (network->type == PR) {
        unsigned int first_exflow_before, second_exflow_before;
        first_exflow_before = networkvertex_exflow_pr(network, edge->first);
        second_exflow_before = networkvertex_exflow_pr(network, edge->second);
        edge_set_flow(edge, flow + added_flow);
        *(network->inflows + edge->second.label) += added_flow;
        *(network->outflows + edge->first.label) += added_flow;

        unsigned int first_exflow, second_exflow;
        first_exflow = networkvertex_exflow_pr(network, edge->first);
        second_exflow = networkvertex_exflow_pr(network, edge->second);
        activate_vertices(
                network,
                *edge,
                first_exflow_before, 
                second_exflow_before, 
                first_exflow, 
                second_exflow
            );
    } else if (network->type == PS) {
        edge_set_flow(edge, flow + added_flow);
    }
}

