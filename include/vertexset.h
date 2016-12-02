#ifndef VERTEX_SET_H
#define VERTEX_SET_H 

#include <stddef.h>
#include <stdlib.h>
#include <util.h>
#include <errno.h>

#include "array.h"
#include "vertex.h"

// A set of vertices, no duplicates
// Field set:   the set holding the actual references to the vertices
// Field contains:  bitmap for keeping track of which elements are in the set
typedef struct vertexset {
    ArrayPointer set;
    unsigned int maxvertices; 
    bool *contains;
    unsigned int *indices;
    bool initialized;
} VertexSet, *VertexSetPointer;

VertexSet uninitialized_vertexset();
 
// Initializes a vertexset of size init_length. All vertices in this set
// get an uninitialized value
VertexSet init_vertexset(const size_t init_length);

// Return true if the vertexset is intialized, false otherwise
bool vertexset_is_initialized(const VertexSet vertexset);

// Return true if the vertexset has no intialized elements, false otherwise
bool vertexset_is_empty(const VertexSet vertexset);

// Does the set contain the specified vertex?
bool vertexset_contains_vertex(const VertexSet vertexset, const Vertex vertex);

bool vertexset_contains_vertices(
        const VertexSet vertexset,
        const VertexPointer vertices,
        size_t length
    );

// Add a vertex to the set
Result add_vertex(VertexSet vertexset, Vertex vertex);

// Get the vertex at the specified position in the set 
VertexPointer get_vertex(const VertexSet vertexset, const unsigned int position);

// Print the set to stout

void print_vertexset(const VertexSet vertexset);

// Free the structure
Result destroy_vertexset(VertexSet vertexset);

#endif
