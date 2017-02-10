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
        const Edge edge
    );
\

unsigned int networkvertex_inflow(
        const NetworkPointer network, 
        const Vertex vertex
    );

int networkvertex_exflow_pr(
        const NetworkPointer network, 
        const Vertex vertex
    );

int networkvertex_exflow_ps(
        const NetworkPointer network, 
        const VertexPointer vertex
    );

void networkvertex_set_flow(
        const NetworkPointer network, 
        const Vertex vertex
    );

bool networkvertex_is_active(
        const NetworkPointer network, 
        const Vertex vertex
    );

int networkvertex_excess(
        const NetworkPointer network,
        const Vertex vertex
    );

int networkvertex_is_strong(
        const NetworkPointer network, 
        const Vertex vertex,
        const VertexPointer vertex_p
    );

#endif
