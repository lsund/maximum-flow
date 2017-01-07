#ifndef PUSH_RELABEL_NETWORK
#define PUSH_RELABEL_NETWORK

#include "network.h"

Result networkvertex_active(const NetworkPointer network, VertexPointer vertex);

void activate_vertices(
        const NetworkPointer network, 
        const EdgePointer edge, 
        const unsigned int first_exflow_before,
        const unsigned int second_exflow_before,
        const unsigned int first_exflow,
        const unsigned int second_exflow
    );

#endif
