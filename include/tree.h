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

// invert the vertex so that the vertex belongs to so it is rooted at vertex instead of
// tree_find_root(vertex)
void tree_invert(VertexPointer vertex);

// Link a vertex rooted at u with node v of another vertex so that tree_a becomes the
// parent of tree_b
void tree_merge(const VertexPointer vertex_a, VertexPointer vertex_b);

// Split the trees between the specified vertex and the parent of vertex
void tree_split(const VertexPointer vertex);

#endif

