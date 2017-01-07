#ifndef NETWORK_VERTEX_H
#define NETWORK_VERTEX_H

#include "network.h"
unsigned int networkedge_flow(const NetworkPointer network, const EdgePointer edge);

unsigned int networkvertex_inflow(const NetworkPointer network, const Vertex vertex);

int networkvertex_exflow(const NetworkPointer network, const Vertex vertex);

void networkvertex_set_flow(const NetworkPointer network, const Vertex vertex);

bool networkvertex_is_active(const NetworkPointer network, const Vertex vertex);

#endif
