#ifndef PUSH_RELABEL_HELPERS
#define PUSH_RELABEL_HELPERS

#include "network.h"

VertexCollection active_vertices(const NetworkPointer network); 

void discharge(const NetworkPointer network, const VertexPointer vertex);

VertexPointer networkvertex_active(const NetworkPointer network);

EdgePointer admissable_edge(
        const NetworkPointer network, 
        const Vertex active
    );

#endif
