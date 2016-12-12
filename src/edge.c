
#include "edge.h"

Edge edge_init()
{
    return edge_make(NULL, NULL);
}

Edge edge_make(const VertexPointer first, const VertexPointer second)
{
    Edge ret;
    ret.first    = first;
    ret.second   = second;
    return ret;
}

Edge edge_make_label(const Label first_label, const Label second_label)
{
    return edge_make(vertex_p_make(first_label), vertex_p_make(second_label));
}

EdgePointer edge_p_edge_make(const Edge edge)
{
    EdgePointer ret = malloc(sizeof(Edge));
    *ret = edge_make(edge.first, edge.second);
    return ret;
}

EdgePointer edge_p_make_label(const Label first_label, const Label second_label)
{
    return edge_p_edge_make(edge_make_label(first_label, second_label));    
}


EdgePointer edge_p_make_vertices(const VertexPointer first, const VertexPointer second)
{
    EdgePointer ret = malloc(sizeof(Edge));
    *ret = edge_make(first, second);
    return ret;
}

Edge edge_swapped(const Edge edge)
{
    return edge_make(edge.second, edge.first);
}

Result edge_get_adjacent(const Edge edge, VertexPointer vertex, VertexPointer *ret)
{
    if (vertex_equals(edge.first, vertex)) {
        *ret = edge.second; 
        return SUCCESS;
    } else if (vertex_equals(edge.second, vertex)) {
        *ret = edge.first;
        return SUCCESS;
    } else {
        return FAIL;
    }
}

void edge_swap(EdgePointer edge)
{
    VertexPointer temp = edge->first;
    edge->first = edge->second;
    edge->second = temp;
}

bool edge_equals(const EdgePointer edge_a, const EdgePointer edge_b)
{
    if (!edge_a || !edge_b) {
        return edge_a == edge_b;
    }
    return vertex_equals(edge_a->first, edge_b->first) && vertex_equals(edge_a->second, edge_b->second);
}

bool edge_is_empty(const EdgePointer edge)
{
    return edge == NULL;
}

bool edge_incident_with(const EdgePointer edge, const VertexPointer vertex)
{
    return vertex_equals(edge->first, vertex) || vertex_equals(edge->second, vertex); 
}

unsigned int edge_to_bitpos(const Edge edge, const unsigned int nvertices)
{
    if (edge.first == NULL || edge.second == NULL) {
        return 0;
    }
    return edge.first->label * nvertices + edge.second->label;
}

void edge_print(const Edge edge)
{
    printf("(%u, %u)\n", edge.first->label, edge.second->label);
}

