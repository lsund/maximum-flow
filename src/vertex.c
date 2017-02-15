
#include "vertex.h"

Vertex vertex_empty()
{
    Vertex ret;
    ret.label          = -1;
    ret.distance_label = 0;
    ret.excess         = 0;
    ret.parent         = NULL;
    return ret;
}

Vertex vertex_make(const Label label)
{
    Vertex ret;
    ret.label          = label;
    ret.distance_label = 0;
    ret.excess         = 0;
    ret.parent         = NULL;
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

Label vertex_distance_label(const VertexPointer vertex)
{
    return vertex->distance_label;
}

void vertex_set_distance_label(const VertexPointer vertex, const Label label)
{
    vertex->distance_label = label;
}

int vertex_excess(const VertexPointer vertex)
{
    return tree_find_branch(vertex)->excess;
}

int vertex_exflow(const VertexPointer vertex)
{
    return vertex->excess;
}

void vertex_print(const Vertex vertex)
{
    printf("%u\n", vertex.label);
}

