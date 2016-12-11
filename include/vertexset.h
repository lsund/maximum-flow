#ifndef VERTEX_SET_H
#define VERTEX_SET_H 

#include <stddef.h>
#include <stdlib.h>
#include <util.h>
#include <errno.h>

#include "array.h"
#include "vertex.h"

// A set of vertices
// Field set:   the set holding the actual references to the vertices
// Field contains:  bitmap for keeping track of which elements are in the set
typedef struct vertexset {
    ArrayPointer set;
} VertexSet, *VertexSetPointer;

// Initializes a vertexset of size init_length. All vertices in this set
// get an uninitialized value
VertexSet vertexset_init(const size_t init_length);

// Return true if the vertexset has no intialized elements, false otherwise
bool vertexset_is_empty(const VertexSet vertexset);

// Does the set contain the specified vertex?
bool vertexset_contains_vertex(const VertexSet vertexset, const VertexPointer vertex);

// is the vertexset a superset of the subset?
bool vertexset_is_super(const VertexSet super, const VertexSet sub);

bool vertexset_equals(const VertexSet vertexset_a, const VertexSet vertexset_b);

// Add a vertex to the set
Result vertexset_set(const VertexSet vertexset, const VertexPointer vertex, const unsigned int position);

Result vertexset_push(const VertexSet edgeset, const VertexPointer vertex);

// Get the vertex at the specified position in the set 
VertexPointer vertexset_get(const VertexSet vertexset, const unsigned int position);

// Find the relative complement of a vertexset and store it in ret
Result vertexset_complement(const VertexSet vertexset_a, const VertexSet vertexset_b, VertexSetPointer ret);

// Print the set to stout
void vertexset_print(const VertexSet vertexset);

// Free the structure
Result vertexset_destroy(VertexSet vertexset);

#endif
