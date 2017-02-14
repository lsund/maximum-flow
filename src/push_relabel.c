
#include "push_relabel.h"

static void push_relabel_initialize(NetworkPointer network)
{
    EdgePointer edge;
    unsigned int capacity;
    size_t i;
    for (i = 0; i < edgecollection_length(network->graph.edges); i++) {
        edge = edgecollection_get(network->graph.edges, i);
        if (vertex_equals(edge->first, *network->source)) {
            capacity = edge_capacity(edge);
            edge_augment(edge, capacity);
        } else {
            edgecollection_push(*(network->residual_edges + edge->first.label), edge); 
        }
    }
    size_t n_vertices = vertexcollection_length(network->graph.vertices);
    vertex_set_distance_label(network->source, n_vertices);
}

static Label find_min(const NetworkPointer network, const Vertex vertex)
{
    Label min = INT_MAX;
    size_t i;
    /* EdgeCollection edges = *(network->residual_edges + vertex.label); */
    EdgeCollection edges = network->graph.edges;
    for (i = 0; i < edgecollection_length(edges); i++) {
        EdgePointer edge = edgecollection_get(edges, i);
        Label label      = vertex_distance_label(edge->second_ref) + 1;
        Label rev_label  = vertex_distance_label(edge->reverse->second_ref) + 1;
        if (vertex_equals(edge->first, vertex) && label < min && edge_is_residual(edge)) {
            min = label;
        } else if (vertex_equals(edge->first, vertex) && rev_label < min && edge_is_residual(edge->reverse)) {
            min = rev_label;
        }
    }
    if (i == 0) {
        runtime_error("find_min: vertex should have at least one outgoing edge");
    }
    return min;
}

static void push(const NetworkPointer network, const EdgePointer edge, const VertexPointer vertex)
{
    unsigned int exflow = vertex_exflow(vertex);
    unsigned int capacity = edge_residual_capacity(edge);
    unsigned int gamma = smaller(exflow, capacity);
    edge_augment(edge, gamma);
}

static void relabel(const NetworkPointer network, const VertexPointer vertex)
{
    Label min_label = find_min(network, *vertex);
    vertex_set_distance_label(vertex, min_label);
}

void push_relabel(NetworkPointer network)
{
    push_relabel_initialize(network);
    VertexPointer active = networkvertex_active(network);
    while (active) {
        EdgePointer admissable = networkedge_admissable(network, *active);
        if (!admissable) {
            relabel(network, active);
        } else {
            push(network, admissable, active);
        }
        active = networkvertex_active(network);
    }
}

