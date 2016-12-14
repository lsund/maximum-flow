#ifndef NETWORK_H
#define NETWORK_H

#include "graph.h"

typedef struct network {
    GraphPointer graph;
    GraphPointer rev_graph;
    VertexPointer source;
    VertexPointer sink;
    unsigned int *capacities;
} Network, *NetworkPointer;

Label network_vertex_distance_label(const NetworkPointer network, const VertexPointer vertex);

unsigned int network_vertex_exflow(const NetworkPointer network, const VertexPointer vertex);

unsigned int network_edge_flow(const NetworkPointer network, const EdgePointer edge);

unsigned int network_edge_capacity(const NetworkPointer network, const EdgePointer edge);

void network_set_edge_capacity(
        const NetworkPointer network, 
        const EdgePointer edge, 
        unsigned int capacity
    );

bool network_edge_is_reverse(const NetworkPointer network, const EdgePointer edge);

Graph network_residual(const NetworkPointer network);

#endif
