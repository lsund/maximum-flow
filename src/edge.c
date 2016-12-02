
#include "edge.h"

Edge empty_edge()
{
    return make_edge(empty_vertex(), empty_vertex());
}

Edge make_edge(const Vertex first, const Vertex second)
{
    Edge ret;
    ret.first = first;
    ret.second = second;
    ret.initialized = true;
    return ret;
}

Edge swapped(const Edge edge)
{
    return make_edge(edge.second, edge.first);
}

void swap(EdgePointer edge)
{
    Vertex temp = edge->first;
    edge->first = edge->second;
    edge->second = temp;
}

bool edges_equal(const Edge edge_a, const Edge edge_b)
{
    bool firsts_equal = vertices_equal(edge_a.first, edge_b.first);
    bool seconds_equal = vertices_equal(edge_a.second, edge_b.second);
    return firsts_equal && seconds_equal;
}

bool edge_is_empty(const Edge edge)
{
    return edges_equal(edge, empty_edge());
}



unsigned int edge_to_bitpos(const Edge edge, const unsigned int nvertices)
{
    return edge.first.label * nvertices + edge.second.label;
}

