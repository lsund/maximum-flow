#ifndef VERTEX_SET_H
#define VERTEX_SET_H 

#include "vertex.h"
#include "collection.h"

// A set of vertices
// Field set:   the set holding the actual references to the vertices
// Field contains:  bitmap for keeping track of which elements are in the set
typedef struct vertexcollection {
    CollectionPointer members;
} VertexCollection, *VertexCollectionPointer;

// Initializes a vertexcollection of size init_length. 
VertexCollection vertexcollection_init(const size_t init_length);

// Return true if the vertexcollection has no intialized elements, false otherwise
bool vertexcollection_is_empty(const VertexCollection vertexcollection);

// Return the number of elements currently in this set
size_t vertexcollection_length(const VertexCollection vertexcollection);

// Get the vertex at the specified position in the set 
VertexPointer vertexcollection_get(const VertexCollection vertexcollection, const unsigned int position);

VertexPointer vertexcollection_get_with_label(const VertexCollection vertexcollection, const Label label);

// Does the set contain the specified vertex?
bool vertexcollection_contains_label(const VertexCollection vertexcollection, const Label label);

// is the vertexcollection a superset of the subset?
bool vertexcollection_is_super(const VertexCollection super, const VertexCollection sub);

bool vertexcollection_equals(const VertexCollection vertexcollection_a, const VertexCollection vertexcollection_b);

// Add a vertex to the set
Result vertexcollection_set(const VertexCollection vertexcollection, const VertexPointer vertex, const unsigned int position);

Result vertexcollection_push(const VertexCollection vertexcollection, const VertexPointer vertex);

// Find the relative complement of a vertexcollection and store it in ret
Result vertexcollection_complement(const VertexCollection vertexcollection_a, const VertexCollection vertexcollection_b, VertexCollectionPointer ret);

// Print the set to stout
void vertexcollection_print(const VertexCollection vertexcollection);

// Free the structure
Result vertexcollection_destroy(VertexCollection vertexcollection);

#endif
