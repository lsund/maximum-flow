
#include "network.h"

bool network_edge_is_residual(const NetworkPointer network, const EdgePointer edge)
{
    // TODO
    return true;
}

unsigned int network_vertex_exflow(const NetworkPointer network, const VertexPointer vertex)
{
    unsigned int inflow, outflow;
    inflow = 0;
    outflow = 0;
    size_t i;
    for (i = 0; i < edgeset_length(network->graph->edgeset); i++) {
        EdgePointer edge = edgeset_get(network->graph->edgeset, i);
        if (vertex_equals(edge->first, vertex)) {
            outflow += network_edge_flow(network, edge);
        } else if (vertex_equals(edge->second, vertex)) {
            inflow += network_edge_flow(network, edge);
        }
    }
    return inflow - outflow;
}

bool network_vertex_is_active(const NetworkPointer network, const VertexPointer vertex)
{
    return network_vertex_exflow(network, vertex) > 0;
}

bool network_edge_is_admissable(const NetworkPointer network, const EdgePointer edge)
{
    unsigned int label_first, label_second;
    label_first = network_vertex_distance_label(network, edge->first);
    label_second = network_vertex_distance_label(network, edge->second);
    bool cond_a = label_first == label_second + 1;
    bool cond_b = network_edge_is_residual(network, edge);
    return cond_a && cond_b;
}

Label network_vertex_distance_label(const NetworkPointer network, const VertexPointer vertex)
{
    // TODO
    return 0;
}

unsigned int network_edge_flow(const NetworkPointer network, const EdgePointer edge)
{
    // TODO
    return 0;
}

unsigned int network_edge_capacity(const NetworkPointer network, const EdgePointer edge)
{
    // TODO
    return 0;
}

void network_set_edge_capacity(
        const NetworkPointer network, 
        const EdgePointer edge, 
        unsigned int capacity
    )
{
    // TODO
    return;
}

bool network_edge_is_reverse(const NetworkPointer network, const EdgePointer edge)
{
    // TODO
    return 0;
}


