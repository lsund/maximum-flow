
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
    ret->source = get_vertex(graph->vertexset, source_label);
    ret->sink   = get_vertex(graph->vertexset, sink_label);
    if (!ret->source || !ret->sink) {
        return FAIL;
    }
    return SUCCESS;
}
