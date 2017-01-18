
#include "network.h"

NetworkPointer network_init(NetworkType type)
{
    NetworkPointer ret   = malloc(sizeof(Network));
    ret->graph           = graph_init();
    ret->reverse_edges   = edgecollection_empty();
    ret->source          = vertex_empty();
    ret->sink            = vertex_empty();
    ret->capacities      = NULL;
    ret->flows           = NULL;
    ret->inflows         = NULL;
    ret->outflows        = NULL;
    ret->residual_edges  = NULL;
    ret->is_reverse      = map_create();
    ret->type            = type;

    ret->active_vertices = vertexcollection_empty();
    ret->distance_labels = NULL;

    ret->excesses        = NULL;
    ret->strong_vertices = vertexcollection_empty();
    ret->weak_vertices   = vertexcollection_empty();

    return ret;
}

unsigned int network_flow(const NetworkPointer network)
{
    return networkvertex_inflow(network, network->sink);
}

void network_destroy(NetworkPointer network)
{
    if (network->type == PR) {
        free(network->distance_labels);
        vertexcollection_destroy(network->active_vertices);
    }
    free(network->flows);
    free(network->capacities);
    free(network->inflows);
    free(network->outflows);
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
    for (i = 1; i <= vertexcollection_length(network->graph.vertices); i++) {
        edgecollection_destroy(*(network->residual_edges + i));
    }
    free(network->residual_edges);
    edgecollection_destroy(network->reverse_edges);
    graph_destroy(network->graph);
    free(network);
}


