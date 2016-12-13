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

Network network_make(
        const GraphPointer graph, 
        const Label source_label, 
        const Label sink_label
    );

Label network_get_vertex_distance_label(const NetworkPointer network, const VertexPointer vertex);

unsigned int network_get_edge_flow(const NetworkPointer network, const EdgePointer edge);

unsigned int network_get_edge_capacity(const NetworkPointer network, const EdgePointer edge);

void network_set_edge_capacity(
        const NetworkPointer network, 
        const EdgePointer edge, 
        unsigned int capacity
    );

bool network_edge_is_reverse(const NetworkPointer network, const EdgePointer edge);

Graph network_residual(const NetworkPointer network);

#endif
