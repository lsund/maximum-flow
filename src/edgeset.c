
#include "edgeset.h"

EdgeSet empty_edgeset()
{
    EdgeSet ret;
    ret.set = NULL;
    return ret;
}

EdgeSet init_edgeset(const size_t size)
{
    if (size > MAX_EDGES) {
        runtime_error("Too large edgeset");
        return empty_edgeset();
    } else {
        EdgeSet ret;
        ret.set      = init_p_array(size);
        ret.set->length = size;
        return ret;
    }
}

EdgeSetPointer init_p_edgeset(const unsigned int nvertices)
{
    EdgeSetPointer ret = malloc(sizeof(EdgeSet));
    *ret = init_edgeset(nvertices); 
    return ret;
}

bool edgeset_is_empty(const EdgeSet edgeset)
{
    return edgeset.set->nelements == 0;
}

bool edgesets_equal(const EdgeSet edgeset_a, const EdgeSet edgeset_b)
{
    bool sets_equal = arrays_equal(edgeset_a.set, edgeset_b.set);
    if (!sets_equal) {
        return false;
    }
    if (edgeset_a.set->nelements != edgeset_b.set->nelements) {
        return false;
    }
    size_t i;
    for (i = 0; i < edgeset_a.set->nelements; i++) {
        EdgePointer edge_a = get_edge(edgeset_a, i);
        EdgePointer edge_b = get_edge(edgeset_a, i);
        if (!edges_equal(edge_a, edge_b)) {
            return false;
        }
    }
    return true;
}

Result set_edge(const EdgeSet edgeset, const EdgePointer edge, const unsigned int position)
{
    if (edge->first->label == edge->second->label) {
        runtime_error("add_edge: can't have looping edges");
    }
    if (position >= edgeset.set->length) {
        runtime_error("add_edge: index out of bounds");
    }
    if (edgeset_contains_edge(edgeset, edge)) {
        runtime_error("set_edge: set already contains this edge");
        return FAIL;
    } else {
        set_element(edgeset.set, edge, position);
        return SUCCESS;
    }
}

Result push_edge(const EdgeSet edgeset, const EdgePointer edge)
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

bool is_super_edgeset(const EdgeSet super, const EdgeSet sub)
{
    if (super.set->nelements != sub.set->nelements) {
        return false;
    }
    size_t i;
    for (i = 0; i < sub.set->nelements; i++) {
        EdgePointer edge = get_edge(sub, i);
        if (!edgeset_contains_edge(super, edge)) {
            return false;
        }
    }
    return true;
}

Result covered_by(const EdgeSet edgeset, const VertexPointer vertex, EdgePointer *edge)
{
    size_t i;
    for (i = 0; i < edgeset.set->nelements; i++) {
        EdgePointer cand = get_edge(edgeset, i);
        if (incident_with(cand, vertex)) {
            *edge = cand;
            return SUCCESS;
        }
    }
    return FAIL;
}

bool is_sub_edgeset(const EdgeSet sub, const EdgeSet super)
{
    if (sub.set->nelements > super.set->nelements) {
        return false;
    }
    size_t i;
    for (i = 0; i < sub.set->nelements; i++) {
        if (!edgeset_contains_edge(super, get_edge(sub, i))) {
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

EdgePointer get_edge(const EdgeSet edgeset, const unsigned int position)
{
    return get_element(edgeset.set, position);
}

size_t n_vertices(const EdgeSet edgeset)
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
            edge_a = get_edge(edgeset_a, i);
            if (edge_a) {
                push_edge(*ret, edge_a);
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
            edge_a = get_edge(edgeset_a, i);
        } else {
            edge_a = NULL;
        }
        if (i < edgeset_b.set->nelements) {
            edge_b = get_edge(edgeset_b, i);
        } else {
            edge_b = NULL;
        }
        if (edges_equal(edge_a, edge_b)) {
            push_edge(*ret, edge_a);
        } else {
            push_edge(*ret, edge_a);
            push_edge(*ret, edge_b);
        }
    }
    return SUCCESS;
}

Result symmetric_difference(const EdgeSet edgeset_a, const EdgeSet edgeset_b, EdgeSetPointer ret)
{
    EdgeSet compl_ab, compl_ba;
    compl_ab = init_edgeset(edgeset_a.set->length);
    compl_ba = init_edgeset(edgeset_b.set->length);
    edgeset_complement(edgeset_a, edgeset_b, &compl_ab);
    edgeset_complement(edgeset_b, edgeset_a, &compl_ba);
    edgeset_union(compl_ab, compl_ba, ret);
    destroy_edgeset(compl_ab);
    destroy_edgeset(compl_ba);
    return SUCCESS;
}

EdgePointer find_incident_uneq(EdgeSet edgeset, VertexPointer vertex, EdgePointer uneq)
{
   unsigned int i;
   EdgePointer edge = NULL;
   for (i = 0; i < edgeset.set->nelements; i++) {
       edge = get_edge(edgeset, i);
       if (!edges_equal(edge, uneq)) {
           if (incident_with(edge, vertex)) {
               break;
           }
       }
       edge = NULL;
   }
   return edge;
}

void print_edgeset(const EdgeSet edgeset)
{
    size_t i;
    for (i = 0; i < edgeset.set->nelements; i++) {
        EdgePointer edge = get_edge(edgeset, i);
        printf("(%d, %d), ", edge->first->label, edge->second->label);
    }
    printf("\n");
}

Result destroy_edgeset(EdgeSet edgeset)
{
    destroy_array(edgeset.set);
    return SUCCESS;
}

