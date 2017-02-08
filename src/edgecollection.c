
#include "edgecollection.h"

EdgeCollection edgecollection_empty()
{
    EdgeCollection ret;
    ret.members = NULL;
    ret.indices = NULL;
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
        ret.indices = map_create();
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

EdgePointer edgecollection_get_reference(
        const EdgeCollection edges,
        const Edge edge
    )
{
    int index = edgecollection_index_of(edges, edge);
    return index == -1 ? NULL : edgecollection_get(edges, index);
}

int edgecollection_index_of(const EdgeCollection edges, const Edge edge)
{
    if (map_exists(edges.indices, edge_hash(edge))) {
        return map_get(edges.indices, edge_hash(edge));
    } else {
        return -1;
    }
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

Result edgecollection_push(const EdgeCollection edges, const EdgePointer edge)
{
    if (!edgecollection_contains_edge(edges, edge)) {
        map_put(edges.indices, edge_hash(*edge), edgecollection_length(edges));
        collection_push(edges.members, edge);
        return SUCCESS;
    } else {
        return FAIL;
    }
}

void edgecollection_remove(EdgeCollectionPointer edges, const EdgePointer edge)
{
    size_t i, n_edges = edgecollection_length(*edges);
    EdgeCollection edges_val = *edges;
    EdgeCollection temp = edgecollection_init(n_edges);
    for (i = 0; i < n_edges; i++) {
        EdgePointer current = edgecollection_get(edges_val, i);
        if (!edge_equals(edge, current)) {
            edgecollection_push(temp, current);  
        }
    }
    edgecollection_destroy(edges_val);
    *edges = temp;
}

bool edgecollection_contains_edge(
        const EdgeCollection edges,
        const EdgePointer edge
    )
{
    unsigned int key = edge_hash(*edge);
    return map_exists(edges.indices, key);
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
    map_destroy(edges.indices);
}

