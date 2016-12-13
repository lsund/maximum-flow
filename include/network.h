#ifndef NETWORK_H
#define NETWORK_H

#include "graph.h"

typedef struct network {
    GraphPointer graph;
    GraphPointer rev_graph;
    VertexPointer source;
    VertexPointer sink;
} Network, *NetworkPointer;

Network network_make(
        const GraphPointer graph, 
        const Label source_label, 
        const Label sink_label
    );

Graph network_residual(const Network network);

Label network_get_vertex_distance_label(const VertexPointer vertex);

float network_get_edge_flow(const EdgePointer edge);

float network_get_edge_capacity(const EdgePointer edge);

float network_edge_is_reverse(const EdgePointer edge);

#endif
