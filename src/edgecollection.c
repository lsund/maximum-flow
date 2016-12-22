
#include "edgecollection.h"

EdgeCollection edgecollection_empty()
{
    EdgeCollection ret;
    ret.members = NULL;
    return ret;
}

EdgeCollection edgecollection_init(const size_t size)
{
    if (size > MAX_EDGES) {
        runtime_error("Too large edgecollection");
        return edgecollection_empty();
    } else {
        EdgeCollection ret;
        ret.members = collection_p_init(size);
        ret.indices = map_create();
        return ret;
    }
}

EdgeCollectionPointer edgecollection_p_init(const unsigned int nvertices)
{
    EdgeCollectionPointer ret = malloc(sizeof(EdgeCollection));
    *ret = edgecollection_init(nvertices); 
    return ret;
}

void edgecollection_reset(EdgeCollection edges)
{
    map_reset(edges.indices);
    collection_reset(edges.members);
}

size_t edgecollection_length(const EdgeCollection edges)
{
    return collection_length(edges.members);
}

EdgePointer edgecollection_get(const EdgeCollection edges, const unsigned int position)
{
    if (position >= edges.members->capacity) {
        runtime_error("vertexcollection_get: index out of bounds");
        return NULL;
    }
    return collection_get(edges.members, position);
}

int edgecollection_index_of(const EdgeCollection edges, const EdgePointer edge)
{
    if (map_exists(edges.indices, edge_hash(edge))) {
        return map_get(edges.indices, edge_hash(edge));
    } else {
        return -1;
    }
}

size_t edgecollection_vertex_count(const EdgeCollection edges)
{
    VertexCollection vertices = edgecollection_vertices(edges);
    size_t temp = vertexcollection_length(vertices);
    vertexcollection_destroy(vertices);
    return temp;
}

VertexCollection edgecollection_vertices(const EdgeCollection edges)
{
    VertexCollection vertices = vertexcollection_init(ARRAY_MIN_SIZE);
    size_t i;
    for (i = 0; i < edgecollection_length(edges); i++) {
        EdgePointer edge = edgecollection_get(edges, i);
        Vertex first = edge->first;
        Vertex second = edge->second;
        if (!vertexcollection_contains_label(vertices, first.label)) {
            vertexcollection_push(vertices, vertex_p_make(first.label));
        }
        if (!vertexcollection_contains_label(vertices, second.label)) {
            vertexcollection_push(vertices, vertex_p_make(second.label));
        }
    }
    return vertices;
}

Result edgecollection_replace(const EdgeCollection edges, const EdgePointer edge, const unsigned int position)
{
    if (!edgecollection_get(edges, position)) {
        runtime_error("set_edge: can only overwrite existing element");
    }
    if (edge && (edge->first.label == edge->second.label)) {
        runtime_error("set_edge: can't have looping edges");
    }
    if (position >= edges.members->capacity) {
        runtime_error("set_edge: index out of bounds");
    }
    collection_replace(edges.members, edge, position);
    return SUCCESS;
}

Result edgecollection_push(const EdgeCollection edges, const EdgePointer edge)
{
    if (!edgecollection_contains_edge(edges, edge)) {
        map_put(edges.indices, edge_hash(edge), edgecollection_length(edges));
        return collection_push(edges.members, edge);
    } else {
        return FAIL;
    }
}

void edgecollection_remove(EdgeCollection edges, const EdgePointer edge)
{
    map_put(edges.indices, edge_hash(edge), -1);
    size_t i, n_edges = edgecollection_length(edges);
    EdgeCollection temp = edgecollection_init(n_edges);
    for (i = 0; i < n_edges; i++) {
        EdgePointer current = edgecollection_get(edges, i);
        if (!edge_equals(edge, current)) {
            edgecollection_push(temp, current);  
        }
    }
    edgecollection_reset(edges);
    for (i = 0; i < edgecollection_length(temp); i++) {
        EdgePointer current = edgecollection_get(temp, i);
        edgecollection_push(edges, current);
    }
    edgecollection_destroy(temp);
}

bool edgecollection_is_empty(const EdgeCollection edges)
{
    return collection_is_empty(edges.members);
}

bool edgecollection_equals(const EdgeCollection edgecollection_a, const EdgeCollection edgecollection_b)
{
    bool sets_equal = collection_equals(edgecollection_a.members, edgecollection_b.members);
    if (!sets_equal) {
        return false;
    }
    if (edgecollection_length(edgecollection_a) != edgecollection_length(edgecollection_b)) {
        return false;
    }
    size_t i;
    for (i = 0; i < edgecollection_length(edgecollection_a); i++) {
        EdgePointer edge_a = edgecollection_get(edgecollection_a, i);
        EdgePointer edge_b = edgecollection_get(edgecollection_a, i);
        if (!edge_equals(edge_a, edge_b)) {
            return false;
        }
    }
    return true;
}

bool edgecollection_is_super(const EdgeCollection super, const EdgeCollection sub)
{
    bool sub_is_empty = edgecollection_is_empty(sub);
    bool super_is_empty = edgecollection_is_empty(super);
    if (sub_is_empty) {
        return true;
    } else if (super_is_empty) {
        return false;
    }
    if (edgecollection_length(super) < edgecollection_length(sub)) {
        return false;
    }
    size_t i;
    for (i = 0; i < edgecollection_length(sub); i++) {
        EdgePointer edge = edgecollection_get(sub, i);
        if (!edgecollection_contains_edge(super, edge)) {
            return false;
        }
    }
    return true;
}

bool edgecollection_is_sub(const EdgeCollection sub, const EdgeCollection super)
{
    return edgecollection_is_super(super, sub);
}

bool edgecollection_contains_edge(const EdgeCollection edges, const EdgePointer edge)
{
    unsigned int key = edge_hash(edge);
    if (!map_exists(edges.indices, key)) {
        return false;
    } else {
        return map_get(edges.indices, key) != -1;
    }
}

bool edgecollection_contains_vertex(const EdgeCollection edges, const VertexPointer vertex)
{
    VertexCollection vertices = edgecollection_vertices(edges);
    size_t i;
    for (i = 0; i < vertexcollection_length(vertices); i++) {
        if (vertex_equals(*vertex, *vertexcollection_get(vertices, i))) {
            vertexcollection_destroy(vertices);
            return true;
        }
    }
    vertexcollection_destroy(vertices);
    return false;
}

bool is_matching(const EdgeCollection edges)
{
    bool *visited = calloc(edgecollection_vertex_count(edges), sizeof(bool));
    size_t i;
    i = 0;
    for (i = 0; i < edgecollection_length(edges); i++) {
        EdgePointer edge = edgecollection_get(edges, i);
        if (*(visited + edge->first.label) || *(visited + edge->second.label)) {
            free(visited);
            return false;
        } else {
            *(visited + edge->first.label) = true;
            *(visited + edge->second.label) = true;
        } 
    }
    free(visited);
    return true;
}

Result edgecollection_covered_by(const EdgeCollection edges, const VertexPointer vertex, EdgePointer *edge)
{
    size_t i;
    for (i = 0; i < edgecollection_length(edges); i++) {
        EdgePointer cand = edgecollection_get(edges, i);
        if (edge_incident_with(cand, *vertex)) {
            *edge = cand;
            return SUCCESS;
        }
    }
    return FAIL;
}

Result edgecollection_complement(const EdgeCollection edgecollection_a, const EdgeCollection edgecollection_b, EdgeCollectionPointer ret)
{
    EdgePointer edge_a;
    size_t i;
    for (i = 0; i < edgecollection_length(edgecollection_a); i++) {
        edge_a = edgecollection_get(edgecollection_a, i);
        if (edge_a && !edgecollection_contains_edge(edgecollection_b, edge_a)) {
                edgecollection_push(*ret, edge_a);
        }
    }
    return SUCCESS;
}

EdgeCollection edgecollection_union(const EdgeCollection edgecollection_a, const EdgeCollection edgecollection_b)
{
    unsigned int larger_size = larger(edgecollection_length(edgecollection_a), edgecollection_length(edgecollection_b));
    unsigned int summed_capacity = edgecollection_a.members->capacity + edgecollection_b.members->capacity;
    EdgeCollection ret = edgecollection_init(summed_capacity);
    EdgePointer edge_a, edge_b;
    size_t i;
    for (i = 0; i < larger_size; i++) {
        edge_a = edgecollection_get(edgecollection_a, i);
        edge_b = edgecollection_get(edgecollection_b, i);
        bool inboth = edgecollection_contains_edge(edgecollection_b, edge_a);
        if (edge_a && edge_b) {
            if (inboth) {
                edgecollection_push(ret, edge_a);
            } else {
                edgecollection_push(ret, edge_a);
                edgecollection_push(ret, edge_b);
            }
        } else if (!edge_b && edge_a) {
            edgecollection_push(ret, edge_a);
        } else if (!edge_a && edge_b) {
            edgecollection_push(ret, edge_b);
        }
    }
    return ret;
}

Result edgecollection_symmetric_difference(const EdgeCollection edgecollection_a, const EdgeCollection edgecollection_b, EdgeCollectionPointer ret)
{
    EdgeCollection compl_ab, compl_ba;
    compl_ab = edgecollection_init(edgecollection_a.members->capacity);
    compl_ba = edgecollection_init(edgecollection_b.members->capacity);
    edgecollection_complement(edgecollection_a, edgecollection_b, &compl_ab);
    edgecollection_complement(edgecollection_b, edgecollection_a, &compl_ba);
    *ret = edgecollection_union(compl_ab, compl_ba);
    edgecollection_destroy(compl_ab);
    edgecollection_destroy(compl_ba);
    return SUCCESS;
}

void edgecollection_print(const EdgeCollection edges)
{
    size_t i;
    for (i = 0; i < edgecollection_length(edges); i++) {
        EdgePointer edge = edgecollection_get(edges, i);
        printf("(%d, %d), ", edge->first.label, edge->second.label);
    }
    printf("\n");
}

Result edgecollection_destroy(EdgeCollection edges)
{
    collection_destroy(edges.members);
    map_destroy(edges.indices);
    return SUCCESS;
}

