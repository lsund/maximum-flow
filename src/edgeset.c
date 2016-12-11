
#include "edgeset.h"

EdgeSet edgeset_empty()
{
    EdgeSet ret;
    ret.set = NULL;
    return ret;
}

EdgeSet edgeset_init(const size_t size)
{
    if (size > MAX_EDGES) {
        runtime_error("Too large edgeset");
        return edgeset_empty();
    } else {
        EdgeSet ret;
        ret.set      = array_p_init(size);
        ret.set->capacity = size;
        return ret;
    }
}

EdgeSetPointer edgeset_p_init(const unsigned int nvertices)
{
    EdgeSetPointer ret = malloc(sizeof(EdgeSet));
    *ret = edgeset_init(nvertices); 
    return ret;
}

bool edgeset_is_empty(const EdgeSet edgeset)
{
    return edgeset.set->length == 0;
}

bool edgesets_equal(const EdgeSet edgeset_a, const EdgeSet edgeset_b)
{
    bool sets_equal = array_equals(edgeset_a.set, edgeset_b.set);
    if (!sets_equal) {
        return false;
    }
    if (edgeset_a.set->length != edgeset_b.set->length) {
        return false;
    }
    size_t i;
    for (i = 0; i < edgeset_a.set->length; i++) {
        EdgePointer edge_a = edgeset_get(edgeset_a, i);
        EdgePointer edge_b = edgeset_get(edgeset_a, i);
        if (!edge_equals(edge_a, edge_b)) {
            return false;
        }
    }
    return true;
}

Result edgeset_set(const EdgeSet edgeset, const EdgePointer edge, const unsigned int position)
{
    if (edge->first->label == edge->second->label) {
        runtime_error("add_edge: can't have looping edges");
    }
    if (position >= edgeset.set->capacity) {
        runtime_error("add_edge: index out of bounds");
    }
        array_set(edgeset.set, edge, position);
        return SUCCESS;
}

Result edgeset_push(const EdgeSet edgeset, const EdgePointer edge)
{
    if (!edgeset_contains_edge(edgeset, edge)) {
        return array_push(edgeset.set, edge);
    } else {
        return FAIL;
    }
}

bool edgeset_contains_edge(const EdgeSet edgeset, const EdgePointer edge)
{
    size_t i; 
    for (i = 0; i < edgeset.set->length; i++) {
        EdgePointer current = edgeset_get(edgeset, i);
        if (edge_equals(current, edge)) {
            return true;
        }
    }
    return false;
}

VertexSet edgeset_vertices(const EdgeSet edgeset)
{
    VertexSet vertices = vertexset_init(ARRAY_MIN_SIZE);
    size_t i;
    for (i = 0; i < edgeset.set->length; i++) {
        EdgePointer edge = edgeset_get(edgeset, i);
        VertexPointer first = edge->first;
        VertexPointer second = edge->second;
        if (!vertexset_contains_label(vertices, first->label)) {
            vertexset_push(vertices, first);
        }
        if (!vertexset_contains_label(vertices, second->label)) {
            vertexset_push(vertices, second);
        }
    }
    return vertices;
}

bool edgeset_is_super(const EdgeSet super, const EdgeSet sub)
{
    if (super.set->length != sub.set->length) {
        return false;
    }
    size_t i;
    for (i = 0; i < sub.set->length; i++) {
        EdgePointer edge = edgeset_get(sub, i);
        if (!edgeset_contains_edge(super, edge)) {
            return false;
        }
    }
    return true;
}

bool is_matching(const EdgeSet edgeset)
{
    bool *visited = calloc(edgeset_vertex_count(edgeset), sizeof(bool));
    size_t i;
    i = 0;
    for (i = 0; i < edgeset.set->length; i++) {
        EdgePointer edge = edgeset_get(edgeset, i);
        if (*(visited + edge->first->label) || *(visited + edge->second->label)) {
            free(visited);
            return false;
        } else {
            *(visited + edge->first->label) = true;
            *(visited + edge->second->label) = true;
        } 
    }
    free(visited);
    return true;
}

Result edgeset_covered_by(const EdgeSet edgeset, const VertexPointer vertex, EdgePointer *edge)
{
    size_t i;
    for (i = 0; i < edgeset.set->length; i++) {
        EdgePointer cand = edgeset_get(edgeset, i);
        if (edge_incident_with(cand, vertex)) {
            *edge = cand;
            return SUCCESS;
        }
    }
    return FAIL;
}

bool edgeset_is_sub(const EdgeSet sub, const EdgeSet super)
{
    if (sub.set->length > super.set->length) {
        return false;
    }
    size_t i;
    for (i = 0; i < sub.set->length; i++) {
        if (!edgeset_contains_edge(super, edgeset_get(sub, i))) {
            return false;
        }
    }
    return true;
}

bool edgeset_contains_vertex(const EdgeSet edgeset, const VertexPointer vertex)
{
    VertexSet vertices = edgeset_vertices(edgeset);
    size_t i;
    for (i = 0; i < vertices.set->length; i++) {
        if (vertex_equals(vertex, vertexset_get(vertices, i))) {
            vertexset_destroy(vertices);
            return true;
        }
    }
    vertexset_destroy(vertices);
    return false;
}

EdgePointer edgeset_get(const EdgeSet edgeset, const unsigned int position)
{
    return array_get(edgeset.set, position);
}

size_t edgeset_vertex_count(const EdgeSet edgeset)
{
    VertexSet vertices = edgeset_vertices(edgeset);
    size_t temp = vertices.set->length;
    vertexset_destroy(vertices);
    return temp;
}

Result edgeset_complement(const EdgeSet edgeset_a, const EdgeSet edgeset_b, EdgeSetPointer ret)
{
    EdgePointer edge_a;
    size_t i;
    for (i = 0; i < edgeset_a.set->length; i++) {
        edge_a = edgeset_get(edgeset_a, i);
        if (edge_a && !edgeset_contains_edge(edgeset_b, edge_a)) {
                edgeset_push(*ret, edge_a);
        }
    }
    return SUCCESS;
}

Result edgeset_union(const EdgeSet edgeset_a, const EdgeSet edgeset_b, EdgeSetPointer ret)
{
    unsigned int larger_size = larger(edgeset_a.set->length, edgeset_b.set->length);
    EdgePointer edge_a, edge_b;
    size_t i;
    for (i = 0; i < larger_size; i++) {
        edge_a = edgeset_get(edgeset_a, i);
        edge_b = edgeset_get(edgeset_b, i);
        bool inboth = edgeset_contains_edge(edgeset_b, edge_a);
        if (edge_a && edge_b) {
            if (inboth) {
                edgeset_push(*ret, edge_a);
            } else {
                edgeset_push(*ret, edge_a);
                edgeset_push(*ret, edge_b);
            }
        } else if (!edge_b && edge_a) {
            edgeset_push(*ret, edge_a);
        } else if (!edge_a && edge_b) {
            edgeset_push(*ret, edge_b);
        }
    }
    return SUCCESS;
}

Result edgeset_symmetric_difference(const EdgeSet edgeset_a, const EdgeSet edgeset_b, EdgeSetPointer ret)
{
    EdgeSet compl_ab, compl_ba;
    compl_ab = edgeset_init(edgeset_a.set->capacity);
    compl_ba = edgeset_init(edgeset_b.set->capacity);
    edgeset_complement(edgeset_a, edgeset_b, &compl_ab);
    edgeset_complement(edgeset_b, edgeset_a, &compl_ba);
    edgeset_union(compl_ab, compl_ba, ret);
    edgeset_destroy(compl_ab);
    edgeset_destroy(compl_ba);
    return SUCCESS;
}

EdgePointer edgeset_find_incident_uneq(EdgeSet edgeset, VertexPointer vertex, EdgePointer uneq)
{
   unsigned int i;
   EdgePointer edge = NULL;
   for (i = 0; i < edgeset.set->length; i++) {
       edge = edgeset_get(edgeset, i);
       if (!edge_equals(edge, uneq)) {
           if (edge_incident_with(edge, vertex)) {
               break;
           }
       }
       edge = NULL;
   }
   return edge;
}

void edgeset_print(const EdgeSet edgeset)
{
    size_t i;
    for (i = 0; i < edgeset.set->length; i++) {
        EdgePointer edge = edgeset_get(edgeset, i);
        printf("(%d, %d), ", edge->first->label, edge->second->label);
    }
    printf("\n");
}

Result edgeset_destroy(EdgeSet edgeset)
{
    array_destroy(edgeset.set);
    return SUCCESS;
}

