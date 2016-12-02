
#include "network.h"

Result make_network(
        const GraphPointer graph, 
        const Label source_label, 
        const Label sink_label,
        NetworkPointer ret
    )
{
    ret->graph  = graph;
    ret->rev_graph = init_graph();
    make_reversed_graph(*graph, ret->rev_graph);
    ret->source = get_vertex_with_label(graph->vertexset, source_label);
    ret->sink   = get_vertex_with_label(graph->vertexset, sink_label);
    if (!is_vertex_initialized(ret->source) || !is_vertex_initialized(ret->sink)) {
        return FAIL;
    }
    return SUCCESS;
}
