
#include "edge.h"

static void build_edge(
        EdgePointer edge,
        const VertexPointer first,
        const VertexPointer second,
        const bool is_reverse
    )
{
    edge->first      = *first;
    edge->second     = *second;
    edge->first_ref  = first;
    edge->second_ref = second;
    edge->first_ref  = first;
    edge->second_ref = second;
    edge->capacity   = 0;
    edge->flow       = 0;
    edge->is_reverse = is_reverse;
}

EdgePointer edge_make(const VertexPointer first, const VertexPointer second)
{
    EdgePointer ret = malloc(sizeof(Edge));
    build_edge(ret, first, second, false);

    ret->reverse = malloc(sizeof(Edge));
    build_edge(ret->reverse, second, first, true);

    ret->reverse->reverse = ret;

    return ret;
}

bool edge_incident_with(const Edge edge, const Vertex vertex)
{
    bool with_first  = vertex_equals(edge.first, vertex);
    bool with_second = vertex_equals(edge.second, vertex); 
    return with_first || with_second;
}

unsigned int edge_capacity(const EdgePointer edge)
{
    return edge->capacity;
}

unsigned int edge_residual_capacity(const EdgePointer edge)
{
    unsigned int capacity, flow;
    if (edge->is_reverse) {
        EdgePointer reverse_edge_p = edge->reverse;
        flow = edge_flow(reverse_edge_p);
        return flow;
    } else {
        capacity = edge->capacity;
        flow = edge_flow(edge);
        return capacity - flow;
    }
}

void edge_set_capacity(const EdgePointer edge, const unsigned int capacity)
{
    edge->capacity = capacity;
}

unsigned int edge_flow(const EdgePointer edge)
{
    return edge->flow;
}

void edge_set_flow(const EdgePointer edge, int flow)
{
    edge->flow = flow;
}

void edge_add_flow(const EdgePointer edge, const int added_flow)
{
    int flow;
    flow = edge_flow(edge);
    edge_set_flow(edge, flow + added_flow);
    edge->second_ref->excess += added_flow;
    edge->first_ref->excess -= added_flow;
}

void edge_fill_flow(
        const EdgePointer edge,
        const unsigned int capacity,
        const EdgeType type
    )
{
    if (type == FORWARD)
    {
        edge_add_flow(edge, capacity - edge_flow(edge));
    } else {
        edge_add_flow(edge->reverse, -capacity);
    }
}

void edge_augment(const EdgePointer edge, const unsigned int added_flow)
{
    if (edge->is_reverse) {
        edge_add_flow(edge->reverse, -added_flow);
    } else {
        edge_add_flow(edge, added_flow);
    }
}

bool edge_is_residual(const EdgePointer edge)
{
    return edge_residual_capacity(edge) > 0;
}

bool edge_is_admissable(const EdgePointer edge)
{
    Label first_label, second_label;
    first_label = vertex_distance_label(edge->first_ref);
    second_label = vertex_distance_label(edge->second_ref);
    return first_label == second_label + 1 && edge_is_residual(edge);
}

void edge_print(const Edge edge)
{
    printf("(%u, %u)\n", edge.first.label, edge.second.label);
}

