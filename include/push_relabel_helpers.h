#ifndef PUSH_RELABEL_HELPERS
#define PUSH_RELABEL_HELPERS

#include "network.h"

void relabel(const NetworkPointer network, const VertexPointer vertex);

void push(const NetworkPointer network, const EdgePointer edge, const VertexPointer vertex);

Label find_min(const NetworkPointer network, const Vertex vertex);

VertexPointer networkvertex_active(const NetworkPointer network);

EdgePointer networkedge_admissable(
        const NetworkPointer network, 
        const Vertex active
    );

#endif
