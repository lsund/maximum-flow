
#include "vertexset.h"

VertexSet uninitialized_vertexset()
{
    VertexSet ret;
    ret.set         = NULL;
    ret.indices     = NULL;
    ret.contains    = NULL;
    ret.initialized = false;
    ret.maxvertices = 0;
    return ret;

}
VertexSet init_vertexset(const size_t init_length) 
{
    VertexSet ret;
    unsigned int actual_length = init_length + 1;
    if (init_length > MAX_VERTICES) {
        return uninitialized_vertexset();
    } else {
        unsigned int i;
        ret.set         = init_p_array(actual_length);
        ret.contains    = calloc(actual_length, sizeof(bool));
        ret.indices     = calloc(actual_length, sizeof(unsigned int));
        ret.maxvertices = init_length;
        ret.initialized = true;
        for (i = 0; i < actual_length; i++) {
            *(ret.set->head + i) = make_p_empty_vertex();
        }
        ret.set->length = actual_length;
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

bool vertexset_is_initialized(const VertexSet vertexset)
{
    return vertexset.initialized;
}

bool vertexset_contains_vertex(const VertexSet vertexset, const Vertex vertex)
{
    if (vertex.label > vertexset.set->length - 1) {
        return false;
    }
    return *(vertexset.contains + vertex_to_bitpos(vertex));
}

bool vertexset_contains_vertices(
        const VertexSet vertexset,
        const VertexPointer vertices,
        size_t length
    )
{
    if (vertexset.set->nelements > length) {
        return false;
    }
    size_t i;
    for (i = 0; i < length; i++) {
        if (!vertexset_contains_vertex(vertexset, *(vertices + i))) {
            return false;
        }
    }
    return true;
}

Result add_vertex(VertexSet vertexset, Vertex vertex) 
{
    if (!is_vertex_initialized(&vertex)) {
        return FAIL;
    }
    if (vertex.label > vertexset.set->length - 1) {
        errno = ERANGE;
        return FAIL;
    }
    if ((size_t) vertex.label > vertexset.set->length - 1) {
        errno = EFAULT;
        return FAIL;
    }
    VertexPointer head = get_element(vertexset.set, vertex.label);
    if (!head) {
        errno = EFAULT;
        return FAIL;
    }
    if (vertexset_contains_vertex(vertexset, vertex)) {
        return FAIL;
    } else {
        *(vertexset.contains + vertex_to_bitpos(vertex)) = true;
        *(vertexset.indices + vertexset.set->nelements) = vertex_to_bitpos(vertex);
        *head = vertex;
        vertexset.set->nelements++; 
    }
    return SUCCESS;
}

VertexPointer get_vertex_at_position(const VertexSet vertexset, const unsigned int position)
{
    if (position >= vertexset.set->length) {
        return NULL;
    }
    unsigned int index = *(vertexset.indices + position);
    return (VertexPointer) get_element(vertexset.set, index);
}

VertexPointer get_vertex_with_label(const VertexSet vertexset, const Label label)
{
    return (VertexPointer) get_element(vertexset.set, label);
}

void print_vertexset(const VertexSet vertexset)
{
    size_t i;
    for (i = 0; i < vertexset.set->nelements; i++) {
        VertexPointer vertex = get_vertex_at_position(vertexset, i);
            printf("Vertex: %d\n", vertex->label);
    }
}

Result destroy_vertexset(VertexSet vertexset)
{
    free(vertexset.contains);
    free(vertexset.indices);
    destroy_array(vertexset.set);
    return SUCCESS;
}

