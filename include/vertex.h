
#ifndef VERTEX_H
#define VERTEX_H

#include <stdbool.h>
#include <stdlib.h>

// The value of an uninitialized vertex
#define UNINIT_VERTEX 0

// Type synonym
typedef unsigned int Label; 

// A vertex is some data point
// Field label: Its (unique) identifier 
typedef struct vertex {
    Label label;
    Label part;
    bool initialized;
} Vertex, *VertexPointer;

// Construct a uninitialized vertex
Vertex empty_vertex();

// Construct a pointer to a uninitialized vertex
VertexPointer make_p_empty_vertex();

// Construct a vertex
Vertex make_vertex(const Label label);

// Return true if the vertices are considered the same, false otherwise
bool vertices_equal(const Vertex vertex_a, const Vertex vertex_b);

// Converts the vertex to an integer, unique relative to its label.
unsigned int vertex_to_bitpos(Vertex vertex);

// Is the vertex initialized?
bool is_vertex_initialized(const VertexPointer vertex);

// Construct a copy of the specified vertex
VertexPointer copy_vertex(const Vertex vertex);

#endif
