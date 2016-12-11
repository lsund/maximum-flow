
#include "vertex.h"

Vertex make_vertex(const Label label)
{
    Vertex ret;
    ret.label = label;
    return ret;
}

VertexPointer make_p_vertex(const Label label)
{
    VertexPointer ret = malloc(sizeof(Vertex));
    *ret = make_vertex(label);
    return ret;
}

VertexPointer copy_vertex(const Vertex vertex)
{
    return make_p_vertex(vertex.label);
}


bool vertices_equal(const VertexPointer vertex_a, const VertexPointer vertex_b)
{
    if (vertex_a == NULL || vertex_b == NULL) {
        return vertex_a == vertex_b;
    } 
    return vertex_a->label == vertex_b->label;
}

unsigned int vertex_to_bitpos(const VertexPointer vertex)
{
    return vertex->label;
}

void print_vertex(const VertexPointer vertex)
{
    printf("%u\n", vertex->label);
}

