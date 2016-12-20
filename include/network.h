#ifndef NETWORK_H
#define NETWORK_H

#include "graph.h"

typedef struct network {
    Graph           graph;
    Graph           residual_graph;
    EdgeCollection  reverse_edges;
    EdgeCollection  active_edges;
    VertexPointer   source;
    VertexPointer   sink;
    unsigned int    *capacities;
    unsigned int    *residual_capacities;
    int             *flows;
    Label           *distance_labels;
} Network, *NetworkPointer;

unsigned int networkvertex_inflow(const NetworkPointer network, const VertexPointer vertex);

unsigned int networkedge_residual_capacity(const NetworkPointer network, const EdgePointer edge);

NetworkPointer network_init();

unsigned int network_flow(const NetworkPointer network);

void network_destroy(NetworkPointer network);

#endif
