
#include "vertexcollection.h"

VertexCollection empty_vertexcollection()
{
    VertexCollection ret;
    ret.members         = NULL;
    return ret;

}

VertexCollection vertexcollection_init(const size_t init_length) 
{
    VertexCollection ret;
    if (init_length > MAX_VERTICES) {
        runtime_error("vertexcollection_init: too many vertices");
        return empty_vertexcollection();
    } else {
        ret.members           = collection_p_init(init_length);
        ret.members->capacity = init_length;
    }
    return ret;
}

VertexCollectionPointer init_p_vertexcollection(const size_t init_length)
{
    VertexCollectionPointer ret = malloc(sizeof(VertexCollection));
    *ret = vertexcollection_init(init_length);
    return ret;
}

bool vertexcollection_is_empty(const VertexCollection vertexcollection)
{
    return vertexcollection_length(vertexcollection) == 0;
}

size_t vertexcollection_length(const VertexCollection vertexcollection)
{
    return collection_length(vertexcollection.members);
}

VertexPointer vertexcollection_get(const VertexCollection vertexcollection, const unsigned int position)
{
    if (position >= vertexcollection.members->capacity) {
        runtime_error("vertexcollection_get: index out of bounds");
        return NULL;
    }
    return (VertexPointer) collection_get(vertexcollection.members, position);
}

VertexPointer vertexcollection_get_with_label(const VertexCollection vertexcollection, const Label label)
{
    size_t i;
    for (i = 0; i < vertexcollection.members->capacity; i++) {
        VertexPointer vertex = vertexcollection_get(vertexcollection, i);
        if (vertex->label == label) {
            return vertex;
        }
    }
    return NULL;
}

bool vertexcollection_contains_label(const VertexCollection vertexcollection, const Label label)
{
    size_t i;
    for (i = 0; i < vertexcollection_length(vertexcollection); i++) {
        if (label == vertexcollection_get(vertexcollection, i)->label) {
            return true;
        }
    }
    return false;
}

bool vertexcollection_is_super(const VertexCollection super, const VertexCollection sub)
{
    if (vertexcollection_length(super) != vertexcollection_length(sub)) {
        return false;
    }
    size_t i;
    for (i = 0; i < vertexcollection_length(sub); i++) {
        VertexPointer vertex = vertexcollection_get(sub, i);
        if (!vertexcollection_contains_label(super, vertex->label)) {
            return false;
        }
    }
    return true;
}

bool vertexcollection_equals(const VertexCollection vertexcollection_a, const VertexCollection vertexcollection_b)
{
    if (!collection_equals(vertexcollection_a.members, vertexcollection_b.members)) {
        return false;
    }
    size_t i;
    for (i = 0; i < vertexcollection_length(vertexcollection_a); i++) {
        VertexPointer vertex_a = vertexcollection_get(vertexcollection_a, i);
        VertexPointer vertex_b = vertexcollection_get(vertexcollection_b, i);
        if (vertex_equals(vertex_a, vertex_b)) {
            return false;
        }
    }
    return true;
}

Result vertexcollection_set(const VertexCollection vertexcollection, const VertexPointer vertex, const unsigned int position) 
{
    if (!vertexcollection_get(vertexcollection, position)) {
        runtime_error("vertexcollection_set: can only overwrite existing element");
    }
    if (vertex->label >= vertexcollection.members->capacity) {
        runtime_error("vertexcollection_set: label too large");
        return FAIL;
    }
    if (vertexcollection_contains_label(vertexcollection, vertex->label)) {
        runtime_error("vertexcollection_set: set already contains this vertex");
        return FAIL;
    } else {
        collection_set(vertexcollection.members, vertex, position);
    }
    return SUCCESS;
}

Result vertexcollection_push(const VertexCollection vertexcollection, const VertexPointer vertex)
{
    if (!vertexcollection_contains_label(vertexcollection, vertex->label)) {
        return collection_push(vertexcollection.members, vertex);
    } else {
        return FAIL;
    }
}

Result vertexcollection_complement(const VertexCollection vertexcollection_a, const VertexCollection vertexcollection_b, VertexCollectionPointer ret)
{
    size_t length_a = vertexcollection_length(vertexcollection_a);
    size_t length_b = vertexcollection_length(vertexcollection_b);
    unsigned int larger_size = larger(length_a, length_b);
    VertexPointer vertex_a;
    size_t i;
    for (i = 0; i < larger_size; i++) {
        if (i < vertexcollection_length(vertexcollection_a)) {
            vertex_a = vertexcollection_get(vertexcollection_a, i);
            if (vertex_a && !vertexcollection_contains_label(vertexcollection_b, vertex_a->label)) {
                vertexcollection_push(*ret, vertex_a);
            } 
        } else {
            break;
        }
    }
    return SUCCESS;
}


void vertexcollection_print(const VertexCollection vertexcollection)
{
    size_t i;
    for (i = 0; i < vertexcollection_length(vertexcollection); i++) {
        VertexPointer vertex = vertexcollection_get(vertexcollection, i);
            printf("%d, ", vertex->label);
    }
    printf("\n");
}

Result vertexcollection_destroy(VertexCollection vertexcollection)
{
    collection_destroy(vertexcollection.members);
    return SUCCESS;
}

