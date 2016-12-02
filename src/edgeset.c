
#include "edgeset.h"

static EdgePointer make_p_empty_edge()
{
    EdgePointer ret = malloc(sizeof(Edge));
    ret->initialized = false;
    return ret;
}

bool is_edge_initialized(const Edge edge)
{
    return edge.initialized;
}

EdgeSet init_edgeset(const unsigned int nvertices)
{
    EdgeSet ret;
    unsigned int length = nvertices * nvertices;
    if (length > MAX_EDGES) {
        ret.set           = NULL;
        ret.contains_edge = NULL;
        ret.indices       = NULL;
    } else {
        unsigned int i;
        ret.set      = init_p_array(length);
        ret.vertices = init_vertexset(nvertices);
        for (i = 0; i < length; i++) {
            *(ret.set->head + i) = make_p_empty_edge();
        }
        ret.set->length = length;
        ret.contains_edge = calloc(sizeof(unsigned int), nvertices * nvertices);
        ret.indices       = calloc(length, sizeof(unsigned int));
    }
    return ret;
}

bool edgeset_is_empty(const EdgeSet edgeset)
{
    return edgeset.set->nelements == 0;
}

void copy_edgeset(const EdgeSet edgeset, const EdgeSetPointer copy)
{
    copy->set             = edgeset.set;
    copy->vertices        = edgeset.vertices;
    copy->contains_edge   = edgeset.contains_edge;
    copy->contains_vertex = edgeset.contains_vertex;
    copy->indices         = edgeset.indices;
}

Result edgepath_from_vertexset(const VertexSet vertexset, EdgeSetPointer ret)
{
    if (vertexset_is_empty(vertexset)) {
        return SUCCESS;
    }
    size_t i;
    Vertex current, next;
    next = *get_vertex(vertexset, 0);
    for (i = 0; i < vertexset.set->nelements - 1; i++) {
        current = next;
        next = *get_vertex(vertexset, i + 1);
        add_edge(*ret, make_edge(current, next));
    }
    return SUCCESS;
}

bool edgeset_contains_edge(const EdgeSet edgeset, const Edge edge)
{
    unsigned int bitpos = edge_to_bitpos(edge, edgeset.vertices.maxvertices);
    return *(edgeset.contains_edge + bitpos);
}

bool edgeset_contains_edges(
        const EdgeSet edgeset,
        const EdgePointer edges,
        size_t length
    )
{
    if (edgeset.set->nelements < length) {
        return false;
    }
    size_t i;
    for (i = 0; i < length; i++) {
        if (!edgeset_contains_edge(edgeset, *(edges + i))) {
            return false;
        }
    }
    return true;
}

bool edgeset_contains_vertex(const EdgeSet edgeset, const Vertex vertex)
{
    return vertexset_contains_vertex(edgeset.vertices, vertex);
}

Result add_edge(EdgeSet edgeset, Edge edge)
{
    if (edge.first.label == edge.second.label) {
        return FAIL;
    }
    unsigned int bitpos = edge_to_bitpos(edge, edgeset.vertices.maxvertices);
    if (bitpos > edgeset.set->length) {
        errno = EFAULT;
        return FAIL;
    }
    EdgePointer head = get_element(edgeset.set, bitpos);
    if (!head) {
        errno = EFAULT;
        return FAIL;
    }
    if (edgeset_contains_edge(edgeset, edge)) {
        return FAIL;
    } else {
        if (larger(edge.first.label, edge.second.label) >= edgeset.vertices.maxvertices) {
            return FAIL;
        }
        *(edgeset.contains_edge + edge_to_bitpos(edge, edgeset.vertices.maxvertices)) = true;
        *(edgeset.contains_edge + edge_to_bitpos(swapped(edge), edgeset.vertices.maxvertices)) = true;
        *(edgeset.indices + edgeset.set->nelements) = edge_to_bitpos(edge, edgeset.vertices.maxvertices);
        *head = edge;
        add_vertex(edgeset.vertices, edge.first);
        add_vertex(edgeset.vertices, edge.second);
        edgeset.set->nelements++; 
        return SUCCESS;
    }
}

Result edgeset_complement(const EdgeSet edgeset_a, const EdgeSet edgeset_b, EdgeSetPointer ret)
{
    unsigned int larger_size = larger(edgeset_a.set->nelements, edgeset_b.set->nelements);
    Edge edge_a;
    EdgePointer edge_p_a;
    size_t i;
    for (i = 0; i < larger_size; i++) {
        if (i < edgeset_a.set->nelements) {
            edge_p_a = get_edge(edgeset_a, i);
            edge_a = edge_p_a ? *edge_p_a : empty_edge();
            if (!edge_is_empty(edge_a) && !edgeset_contains_edge(edgeset_b, edge_a)) {
                add_edge(*ret, edge_a);
            }
        } else {
            break;
        }
    }
    return SUCCESS;
}

Result edgeset_union(const EdgeSet edgeset_a, const EdgeSet edgeset_b, EdgeSetPointer ret)
{
    unsigned int larger_size = larger(edgeset_a.set->nelements, edgeset_b.set->nelements);
    Edge edge_a, edge_b;
    EdgePointer edge_p_a, edge_p_b;
    size_t i;
    for (i = 0; i < larger_size; i++) {
        if (i < edgeset_a.set->nelements) {
            edge_p_a = get_edge(edgeset_a, i);
            edge_a = *edge_p_a;
        } else {
            edge_a = empty_edge();
        }
        if (i < edgeset_b.set->nelements) {
            edge_p_b = get_edge(edgeset_b, i);
            edge_b = *edge_p_b;
        } else {
            edge_b = empty_edge();
        }
        if (edges_equal(edge_a, edge_b)) {
            add_edge(*ret, edge_a);
        } else {
            add_edge(*ret, edge_a);
            add_edge(*ret, edge_b);
        }
    }
    return SUCCESS;
}

Result symmetric_difference(const EdgeSet edgeset_a, const EdgeSet edgeset_b, EdgeSetPointer ret)
{
    EdgeSet compl_ab, compl_ba;
    unsigned int nvertices = larger(edgeset_a.vertices.set->length - 1, edgeset_b.vertices.set->length - 1);
    compl_ab = init_edgeset(nvertices);
    compl_ba = init_edgeset(nvertices);
    edgeset_complement(edgeset_a, edgeset_b, &compl_ab);
    edgeset_complement(edgeset_b, edgeset_a, &compl_ba);
    edgeset_union(compl_ab, compl_ba, ret);
    destroy_edgeset(compl_ab);
    destroy_edgeset(compl_ba);
    return SUCCESS;
}

EdgePointer get_edge(const EdgeSet edgeset , const unsigned int position)
{
    return (EdgePointer) get_element(edgeset.set, *(edgeset.indices + position)); 
}

void print_edgeset(const EdgeSet edgeset)
{
    size_t i;
    for (i = 0; i < edgeset.set->nelements; i++) {
        Edge edge = *((EdgePointer) get_edge(edgeset, i));
        printf("Edge: (%d, %d)\n", edge.first.label, edge.second.label);
    }
}

Result destroy_edgeset(EdgeSet edgeset)
{
    destroy_array(edgeset.set);
    destroy_vertexset(edgeset.vertices);
    free(edgeset.contains_edge);
    free(edgeset.indices);
    return SUCCESS;
}

