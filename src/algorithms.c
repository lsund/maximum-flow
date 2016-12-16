
#include "algorithms.h"

static void push_relabel_initialize(NetworkPointer network)
{
    size_t i;
    for (i = 0; i < edgecollection_length(network->graph->edges); i++) {
        EdgePointer edge = edgecollection_get(network->graph->edges, i);
        if (edge_incident_with(edge, network->source)) {
            unsigned int capacity = network_edge_capacity(network, edge);
            network_set_edge_flow(network, edge, capacity);
        } else {
            network_set_edge_flow(network, edge, 0);
        }
    }
}

static void push(const NetworkPointer network, const EdgePointer edge, const VertexPointer vertex)
{
    unsigned int exflow = network_vertex_exflow(network, vertex);
    unsigned int capacity = network_edge_capacity(network, edge);
    unsigned int gamma = smaller(exflow, capacity);
    network_augment_edge(network, edge, gamma);
}

static void relabel(const NetworkPointer network, const VertexPointer vertex)
{
    EdgeCollection incident_with_vertex = graph_incident_with(network->graph, vertex);
    size_t i;
    Label min;
    for (i = 0; i < edgecollection_length(incident_with_vertex); i++) {
        EdgePointer edge = edgecollection_get(incident_with_vertex, i);
        if (network_edge_is_residual(network, edge)) {
            Label label = network_vertex_distance_label(network, edge->second) + 1;
            if (label < min) {
                min = label;
            }
        }
    }
    if (i == 0) {
        runtime_error("relabel: vertex should have at least one outgoing edge");
    }
    network_vertex_set_distance_label(network, vertex, min);
}

void push_relabel(NetworkPointer network)
{
    push_relabel_initialize(network);
    VertexPointer active = network_active_vertex(network);
    while (active) {
        EdgeCollection active_incident = graph_incident_with(network->graph, active);
        EdgePointer admissable = network_admissable_edge(network, active_incident);
        if (!admissable) {
            relabel(network, active);
        } else {
            push(network, admissable, active);
        }
        active = network_active_vertex(network);
    }
}
