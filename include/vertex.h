
#ifndef VERTEX_H
#define VERTEX_H

#include <stdbool.h>
#include <stdlib.h>

#include "array.h"

// Type synonym
typedef unsigned int Label; 

// A vertex is some data point
// Field label: Its (unique) identifier 
typedef struct vertex {
    Label label;
    Array neighbors;
} Vertex, *VertexPointer;

// Construct a vertex
Vertex make_vertex(const Label label);

// Construct a pointer to a vertex with a label
VertexPointer make_p_vertex(const Label label);

// Return true if the vertices are considered the same, false otherwise
bool vertices_equal(const VertexPointer vertex_a, const VertexPointer vertex_b);

// Converts the vertex to an integer, unique relative to its label.
unsigned int vertex_to_bitpos(const VertexPointer vertex);

// Construct a copy of the specified vertex
VertexPointer copy_vertex(const Vertex vertex);

// Print the label of a vertex to stdout
void print_vertex(const VertexPointer vertex);

#endif
