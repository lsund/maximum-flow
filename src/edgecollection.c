
#include "edgecollection.h"

EdgeCollection edgecollection_empty()
{
    EdgeCollection ret;
    ret.members = NULL;
    return ret;
}

EdgeCollection edgecollection_init(const size_t size)
{
    if (size > MAX_EDGES) {
        runtime_error("Too large edgecollection");
        return edgecollection_empty();
    } else {
        EdgeCollection ret;
        ret.members = collection_p_init(size);
        return ret;
    }
}

EdgeCollection edgecollection_init_min()
{
    return edgecollection_init(COLL_MIN_SIZE);
}

size_t edgecollection_length(const EdgeCollection edges)
{
    return collection_length(edges.members);
}

EdgePointer edgecollection_get(
        const EdgeCollection edges,
        const unsigned int position
    )
{
    if (position >= edges.members->capacity) {
        runtime_error("vertexcollection_get: index out of bounds");
        return NULL;
    }
    return collection_get(edges.members, position);
}

VertexCollection edgecollection_vertices(const EdgeCollection edges)
{
    VertexCollection vertices = vertexcollection_init(COLL_MIN_SIZE);
    size_t i;
    for (i = 0; i < edgecollection_length(edges); i++) {
        EdgePointer edge = edgecollection_get(edges, i);
        Vertex first = edge->first;
        Vertex second = edge->second;
        if (!vertexcollection_contains_label(vertices, first.label)) {
            vertexcollection_push(vertices, vertex_p_make(first.label));
        }
        if (!vertexcollection_contains_label(vertices, second.label)) {
            vertexcollection_push(vertices, vertex_p_make(second.label));
        }
    }
    return vertices;
}

void edgecollection_push(const EdgeCollection edges, const EdgePointer edge)
{
    collection_push(edges.members, edge);
}

void edgecollection_print(const EdgeCollection edges)
{
    size_t i;
    for (i = 0; i < edgecollection_length(edges); i++) {
        EdgePointer edge = edgecollection_get(edges, i);
        printf("(%d, %d), ", edge->first.label, edge->second.label);
    }
    printf("\n");
}

void edgecollection_destroy(EdgeCollection edges)
{
    collection_destroy(edges.members);
}

