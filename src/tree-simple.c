
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

VertexPointer stree_find_root(const STreePointer tree)
{
    if (!tree->parent) {
        return tree->vertex;
    }

    STreePointer current = tree;
    while (current->parent) {
        current = current->parent;
    }

    return current->vertex;
}

CollectionPointer stree_path_to_root(const STreePointer tree)
{
    CollectionPointer ret = collection_p_init(ARRAY_MIN_SIZE);
    collection_push(ret, tree);
    if (!tree->parent) {
        return ret;
    }
    STreePointer current = tree;
    while (current->parent) {
        current = current->parent;
        collection_push(ret, current);
    }
    return ret;
}

void stree_invert(STreePointer tree)
{
    CollectionPointer path = stree_path_to_root(tree);
    size_t i;
    tree->parent = NULL;
    for (i = 1; i < collection_length(path); i++) {
        STreePointer current = (STreePointer) collection_get(path, i);
        STreePointer previous = (STreePointer) collection_get(path, i - 1);
        current->parent = previous;
    }
    collection_destroy(path);
}

