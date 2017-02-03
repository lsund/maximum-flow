
#include "pseudoflow_network.h"

bool is_residual(const NetworkPointer network, const EdgePointer edge)
{
    return networkedge_residual_capacity(network, edge) > 0;
}

bool is_merger_edge(const NetworkPointer network, const EdgePointer edge)
{
    bool is_source_edge = edge_incident_with(edge, *network->source);
    bool is_sink_edge = edge_incident_with(edge, *network->sink);
    bool is_valid_edge = !(is_source_edge || is_sink_edge);
    if (!is_valid_edge) {
        return false;
    }
    bool first_is_strong = networkvertex_is_strong(network, edge->first);
    bool second_is_weak = !networkvertex_is_strong(network, edge->second);
    return first_is_strong && second_is_weak;
}

EdgePointer merger_edge(const NetworkPointer network)
{
    size_t i;
    for (i = 0; i < edgecollection_length(network->graph.edges); i++) {
        EdgePointer edge = edgecollection_get(network->graph.edges, i);
        if (is_residual(network, edge) && is_merger_edge(network, edge)) {
            return edge;
        }
    }
    for (i = 0; i < edgecollection_length(network->reverse_edges); i++) {
        EdgePointer edge = edgecollection_get(network->reverse_edges, i);
        if (is_residual(network, edge) && is_merger_edge(network, edge)) {
            return edge;
        }
    }
    return NULL;
}

