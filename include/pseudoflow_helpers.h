
#include "network.h"

VertexPointer merge(
        const VertexPointer strong_vertex,
        const VertexPointer weak_vertex
    );

unsigned int push_flow(
        const NetworkPointer network,
        const EdgePointer edge,
        const unsigned int amount
    );

EdgePointer merger_edge(const NetworkPointer network);

