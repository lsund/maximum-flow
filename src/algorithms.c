
#include "algorithms.h"

static void push_relabel_initialize(NetworkPointer network)
{
    size_t i;
    for (i = 0; i < edgecollection_length(network->graph->edges); i++) {
        EdgePointer edge = edgecollection_get(network->graph->edges, i);
        if (vertex_equals(edge->first, network->source)) {
            unsigned int capacity = networkedge_capacity(network, edge);
            networkedge_set_flow(network, edge, capacity);
        } else {
            networkedge_set_flow(network, edge, 0);
        }
    }
    size_t n_vertices = vertexcollection_length(network->graph->vertices);
    networkvertex_set_distance_label(network, network->source, n_vertices);
}

static Label find_min(const NetworkPointer network, const EdgeCollection edges)
{
    Label min = INT_MAX;
    size_t i;
    for (i = 0; i < edgecollection_length(edges); i++) {
        EdgePointer edge = edgecollection_get(edges, i);
            Label label = networkvertex_distance_label(network, edge->second) + 1;
            if (label < min) {
                min = label;
            }
    }
    if (i == 0) {
        runtime_error("relabel: vertex should have at least one outgoing edge");
    }
    return min;
}

static void push(const NetworkPointer network, const EdgePointer edge, const VertexPointer vertex)
{
    unsigned int exflow = networkvertex_exflow(network, vertex);
    unsigned int capacity = networkedge_residual_capacity(network, edge);
    unsigned int gamma = smaller(exflow, capacity);
    networkedge_augment(network, edge, gamma);
}

static void relabel(const NetworkPointer network, const VertexPointer vertex)
{
    GraphPointer residual_graph = network_residual_graph(network);
    EdgeCollection out_edges = graph_out_edges_from(residual_graph, vertex);
    networkvertex_set_distance_label(network, vertex, find_min(network, out_edges));
    edgecollection_destroy(out_edges);
    graph_destroy(residual_graph);
}

void push_relabel(NetworkPointer network)
{
    push_relabel_initialize(network);
    VertexPointer active = network_active_vertex(network);
    while (active) {
        GraphPointer residual_graph = network_residual_graph(network);
        EdgeCollection out_edges = graph_out_edges_from(residual_graph, active);
        EdgePointer admissable = networkedge_admissable(network, out_edges);
        edgecollection_destroy(out_edges);
        graph_destroy(residual_graph);
        if (!admissable) {
            relabel(network, active);
        } else {
            push(network, admissable, active);
        }
        active = network_active_vertex(network);
    }
}
