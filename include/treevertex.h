#ifndef TREE_VERTEX_H
#define TREE_VERTEX_H

#include "edgeset.h"
#include "stddef.h" 

// A vertex of a tree.
// Field content:   The actual vertex this tree vertex represents
// Field children:  The set of children vertices
typedef struct treevertex {
    VertexPointer content;
    size_t rank;
    void * parent;
    bool is_root;
    ArrayPointer children;
} TreeVertex, *TreeVertexPointer;

// Creates a pointer to a treevertex using a vertex
TreeVertexPointer make_p_tree_vertex(VertexPointer vertex);

// Creates a pointer to a treevertex using a label
TreeVertexPointer make_p_tree_vertex_label(const Label label);

Result treevertex_insert(
        TreeVertexPointer tree_a, 
        const Label under, 
        TreeVertexPointer tree_b
    );

// Return a pointer to the TreeVertex corresponding to the given vertex 
TreeVertexPointer treevertex_get(TreeVertexPointer root, VertexPointer content);

// Attempts to return the vertices of the tree rooted in root. Returns SUCCESS
// when successful with the vertices stored as a vertexset in the return
// parameter. Returns FAIL otherwise.
Result treevertex_vertices(TreeVertexPointer root, VertexSet ret_vertexset);

void treevertex_odds_evens(TreeVertexPointer root, bool even, VertexSetPointer evens, VertexSetPointer odds);

void treevertex_print(TreeVertexPointer root);

TreeVertexPointer treevertex_subtree(TreeVertexPointer root, VertexPointer under);

// frees the structure
Result treevertex_destroy(TreeVertexPointer root);

#endif
