
#include "tree-simple.h"

STreePointer stree_singleton(const VertexPointer vertex)
{
    STreePointer ret = malloc(sizeof(STree));
    ret->parent = NULL;
    ret->vertex = vertex;
    return ret;
}

STreePointer stree_singleton_label(const Label label)
{
    return stree_singleton(vertex_p_make(label));
}

void stree_merge(STreePointer tree_a, STreePointer tree_b)
{
    tree_b->parent = tree_a;
}

