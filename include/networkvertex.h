#ifndef NETWORK_VERTEX_H
#define NETWORK_VERTEX_H

#include "network.h"

void networkvertex_add_neighbour(
        const NetworkPointer network, 
        const VertexPointer neighbour, 
        const Vertex vertex
    );

unsigned int networkedge_flow(
        const NetworkPointer network, 
        const EdgePointer edge
    );

unsigned int networkvertex_inflow(
        const NetworkPointer network, 
        const Vertex vertex
    );

int networkvertex_exflow_pr(
        const NetworkPointer network, 
        const VertexPointer vertex
    );

int networkvertex_excess(
        const NetworkPointer network,
        const Vertex vertex
    );

int networkvertex_is_strong(
        const NetworkPointer network, 
        const VertexPointer vertex_p
    );

#endif
