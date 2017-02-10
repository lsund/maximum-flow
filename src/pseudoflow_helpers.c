
#include "pseudoflow_helpers.h"

static void split(
        const NetworkPointer network,
        const Edge edge
    ) 
{
    VertexPointer vertex;
    vertex = vertexcollection_get_reference(
                    network->graph.vertices,
                    edge.first
                );
    tree_merge(network->root, vertex);
}

static void merge(
        const VertexPointer strong_branch, 
        const VertexPointer strong_vertex, 
        const VertexPointer weak_vertex
    )
{
        strong_branch->parent = NULL;
        tree_invert(strong_vertex);
        tree_merge(weak_vertex, strong_vertex);
}

static unsigned int augment(
        const NetworkPointer network,
        const Edge edge,
        const unsigned int amount
    )
{
    int increased_flow;
    networkedge_augment(network, edge, amount);
    if (networkedge_is_reverse(network, edge)) {
        increased_flow = amount;
    } else {
        increased_flow = amount;
    }
    *(network->excesses + edge.first.label) -= increased_flow;
    *(network->excesses + edge.second.label) += increased_flow;
    return amount;
}

static unsigned int push_and_split(
        const NetworkPointer network,
        const Edge edge,
        const unsigned int residual_capacity
    )
{
    int new_delta;
    split(network, edge);
    new_delta = residual_capacity;
    if (networkedge_is_reverse(network, edge)) {
        networkedge_fill_flow(network, edge, residual_capacity, REVERSE);
    } else {
        unsigned int capacity;
        capacity = networkedge_capacity(network, edge);
        networkedge_fill_flow(network, edge, capacity, FORWARD);
    }
    return new_delta;
}

VertexPointer update_tree(
        const VertexPointer strong_vertex,
        const VertexPointer weak_vertex
    )
{
    VertexPointer strong_branch = tree_find_branch(strong_vertex);
    merge(strong_branch, strong_vertex, weak_vertex);
    return strong_branch;
}

unsigned int push_flow(
        const NetworkPointer network,
        const Edge edge,
        const unsigned int amount
    )
{
    unsigned int new_delta;
    unsigned int residual_capacity;
    residual_capacity = networkedge_residual_capacity(network, edge);
    if (residual_capacity >= amount) {
        new_delta = augment(network, edge, amount);
    } else {
        new_delta = push_and_split(network, edge, residual_capacity);
    }
    return new_delta;
}

