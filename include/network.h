#ifndef NETWORK_H
#define NETWORK_H

#include "graph.h"

typedef struct network {
    Graph                   graph;
    EdgeCollection          reverse_edges;
    VertexCollection        active_vertices;
    EdgeCollectionPointer   residual_edges;
    Vertex                  source;
    Vertex                  sink;
    unsigned int            *capacities, *inflows, *outflows;
    int                     *flows;
    Label                   *distance_labels;
    Map                     is_reverse;
} Network, *NetworkPointer;

unsigned int networkvertex_inflow(const NetworkPointer network, const Vertex vertex);

unsigned int networkedge_residual_capacity(const NetworkPointer network, const EdgePointer edge);

NetworkPointer network_init();

unsigned int network_flow(const NetworkPointer network);

void network_destroy(NetworkPointer network);

#endif
