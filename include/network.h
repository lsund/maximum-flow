#ifndef NETWORK_H
#define NETWORK_H

#include "graph.h"
#include "tree.h"

typedef enum networktype { PR, PS } NetworkType;

typedef struct network {
    NetworkType             type;
    Graph                   graph;
    VertexPointer           source, sink, root;
    EdgeCollection          *neighbors;
} Network, *NetworkPointer;

NetworkPointer network_make(
        const NetworkType type,
        const unsigned int n_vertices
    );

EdgeCollection network_edgepath_to_treeroot(const NetworkPointer network,
        const VertexPointer vertex
    );

unsigned int network_flow(const NetworkPointer network);

void network_add_out_edge(
        const NetworkPointer network,
        const Vertex vertex,
        const EdgePointer edge
    );

EdgeCollection network_get_out_edges(
        const NetworkPointer network,
        const Vertex vertex
    );

EdgePointer network_get_out_edge(
        const NetworkPointer network,
        const Vertex first, 
        const Vertex second
    );

void network_destroy(NetworkPointer network);

#endif
