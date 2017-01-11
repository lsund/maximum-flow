
#include "pseudoflow.h"

static void initialize_strong(NetworkPointer network)
{
}

static void pseudoflow_initialize(NetworkPointer network)
{
    EdgePointer edge;
    VertexPointer vertex;
    VertexCollection vertices;
    unsigned int capacity;
    size_t i;
    vertices = network->graph.vertices;
    /* for (i = 0; i < vertexcollection_length(network->graph.vertices); i++) { */
    /*     edge = edgecollection_get(network->graph.edges, i); */
    /*     if (vertex_equals(edge->first, network->source)) { */
    /*         capacity = networkedge_capacity(network, edge); */
    /*         networkedge_augment(network, edge, capacity); */
    /*         *(network->excesses + i) = capacity; */
    /*         vertex = vertexcollection_get_reference(vertices, edge->first); */
    /*         vertexcollection_push(network->strong_vertices, vertex); */
    /*     } else if (vertex_equals(edge->second, network->sink)) { */
    /*         capacity = networkedge_capacity(network, edge); */
    /*         networkedge_augment(network, edge, capacity); */
    /*         *(network->excesses + i) = -capacity; */
    /*         vertex = vertexcollection_get_reference(vertices, edge->first); */
    /*         vertexcollection_push(network->weak_vertices, vertex); */
    /*     } else { */
        /* } */
    /* } */
}

void pseudoflow(NetworkPointer network)
{
    // blah
    return;
}
