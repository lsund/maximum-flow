#ifndef NETWORK_H
#define NETWORK_H

#include "graph.h"
#include "tree.h"

typedef enum networktype { PR, PS } NetworkType;

typedef struct network {
    NetworkType             type;
    Graph                   graph;
    EdgeCollection          reverse_edges;
    EdgeCollectionPointer   residual_edges;
    VertexPointer           source, sink;
    unsigned int            *capacities, *inflows, *outflows;
    int                     *flows;
    Map                     is_reverse;

    VertexCollection        active_vertices;
    Label                   *distance_labels;

    VertexCollection        strong_vertices, weak_vertices; 
    int                     *excesses;
} Network, *NetworkPointer;

unsigned int networkvertex_inflow(const NetworkPointer network, const Vertex vertex);

unsigned int networkedge_residual_capacity(const NetworkPointer network, const EdgePointer edge);

NetworkPointer network_init(NetworkType type);

unsigned int network_flow(const NetworkPointer network);

void network_destroy(NetworkPointer network);

#endif
