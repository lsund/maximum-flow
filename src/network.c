
#include "network.h"

Graph network_residual(const NetworkPointer network)
{
    Graph ret;
/*     ret.vertexset = network.graph->vertexset; */
/*     ret.edgeset = edgeset_init(network.graph->edgeset.set->capacity); */
/*     size_t i; */
/*     for (i = 0; i < network.graph->edgeset.set->length; i++) { */
/*         NetworkEdgePointer edge = edgeset_get(network.graph->edgeset, i); */
/*         if (networkedge_residual_capacity( */
/*     } */
    return ret;
}

unsigned int network_vertex_exflow(const NetworkPointer network, const VertexPointer vertex)
{
    unsigned int inflow, outflow;
    inflow = 0;
    outflow = 0;
    size_t i;
    for (i = 0; i < network->graph->edgeset.set->length; i++) {
        EdgePointer edge = edgeset_get(network->graph->edgeset, i);
        if (vertex_equals(edge->first, vertex)) {
            outflow += network_edge_flow(network, edge);
        } else if (vertex_equals(edge->second, vertex)) {
            inflow += network_edge_flow(network, edge);
        }
    }
    return inflow - outflow;
}

Label network_vertex_distance_label(const NetworkPointer network, const VertexPointer vertex)
{
    return 0;
}

unsigned int network_edge_flow(const NetworkPointer network, const EdgePointer edge)
{
    return 0;
}

unsigned int network_get_edge_capacity(const NetworkPointer network, const EdgePointer edge)
{
    return 0;
}

void network_set_edge_capacity(
        const NetworkPointer network, 
        const EdgePointer edge, 
        unsigned int capacity
    )
{
    return;
}

bool network_edge_is_reverse(const NetworkPointer network, const EdgePointer edge)
{
    return 0;
}


