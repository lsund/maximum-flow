
#include "networkedge.h"

NetworkEdge networkedge_make(
        const EdgePointer content, 
        const float capacity, 
        const float flow, 
        const bool is_reverse
    )
{
    NetworkEdge ret;
    ret.content       = content;
    ret.capacity   = capacity;
    ret.flow       = flow;
    ret.is_reverse = is_reverse;
    return ret;
}

NetworkEdgePointer networkedge_p_make(
        const EdgePointer content, 
        const float capacity, 
        const float flow, 
        const bool is_reverse
    )
{
    NetworkEdgePointer ret = malloc(sizeof(NetworkEdge));
    *ret = networkedge_make(content, capacity, flow, is_reverse);
    return ret;
}

NetworkEdgePointer networkedge_p_make_label(
        const Label first_label,
        const Label second_label
    )
{
    return networkedge_p_make(edge_p_make_label(first_label, second_label), 0, 0, false);
}

float networkedge_residual_capacity(const NetworkEdge networkedge)
{
    return networkedge.is_reverse ? networkedge.flow : networkedge.capacity - networkedge.flow;
}

