
#include "pseudoflow_helpers.h"

static bool is_strong_weak_edge(const NetworkPointer network, const Edge edge)
{
    bool is_source_edge = edge_incident_with(edge, *network->source);
    bool is_sink_edge = edge_incident_with(edge, *network->sink);
    bool is_valid_edge = !(is_source_edge || is_sink_edge);
    if (!is_valid_edge) {
        return false;
    }
    bool first_is_strong = vertex_excess(edge.first) > 0;
    bool second_is_weak = vertex_excess(edge.second) <= 0;
    return first_is_strong && second_is_weak;
}

static bool is_merger_edge(const NetworkPointer network, const EdgePointer edge)
{
    return edge_is_residual(edge) && is_strong_weak_edge(network, *edge);
}

static void split(const NetworkPointer network, const EdgePointer edge) 
{
    VertexPointer vertex;
    vertex = edge->first;
    tree_merge(network->root, vertex);
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
        edge_augment(edge, amount);
        new_delta = amount;
    } else {
        new_delta = push_and_split(network, edge, residual_capacity);
    }
    return new_delta;
}

EdgePointer merger_edge(const NetworkPointer network)
{
    EdgeCollection edges = network->graph.edges;
    size_t i;
    for (i = 0; i < edgecollection_length(edges); i++) {
        EdgePointer edge = edgecollection_get(edges, i);
        if (is_merger_edge(network, edge)) {
            return edge;
        } else if (is_merger_edge(network, edge->reverse)) {
            return edge->reverse;
        }
    }
    return NULL;
}

