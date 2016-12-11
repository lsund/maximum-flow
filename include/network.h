#ifndef NETWORK_H
#define NETWORK_H

#include "graph.h"

typedef struct network {
    GraphPointer graph;
    GraphPointer rev_graph;
    VertexPointer source;
    VertexPointer sink;
} Network, *NetworkPointer;

Result network_make(
        const GraphPointer graph, 
        const Label source_label, 
        const Label sink_label,
        NetworkPointer ret
    );

#endif
