
#include "tree.h"

void tree_merge(VertexPointer vertex_a, VertexPointer vertex_b)
{
    vertex_b->parent = vertex_a;
}

VertexPointer tree_find_root(const VertexPointer vertex)
{
    if (!vertex->parent) {
        return vertex;
    }

    VertexPointer current = vertex;
    while (current->parent) {
        current = current->parent;
    }

    return current;
}

CollectionPointer tree_path_to_root(const VertexPointer vertex)
{
    CollectionPointer ret = collection_p_init(ARRAY_MIN_SIZE);
    collection_push(ret, vertex);
    if (!vertex->parent) {
        return ret;
    }
    VertexPointer current = vertex;
    while (current->parent) {
        current = current->parent;
        collection_push(ret, current);
    }
    return ret;
}

void tree_invert(VertexPointer vertex)
{
    CollectionPointer path = tree_path_to_root(vertex);
    size_t i;
    vertex->parent = NULL;
    for (i = 1; i < collection_length(path); i++) {
        VertexPointer current = (VertexPointer) collection_get(path, i);
        VertexPointer previous = (VertexPointer) collection_get(path, i - 1);
        current->parent = previous;
    }
    collection_destroy(path);
}

