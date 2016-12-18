
#include "algorithms.h"
#include <limits.h>

static void push_relabel_initialize(NetworkPointer network)
{
    size_t i;
    for (i = 0; i < edgecollection_length(network->graph->edges); i++) {
        EdgePointer edge = edgecollection_get(network->graph->edges, i);
        if (edge_incident_with(edge, network->source)) {
            unsigned int capacity = network_edge_capacity(network, edge, false);
            network_set_edge_flow(network, edge, capacity);
        } else {
            network_set_edge_flow(network, edge, 0);
        }
    }
    size_t n_vertices = vertexcollection_length(network->graph->vertices);
    network_vertex_set_distance_label(network, network->source, n_vertices);
}

static Label find_min(const NetworkPointer network, const EdgeCollection edges)
{
    Label min = INT_MAX;
    size_t i, j;
    j = 0;
    for (i = 0; i < edgecollection_length(edges); i++) {
        EdgePointer edge = edgecollection_get(edges, i);
        if (network_edge_is_residual(network, edge)) {
            j++;
            Label label = network_vertex_distance_label(network, edge->second) + 1;
            if (label < min) {
                min = label;
            }
        }
    }
    if (j == 0) {
        runtime_error("relabel: vertex should have at least one outgoing edge");
    }
    return min;
}

static void push(const NetworkPointer network, const EdgePointer edge, const VertexPointer vertex)
{
    unsigned int exflow = network_vertex_exflow(network, vertex);
    unsigned int capacity = network_edge_capacity(network, edge, true);
    unsigned int gamma = smaller(exflow, capacity);
    network_augment_edge(network, edge, gamma);
}

static void relabel(const NetworkPointer network, const VertexPointer vertex)
{
    EdgeCollection out_edges = graph_out_edges_from(network->graph_all, vertex);
    network_vertex_set_distance_label(network, vertex, find_min(network, out_edges));
}

void push_relabel(NetworkPointer network)
{
    push_relabel_initialize(network);
    VertexPointer active = network_active_vertex(network);
    while (active) {
        EdgeCollection out_edges = graph_out_edges_from(network->graph_all, active);
        EdgePointer admissable = network_admissable_edge(network, out_edges);
        if (!admissable) {
            relabel(network, active);
        } else {
            push(network, admissable, active);
        }
        active = network_active_vertex(network);
    }
}
