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

