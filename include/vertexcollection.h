#ifndef VERTEX_SET_H
#define VERTEX_SET_H 

#include "vertex.h"
#include "collection.h"

// A set of vertices
// Field set:   the set holding the actual references to the vertices
// Field contains:  bitmap for keeping track of which elements are in the set
typedef struct vertexcollection {
    CollectionPointer members;
    Map indices;
} VertexCollection, *VertexCollectionPointer;

// Initializes a vertexcollection of size init_length. 
VertexCollection vertexcollection_init(const size_t init_length);

void vertexcollection_reset(VertexCollection vertices);

// Return true if the vertexcollection has no intialized elements, false otherwise
bool vertexcollection_is_empty(const VertexCollection vertices);

// Return the number of elements currently in this set
size_t vertexcollection_length(const VertexCollection vertices);

// Get the vertex at the specified position in the set 
VertexPointer vertexcollection_get(const VertexCollection vertices, const unsigned int position);

VertexPointer vertexcollection_get_first(const VertexCollection vertices);

VertexPointer vertexcollection_get_with_label(const VertexCollection vertices, const Label label);

unsigned int vertexcollection_index_of(const VertexCollection vertices, const Vertex vertex);

// Does the set contain the specified vertex?
bool vertexcollection_contains_label(const VertexCollection vertices, const Label label);

// is the vertexcollection a superset of the subset?
bool vertexcollection_is_super(const VertexCollection super, const VertexCollection sub);

bool vertexcollection_equals(const VertexCollection vertexcollection_a, const VertexCollection vertexcollection_b);

// Add a vertex to the set
Result vertexcollection_replace(const VertexCollection vertices, const VertexPointer vertex, const unsigned int position);

Result vertexcollection_push(const VertexCollection vertices, const VertexPointer vertex);

void vertexcollection_remove(VertexCollectionPointer vertices, const Vertex vertex);

// Find the relative complement of a vertexcollection and store it in ret
Result vertexcollection_complement(const VertexCollection vertexcollection_a, const VertexCollection vertexcollection_b, VertexCollectionPointer ret);

// Print the set to stout
void vertexcollection_print(const VertexCollection vertices);

// Free the structure
Result vertexcollection_destroy(VertexCollection vertices);

#endif
