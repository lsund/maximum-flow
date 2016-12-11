
#include "matching.h"

bool matching_exposing(const VertexPointer vertex, const EdgeSet matching)
{
    return !edgeset_contains_vertex(matching, vertex);
}

Result matching_find_exposed(const VertexSet vertexset, const EdgeSet matching, unsigned int *index)
{
    size_t i;
    for (i = 0; i < vertexset.set->nelements; i++) {
        VertexPointer vertex = vertexset_get(vertexset, i);
        if (matching_exposing(vertex, matching)) {
            *index = i;
            return SUCCESS;
        }
    }
    return FAIL;
}

bool matching_is_perfect(const EdgeSet matching, const VertexSet vertexset)
{
    size_t i;
    for (i = 0; i < vertexset.set->nelements; i++) {
        VertexPointer vertex = vertexset_get(vertexset, i);
        if (!edgeset_contains_vertex(matching, vertex)) {
            return false;
        }
    }
    if (!is_matching(matching)) {
        return false;
    } else {
        size_t size = matching.set->nelements;
        if (size == (size_t) ceil(((float) vertexset.set->nelements) / 2))  {
            return true;
        }
        return false;
    }
}

Result matching_augment(const EdgeSet matching, const EdgeSet path, EdgeSetPointer ret)
{
    edgeset_symmetric_difference(matching, path, ret);
    return SUCCESS;
}

Result matching_perfect_odd_path(EdgeSet circuit, VertexPointer ignore, EdgeSetPointer ret)
{
    EdgePointer first, last;
    first = edgeset_find_incident_uneq(circuit, ignore, NULL);
    last = first;
    VertexPointer front = ignore;

    bool add = false;
    do {
        if (add) {
            edgeset_push(*ret, last);
        }
        if (vertex_equals(last->first, front)) {
            front = last->second;
        }
        else { 
            front = last->first;
        }
        last = edgeset_find_incident_uneq(circuit, front, last);
        add = !add;
    } while (!edge_equals(last, first));
    return SUCCESS;
}

