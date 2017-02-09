
#include "edge.h"

Edge edge_make_vertices(const Vertex first, const Vertex second)
{
    Edge ret;
    ret.first    = first;
    ret.second   = second;
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

bool edge_equals(const EdgePointer edge_a, const EdgePointer edge_b)
{
    if (!edge_a || !edge_b) {
        return edge_a == edge_b;
    }
    bool first_equals  = vertex_equals(edge_a->first, edge_b->first);
    bool second_equals = vertex_equals(edge_a->second, edge_b->second);
    return first_equals && second_equals;
}

bool edge_equals_reverse(const EdgePointer edge_a, const EdgePointer edge_b)
{
    Edge reverse_b = edge_swapped(*edge_b);
    return edge_equals(edge_a, &reverse_b); 
}

bool edge_incident_with(const EdgePointer edge, const Vertex vertex)
{
    bool with_first  = vertex_equals(edge->first, vertex);
    bool with_second = vertex_equals(edge->second, vertex); 
    return with_first || with_second;
}

unsigned int edge_hash(const Edge edge)
{
    unsigned int a = edge.first.label;
    unsigned int b = edge.second.label;
    return a >= b ? a * a + a + b : a + b * b; 
}

void edge_print(const Edge edge)
{
    printf("(%u, %u)\n", edge.first.label, edge.second.label);
}

