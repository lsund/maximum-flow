#ifndef NETWORK_EDGE_H
#define NETWORK_EDGE_H

#include "network.h"

Label networkvertex_distance_label(const NetworkPointer network, const VertexPointer vertex);

unsigned int networkedge_capacity(const NetworkPointer network, const EdgePointer edge);

unsigned int networkedge_residual_capacity(const NetworkPointer network, const EdgePointer edge);

unsigned int networkedge_flow(const NetworkPointer network, const EdgePointer edge);

bool networkedge_is_reverse(const NetworkPointer network, const EdgePointer edge);

EdgePointer networkedge_reverse(const NetworkPointer network, const EdgePointer edge);

void networkedge_augment(const NetworkPointer network, const EdgePointer edge, const unsigned int added_flow);

EdgePointer networkedge_admissable(const NetworkPointer network, const EdgeCollection edges, GraphPointer residual_graph);

void networkedge_set_capacity(
        const NetworkPointer network, 
        const EdgePointer edge, 
        const unsigned int capacity
    );

void networkedge_set_flow(
        const NetworkPointer network, 
        const EdgePointer edge, 
        const int flow
    );

#endif