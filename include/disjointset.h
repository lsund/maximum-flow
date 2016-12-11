#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include "array.h"
#include "vertex.h"
#include "tree.h"

// Disjoint set datastructure implemented using tree vertices from tree.h

// Creates a singleton set O(1)
TreeVertexPointer make_dset(VertexPointer vertex);

// Finds the representative of this subset O(log n)
TreeVertexPointer dset_find(const TreeVertexPointer treevertex);

// Merges two subsets O(1)
Result dset_union(TreeVertexPointer treevertex_a, TreeVertexPointer treevertex_b);

#endif
