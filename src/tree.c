
#include "tree.h"

static EdgeCollection vertexcollection_to_edgecollection(const VertexCollection vertices, const EdgeCollection all_edges)
{
    size_t i;
    EdgeCollection epath_rev = edgecollection_init(ARRAY_MIN_SIZE);
    for (i = 0; i < vertexcollection_length(vertices) - 1; i++) {
        VertexPointer first = vertexcollection_get(vertices, i);
        VertexPointer second = vertexcollection_get(vertices, i + 1);
        Edge edge = edge_make_vertices(*first, *second);
        EdgePointer edge_p = edgecollection_get_reference(all_edges, edge_swapped(edge));
        edgecollection_push(epath_rev, edge_p);
    }
    EdgeCollection epath = edgecollection_init(ARRAY_MIN_SIZE);
    // Temp code[
    for (i = edgecollection_length(epath_rev); i > 0; i--) {
        EdgePointer edge = edgecollection_get(epath_rev, i - 1);
        edgecollection_push(epath, edge);
    }
    return epath;
}

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
    VertexCollection ret = vertexcollection_init(ARRAY_MIN_SIZE);
    vertexcollection_push(ret, vertex);
    if (!vertex->parent) {
        return ret;
    }
    VertexPointer current = vertex;
    while (current->parent) {
        current = current->parent;
        vertexcollection_push(ret, current);
    }
    return ret;
}

EdgeCollection tree_edgepath_from_root(const VertexPointer vertex, const EdgeCollection all_edges)
{
    VertexCollection path = tree_path_to_root(vertex);
    return vertexcollection_to_edgecollection(path, all_edges);
}

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

