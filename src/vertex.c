
#include "vertex.h"

Vertex empty_vertex()
{
    Vertex ret;
    ret.label = UNINIT_VERTEX;
    ret.initialized = false;
    return ret;
}

Vertex make_vertex(const Label label)
{
    Vertex ret;
    ret.label = label;
    ret.initialized = true;
    return ret;
}

VertexPointer make_p_empty_vertex()
{
    VertexPointer ret = malloc(sizeof(Vertex));
    *ret = empty_vertex();
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


bool vertices_equal(const Vertex vertex_a, const Vertex vertex_b)
{
    return vertex_a.label == vertex_b.label && vertex_a.initialized == vertex_b.initialized;
}

unsigned int vertex_to_bitpos(const Vertex vertex)
{
    return vertex.label;
}

bool is_vertex_initialized(const VertexPointer vertex)
{
    return vertex->initialized;
}

