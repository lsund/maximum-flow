#ifndef TREE_H
#define TREE_H

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

// Creates a pointer to a treevertex using a vertex
TreeVertexPointer make_p_tree_vertex(VertexPointer vertex);

// Creates a pointer to a treevertex using a label
TreeVertexPointer make_p_tree_vertex_label(const Label label);

// Construct a empty tree
Tree empty_tree();

// Construct a tree with just a rootvertex as given, capable of
// having a maximum number of vertices specified as maxsize
Tree make_singleton_tree(const VertexPointer vertex, const size_t maxsize);

// Construct a tree with just a rootvertex with the specified label, capable of
// having a maximum number of vertices specified as maxsize
Tree make_singleton_tree_label(const Label rootlabel, const size_t maxsize);

// Construct a tree using a treevertexpointer capable of having a maximum number
// of vertices specified as maxsize
Tree make_tree(const TreeVertexPointer root, const size_t maxsize);

// Attempts to return the vertices of the tree rooted in root. Returns SUCCESS
// when successful with the vertices stored as a vertexset in the return
// parameter. Returns FAIL otherwise.
Result tree_vertices(TreeVertexPointer root, VertexSet ret_vertexset);

// Return a pointer to the TreeVertex corresponding to the given vertex 
TreeVertexPointer get_tree_vertex(TreeVertexPointer root, VertexPointer content);

// Returns true if the vertex contains the specified vertex, false otherwise.
bool tree_contains_vertex(Tree tree, VertexPointer vertex);

// Attempts to insert the tree-vertex under a vertex with the specified label in
// the tree. Retruns SUCCESS if successful, FAIL otherwise.
Result insert(TreeVertexPointer treevertex, const Label under, Tree tree);

// Stores references to all vertices that have even / odd distance to the root
// of the tree the two respective sets 
void tree_evens_odds(Tree tree, VertexSetPointer evens, VertexSetPointer odds);

// See tree_evens_odds
void tree_evens(Tree tree, VertexSetPointer evens);

// See tree_evens_odds
void tree_odds(Tree tree, VertexSetPointer odds);

// Traverse the tree, print to stdout
void traverse(Tree tree);

// free the structure
Result destroy_tree(Tree tree);

// frees the structure
Result destroy_tree_vertex(TreeVertexPointer root);

// Just testing exports
Result (*t_insert_aux)(
        TreeVertexPointer tree_a, 
        const Label under, 
        TreeVertexPointer tree_b
    );

#endif
