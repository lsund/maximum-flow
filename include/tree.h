#ifndef TREE_SIMPLE__H
#define TREE_SIMPLE__H

#include "graph.h"

// Find the branch of the tree that the vertex belongs to ie. the subtree with
// parent root.
VertexPointer tree_find_branch(const VertexPointer vertex);

// Find the root of the tree that vertex belongs to
VertexPointer tree_find_root(const VertexPointer vertex);

// Find the minimum key on the path from v to the root if its vertex
VertexPointer tree_find_min(const VertexPointer vertex);

// The path from the vertex to the root, as a reference to a collection
VertexCollection tree_path_to_root(const VertexPointer vertex);

EdgeCollection tree_edgepath_to_root(const VertexPointer vertex, const EdgeCollection all_edges);

/* EdgeCollection tree_edgepath_to_branch(const VertexPointer vertex, const EdgeCollection all_edges); */

/* EdgeCollection tree_edgepath_from_branch(const VertexPointer vertex, const EdgeCollection all_edges); */

// Add the value delta to the keys of all nodes on the path from v to the root
// of its vertex
void tree_add_cost(const VertexPointer vertex, const unsigned int delta);

// invert the vertex so that the vertex belongs to so it is rooted at vertex instead of
// tree_find_root(vertex)
void tree_invert(VertexPointer vertex);

// Link a vertex rooted at u with node v of another vertex so that tree_a becomes the
// parent of tree_b
void tree_merge(const VertexPointer vertex_a, VertexPointer vertex_b);

// Split the trees between the specified vertex and the parent of vertex
void tree_split(const VertexPointer vertex);

#endif

