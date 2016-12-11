
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
        ret.set->length = size;
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
    return edgeset.set->nelements == 0;
}

bool edgesets_equal(const EdgeSet edgeset_a, const EdgeSet edgeset_b)
{
    bool sets_equal = array_equals(edgeset_a.set, edgeset_b.set);
    if (!sets_equal) {
        return false;
    }
    if (edgeset_a.set->nelements != edgeset_b.set->nelements) {
        return false;
    }
    size_t i;
    for (i = 0; i < edgeset_a.set->nelements; i++) {
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
    if (position >= edgeset.set->length) {
        runtime_error("add_edge: index out of bounds");
    }
    if (edgeset_contains_edge(edgeset, edge)) {
        runtime_error("edgeset_set: set already contains this edge");
        return FAIL;
    } else {
        array_set(edgeset.set, edge, position);
        return SUCCESS;
    }
}

Result edgeset_push(const EdgeSet edgeset, const EdgePointer edge)
{
    runtime_error("tbi");
    return FAIL;
}

bool edgeset_contains_edge(const EdgeSet edgeset, const EdgePointer Edge)
{
    runtime_error("tbi");
    return false;
}

VertexSetPointer edgeset_vertices(const EdgeSet edgeset)
{
    runtime_error("tbi");
    return NULL;
}

bool edgeset_is_super(const EdgeSet super, const EdgeSet sub)
{
    if (super.set->nelements != sub.set->nelements) {
        return false;
    }
    size_t i;
    for (i = 0; i < sub.set->nelements; i++) {
        EdgePointer edge = edgeset_get(sub, i);
        if (!edgeset_contains_edge(super, edge)) {
            return false;
        }
    }
    return true;
}

bool is_matching(const EdgeSet edgeset)
{
    bool *visited = calloc(edgeset_vertice_count(edgeset), sizeof(bool));
    size_t i;
    i = 0;
    for (i = 0; i < edgeset.set->nelements; i++) {
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
    for (i = 0; i < edgeset.set->nelements; i++) {
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
    if (sub.set->nelements > super.set->nelements) {
        return false;
    }
    size_t i;
    for (i = 0; i < sub.set->nelements; i++) {
        if (!edgeset_contains_edge(super, edgeset_get(sub, i))) {
            return false;
        }
    }
    return true;
}

bool edgeset_contains_vertex(const EdgeSet edgeset, const VertexPointer vertex)
{
    runtime_error("tbi");
    return false;
}

EdgePointer edgeset_get(const EdgeSet edgeset, const unsigned int position)
{
    return array_get(edgeset.set, position);
}

size_t edgeset_vertice_count(const EdgeSet edgeset)
{
    runtime_error("tbi");
    return 0;
}

Result edgeset_complement(const EdgeSet edgeset_a, const EdgeSet edgeset_b, EdgeSetPointer ret)
{
    unsigned int larger_size = larger(edgeset_a.set->nelements, edgeset_b.set->nelements);
    EdgePointer edge_a;
    size_t i;
    for (i = 0; i < larger_size; i++) {
        if (i < edgeset_a.set->nelements) {
            edge_a = edgeset_get(edgeset_a, i);
            if (edge_a) {
                edgeset_push(*ret, edge_a);
            } else {
                runtime_error("edgeset_complement: no edge present");
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
    EdgePointer edge_a, edge_b;
    size_t i;
    for (i = 0; i < larger_size; i++) {
        if (i < edgeset_a.set->nelements) {
            edge_a = edgeset_get(edgeset_a, i);
        } else {
            edge_a = NULL;
        }
        if (i < edgeset_b.set->nelements) {
            edge_b = edgeset_get(edgeset_b, i);
        } else {
            edge_b = NULL;
        }
        if (edge_equals(edge_a, edge_b)) {
            edgeset_push(*ret, edge_a);
        } else {
            edgeset_push(*ret, edge_a);
            edgeset_push(*ret, edge_b);
        }
    }
    return SUCCESS;
}

Result edgeset_symmetric_difference(const EdgeSet edgeset_a, const EdgeSet edgeset_b, EdgeSetPointer ret)
{
    EdgeSet compl_ab, compl_ba;
    compl_ab = edgeset_init(edgeset_a.set->length);
    compl_ba = edgeset_init(edgeset_b.set->length);
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
   for (i = 0; i < edgeset.set->nelements; i++) {
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
    for (i = 0; i < edgeset.set->nelements; i++) {
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

