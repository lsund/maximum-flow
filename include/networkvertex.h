#ifndef NETWORK_VERTEX_H
#define NETWORK_VERTEX_H

#include "network.h"
unsigned int networkedge_flow(const NetworkPointer network, const EdgePointer edge);

Label networkvertex_distance_label(const NetworkPointer network, const VertexPointer vertex);

unsigned int networkvertex_inflow(const NetworkPointer network, const VertexPointer vertex);

int networkvertex_exflow(const NetworkPointer network, const VertexPointer vertex);

void networkvertex_set_flow(const NetworkPointer network, const VertexPointer vertex);

void networkvertex_set_distance_label(const NetworkPointer network, const VertexPointer vertex, const unsigned int label);

bool networkvertex_is_active(const NetworkPointer network, const VertexPointer vertex);

VertexPointer network_active_vertex(const NetworkPointer network);

#endif
