#ifndef EDGE_H
#define EDGE_H

#include <stdbool.h>

#include "vertex.h"
#include "util.h"

// An edge is a set containing two vertices
// An edge is therefore assumed to be non-looping. Modules that uses this
// structure is assumed to treat the edges as unique, that is this structure
// should not be used in multi-graphs.
//
// Field first:     The first vertex
// Field second:    The second vertex
typedef struct edge {
    Vertex first;
    Vertex second;
} Edge, *EdgePointer;

// Constructs an edge from two vertices
Edge edge_make_vertices(const Vertex first, const Vertex second);

// Same as edge_make_vertices, but returns a pointer to an edge
EdgePointer edge_p_make_vertices(const Vertex first, const Vertex second);

// Constructs an edge from two vertex labels
Edge edge_make_label(const Label first_label, const Label second_label); 

// Same as edge_make_label, but returns a pointer to an edge. 
EdgePointer edge_p_make_label(
        const Label first_label,
        const Label second_label
    ); 

// Constructs a pointer to the specified edge
EdgePointer edge_p_make_edge(const Edge edge);

// Returns an edge, where the first and the second vertex are swapped
Edge edge_swapped(const Edge edge);

// Returns true if the edge contains the given vertex, false otherwise
bool edge_incident_with(const EdgePointer edge, const Vertex vertex);

// Returns true if the two edges are considered equal, false otherwise
bool edge_equals(const EdgePointer edge_a, const EdgePointer edge_b);

// Returns true if edge_b equals the reverse edge of b
bool edge_equals_reverse(const EdgePointer edge_a, const EdgePointer edge_b);

// Ruterns an unique integer for each unique edge
unsigned int edge_hash(const Edge edge);

// Print an edge as "(v, w)" to stdout
void edge_print(const Edge edge);

#endif
