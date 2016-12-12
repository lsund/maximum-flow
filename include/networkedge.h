#ifndef NETWORK_EDGE_H
#define NETWORK_EDGE_H

#include "edge.h"

typedef struct networkedge {
    EdgePointer content;
    float capacity;
    float flow;
    bool is_reverse;
} NetworkEdge, *NetworkEdgePointer;

NetworkEdge networkedge_make(
        const EdgePointer content, 
        const float capacity, 
        const float flow, 
        const bool is_reverse
    );

NetworkEdgePointer networkedge_p_make(
        const EdgePointer content, 
        const float capacity, 
        const float flow, 
        const bool is_reverse
    );

NetworkEdgePointer networkedge_p_make_label(
        const Label first_label,
        const Label second_label
    );

float networkedge_residual_capacity(const NetworkEdge networkedge);

#endif
