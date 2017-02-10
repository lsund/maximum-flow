#ifndef PUSH_RELABEL_NETWORK
#define PUSH_RELABEL_NETWORK

#include "network.h"

Result networkvertex_active(
        const NetworkPointer network,
        VertexPointer vertex);

void activate_vertices(
        const NetworkPointer network, 
        const Edge edge, 
        const unsigned int first_exflow_before,
        const unsigned int second_exflow_before,
        const unsigned int first_exflow,
        const unsigned int second_exflow
    );

Label networkvertex_distance_label(
        const NetworkPointer network, 
        const Vertex vertex
    );

void networkvertex_set_distance_label(
        const NetworkPointer network,
        const Vertex vertex, 
        const unsigned int label
    );

EdgePointer networkedge_admissable(
        const NetworkPointer network, 
        const Vertex active
    );

#endif
