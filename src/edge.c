
#include "edge.h"

Edge empty_edge()
{
    return make_edge(NULL, NULL);
}

Edge make_edge(const VertexPointer first, const VertexPointer second)
{
    Edge ret;
    ret.first = first;
    ret.second = second;
    ret.initialized = true;
    return ret;
}

Edge make_edge_label(const Label first_label, const Label second_label)
{
    return make_edge(make_p_vertex(first_label), make_p_vertex(second_label));
}

EdgePointer make_p_edge_edge(const Edge edge)
{
    EdgePointer ret = malloc(sizeof(Edge));
    *ret = make_edge(edge.first, edge.second);
    return ret;
}

EdgePointer make_p_edge_label(const Label first_label, const Label second_label)
{
    return make_p_edge_edge(make_edge_label(first_label, second_label));    
}


EdgePointer make_p_edge_vertices(const VertexPointer first, const VertexPointer second)
{
    EdgePointer ret = malloc(sizeof(Edge));
    *ret = make_edge(first, second);
    return ret;
}

Edge swapped(const Edge edge)
{
    return make_edge(edge.second, edge.first);
}

Result get_other(const Edge edge, VertexPointer vertex, VertexPointer *ret)
{
    if (vertices_equal(edge.first, vertex)) {
        *ret = edge.second; 
        return SUCCESS;
    } else if (vertices_equal(edge.second, vertex)) {
        *ret = edge.first;
        return SUCCESS;
    } else {
        return FAIL;
    }
}

void swap(EdgePointer edge)
{
    VertexPointer temp = edge->first;
    edge->first = edge->second;
    edge->second = temp;
}

bool edges_equal(const EdgePointer edge_a, const EdgePointer edge_b)
{
    return edge_a == edge_b;
}

bool edge_is_empty(const EdgePointer edge)
{
    return edge == NULL;
}

bool incident_with(const EdgePointer edge, const VertexPointer vertex)
{
    return vertices_equal(edge->first, vertex) || vertices_equal(edge->second, vertex); 
}

unsigned int edge_to_bitpos(const Edge edge, const unsigned int nvertices)
{
    if (edge.first == NULL || edge.second == NULL) {
        return 0;
    }
    return edge.first->label * nvertices + edge.second->label;
}

void print_edge(const Edge edge)
{
    printf("(%u, %u)\n", edge.first->label, edge.second->label);
}

