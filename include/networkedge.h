#ifndef NETWORK_EDGE_H
#define NETWORK_EDGE_H

#include "network.h"
#include "push_relabel_network.h"

Label networkvertex_distance_label(const NetworkPointer network, const Vertex vertex);
int networkvertex_exflow(const NetworkPointer network, const Vertex vertex);

unsigned int networkedge_capacity(const NetworkPointer network, const EdgePointer edge);

unsigned int networkedge_residual_capacity(const NetworkPointer network, const EdgePointer edge);

unsigned int networkedge_flow(const NetworkPointer network, const EdgePointer edge);

bool networkedge_is_reverse(const NetworkPointer network, const EdgePointer edge);

EdgePointer networkedge_reverse(const NetworkPointer network, const EdgePointer edge);

void networkedge_augment(const NetworkPointer network, const EdgePointer edge, const unsigned int added_flow);

EdgePointer networkedge_admissable(
        const NetworkPointer network, 
        const Vertex active
    );

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

void networkedge_add_flow(
        const NetworkPointer network, 
        const EdgePointer edge, 
        int added_flow
    );

#endif
