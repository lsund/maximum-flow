#ifndef NETWORK_H
#define NETWORK_H

#include "graph.h"
#include "networkedge.h"

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

#endif
