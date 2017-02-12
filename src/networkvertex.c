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
        runtime_error("not supported for pr");
        return 0;
    }
}

int networkvertex_is_strong(
        const NetworkPointer network,
        const VertexPointer vertex_p
    )
{
    if (network->type == PR) {
        return vertex_exflow(vertex_p) > 0;
    } else {
        return vertex_excess(vertex_p) > 0;
    }
}

