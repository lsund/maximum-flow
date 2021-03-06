#ifndef VERTEX_H
#define VERTEX_H

#include "util.h"

typedef struct vertex Vertex, *VertexPointer;

// A vertex is some data point
// Field label: Its (unique) identifier 
struct vertex {
    Label label;
    VertexPointer parent;
    Label distance_label;
    unsigned int excess;
};

// Construct a pointer to a vertex with a label
VertexPointer vertex_make(const Label label);

// Return true if the vertices are considered the same, false otherwise
bool vertex_equals(const Vertex vertex_a, const Vertex vertex_b);

Label vertex_distance_label(const VertexPointer vertex);

void vertex_set_distance_label(
        const VertexPointer vertex, 
        const unsigned int label
    );

int vertex_excess(const VertexPointer vertex);

int vertex_exflow(const VertexPointer vertex);

// Print the label of a vertex to stdout
void vertex_print(const Vertex vertex);

VertexPointer tree_find_branch(const VertexPointer vertex);

#endif
