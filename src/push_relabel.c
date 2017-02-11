
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
            networkedge_augment(network, edge, capacity);
        } else {
            edgecollection_push(*(network->residual_edges + edge->first.label), edge); 
        }
    }
    size_t n_vertices = vertexcollection_length(network->graph.vertices);
    networkvertex_set_distance_label(network, *network->source, n_vertices);
}

static Label find_min(const NetworkPointer network, const Vertex vertex)
{
    Label min = INT_MAX;
    size_t i;
    EdgeCollection edges = *(network->residual_edges + vertex.label);
    for (i = 0; i < edgecollection_length(edges); i++) {
        EdgePointer edge = edgecollection_get(edges, i);
        Label label = networkvertex_distance_label(network, edge->second) + 1;
        if (label < min) {
            min = label;
        }
    }
    if (i == 0) {
        runtime_error("find_min: vertex should have at least one outgoing edge");
    }
    return min;
}

static void push(const NetworkPointer network, const EdgePointer edge, const Vertex vertex)
{
    unsigned int exflow = networkvertex_exflow_pr(network, vertex);
    unsigned int capacity = edge_residual_capacity(edge);
    unsigned int gamma = smaller(exflow, capacity);
    networkedge_augment(network, edge, gamma);
}

static void relabel(const NetworkPointer network, const Vertex vertex)
{
    Label min_label = find_min(network, vertex);
    networkvertex_set_distance_label(network, vertex, min_label);
}

void push_relabel(NetworkPointer network)
{
    push_relabel_initialize(network);
    Vertex active;
    Result has_active = networkvertex_active(network, &active);
    while (has_active == SUCCESS) {
        EdgePointer admissable = networkedge_admissable(network, active);
        if (!admissable) {
            relabel(network, active);
        } else {
            push(network, admissable, active);
        }
        has_active = networkvertex_active(network, &active);
    }
}

