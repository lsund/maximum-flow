
#ifndef EDGE_SET_H
#define EDGE_SET_H

#include <stddef.h>
#include <errno.h>
#include <stdlib.h>

#include "array.h"
#include "util.h"
#include "edge.h"
#include "vertexset.h"

// A set of edges, no duplicates. 
// Field set:       actual references to the edges. 
// Field nvertices: how many vertices are touched by this set of edges? 
// Field contains:  bitmap for keeping track of which elements are in the set
typedef struct edgeset {
    ArrayPointer set;
} EdgeSet, *EdgeSetPointer;

EdgeSet edgeset_empty();

EdgeSet edgeset_init(const size_t size);

// Initializes an edgeset using edgeset_init and returns a pointer to it
EdgeSetPointer edgeset_p_init(const unsigned int nvertices);

// Returns true if the edgeset has no initialized elements, false otherwise.
bool edgeset_is_empty(const EdgeSet edgeset);

bool edgesets_equal(const EdgeSet edgeset_a, const EdgeSet edgeset_b);

size_t edgeset_vertex_count(const EdgeSet edgeset);

// Attempts to compute the complement of two edgesets. On success, the complement
// of edgeset_a and edgeset_b is stored in Ret and SUCCESS is returned.
// Otherwise, FAIL is returned.
Result edgeset_complement(const EdgeSet edgeset_a, const EdgeSet edgeset_b, EdgeSetPointer ret);

// Attempts to compute the union of two edgesets. On success, the union
// of edgeset_a and edgeset_b is stored in Ret and SUCCESS is returned.
// Otherwise, FAIL is returned.
Result edgeset_union(const EdgeSet edgeset_a, const EdgeSet edgeset_b, EdgeSetPointer ret);

// Attempts to compute the symmetric difference of two edgesets. On success, the symmetric difference
// of edgeset_a and edgeset_b is stored in Ret and SUCCESS is returned.
// Otherwise, FAIL is returned.
Result edgeset_symmetric_difference(const EdgeSet edgeset_a, const EdgeSet edgeset_b, EdgeSetPointer ret);

// Add an edge to the edgeset
Result edgeset_set(const EdgeSet edgeset, const EdgePointer edge, const unsigned int position);

Result edgeset_push(const EdgeSet edgeset, const EdgePointer edge);

// Get the edge at the specified position
EdgePointer edgeset_get(const EdgeSet edgeset , const unsigned int position);

// The vertices of this edgeset
VertexSet edgeset_vertices(const EdgeSet edgeset);

// Returns true if the edgeset contains the specified edge, false otherwise
bool edgeset_is_super(const EdgeSet super, const EdgeSet sub);

// Returns true if all edges in sub are also in super
bool edgeset_is_sub(const EdgeSet sub, const EdgeSet super);

// Returns true if the edgeset contains every edge in the list of edges
// specified by edges, false otherwise
bool edgeset_contains_edge(const EdgeSet edgeset, const EdgePointer edge);

// Returns true if the edgeset contains the specified vertex, false otherwise
bool edgeset_contains_vertex(const EdgeSet edgeset, const VertexPointer vertex);

// Is this edgeset a matching?
bool is_matching(const EdgeSet edgeset);

// Return a pointer to an edge in edgeset that covers the given vertex, if such 
// and edge exists.
Result edgeset_covered_by(const EdgeSet edgeset, const VertexPointer vertex, EdgePointer *edge);

// Returns an edge incident to vertex, unequal to the given edge if it exists. Returns an
// empty edge otherwise
EdgePointer edgeset_find_incident_uneq(EdgeSet edgeset, VertexPointer vertex, EdgePointer uneq);

// Print the set tos stdout
void edgeset_print(const EdgeSet edgeset);

// Free the structure
Result edgeset_destroy(EdgeSet edgeset);

#endif
