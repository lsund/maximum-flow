
#include "matching.h"

bool is_matching(const EdgeSet edgeset)
{
    bool *visited = calloc(n_vertices(edgeset), sizeof(bool));
    size_t i;
    i = 0;
    for (i = 0; i < edgeset.set->nelements; i++) {
        EdgePointer edge = get_edge(edgeset, i);
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

bool is_exposed(const VertexPointer vertex, const EdgeSet matching)
{
    return !edgeset_contains_vertex(matching, vertex);
}

Result find_exposed(const VertexSet vertexset, const EdgeSet matching, unsigned int *index)
{
    size_t i;
    for (i = 0; i < vertexset.set->nelements; i++) {
        VertexPointer vertex = get_vertex(vertexset, i);
        if (is_exposed(vertex, matching)) {
            *index = i;
            return SUCCESS;
        }
    }
    return FAIL;
}

bool is_perfect(const EdgeSet matching, const VertexSet vertexset)
{
    size_t i;
    for (i = 0; i < vertexset.set->nelements; i++) {
        VertexPointer vertex = get_vertex(vertexset, i);
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

Result augment(const EdgeSet matching, const EdgeSet path, EdgeSetPointer ret)
{
    symmetric_difference(matching, path, ret);
    return SUCCESS;
}

Result perfect_matching_odd_path(EdgeSet circuit, VertexPointer ignore, EdgeSetPointer ret)
{
    EdgePointer first, last;
    first = find_incident_uneq(circuit, ignore, NULL);
    last = first;
    VertexPointer front = ignore;

    bool add = false;
    do {
        if (add) {
            push_edge(*ret, last);
        }
        if (vertices_equal(last->first, front)) {
            front = last->second;
        }
        else { 
            front = last->first;
        }
        last = find_incident_uneq(circuit, front, last);
        add = !add;
    } while (!edges_equal(last, first));
    return SUCCESS;
}

