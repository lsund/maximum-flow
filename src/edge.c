
#include "edge.h"

Edge edge_make_vertices(const Vertex first, const Vertex second)
{
    Edge ret;
    ret.first    = first;
    ret.second   = second;
    ret.capacity = 0;
    ret.flow     = 0;
    return ret;
}

Edge edge_make_label(const Label first_label, const Label second_label)
{
    Vertex first, second;
    first  = vertex_make(first_label);
    second = vertex_make(second_label);
    return edge_make_vertices(first, second);
}

EdgePointer edge_p_make_edge(const Edge edge)
{
    EdgePointer ret = malloc(sizeof(Edge));
    *ret = edge_make_vertices(edge.first, edge.second);
    return ret;
}

EdgePointer edge_p_make_label(const Label first_label, const Label second_label)
{
    return edge_p_make_edge(edge_make_label(first_label, second_label));    
}


EdgePointer edge_p_make_vertices(const Vertex first, const Vertex second)
{
    EdgePointer ret = malloc(sizeof(Edge));
    *ret = edge_make_vertices(first, second);
    return ret;
}

EdgePointer edge_p_make_p_vertices(const VertexPointer first, const VertexPointer second)
{
    EdgePointer ret = edge_p_make_vertices(*first, *second);
    ret->first_ref = first;
    ret->second_ref = second;
    return ret;
}

Edge edge_swapped(const Edge edge)
{
    return edge_make_vertices(edge.second, edge.first);
}

bool edge_equals(const Edge edge_a, const Edge edge_b)
{
    bool first_equals  = vertex_equals(edge_a.first, edge_b.first);
    bool second_equals = vertex_equals(edge_a.second, edge_b.second);
    return first_equals && second_equals;
}

bool edge_equals_reverse(const Edge edge_a, const Edge edge_b)
{
    Edge reverse_b = edge_swapped(edge_b);
    return edge_equals(edge_a, reverse_b); 
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

unsigned int edge_hash(const Edge edge)
{
    unsigned int a = edge.first.label;
    unsigned int b = edge.second.label;
    return a >= b ? a * a + a + b : a + b * b; 
}

bool edge_is_residual(const EdgePointer edge)
{
    return edge_residual_capacity(edge) > 0;
}

void edge_print(const Edge edge)
{
    printf("(%u, %u)\n", edge.first.label, edge.second.label);
}

