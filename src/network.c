
#include "network.h"

NetworkPointer network_init()
{
    NetworkPointer ret   = malloc(sizeof(Network));
    ret->graph           = NULL;
    ret->reverse_edges   = edgecollection_init(ARRAY_MIN_SIZE);
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
    VertexCollection vertices = vertexcollection_init(ARRAY_MIN_SIZE);
    size_t i;
    for (i = 0; i < vertexcollection_length(network->graph->vertices); i++) {
        VertexPointer p_vertex = vertexcollection_get(network->graph->vertices, i);
        vertexcollection_push(vertices, p_vertex);
    }
    EdgeCollection edges = edgecollection_init(ARRAY_MIN_SIZE);
    for (i = 0; i < edgecollection_length(network->graph->edges); i++) {
        EdgePointer p_edge = edgecollection_get(network->graph->edges, i);
        Edge reverse_edge = edge_swapped(*p_edge);
        unsigned int index = edgecollection_index_of(network->reverse_edges, &reverse_edge);
        EdgePointer reverse_p_edge = edgecollection_get(network->reverse_edges, index);
        if (networkedge_residual_capacity(network, p_edge) > 0) { 
            edgecollection_push(edges, p_edge);
        }
        if (networkedge_residual_capacity(network, reverse_p_edge) > 0) {
            edgecollection_push(edges, reverse_p_edge);
        }
    }
    return graph_make(vertices, edges);
}

void network_destroy(NetworkPointer network)
{
    free(network->distance_labels);
    free(network->flows);
    free(network->capacities);
    size_t i;
    for (i = 0; i < edgecollection_length(network->graph->edges); i++) {
        EdgePointer edge = edgecollection_get(network->graph->edges, i);
        EdgePointer rev_edge = edgecollection_get(network->reverse_edges, i);
        free(edge);
        free(rev_edge);
    }
    for (i = 0; i < vertexcollection_length(network->graph->vertices); i++) {
        VertexPointer vertex = vertexcollection_get(network->graph->vertices, i);
        free(vertex);
    }
    edgecollection_destroy(network->reverse_edges);
    graph_destroy(network->graph);
    free(network);
}

