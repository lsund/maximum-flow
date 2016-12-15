
#include "vertexset.h"

VertexSet empty_vertexset()
{
    VertexSet ret;
    ret.set         = NULL;
    return ret;

}

VertexSet vertexset_init(const size_t init_length) 
{
    VertexSet ret;
    if (init_length > MAX_VERTICES) {
        runtime_error("vertexset_init: too many vertices");
        return empty_vertexset();
    } else {
        ret.set         = array_p_init(init_length);
        ret.set->capacity = init_length;
    }
    return ret;
}

VertexSetPointer init_p_vertexset(const size_t init_length)
{
    VertexSetPointer ret = malloc(sizeof(VertexSet));
    *ret = vertexset_init(init_length);
    return ret;
}

bool vertexset_is_empty(const VertexSet vertexset)
{
    return vertexset_length(vertexset) == 0;
}

size_t vertexset_length(const VertexSet vertexset)
{
    return array_length(vertexset.set);
}

VertexPointer vertexset_get(const VertexSet vertexset, const unsigned int position)
{
    if (position >= vertexset.set->capacity) {
        runtime_error("vertexset_get: index out of bounds");
        return NULL;
    }
    return (VertexPointer) array_get(vertexset.set, position);
}

VertexPointer vertexset_get_with_label(const VertexSet vertexset, const Label label)
{
    size_t i;
    for (i = 0; i < vertexset.set->capacity; i++) {
        VertexPointer vertex = vertexset_get(vertexset, i);
        if (vertex->label == label) {
            return vertex;
        }
    }
    return NULL;
}

bool vertexset_contains_label(const VertexSet vertexset, const Label label)
{
    size_t i;
    for (i = 0; i < vertexset_length(vertexset); i++) {
        if (label == vertexset_get(vertexset, i)->label) {
            return true;
        }
    }
    return false;
}

bool vertexset_is_super(const VertexSet super, const VertexSet sub)
{
    if (super.set->length != sub.set->length) {
        return false;
    }
    size_t i;
    for (i = 0; i < sub.set->length; i++) {
        VertexPointer vertex = vertexset_get(sub, i);
        if (!vertexset_contains_label(super, vertex->label)) {
            return false;
        }
    }
    return true;
}

bool vertexset_equals(const VertexSet vertexset_a, const VertexSet vertexset_b)
{
    if (!array_equals(vertexset_a.set, vertexset_b.set)) {
        return false;
    }
    size_t i;
    for (i = 0; i < vertexset_a.set->length; i++) {
        VertexPointer vertex_a = vertexset_get(vertexset_a, i);
        VertexPointer vertex_b = vertexset_get(vertexset_b, i);
        if (vertex_equals(vertex_a, vertex_b)) {
            return false;
        }
    }
    return true;
}

Result vertexset_set(const VertexSet vertexset, const VertexPointer vertex, const unsigned int position) 
{
    if (!vertexset_get(vertexset, position)) {
        runtime_error("vertexset_set: can only overwrite existing element");
    }
    if (vertex->label >= vertexset.set->capacity) {
        runtime_error("vertexset_set: label too large");
        return FAIL;
    }
    if (vertexset_contains_label(vertexset, vertex->label)) {
        runtime_error("vertexset_set: set already contains this vertex");
        return FAIL;
    } else {
        array_set(vertexset.set, vertex, position);
    }
    return SUCCESS;
}

Result vertexset_push(const VertexSet vertexset, const VertexPointer vertex)
{
    if (!vertexset_contains_label(vertexset, vertex->label)) {
        return array_push(vertexset.set, vertex);
    } else {
        return FAIL;
    }
}

Result vertexset_complement(const VertexSet vertexset_a, const VertexSet vertexset_b, VertexSetPointer ret)
{
    unsigned int larger_size = larger(vertexset_a.set->length, vertexset_b.set->length);
    VertexPointer vertex_a;
    size_t i;
    for (i = 0; i < larger_size; i++) {
        if (i < vertexset_a.set->length) {
            vertex_a = vertexset_get(vertexset_a, i);
            if (vertex_a && !vertexset_contains_label(vertexset_b, vertex_a->label)) {
                vertexset_push(*ret, vertex_a);
            } 
        } else {
            break;
        }
    }
    return SUCCESS;
}


void vertexset_print(const VertexSet vertexset)
{
    size_t i;
    for (i = 0; i < vertexset_length(vertexset); i++) {
        VertexPointer vertex = vertexset_get(vertexset, i);
            printf("%d, ", vertex->label);
    }
    printf("\n");
}

Result vertexset_destroy(VertexSet vertexset)
{
    array_destroy(vertexset.set);
    return SUCCESS;
}

