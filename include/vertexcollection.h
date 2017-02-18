#ifndef VERTEX_SET_H
#define VERTEX_SET_H 

#include "vertex.h"
#include "collection.h"

// A set of vertices
// Field set:   the set holding the actual references to the vertices
typedef struct vertexcollection {
    CollectionPointer members;
} VertexCollection, *VertexCollectionPointer;

VertexCollection vertexcollection_empty();

bool vertexcollection_is_empty(const VertexCollection vertices);

// Initializes a vertexcollection of size init_length. 
VertexCollection vertexcollection_init(const size_t init_length);

VertexCollection vertexcollection_init_min();

// Return the number of elements currently in this set
size_t vertexcollection_length(const VertexCollection vertices);

// Get the vertex at the specified position in the set 
VertexPointer vertexcollection_get(
        const VertexCollection vertices,
        const unsigned int position
    );

void vertexcollection_push(
        const VertexCollection vertices,
        const VertexPointer vertex
    );

// Print the set to stout
void vertexcollection_print(const VertexCollection vertices);

// Free the structure
Result vertexcollection_destroy(VertexCollection vertices);

#endif
