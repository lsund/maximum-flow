#ifndef TREE_SIMPLE__H
#define TREE_SIMPLE__H

#include "graph.h"

typedef struct stree STree, *STreePointer;

struct stree {
    VertexPointer vertex;
    STreePointer parent;
};

// A singleton tree, created from a label 
STreePointer stree_singleton_label(const Label label);

// A singleton trere, created from a vertex reference
STreePointer stree_singleton(const VertexPointer vertex);

// Find the root of the tree that v belongs to
VertexPointer stree_find_root(const STreePointer tree);

// Find the minimum key on the path from v to the root if its tree
VertexPointer stree_find_min(STreePointer tree);

// The path from the vertex to the root, as a reference to a collection
CollectionPointer stree_path_to_root(const STreePointer tree);

// Add the value delta to the keys of all nodes on the path from v to the root
// of its tree
void stree_add_cost(STreePointer tree, unsigned int delta);

// invert the tree so that the tree belongs to so it is rooted at tree instead of
// stree_find_root(tree)
void stree_invert(STreePointer tree);

// Link a tree rooted at u with node v of another tree so that tree_a becomes the
// parent of tree_b
void stree_merge(STreePointer tree_a, STreePointer tree_b);

// Split the trees between the specified tree and the parent of tree
void stree_split(STreePointer tree);

#endif

