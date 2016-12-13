
#include "network.h"

// Denote the value of this function dl(v) for any vertex
// dl(t) = 0
// dl(s) = n
// dl(v) <= dl(w) + 1 for all (v, w) in E(G_f).
static unsigned int distance_labeling(const Graph graph, const Vertex vertex)
{
    runtime_error("tbi");
    return 0;
}

Network network_make(
        const GraphPointer graph, 
        const Label source_label, 
        const Label sink_label
    )
{
    Network ret;
    ret.graph  = graph;
    // TODO
    /* ret.rev_graph = graph_init(); */
    graph_make_reversed(*graph, ret.rev_graph);
    ret.source = vertexset_get(graph->vertexset, source_label);
    ret.sink   = vertexset_get(graph->vertexset, sink_label);
    if (!ret.source || !ret.sink) {
        runtime_error("network make: No such source or sink");
    }
    return ret;
}

Label network_get_vertex_distance_label(const NetworkPointer network, const VertexPointer vertex)
{
    return 0;
}

unsigned int network_get_edge_flow(const NetworkPointer network, const EdgePointer edge)
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

