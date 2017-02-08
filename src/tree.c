
#include "tree.h"


void tree_merge(VertexPointer vertex_a, VertexPointer vertex_b)
{
    vertex_b->parent = vertex_a;
}

VertexPointer tree_find_branch(const VertexPointer vertex)
{
    if (!vertex->parent) {
        runtime_error("root does not belong to a branch");
    }

    VertexPointer current = vertex;
    while (current->parent->parent) {
        current = current->parent;
    }

    return current;
}

VertexPointer tree_find_root(const VertexPointer vertex)
{
    if (!vertex->parent) {
        return vertex;
    } else {
        return tree_find_branch(vertex)->parent;
    }
}

VertexCollection tree_path_to_root(const VertexPointer vertex)
{
    VertexCollection ret = vertexcollection_init(COLL_MIN_SIZE);
    vertexcollection_push(ret, vertex);
    if (!vertex->parent) {
        return ret;
    }
    VertexPointer current = vertex;
    while (current->parent) {
        if (current == current->parent->parent) {
            runtime_error("tree_path_to_root: both are eachothers parents");
        }
        current = current->parent;
        vertexcollection_push(ret, current);
    }
    return ret;
}

/* EdgeCollection tree_edgepath_to_branch(const VertexPointer vertex, const EdgeCollection all_edges) */
/* { */
/*     VertexCollection path = tree_path_to_root(vertex); */
/*     vertexcollection_pop(path); */
/*     return vertexcollection_to_edgecollection(path, all_edges, false); */
/* } */

/* EdgeCollection tree_edgepath_from_branch(const VertexPointer vertex, const EdgeCollection all_edges) */
/* { */
/*     VertexCollection path = tree_path_to_root(vertex); */
/*     vertexcollection_pop(path); */
/*     return vertexcollection_to_edgecollection(path, all_edges, true); */
/* } */

void tree_invert(VertexPointer vertex)
{
    VertexCollection path = tree_path_to_root(vertex);
    size_t i;
    vertex->parent = NULL;
    for (i = 1; i < vertexcollection_length(path); i++) {
        VertexPointer current = (VertexPointer) vertexcollection_get(path, i);
        VertexPointer previous = (VertexPointer) vertexcollection_get(path, i - 1);
        current->parent = previous;
    }
    vertexcollection_destroy(path);
}

