#include "networkvertex.h"

unsigned int networkvertex_inflow(
        const NetworkPointer network,
        const Vertex vertex)
{
    if (network->type == PS) {
        EdgeCollection edges = network->graph.edges;
        unsigned int sum;
        size_t i;
        for (i = 0, sum = 0; i < edgecollection_length(edges); i++) {
            EdgePointer edge = edgecollection_get(edges, i);
            if (vertex_equals(edge->second, vertex)) {
                sum += edge_flow(edge);
            }
        }
        return sum;
    } else {
        return *(network->inflows + vertex.label);
    }
}

int networkvertex_exflow_pr(const NetworkPointer network, const VertexPointer vertex)
{
    unsigned int inflow, outflow;
    inflow = *(network->inflows + vertex->label);
    outflow = *(network->outflows + vertex->label);
    return inflow - outflow;
}

int networkvertex_is_strong(
        const NetworkPointer network,
        const VertexPointer vertex_p
    )
{
    if (network->type == PR) {
        return networkvertex_exflow_pr(network, vertex_p) > 0;
    } else {
        return vertex_exflow_ps(vertex_p) > 0;
    }
}

