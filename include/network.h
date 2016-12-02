#ifndef NETWORK_H
#define NETWORK_H

#include "graph.h"

typedef struct network {
    GraphPointer graph;
    GraphPointer rev_graph;
    VertexPointer source;
    VertexPointer sink;
} Network, *NetworkPointer;

Result make_network(
        const GraphPointer graph, 
        const Label source_label, 
        const Label sink_label,
        NetworkPointer ret
    );

// Denote the value of this function dl(v) for any vertex
// dl(t) = 0
// dl(s) = n
// dl(v) <= dl(w) + 1 for all (v, w) in E(G_f).
unsigned int distance_labeling(const Graph graph, const Vertex vertex);

#endif
