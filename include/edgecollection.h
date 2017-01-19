
#ifndef EDGE_COLLECTION_H
#define EDGE_COLLECTION_H

#include "edge.h"
#include "util.h"
#include "vertexcollection.h"
#include "map.h"

typedef struct edgecollection {
    CollectionPointer members;
    Map indices;
} EdgeCollection, *EdgeCollectionPointer;

// Returns a dummy edgecollection with it's collection set to NULL
EdgeCollection edgecollection_empty();

// Returns the edgecollection with its collection initialized, with an initial capacity of
// size.
EdgeCollection edgecollection_init(const size_t size);

// Initializes an edgecollection using edgecollection_init and returns a pointer to it
EdgeCollectionPointer edgecollection_p_init(const unsigned int nvertices);

void edgecollection_reset(EdgeCollection edges);

// Return the number of elements currently in this collection
size_t edgecollection_length(const EdgeCollection edges);

// Get the edge at the specified position
EdgePointer edgecollection_get(const EdgeCollection edges, const unsigned int position);

EdgePointer edgecollection_get_reference(const EdgeCollection edges, const Edge edge);

int edgecollection_index_of(const EdgeCollection edges, const Edge edge);

size_t edgecollection_vertex_count(const EdgeCollection edges);

// The vertices of this edgecollection
VertexCollection edgecollection_vertices(const EdgeCollection edges);

// Sets the last element to the specified edge, and increments the number of
// elements
Result edgecollection_push(const EdgeCollection edges, const EdgePointer edge);

// Removes the element from the edgecollection
/* void edgecollection_remove(EdgeCollection edges, const EdgePointer edge); */
void edgecollection_remove(EdgeCollectionPointer edges, const EdgePointer edge);

// Returns true if the edgecollection has no initialized elements, false otherwise.
bool edgecollection_is_empty(const EdgeCollection edges);

bool edgecollection_equals(const EdgeCollection edgecollection_a, const EdgeCollection edgecollection_b);

// Returns true if the edgecollection contains the specified edge, false otherwise
bool edgecollection_is_super(const EdgeCollection super, const EdgeCollection sub);

// Returns true if all edges in sub are also in super
bool edgecollection_is_sub(const EdgeCollection sub, const EdgeCollection super);

// Returns true if the edgecollection contains every edge in the list of edges
// specified by edges, false otherwise
bool edgecollection_contains_edge(const EdgeCollection edges, const EdgePointer edge);

// Returns true if the edgecollection contains the specified vertex, false otherwise
bool edgecollection_contains_vertex(const EdgeCollection edges, const VertexPointer vertex);

// Is this edgecollection a matching?
bool is_matching(const EdgeCollection edges);

// Return a pointer to an edge in edgecollection that covers the given vertex, if such 
// and edge exists.
Result edgecollection_covered_by(const EdgeCollection edges, const VertexPointer vertex, EdgePointer *edge);

void edgecollection_link(const EdgeCollection edges_a, const EdgeCollection edges_b);

// Attempts to compute the complement of two edgecollections. On success, the complement
// of edgecollection_a and edgecollection_b is stored in Ret and SUCCESS is returned.
// Otherwise, FAIL is returned.
Result edgecollection_complement(const EdgeCollection edgecollection_a, const EdgeCollection edgecollection_b, EdgeCollectionPointer ret);

// Attempts to compute the union of two edgecollections. On success, the union
// of edgecollection_a and edgecollection_b is stored in Ret and SUCCESS is returned.
// Otherwise, FAIL is returned.
EdgeCollection edgecollection_union(const EdgeCollection edgecollection_a, const EdgeCollection edgecollection_b);

// Attempts to compute the symmetric difference of two edgecollections. On success, the symmetric difference
// of edgecollection_a and edgecollection_b is stored in Ret and SUCCESS is returned.
// Otherwise, FAIL is returned.
Result edgecollection_symmetric_difference(const EdgeCollection edgecollection_a, const EdgeCollection edgecollection_b, EdgeCollectionPointer ret);

// Print the collection tos stdout
void edgecollection_print(const EdgeCollection edges);

// Free the structure
Result edgecollection_destroy(EdgeCollection edges);

#endif
