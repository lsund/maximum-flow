
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

EdgeSet empty_edgeset();

EdgeSet init_edgeset(const size_t size);

// Initializes an edgeset using init_edgeset and returns a pointer to it
EdgeSetPointer init_p_edgeset(const unsigned int nvertices);

// Returns true if the edgeset has no initialized elements, false otherwise.
bool edgeset_is_empty(const EdgeSet edgeset);

bool edgesets_equal(const EdgeSet edgeset_a, const EdgeSet edgeset_b);

size_t n_vertices(const EdgeSet edgeset);

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
Result symmetric_difference(const EdgeSet edgeset_a, const EdgeSet edgeset_b, EdgeSetPointer ret);

// Add an edge to the edgeset
Result set_edge(const EdgeSet edgeset, const EdgePointer edge, const unsigned int position);

Result push_edge(const EdgeSet edgeset, const EdgePointer edge);

// Get the edge at the specified position
EdgePointer get_edge(const EdgeSet edgeset , const unsigned int position);

VertexSetPointer edgeset_vertices(const EdgeSet edgeset);

// Returns true if the edgeset contains the specified edge, false otherwise
bool is_super_edgeset(const EdgeSet super, const EdgeSet sub);

// Returns true if all edges in sub are also in super
bool is_sub_edgeset(const EdgeSet sub, const EdgeSet super);

// Returns true if the edgeset contains every edge in the list of edges
// specified by edges, false otherwise
bool edgeset_contains_edge(const EdgeSet edgeset, const EdgePointer Edge);

// Returns true if the edgeset contains the specified vertex, false otherwise
bool edgeset_contains_vertex(const EdgeSet edgeset, const VertexPointer vertex);

// Return a pointer to an edge in edgeset that covers the given vertex, if such 
// and edge exists.
Result covered_by(const EdgeSet edgeset, const VertexPointer vertex, EdgePointer *edge);

// Returns an edge incident to vertex, unequal to the given edge if it exists. Returns an
// empty edge otherwise
EdgePointer find_incident_uneq(EdgeSet edgeset, VertexPointer vertex, EdgePointer uneq);

// Print the set tos stdout
void print_edgeset(const EdgeSet edgeset);

// Free the structure
Result destroy_edgeset(EdgeSet edgeset);

// Free everything but the vertices
Result soft_destroy_edgeset(EdgeSet edgeset);

#endif
