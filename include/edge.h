#ifndef EDGE_H
#define EDGE_H

#include <stdbool.h>

#include "vertex.h"

// An edge is a relation between two vertices 
// Field first:     The first vertex in the relation
// Field second:    The second vertex in the relation 
typedef struct edge {
    VertexPointer first;
    VertexPointer second;
    bool initialized;
} Edge, *EdgePointer;

// Constructs an edge
Edge make_edge(const VertexPointer first, const VertexPointer second);

EdgePointer make_p_edge_vertices(const VertexPointer first, const VertexPointer second);

EdgePointer make_p_edge_edge(const Edge edge);

EdgePointer make_p_edge_label(const Label first_label, const Label second_label); 

// Constructs an edge from labels
Edge make_edge_label(const Label first_label, const Label second_label); 


// Returns the edge, where the first and second field in the specified edge are
// swapped
Edge swapped(const Edge edge);

// Return the other endpoint of an edge, given one its endpoints
Result get_other(const Edge edge, VertexPointer vertex, VertexPointer *ret);

// Mutates the edge, sets the first field to the second and the second field to
// the first
void swap(EdgePointer edge);

// Returns true if the two edges are considered equal, false otherwise
bool edges_equal(const EdgePointer edge_a, const EdgePointer edge_b);

bool incident_with(const EdgePointer edge, const VertexPointer vertex);

// Print an edge as "(v, w)" to stdout
void print_edge(const Edge edge);

#endif
