#ifndef TREE_H
#define TREE_H

#include "treevertex.h"

// A tree graph, a undirected graph with no cycles.
// Field root:      the root vertex
typedef struct tree {
    TreeVertexPointer root;
} Tree, *TreePointer;

// Construct a empty tree
Tree tree_empty();

// Construct a tree with just a rootvertex as given;
Tree tree_singleton(const VertexPointer vertex);

// Construct a tree with just a rootvertex with the specified label;
Tree tree_singleton_label(const Label rootlabel);

// Construct a tree using a treevertexpointer;
Tree tree_make(const TreeVertexPointer root);

Tree tree_get(Tree tree, VertexPointer vertex);

size_t tree_size(Tree tree);

// Attempts to tree_insert the tree-vertex under a vertex with the specified label in
// the tree. Retruns SUCCESS if successful, FAIL otherwise.
Result tree_insert(TreeVertexPointer treevertex, const Label under, Tree tree);

Result tree_insert_under_root(VertexPointer vertex, Tree tree);

// Stores references to all vertices that have even / odd distance to the root
// of the tree the two respective sets 
void tree_evens_odds(Tree tree, VertexCollectionPointer evens, VertexCollectionPointer odds);

// See tree_evens_odds
void tree_evens(Tree tree, VertexCollectionPointer evens);

// See tree_evens_odds
void tree_odds(Tree tree, VertexCollectionPointer odds);

// Traverse the tree, print to stdout
void tree_print(Tree tree);

// free the structure
Result tree_destroy(Tree tree);

#endif
