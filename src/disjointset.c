
#include "disjointset.h"

TreeVertexPointer make_dset(VertexPointer vertex)
{
    TreeVertexPointer ret = make_p_tree_vertex(vertex);
    ret->is_root = true;
    return ret;
}

TreeVertexPointer dset_find(const TreeVertexPointer treevertex)
{
    if (treevertex->is_root) {
        return treevertex;
    } else {
        return dset_find(treevertex->parent);
    }
}

Result dset_union(TreeVertexPointer treevertex_a, TreeVertexPointer treevertex_b)
{
    TreeVertexPointer root_a, root_b;
    root_a = dset_find(treevertex_a);
    root_b = dset_find(treevertex_b);
    if (root_a->content->label == root_b->content->label) {
        return SUCCESS;
    } else {
        if (root_a->rank < root_b->rank) {
            root_a->parent = root_b;
            root_a->is_root = false;
        } else if (root_a->rank > root_b->rank) {
            root_b->parent = root_a;
            root_b->is_root = false;
        } else {
            root_b->parent = root_a;
            root_b->is_root = false;
            root_a->rank += 1;
        }
        return SUCCESS;
    }
}

