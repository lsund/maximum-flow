#ifndef NETWORK_EDGE_H
#define NETWORK_EDGE_H

#include "network.h"
#include "push_relabel_network.h"

typedef enum EdgeType { FORWARD, REVERSE } EdgeType;

EdgePointer networkedge_get_sink_edge(
        const NetworkPointer network,
        const VertexPointer vertex
    );

EdgePointer networkedge_get_source_edge(
        const NetworkPointer network,
        const VertexPointer vertex
    );

Label networkvertex_distance_label(const NetworkPointer network, const Vertex vertex);

int networkvertex_exflow_pr(const NetworkPointer network, const Vertex vertex);

int networkvertex_exflow_ps(const NetworkPointer network, const VertexPointer vertex);

unsigned int networkedge_capacity(
        const NetworkPointer network, 
        const Edge edge
    );

unsigned int networkedge_residual_capacity(
        const NetworkPointer network, 
        const Edge edge
    );

unsigned int networkedge_flow(const NetworkPointer network, const Edge edge);

bool networkedge_is_reverse(const NetworkPointer network, const Edge edge);

void networkedge_augment(const NetworkPointer network, const Edge edge, const unsigned int added_flow);

void networkedge_set_capacity(
        const NetworkPointer network, 
        const Edge edge, 
        unsigned int capacity
    );

void networkedge_fill_flow(
        const NetworkPointer network,
        const Edge edge,
        const unsigned int capacity,
        const EdgeType type
    );

void networkedge_set_flow(
        const NetworkPointer network, 
        const Edge edge, 
        int flow
    );

void networkedge_add_flow(
        const NetworkPointer network,
        const Edge edge, 
        int added_flow
    );

#endif
