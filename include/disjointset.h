#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include "array.h"
#include "vertex.h"
#include "tree.h"

// Disjoint set datastructure implemented using tree vertices from tree.h

// Creates a singleton set O(1)
TreeVertexPointer disjointset_make(VertexPointer vertex);

// Finds the representative of this subset O(log n)
TreeVertexPointer disjointset_find(const TreeVertexPointer treevertex);

// Merges two subsets O(1)
Result disjointset_union(TreeVertexPointer treevertex_a, TreeVertexPointer treevertex_b);

#endif
