
#include "vertex.h"

Vertex vertex_empty()
{
    Vertex ret;
    ret.label = 0; // TODO
    ret.parent = NULL;
    return ret;
}

Vertex vertex_make(const Label label)
{
    Vertex ret;
    ret.label = label;
    ret.parent = NULL;
    return ret;
}

VertexPointer vertex_p_make(const Label label)
{
    VertexPointer ret = malloc(sizeof(Vertex));
    *ret = vertex_make(label);
    return ret;
}

bool vertex_equals(const Vertex vertex_a, const Vertex vertex_b)
{
    return vertex_a.label == vertex_b.label;
}

void vertex_print(const Vertex vertex)
{
    printf("%u\n", vertex.label);
}

