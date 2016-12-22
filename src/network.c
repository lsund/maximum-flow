
#include "network.h"

NetworkPointer network_init()
{
    NetworkPointer ret   = malloc(sizeof(Network));
    ret->graph           = graph_init();
    ret->residual_graph  = graph_init();
    ret->reverse_edges   = edgecollection_init(ARRAY_MIN_SIZE);
    ret->active_edges    = edgecollection_init(ARRAY_MIN_SIZE);
    ret->source          = vertex_empty();
    ret->sink            = vertex_empty();
    ret->capacities      = NULL;
    ret->flows           = NULL;
    ret->distance_labels = NULL;
    ret->inflows         = NULL;
    ret->outflows        = NULL;
    return ret;
}

unsigned int network_flow(const NetworkPointer network)
{
    return networkvertex_inflow(network, network->sink);
}

void network_destroy(NetworkPointer network)
{
    free(network->distance_labels);
    free(network->flows);
    free(network->capacities);
    size_t i;
    for (i = 0; i < edgecollection_length(network->graph.edges); i++) {
        EdgePointer edge = edgecollection_get(network->graph.edges, i);
        EdgePointer rev_edge = edgecollection_get(network->reverse_edges, i);
        free(edge);
        free(rev_edge);
    }
    for (i = 0; i < vertexcollection_length(network->graph.vertices); i++) {
        VertexPointer vertex = vertexcollection_get(network->graph.vertices, i);
        free(vertex);
    }
    edgecollection_destroy(network->reverse_edges);
    edgecollection_destroy(network->active_edges);
    graph_destroy(network->graph);
    graph_destroy(network->residual_graph);
    free(network);
}


