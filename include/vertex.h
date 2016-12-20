#ifndef VERTEX_H
#define VERTEX_H

#include "util.h"

// Type synonym
typedef unsigned int Label; 

// A vertex is some data point
// Field label: Its (unique) identifier 
typedef struct vertex {
    Label label;
} Vertex, *VertexPointer;

Vertex vertex_empty();

// Construct a vertex
Vertex vertex_make(const Label label);

// Construct a pointer to a vertex with a label
VertexPointer vertex_p_make(const Label label);

// Return true if the vertices are considered the same, false otherwise
bool vertex_equals(const Vertex vertex_a, const Vertex vertex_b);

// Print the label of a vertex to stdout
void vertex_print(const Vertex vertex);

#endif
