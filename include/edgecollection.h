
#ifndef EDGE_SET_H
#define EDGE_SET_H

#include "edge.h"
#include "util.h"
#include "vertexcollection.h"

typedef struct edgecollection {
    CollectionPointer members;
} EdgeCollection, *EdgeCollectionPointer;

// Returns a dummy edgecollection with it's collection set to NULL
EdgeCollection edgecollection_empty();

// Returns the edgecollection with its collection initialized, with an initial capacity of
// size.
EdgeCollection edgecollection_init(const size_t size);

// Initializes an edgecollection using edgecollection_init and returns a pointer to it
EdgeCollectionPointer edgecollection_p_init(const unsigned int nvertices);

// Return the number of elements currently in this collection
size_t edgecollection_length(const EdgeCollection edgecollection);

// Get the edge at the specified position
EdgePointer edgecollection_get(const EdgeCollection edgecollection , const unsigned int position);

size_t edgecollection_vertex_count(const EdgeCollection edgecollection);

// The vertices of this edgecollection
VertexCollection edgecollection_vertices(const EdgeCollection edgecollection);

// Add an edge to the edgecollection
Result edgecollection_set(const EdgeCollection edgecollection, const EdgePointer edge, const unsigned int position);

// Sets the last element to the specified edge, and increments the number of
// elements
Result edgecollection_push(const EdgeCollection edgecollection, const EdgePointer edge);

// Returns true if the edgecollection has no initialized elements, false otherwise.
bool edgecollection_is_empty(const EdgeCollection edgecollection);

bool edgecollection_equals(const EdgeCollection edgecollection_a, const EdgeCollection edgecollection_b);

// Returns true if the edgecollection contains the specified edge, false otherwise
bool edgecollection_is_super(const EdgeCollection super, const EdgeCollection sub);

// Returns true if all edges in sub are also in super
bool edgecollection_is_sub(const EdgeCollection sub, const EdgeCollection super);

// Returns true if the edgecollection contains every edge in the list of edges
// specified by edges, false otherwise
bool edgecollection_contains_edge(const EdgeCollection edgecollection, const EdgePointer edge);

// Returns true if the edgecollection contains the specified vertex, false otherwise
bool edgecollection_contains_vertex(const EdgeCollection edgecollection, const VertexPointer vertex);

// Is this edgecollection a matching?
bool is_matching(const EdgeCollection edgecollection);

// Return a pointer to an edge in edgecollection that covers the given vertex, if such 
// and edge exists.
Result edgecollection_covered_by(const EdgeCollection edgecollection, const VertexPointer vertex, EdgePointer *edge);

// Attempts to compute the complement of two edgecollections. On success, the complement
// of edgecollection_a and edgecollection_b is stored in Ret and SUCCESS is returned.
// Otherwise, FAIL is returned.
Result edgecollection_complement(const EdgeCollection edgecollection_a, const EdgeCollection edgecollection_b, EdgeCollectionPointer ret);

// Attempts to compute the union of two edgecollections. On success, the union
// of edgecollection_a and edgecollection_b is stored in Ret and SUCCESS is returned.
// Otherwise, FAIL is returned.
Result edgecollection_union(const EdgeCollection edgecollection_a, const EdgeCollection edgecollection_b, EdgeCollectionPointer ret);

// Attempts to compute the symmetric difference of two edgecollections. On success, the symmetric difference
// of edgecollection_a and edgecollection_b is stored in Ret and SUCCESS is returned.
// Otherwise, FAIL is returned.
Result edgecollection_symmetric_difference(const EdgeCollection edgecollection_a, const EdgeCollection edgecollection_b, EdgeCollectionPointer ret);

// Print the collection tos stdout
void edgecollection_print(const EdgeCollection edgecollection);

// Free the structure
Result edgecollection_destroy(EdgeCollection edgecollection);

#endif
