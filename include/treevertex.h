#ifndef TREE_VERTEX_H
#define TREE_VERTEX_H

#include "edgecollection.h"
#include "stddef.h" 

// A vertex of a tree.
// Field content:   The actual vertex this tree vertex represents
// Field children:  The set of children vertices
typedef struct treevertex {
    VertexPointer content;
    size_t rank;
    void *parent;
    bool is_root;
    CollectionPointer children;
} TreeVertex, *TreeVertexPointer;

// Creates a pointer to a treevertex using a vertex
TreeVertexPointer treevertex_p_make(VertexPointer vertex);

// Creates a pointer to a treevertex using a label
TreeVertexPointer treevertex_p_make_label(const Label label);

// Inserts The treevertex tree_a under the specified label in in the
// treevertex tree_b
Result treevertex_insert(
        TreeVertexPointer tree_a, 
        const Label under, 
        TreeVertexPointer tree_b
    );

// Return a pointer to the TreeVertex corresponding to the given vertex that is
// contained in the treevertex root.
TreeVertexPointer treevertex_get(TreeVertexPointer root, VertexPointer content);

// The child of the root, identical to the specified treevertex
// reference
TreeVertexPointer treevertex_get_root_child(TreeVertexPointer of);

// The number of ancestors starting in root + 1
size_t treevertex_size(TreeVertexPointer root);

// Attempts to return the vertices of the tree rooted in root. Returns SUCCESS
// when successful with the vertices stored as a vertexcollection in the return
// parameter. Returns FAIL otherwise.
void treevertex_vertices(TreeVertexPointer root, VertexCollection ret_vertexcollection);

// Stores references to all vertices that have even / odd distance to the root
// of the tree the two respective sets 
void treevertex_odds_evens(TreeVertexPointer root, bool even, VertexCollectionPointer evens, VertexCollectionPointer odds);

// Prints a string representation of the tree vertex
void treevertex_print(TreeVertexPointer root);

// The subtree under root, which has it's own root under the specified vertex
TreeVertexPointer treevertex_subtree(TreeVertexPointer root, VertexPointer under);

// frees the structure
Result treevertex_destroy(TreeVertexPointer root);

#endif
