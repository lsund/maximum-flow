
#include "pseudoflow_helpers.h"

static void split(
        const NetworkPointer network,
        const EdgePointer edge
    ) 
{
    VertexPointer vertex;
    vertex = edge->first_ref;
    tree_merge(network->root, vertex);
}

static unsigned int augment(
        const NetworkPointer network,
        const EdgePointer edge,
        const unsigned int amount
    )
{
    int increased_flow;
    networkedge_augment(network, edge, amount);
    if (edge->is_reverse) {
        increased_flow = amount;
    } else {
        increased_flow = amount;
    }
    edge->first_ref->excess -= increased_flow;
    edge->second_ref->excess += increased_flow;
    return amount;
}

static unsigned int push_and_split(
        const NetworkPointer network,
        const EdgePointer edge,
        const unsigned int residual_capacity
    )
{
    int new_delta;
    split(network, edge);
    new_delta = residual_capacity;
    if (edge->is_reverse) {
        edge_fill_flow(edge, residual_capacity, REVERSE);
    } else {
        unsigned int capacity;
        capacity = edge_capacity(edge);
        edge_fill_flow(edge, capacity, FORWARD);
    }
    return new_delta;
}

VertexPointer merge(
        const VertexPointer strong_vertex,
        const VertexPointer weak_vertex
    )
{
    VertexPointer strong_branch = tree_find_branch(strong_vertex);
    strong_branch->parent = NULL;
    tree_invert(strong_vertex);
    tree_merge(weak_vertex, strong_vertex);
    return strong_branch;
}

unsigned int push_flow(
        const NetworkPointer network,
        const EdgePointer edge,
        const unsigned int amount
    )
{
    unsigned int new_delta;
    unsigned int residual_capacity;
    residual_capacity = edge_residual_capacity(edge);
    if (residual_capacity >= amount) {
        new_delta = augment(network, edge, amount);
    } else {
        new_delta = push_and_split(network, edge, residual_capacity);
    }
    return new_delta;
}

static bool is_merger_edge(const NetworkPointer network, const Edge edge)
{
    bool is_source_edge = edge_incident_with(edge, *network->source);
    bool is_sink_edge = edge_incident_with(edge, *network->sink);
    bool is_valid_edge = !(is_source_edge || is_sink_edge);
    if (!is_valid_edge) {
        return false;
    }
    bool first_is_strong = networkvertex_is_strong(network, edge.first_ref);
    bool second_is_weak = !networkvertex_is_strong(network, edge.second_ref);
    return first_is_strong && second_is_weak;
}

EdgePointer merger_edge(const NetworkPointer network)
{
    size_t i;
    for (i = 0; i < edgecollection_length(network->graph.edges); i++) {
        EdgePointer edge = edgecollection_get(network->graph.edges, i);
        if (edge_is_residual(edge) && is_merger_edge(network, *edge)) {
            return edge;
        }
    }
    for (i = 0; i < edgecollection_length(network->reverse_edges); i++) {
        EdgePointer edge = edgecollection_get(network->reverse_edges, i);
        if (edge_is_residual(edge) && is_merger_edge(network, *edge)) {
            return edge;
        }
    }
    return NULL;
}

