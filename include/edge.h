#ifndef EDGE_H
#define EDGE_H

#include <stdbool.h>

#include "vertex.h"
#include "util.h"

// An edge is a relation between two vertices 
// Field first:     The first vertex in the relation
// Field second:    The second vertex in the relation 
typedef struct edge {
    Vertex first;
    Vertex second;
    bool residual;
} Edge, *EdgePointer;

Edge edge_init();

// Constructs an edge given its two endpoint
Edge edge_make_vertices(const Vertex first, const Vertex second);

// Constructs an edge, conostructing new endpoints using the specified labels
Edge edge_make_label(const Label first_label, const Label second_label); 

// Same as edge_make_vertices(), but returns a pointer to that edge
EdgePointer edge_p_make_vertices(const Vertex first, const Vertex second);

// Constructs an edge the same as the specified argument, returns a pointer to
// that edge.
EdgePointer edge_p_make_edge(const Edge edge);

// Same as edge_make_label(), but returns a pointer to that edge. 
EdgePointer edge_p_make_label(const Label first_label, const Label second_label); 

// Returns the edge, where the first and second field  are edge_swapped
Edge edge_swapped(const Edge edge);

// Mutates the edge, sets the first field to the second and the second field to
// the first
void edge_swap(EdgePointer edge);

// Sets ret the other endpoint of an edge, given one its endpoints and returns
// SUCCESS. If the vertex does not contain the specified vertex, return FAIL.
Vertex edge_get_adjacent(const EdgePointer edge, Vertex vertex);

bool edge_is_empty(const EdgePointer edge);

// Returns true if the edge contains the given vertex, false otherwise
bool edge_incident_with(const EdgePointer edge, const Vertex vertex);

// Returns true if the two edges are considered equal, false otherwise
bool edge_equals(const EdgePointer edge_a, const EdgePointer edge_b);

bool edge_equals_reverse(const EdgePointer edge_a, const EdgePointer edge_b);

unsigned int edge_p_hash(const EdgePointer edge);

unsigned int edge_hash(const Edge edge);

// Print an edge as "(v, w)" to stdout
void edge_print(const Edge edge);

#endif
