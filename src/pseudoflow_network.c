
#include "pseudoflow_network.h"

bool is_merger_edge(const NetworkPointer network, const Edge edge)
{
    bool is_source_edge = edge_incident_with(edge, *network->source);
    bool is_sink_edge = edge_incident_with(edge, *network->sink);
    bool is_valid_edge = !(is_source_edge || is_sink_edge);
    if (!is_valid_edge) {
        return false;
    }
    bool first_is_strong = networkvertex_is_strong(network, edge.first, edge.first_ref);
    bool second_is_weak = !networkvertex_is_strong(network, edge.second, edge.second_ref);
    return first_is_strong && second_is_weak;
}

EdgePointer merger_edge(const NetworkPointer network)
{
    size_t i;
    for (i = 0; i < edgecollection_length(network->graph.edges); i++) {
        EdgePointer edge = edgecollection_get(network->graph.edges, i);
        if (edge_is_residual(edge) && is_merger_edge(network, *edge)) {
            return edge;
        }
    }
    for (i = 0; i < edgecollection_length(network->reverse_edges); i++) {
        EdgePointer edge = edgecollection_get(network->reverse_edges, i);
        if (edge_is_residual(edge) && is_merger_edge(network, *edge)) {
            return edge;
        }
    }
    return NULL;
}

