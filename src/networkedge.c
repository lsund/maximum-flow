#include "networkedge.h"

static void activate_vertices(
        const NetworkPointer network, 
        const EdgePointer edge, 
        const unsigned int first_exflow_before,
        const unsigned int second_exflow_before,
        const unsigned int first_exflow,
        const unsigned int second_exflow)
{
    if (first_exflow_before > 0 && first_exflow == 0) {
        vertexcollection_remove(&network->active_vertices, edge->first);
    }
    if (second_exflow_before > 0 && second_exflow == 0) {
        vertexcollection_remove(&network->active_vertices, edge->second);
    }
    VertexCollection vertices= network->graph.vertices;
    if (first_exflow_before == 0 && first_exflow > 0) {
        if (edge->first.label != network->source.label) {
            unsigned int index = vertexcollection_index_of(vertices, edge->first);
            VertexPointer vertex = vertexcollection_get(vertices, index);
            vertexcollection_push(network->active_vertices, vertex);
        }
    }
    if (second_exflow_before == 0 && second_exflow > 0) {
        if (edge->second.label != network->sink.label) {
            unsigned int index = vertexcollection_index_of(vertices, edge->second);
            VertexPointer vertex = vertexcollection_get(vertices, index);
            vertexcollection_push(network->active_vertices, vertex);
        }
    }
}

unsigned int networkedge_capacity(
        const NetworkPointer network, 
        const EdgePointer edge
    )
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
    unsigned int index;
    index = edgecollection_index_of(network->graph.edges, edge);
    return *(network->flows + index);
}

EdgePointer networkedge_admissable(
        const NetworkPointer network, 
        const Vertex active
    )
{
    EdgeCollection edges = *(network->residual_edges + active.label);
    size_t i;
    unsigned int label_first, label_second;
    for (i = 0; i < edgecollection_length(edges); i++) {
        EdgePointer edge = edgecollection_get(edges, i);
        label_first = networkvertex_distance_label(network, edge->first);
        label_second = networkvertex_distance_label(network, edge->second);
        if (label_first == label_second + 1) {
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
    index = edgecollection_index_of(network->graph.edges, edge);
    *(network->flows + index) = flow;
}

void networkedge_add_flow(
        const NetworkPointer network, 
        const EdgePointer edge, 
        int added_flow
    )
{
    unsigned int first_exflow_before, second_exflow_before, first_exflow, 
                 second_exflow, index;
    first_exflow_before = networkvertex_exflow(network, edge->first);
    second_exflow_before = networkvertex_exflow(network, edge->second);

    int flow;
    index = edgecollection_index_of(network->graph.edges, edge);
    flow = networkedge_flow(network, edge);
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
}

void networkedge_set_capacity(
        const NetworkPointer network, 
        const EdgePointer edge, 
        unsigned int capacity
    )
{
    unsigned int index;
    index = edgecollection_index_of(network->graph.edges, edge);
    *(network->capacities + index) = capacity;
}

