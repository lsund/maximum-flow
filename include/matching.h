
#ifndef MATCHING_H
#define MATCHING_H

#include <math.h>

#include "edgeset.h"
#include "graph.h"

// Is this edgeset a matching?
bool is_matching(const EdgeSet edgeset);

// Returns true if the vertex is exposed by the edgeset
bool is_exposed(const VertexPointer vertex, const EdgeSet matching);

// Find a vertex in vertexset not covered by matching and return its index
Result find_exposed(const VertexSet vertexset, const EdgeSet matching, unsigned int *index);

// Return whether the given matching is a perfect matching of vertexset 
bool is_perfect(const EdgeSet matching, const VertexSet vertexset);

// Augment a given matching along path, result is stored in ret
Result augment(const EdgeSet matching, const EdgeSet path, EdgeSetPointer ret);

// Read the hint matching for a given graph from a file and store it in ret.
// This function checks correctness of given hint extensively
Result set_hint_matching(const char *fp, Graph graph, EdgeSetPointer ret);

// Finds a maximal matching by looping over the edgeset and adding each edge to
// the matching when possible 
Result greedy_maximal_matching(EdgeSet edgeset, EdgeSetPointer ret);

// Find a perfect matching in the odd circuit, after removing the vertex ignore
// from the circuit
Result perfect_matching_odd_path(EdgeSet circuit, VertexPointer ignore, EdgeSetPointer ret); 

#endif
