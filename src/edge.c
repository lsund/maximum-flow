
#include "edge.h"

Edge edge_init()
{
    return edge_make_vertices(vertex_empty(), vertex_empty());
}

Edge edge_make_vertices(const Vertex first, const Vertex second)
{
    Edge ret;
    ret.first    = first;
    ret.second   = second;
    return ret;
}

Edge edge_make_label(const Label first_label, const Label second_label)
{
    return edge_make_vertices(vertex_make(first_label), vertex_make(second_label));
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

Edge edge_swapped(const Edge edge)
{
    return edge_make_vertices(edge.second, edge.first);
}

Vertex edge_get_adjacent(const EdgePointer edge, Vertex vertex)
{
    if (vertex_equals(edge->first, vertex)) {
        return edge->second; 
    } else if (vertex_equals(edge->second, vertex)) {
        return edge->first;
    } else {
        runtime_error("eedge_get_adjacent: edge does not contain that vertex");
    }
    return vertex_empty();
}

void edge_swap(EdgePointer edge)
{
    Vertex temp = edge->first;
    edge->first = edge->second;
    edge->second = temp;
}

bool edge_is_empty(const EdgePointer edge)
{
    return edge == NULL;
}

bool edge_equals(const EdgePointer edge_a, const EdgePointer edge_b)
{
    if (!edge_a || !edge_b) {
        return edge_a == edge_b;
    }
    return vertex_equals(edge_a->first, edge_b->first) && vertex_equals(edge_a->second, edge_b->second);
}

bool edge_equals_reverse(const EdgePointer edge_a, const EdgePointer edge_b)
{
    return vertex_equals(edge_a->first, edge_b->second) && vertex_equals(edge_a->second, edge_b->first);
}

bool edge_incident_with(const EdgePointer edge, const Vertex vertex)
{
    return vertex_equals(edge->first, vertex) || vertex_equals(edge->second, vertex); 
}

unsigned int edge_to_bitpos(const Edge edge, const unsigned int nvertices)
{
    return edge.first.label * nvertices + edge.second.label;
}

unsigned int edge_hash(const EdgePointer edge)
{
    unsigned int a = edge->first.label;
    unsigned int b = edge->second.label;
    return a >= b ? a * a + a + b : a + b * b; 
}

void edge_print(const Edge edge)
{
    printf("(%u, %u)\n", edge.first.label, edge.second.label);
}

