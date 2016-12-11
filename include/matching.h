
#ifndef MATCHING_H
#define MATCHING_H

#include <math.h>

#include "edgeset.h"
#include "graph.h"

// Returns true if the vertex is exposed by the edgeset
bool matching_exposing(const VertexPointer vertex, const EdgeSet matching);

// Find a vertex in vertexset not covered by matching and return its index
Result matching_find_exposed(const VertexSet vertexset, const EdgeSet matching, unsigned int *index);

// Return whether the given matching is a perfect matching of vertexset 
bool matching_is_perfect(const EdgeSet matching, const VertexSet vertexset);

// Augment a given matching along path, result is stored in ret
Result matching_augment(const EdgeSet matching, const EdgeSet path, EdgeSetPointer ret);

// Find a perfect matching in the odd circuit, after removing the vertex ignore
// from the circuit
Result matching_perfect_odd_path(EdgeSet circuit, VertexPointer ignore, EdgeSetPointer ret); 

#endif
