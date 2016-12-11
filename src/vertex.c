
#include "vertex.h"

Vertex vertex_make(const Label label)
{
    Vertex ret;
    ret.label = label;
    return ret;
}

VertexPointer vertex_p_make(const Label label)
{
    VertexPointer ret = malloc(sizeof(Vertex));
    *ret = vertex_make(label);
    return ret;
}

VertexPointer vertex_copy(const Vertex vertex)
{
    return vertex_p_make(vertex.label);
}


bool vertex_equals(const VertexPointer vertex_a, const VertexPointer vertex_b)
{
    if (!vertex_a || !vertex_b) {
        return vertex_a == vertex_b;
    } 
    return vertex_a->label == vertex_b->label;
}

unsigned int vertex_to_bitpos(const VertexPointer vertex)
{
    return vertex->label;
}

void vertex_print(const VertexPointer vertex)
{
    printf("%u\n", vertex->label);
}

