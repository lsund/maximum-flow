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

int networkvertex_exflow_pr(const NetworkPointer network, const Vertex vertex)
{
    unsigned int inflow, outflow;
    inflow = *(network->inflows + vertex.label);
    outflow = *(network->outflows + vertex.label);
    return inflow - outflow;
}

int networkvertex_exflow_ps(const NetworkPointer network, const VertexPointer vertex)
{
    VertexPointer branch = tree_find_branch(vertex);
    return *(network->excesses + branch->label);
}

int networkvertex_is_strong(const NetworkPointer network, const Vertex vertex, const VertexPointer vertex_p)
{
    if (network->type == PR) {
        return networkvertex_exflow_pr(network, vertex) > 0;
    } else {
        return networkvertex_exflow_ps(network, vertex_p) > 0;
    }
}


bool networkvertex_is_active(const NetworkPointer network, const Vertex vertex)
{
    return networkvertex_exflow_pr(network, vertex) > 0;
}

