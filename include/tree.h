#ifndef TREE_H
#define TREE_H

#include "treevertex.h"

// A tree graph, a undirected graph with no cycles.
// Field root:      the root vertex
// Field contains:  bitmap for keeping track of which vertices are in tree
// Field maxsize:   limit for |V| for this tree
typedef struct tree {
    TreeVertexPointer root;
    bool *contains;
    size_t maxsize;
    size_t *nvertices;
} Tree, *TreePointer;

// Construct a empty tree
Tree tree_empty();

// Construct a tree with just a rootvertex as given, capable of
// having a maximum number of vertices specified as maxsize
Tree tree_singleton(const VertexPointer vertex, const size_t maxsize);

// Construct a tree with just a rootvertex with the specified label, capable of
// having a maximum number of vertices specified as maxsize
Tree tree_singleton_label(const Label rootlabel, const size_t maxsize);

// Construct a tree using a treevertexpointer capable of having a maximum number
// of vertices specified as maxsize
Tree tree_make(const TreeVertexPointer root, const size_t maxsize);

// Returns true if the vertex contains the specified vertex, false otherwise.
bool tree_contains_vertex(Tree tree, VertexPointer vertex);

// Attempts to tree_insert the tree-vertex under a vertex with the specified label in
// the tree. Retruns SUCCESS if successful, FAIL otherwise.
Result tree_insert(TreeVertexPointer treevertex, const Label under, Tree tree);

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
