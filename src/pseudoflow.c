
#include "pseudoflow.h"

typedef enum vertextype { STRONG, WEAK } VertexType; 

static void initialize_source_sink_vertex(
        const NetworkPointer network, 
        const VertexPointer vertex,
        const EdgePointer edge,
        const VertexType type
    )
{
    unsigned int capacity;
    capacity = networkedge_capacity(network, edge);
    networkedge_augment(network, edge, capacity);
    if (type == STRONG) {
        *(network->excesses + vertex->label) = capacity;
    } else {
        *(network->excesses + vertex->label) = -capacity;
    }
}

static void initialize_vertex(
        const NetworkPointer network, 
        const VertexPointer vertex,
        const EdgePointer edge,
        const VertexType type
    )
{
    VertexCollection vertices;
    vertices = network->graph.vertices;
    if (edge) {
        initialize_source_sink_vertex(network, vertex, edge, type);
    } else {
        *(network->excesses + vertex->label) = 0;
    }
    tree_merge(network->root, vertex);
}

void pseudoflow_initialize(const NetworkPointer network)
{
    VertexPointer vertex;
    size_t i;
    for (i = 0; i < vertexcollection_length(network->graph.vertices); i++) {
        vertex = vertexcollection_get(network->graph.vertices, i);
        bool is_source = vertex_equals(*vertex, *network->source);
        bool is_sink = vertex_equals(*vertex, *network->sink);
        if (!is_source && !is_sink) {
            bool is_source_vertex = vertexcollection_contains_label(
                                            network->source_neighbours, 
                                            vertex->label
                                        );
            bool is_sink_vertex   = vertexcollection_contains_label(
                                            network->sink_neighbours,
                                            vertex->label
                                        );
            EdgePointer edge;
            if (is_source_vertex) {
                edge = networkedge_get_source_edge(network, vertex);
                initialize_vertex(network, vertex, edge, STRONG);
            } else if (is_sink_vertex) {
                edge = networkedge_get_sink_edge(network, vertex);
                initialize_vertex(network, vertex, edge, WEAK);
            } else {
                initialize_vertex(network, vertex, NULL, WEAK);
            }
        }
    }
}

static void split(
        const NetworkPointer network,
        const EdgePointer edge
    ) 
{
    VertexPointer vertex = vertexcollection_get_reference(network->graph.vertices, edge->first);
    tree_merge(network->root, vertex);
}

static void merge(
        const VertexPointer strong_branch, 
        const VertexPointer strong_vertex, 
        const VertexPointer weak_vertex
    )
{
        strong_branch->parent = NULL;
        tree_invert(strong_vertex);
        tree_merge(weak_vertex, strong_vertex);
}

void pseudoflow(NetworkPointer network)
{
    pseudoflow_initialize(network);
    EdgePointer merger = merger_edge(network);
    VertexPointer strong_vertex, weak_vertex;
    while (merger) {

        strong_vertex = vertexcollection_get_reference(
                network->graph.vertices,
                merger->first
        );
        weak_vertex = vertexcollection_get_reference(
                network->graph.vertices,
                merger->second
        );

        VertexPointer strong_branch = tree_find_branch(strong_vertex);
        unsigned int delta = *(network->excesses + strong_branch->label);
        merge(strong_branch, strong_vertex, weak_vertex);
        EdgeCollection path;
        path = network_edgepath_to_treeroot(network, strong_branch);

        unsigned int residual_capacity;
        size_t i;
        for (i = 0; i < edgecollection_length(path); i++) {
            EdgePointer edge = edgecollection_get(path, i);
            residual_capacity = networkedge_residual_capacity(network, edge);
            int increased_flow;
            if (residual_capacity >= delta) {
                networkedge_augment(network, edge, delta);
                if (networkedge_is_reverse(network, edge)) {
                    increased_flow = delta;
                } else {
                    increased_flow = delta;
                }
                *(network->excesses + edge->first.label) -= increased_flow;
                *(network->excesses + edge->second.label) += increased_flow;
            } else {
                split(network, edge);
                delta = residual_capacity;
                if (networkedge_is_reverse(network, edge)) {
                    Edge reverse_edge = edge_swapped(*edge);
                    unsigned int index = edgecollection_index_of(network->graph.edges, reverse_edge);
                    EdgePointer reverse_edge_p = edgecollection_get_reference(network->graph.edges, reverse_edge);
                    int flow = *(network->flows + index);
                    networkedge_set_flow(network, reverse_edge_p, flow - delta);
                    increased_flow = delta;
                    *(network->excesses + reverse_edge_p->first.label) += increased_flow;
                    *(network->excesses + reverse_edge_p->second.label) -= increased_flow;
                } else {
                    unsigned int index = edgecollection_index_of(network->graph.edges, *edge);
                    int flow = *(network->flows + index);
                    unsigned int capacity = networkedge_capacity(network, edge);
                    increased_flow = capacity - flow;
                    networkedge_set_flow(network, edge, capacity);
                    *(network->excesses + edge->first.label) -= increased_flow;
                    *(network->excesses + edge->second.label) += increased_flow;
                }
            }
        }
        edgecollection_destroy(path);
        merger = merger_edge(network);
    }
    return;
}


