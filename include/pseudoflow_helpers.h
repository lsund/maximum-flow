
#include "network_functions.h"
#include "pseudoflow_network.h"

VertexPointer update_tree(
        const VertexPointer strong_vertex,
        const VertexPointer weak_vertex
    );

unsigned int push_flow(
        const NetworkPointer network,
        const EdgePointer edge,
        const unsigned int amount
    );
