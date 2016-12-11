
#include "vertexset.h"

VertexSet empty_vertexset()
{
    VertexSet ret;
    ret.set         = NULL;
    return ret;

}

VertexSet init_vertexset(const size_t init_length) 
{
    VertexSet ret;
    if (init_length > MAX_VERTICES) {
        runtime_error("init_vertexset: too many vertices");
        return empty_vertexset();
    } else {
        ret.set         = init_p_array(init_length);
        ret.set->length = init_length;
    }
    return ret;
}

VertexSetPointer init_p_vertexset(const size_t init_length)
{
    VertexSetPointer ret = malloc(sizeof(VertexSet));
    *ret = init_vertexset(init_length);
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
    return get_element(vertexset.set, vertex->label);
}

bool is_super_vertexset(const VertexSet super, const VertexSet sub)
{
    if (super.set->nelements != sub.set->nelements) {
        return false;
    }
    size_t i;
    for (i = 0; i < sub.set->nelements; i++) {
        VertexPointer vertex = get_vertex(sub, i);
        if (!vertexset_contains_vertex(super, vertex)) {
            return false;
        }
    }
    return true;
}

bool vertexsets_equal(const VertexSet vertexset_a, const VertexSet vertexset_b)
{
    if (!arrays_equal(vertexset_a.set, vertexset_b.set)) {
        return false;
    }
    size_t i;
    for (i = 0; i < vertexset_a.set->nelements; i++) {
        VertexPointer vertex_a = get_vertex(vertexset_a, i);
        VertexPointer vertex_b = get_vertex(vertexset_b, i);
        if (vertices_equal(vertex_a, vertex_b)) {
            return false;
        }
    }
    return true;
}

Result set_vertex(const VertexSet vertexset, const VertexPointer vertex, const unsigned int position) 
{
    if (vertex->label >= vertexset.set->length) {
        runtime_error("set_vertex: label too large");
        return FAIL;
    }
    if (vertexset_contains_vertex(vertexset, vertex)) {
        runtime_error("set_vertex: set already contains this vertex");
        return FAIL;
    } else {
        set_element(vertexset.set, vertex, position);
        vertexset.set->nelements++; 
    }
    return SUCCESS;
}

Result push_vertex(const VertexSet edgeset, const VertexPointer vertex)
{
    runtime_error("tbi");
    return FAIL;
}

VertexPointer get_vertex(const VertexSet vertexset, const unsigned int position)
{
    if (position >= vertexset.set->length) {
        runtime_error("get_vertex: index out of bounds");
        return NULL;
    }
    return (VertexPointer) get_element(vertexset.set, position);
}

Result vertexset_complement(const VertexSet vertexset_a, const VertexSet vertexset_b, VertexSetPointer ret)
{
    unsigned int larger_size = larger(vertexset_a.set->nelements, vertexset_b.set->nelements);
    VertexPointer vertex_a;
    size_t i;
    for (i = 0; i < larger_size; i++) {
        if (i < vertexset_a.set->nelements) {
            vertex_a = get_vertex(vertexset_a, i);
            if (vertex_a) {
                push_vertex(*ret, vertex_a);
            } else {
                runtime_error("vertexset_complement: no edge present");
            }
        } else {
            break;
        }
    }
    return SUCCESS;
}


void print_vertexset(const VertexSet vertexset)
{
    size_t i;
    for (i = 0; i < vertexset.set->nelements; i++) {
        VertexPointer vertex = get_vertex(vertexset, i);
            printf("%d, ", vertex->label);
    }
    printf("\n");
}

Result destroy_vertexset(VertexSet vertexset)
{
    destroy_array(vertexset.set);
    return SUCCESS;
}

