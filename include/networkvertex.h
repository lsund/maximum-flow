#ifndef NETWORK_VERTEX_H
#define NETWORK_VERTEX_H

#include "network.h"

unsigned int networkvertex_inflow(
        const NetworkPointer network, 
        const Vertex vertex
    );

int networkvertex_is_strong(
        const NetworkPointer network, 
        const VertexPointer vertex_p
    );

#endif
