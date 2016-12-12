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
    float capacity;
    float flow;
} Edge, *EdgePointer;

Edge edge_init();

// Constructs an edge
Edge edge_make(const VertexPointer first, const VertexPointer second);

// Constructs an edge from labels
Edge edge_make_label(const Label first_label, const Label second_label); 

EdgePointer edge_p_make_vertices(const VertexPointer first, const VertexPointer second);

EdgePointer edge_p_edge_make(const Edge edge);

EdgePointer edge_p_make_label(const Label first_label, const Label second_label); 

// Returns the edge, where the first and second field in the specified edge are
// edge_swapped
Edge edge_swapped(const Edge edge);

// Return the other endpoint of an edge, given one its endpoints
Result edge_get_adjacent(const Edge edge, VertexPointer vertex, VertexPointer *ret);

// Mutates the edge, sets the first field to the second and the second field to
// the first
void edge_swap(EdgePointer edge);

// Returns true if the two edges are considered equal, false otherwise
bool edge_equals(const EdgePointer edge_a, const EdgePointer edge_b);

bool edge_incident_with(const EdgePointer edge, const VertexPointer vertex);

// Print an edge as "(v, w)" to stdout
void edge_print(const Edge edge);

#endif
