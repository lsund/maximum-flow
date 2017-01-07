#include "networkvertex.h"

unsigned int networkvertex_inflow(const NetworkPointer network, const Vertex vertex)
{
    return *(network->inflows + vertex.label);
}

int networkvertex_exflow(const NetworkPointer network, const Vertex vertex)
{
    unsigned int inflow, outflow;
    inflow = *(network->inflows + vertex.label);
    outflow = *(network->outflows + vertex.label);
    return inflow - outflow;
}

bool networkvertex_is_active(const NetworkPointer network, const Vertex vertex)
{
    return networkvertex_exflow(network, vertex) > 0;
}

