
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
    VertexSet vertices;
    bool *contains_edge, *contains_vertex;
    unsigned int *indices;
} EdgeSet, *EdgeSetPointer;

// Initializes an edgeset of size nvertices * nvertices. All edges in this set
// get an uninitialized value
EdgeSet init_edgeset(const unsigned int nvertices);

// Returns true if the edgeset has no initialized elements, false otherwise.
bool edgeset_is_empty(const EdgeSet edgeset);

// Sets all fields in the copy to their equivalent values in the edgeset
void copy_edgeset(const EdgeSet edgeset, const EdgeSetPointer copy);

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

// Attempts to compute an edgeset as a path from the given vertexset. For
// example, if the vertexset contains {a, b, c, d ... } this procedure will set ret
// to { {a,b}, {b, c}, {c,d}, ... }. Will return SUCCESS if this was successful,
// FAIL otherwise.
Result edgepath_from_vertexset(const VertexSet vertexset, EdgeSetPointer ret);

// Add an edge to the edgeset
Result add_edge(EdgeSet edgeset, Edge edge);

// Get the edge at the specified position
EdgePointer get_edge_at_position(const EdgeSet edgeset , const unsigned int position);

// Returns true if the edgeset contains the specified edge, false otherwise
bool edgeset_contains_edge(const EdgeSet edgeset, const Edge edge);

// Returns true if the edgeset contains the specified vertex, false otherwise
bool edgeset_contains_vertex(const EdgeSet edgeset, const Vertex vertex);

// Returns true if the edgeset contains every edge in the list of edges
// specified by edges, false otherwise
bool edgeset_contains_edges(
        const EdgeSet edgeset,
        const EdgePointer edges,
        size_t length
    );

// Print the set tos stdout
void print_edgeset(const EdgeSet edgeset);

// Free the structure
Result destroy_edgeset(EdgeSet edgeset);

#endif
