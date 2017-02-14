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
    unsigned int            *capacities;
    int                     *flows;
    Map                     is_reverse;

    VertexCollection        active_vertices;
    Label                   *distance_labels;

    VertexCollection        strong_vertices, weak_vertices; 
    VertexCollection        source_neighbours, sink_neighbours;
    EdgeCollection          source_edges, sink_edges;
    int                     *excesses;
    VertexPointer           root;
} Network, *NetworkPointer;

EdgeCollection network_edgepath_to_treeroot(const NetworkPointer network, const VertexPointer vertex);

int networkvertex_exflow_ps(
        const NetworkPointer network, 
        const VertexPointer vertex
    );
int networkvertex_exflow_pr(const NetworkPointer network, const VertexPointer vertex);

unsigned int networkvertex_inflow(const NetworkPointer network, const Vertex vertex);

unsigned int networkedge_flow(const NetworkPointer network, const EdgePointer edge);

void network_init(NetworkPointer network, NetworkType type, const unsigned int n_vertices, const unsigned int n_edges);

unsigned int network_flow(const NetworkPointer network);

void network_destroy(NetworkPointer network);

EdgePointer networkedge_get_sink_edge(
        const NetworkPointer network,
        const VertexPointer vertex
    );

EdgePointer networkedge_get_source_edge(
        const NetworkPointer network,
        const VertexPointer vertex
    );

#endif
