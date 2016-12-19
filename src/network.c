
#include "network.h"

NetworkPointer network_init()
{
    NetworkPointer ret   = malloc(sizeof(Network));
    ret->graph           = NULL;
    ret->source          = NULL;
    ret->sink            = NULL;
    ret->capacities      = NULL;
    ret->flows           = NULL;
    ret->distance_labels = NULL;
    return ret;
}

unsigned int network_flow(const NetworkPointer network)
{
    return networkvertex_inflow(network, network->sink);
}

GraphPointer network_residual_graph(const NetworkPointer network)
{
    VertexCollection vertices = network->graph->vertices; 
    EdgeCollection edges = edgecollection_init(ARRAY_MIN_SIZE);
    size_t i;
    for (i = 0; i < edgecollection_length(network->graph->edges); i++) {
        EdgePointer p_edge = edgecollection_get(network->graph->edges, i);
        Edge reverse_edge = edge_swapped(*p_edge);
        EdgePointer reverse_p_edge = edge_p_make_edge(reverse_edge);
        if (networkedge_residual_capacity(network, p_edge)) { 
            edgecollection_push(edges, p_edge);
        }
        if (networkedge_residual_capacity(network, reverse_p_edge)) {
            edgecollection_push(edges, reverse_p_edge);
        }
    }
    return graph_make(vertices, edges);
}
