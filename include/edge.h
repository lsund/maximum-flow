#ifndef EDGE_H
#define EDGE_H

#include <stdbool.h>

#include "vertex.h"

// An edge is a relation between two vertices 
// Field first:     The first vertex in the relation
// Field second:    The second vertex in the relation 
typedef struct edge {
    Vertex first;
    Vertex second;
    bool initialized;
} Edge, *EdgePointer;

// Constructs an uninitialized edge.
Edge empty_edge();

// Constructs an edge
Edge make_edge(const Vertex fst, const Vertex snd);

// Returns the edge, where the first and second field in the specified edge are
// swapped
Edge swapped(const Edge edge);

// mutates the edge, sets the first field to the second and the second field to
// the first
void swap(EdgePointer edge);

// Returns true if the edge is uninitialized
bool edge_is_empty(const Edge edge);

// Returns true if the two edges are considered equal, false otherwise
bool edges_equal(const Edge edge_a, const Edge edge_b);

// Converts the edge to an unique integer relative to the labels of its
// vertices. This only works if nverticies is specified as the largest number
// that a label of a vertex can take, in the context of calling this function.
unsigned int edge_to_bitpos(const Edge edge, const unsigned int nvertices);

#endif
