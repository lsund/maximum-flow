
#include "pseudoflow_network.h"

bool is_residual(const NetworkPointer network, const EdgePointer edge)
{
    return networkedge_residual_capacity(network, edge) > 0;
}

bool is_merger_edge(const NetworkPointer network, const EdgePointer edge)
{
    return (
            vertexcollection_contains_label(
                network->strong_vertices, 
                edge->first.label
            ) &&
            vertexcollection_contains_label(
                network->weak_vertices, 
                edge->second.label
            )
       );
}

EdgePointer merger_edge(const NetworkPointer network)
{
    // Later maintain residual edges. For now just iterate over forward and
    // backward edges
    size_t i;
    for (i = 0; i < edgecollection_length(network->graph.edges); i++) {
        EdgePointer edge = edgecollection_get(network->graph.edges, i);
        if (is_residual(network, edge) && is_merger_edge(network, edge)) {
            return edge;
        }
    }
    for (i = 0; i < edgecollection_length(network->reverse_edges); i++) {
        EdgePointer edge = edgecollection_get(network->graph.edges, i);
        if (is_residual(network, edge) && is_merger_edge(network, edge)) {
            return edge;
        }
    }
    return NULL;
}

