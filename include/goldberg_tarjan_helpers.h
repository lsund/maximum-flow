#ifndef GOLDBERG_TARJAN_HELPERS_H
#define GOLDBERG_TARJAN_HELPERS_H

#include "network.h"

VertexCollection active_vertices(const NetworkPointer network); 

void discharge(const NetworkPointer network, const VertexPointer vertex);

#endif
