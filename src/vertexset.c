
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
        ret.set->length = init_length;
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
    return vertexset.set->nelements == 0;
}

bool vertexset_contains_vertex(const VertexSet vertexset, const VertexPointer vertex)
{
    if (vertex->label > vertexset.set->length - 1) {
        return false;
    }
    return array_get(vertexset.set, vertex->label);
}

bool vertexset_is_super(const VertexSet super, const VertexSet sub)
{
    if (super.set->nelements != sub.set->nelements) {
        return false;
    }
    size_t i;
    for (i = 0; i < sub.set->nelements; i++) {
        VertexPointer vertex = vertexset_get(sub, i);
        if (!vertexset_contains_vertex(super, vertex)) {
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
    for (i = 0; i < vertexset_a.set->nelements; i++) {
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
    if (vertex->label >= vertexset.set->length) {
        runtime_error("vertexset_set: label too large");
        return FAIL;
    }
    if (vertexset_contains_vertex(vertexset, vertex)) {
        runtime_error("vertexset_set: set already contains this vertex");
        return FAIL;
    } else {
        array_set(vertexset.set, vertex, position);
        vertexset.set->nelements++; 
    }
    return SUCCESS;
}

Result vertexset_push(const VertexSet edgeset, const VertexPointer vertex)
{
    runtime_error("tbi");
    return FAIL;
}

VertexPointer vertexset_get(const VertexSet vertexset, const unsigned int position)
{
    if (position >= vertexset.set->length) {
        runtime_error("vertexset_get: index out of bounds");
        return NULL;
    }
    return (VertexPointer) array_get(vertexset.set, position);
}

Result vertexset_complement(const VertexSet vertexset_a, const VertexSet vertexset_b, VertexSetPointer ret)
{
    unsigned int larger_size = larger(vertexset_a.set->nelements, vertexset_b.set->nelements);
    VertexPointer vertex_a;
    size_t i;
    for (i = 0; i < larger_size; i++) {
        if (i < vertexset_a.set->nelements) {
            vertex_a = vertexset_get(vertexset_a, i);
            if (vertex_a) {
                vertexset_push(*ret, vertex_a);
            } else {
                runtime_error("vertexset_complement: no edge present");
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
    for (i = 0; i < vertexset.set->nelements; i++) {
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

