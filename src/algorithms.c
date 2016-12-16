
#include "network.h"

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

static void relabel(const NetworkPointer network, const VertexPointer vertex)
{
}

static void push(const NetworkPointer network, const EdgePointer edge)
{
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
            push(network, admissable);
        }
        active = network_active_vertex(network);
    }
}
