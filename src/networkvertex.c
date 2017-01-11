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

/* bool network_vertexset_is_strong( */
/*         const NetworkPointer network, */ 
/*         const VertexCollection vertices */
/*     ) */
/* { */
/*     size_t i = 0; */
/*     int sum = 0; */
/*     for (i = 0; i < vertexcollection_length(vertices); i++) { */
/*         sum += networkvertex_exflow(network, *vertexcollection_get(vertices, i)); */
/*     } */
/*     return sum > 0; */
/* } */

