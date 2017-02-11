#ifndef PUSH_RELABEL_NETWORK
#define PUSH_RELABEL_NETWORK

#include "network.h"

VertexPointer networkvertex_active(const NetworkPointer network);

void activate_vertices(
        const NetworkPointer network, 
        const Edge edge, 
        const unsigned int first_exflow_before,
        const unsigned int second_exflow_before,
        const unsigned int first_exflow,
        const unsigned int second_exflow
    );

EdgePointer networkedge_admissable(
        const NetworkPointer network, 
        const Vertex active
    );

#endif
