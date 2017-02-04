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
                sum += networkedge_flow(network, edge);
            }
        }
        return sum;
    } else {
        return *(network->inflows + vertex.label);
    }
}

int networkvertex_exflow(const NetworkPointer network, const Vertex vertex)
{
    if (network->type == PR) {
        unsigned int inflow, outflow;
        inflow = *(network->inflows + vertex.label);
        outflow = *(network->outflows + vertex.label);
        return inflow - outflow;
    } else {
        VertexPointer vertex_p, branch;
        vertex_p   = vertexcollection_get_reference(
                        network->graph.vertices,
                        vertex
                    );
        branch     = tree_find_branch(vertex_p);
        return *(network->excesses + branch->label);
    }
}

int networkvertex_is_strong(const NetworkPointer network, const Vertex vertex)
{
    return networkvertex_exflow(network, vertex) > 0;
}


bool networkvertex_is_active(const NetworkPointer network, const Vertex vertex)
{
    return networkvertex_exflow(network, vertex) > 0;
}

