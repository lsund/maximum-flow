
#include "matching.h"

bool matching_exposing(const VertexPointer vertex, const EdgeSet matching)
{
    return !edgeset_contains_vertex(matching, vertex);
}

Result matching_find_exposed(const VertexSet vertexset, const EdgeSet matching, unsigned int *index)
{
    size_t i;
    for (i = 0; i < vertexset.set->length; i++) {
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
    for (i = 0; i < vertexset.set->length; i++) {
        VertexPointer vertex = vertexset_get(vertexset, i);
        if (!edgeset_contains_vertex(matching, vertex)) {
            return false;
        }
    }
    if (!is_matching(matching)) {
        return false;
    } else {
        size_t size = matching.set->length;
        if (size == (size_t) ceil(((float) vertexset.set->length) / 2))  {
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

