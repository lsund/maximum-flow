
#include "vertexcollection.h"

VertexCollection vertexcollection_empty()
{
    VertexCollection ret;
    ret.members = NULL;
    return ret;

}

bool vertexcollection_is_empty(const VertexCollection vertices)
{
    return vertexcollection_length(vertices) == 0;
}

VertexCollection vertexcollection_init(const size_t init_length) 
{
    VertexCollection ret;
    if (init_length > MAX_VERTICES) {
        runtime_error("vertexcollection_init: too many vertices");
        return vertexcollection_empty();
    } else {
        ret.members = collection_p_init(init_length);
    }
    return ret;
}

VertexCollection vertexcollection_init_min()
{
    return vertexcollection_init(COLL_MIN_SIZE);
}

VertexCollectionPointer init_p_vertexcollection(const size_t init_length)
{
    VertexCollectionPointer ret = malloc(sizeof(VertexCollection));
    *ret = vertexcollection_init(init_length);
    return ret;
}

size_t vertexcollection_length(const VertexCollection vertices)
{
    return collection_length(vertices.members);
}

VertexPointer vertexcollection_get(
        const VertexCollection vertices, 
        const unsigned int position
    )
{
    if (position >= vertices.members->capacity) {
        runtime_error("vertexcollection_get: index out of bounds");
    }
    return (VertexPointer) collection_get(vertices.members, position);
}

void vertexcollection_push(
        const VertexCollection vertices,
        const VertexPointer vertex
    )
{
    collection_push(vertices.members, vertex);
}


void vertexcollection_print(const VertexCollection vertices)
{
    size_t i;
    for (i = 0; i < vertexcollection_length(vertices); i++) {
        Vertex vertex = *vertexcollection_get(vertices, i);
            printf("%d, ", vertex.label);
    }
    printf("\n");
}

Result vertexcollection_destroy(VertexCollection vertices)
{
    collection_destroy(vertices.members);
    return SUCCESS;
}

