#ifndef TREE_SIMPLE__H
#define TREE_SIMPLE__H

#include "graph.h"

// Find the root of the vertex that v belongs to
VertexPointer tree_find_root(const VertexPointer vertex);

// Find the minimum key on the path from v to the root if its vertex
VertexPointer tree_find_min(VertexPointer vertex);

// The path from the vertex to the root, as a reference to a collection
CollectionPointer tree_path_to_root(const VertexPointer vertex);

// Add the value delta to the keys of all nodes on the path from v to the root
// of its vertex
void tree_add_cost(VertexPointer vertex, unsigned int delta);

// invert the vertex so that the vertex belongs to so it is rooted at vertex instead of
// tree_find_root(vertex)
void tree_invert(VertexPointer vertex);

// Link a vertex rooted at u with node v of another vertex so that tree_a becomes the
// parent of tree_b
void tree_merge(VertexPointer vertex_a, VertexPointer vertex_b);

// Split the trees between the specified vertex and the parent of vertex
void tree_split(VertexPointer vertex);

#endif

