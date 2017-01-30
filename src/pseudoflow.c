
#include "pseudoflow.h"

typedef enum vertextype { STRONG, WEAK } VertexType; 

static void split(
        const NetworkPointer network,
        const EdgePointer edge
    ) 
{
    VertexPointer vertex = vertexcollection_get_reference(network->graph.vertices, edge->first);
    tree_merge(network->root, vertex);
}

static void initialize_vertex(
        const NetworkPointer network, 
        const EdgePointer edge,
        const VertexType type
    )
{
    unsigned int capacity;
    VertexPointer vertex;
    VertexCollection vertices, strongs, weaks;
    vertices = network->graph.vertices;
    if (type == STRONG) {
        strongs = network->strong_vertices;
        capacity = networkedge_capacity(network, edge);
        networkedge_augment(network, edge, capacity);
        vertex = vertexcollection_get_reference(vertices, edge->second);
        vertexcollection_push(strongs, vertex);
    } else {
        weaks = network->weak_vertices;
        capacity = networkedge_capacity(network, edge);
        networkedge_augment(network, edge, capacity);
        vertex = vertexcollection_get_reference(vertices, edge->first);
        vertexcollection_push(weaks, vertex);
    }
    tree_merge(network->root, vertex);
}

void pseudoflow_initialize(const NetworkPointer network)
{
    EdgePointer edge;
    VertexPointer vertex;
    VertexCollection strongs, weaks;
    size_t i;
    strongs = network->strong_vertices;
    weaks = network->weak_vertices;
    for (i = 0; i < edgecollection_length(network->graph.edges); i++) {
        edge = edgecollection_get(network->graph.edges, i);
        if (vertex_equals(edge->first, *network->source)) {
            initialize_vertex(network, edge, STRONG);
        } else if (vertex_equals(edge->second, *network->sink)) {
            initialize_vertex(network, edge, WEAK);
        }
    }
    for (i = 0; i < vertexcollection_length(network->graph.vertices); i++) {
        vertex = vertexcollection_get(network->graph.vertices, i);
        Label label = vertex->label;
        if (
                !vertexcollection_contains_label(strongs, label) &&
                !vertexcollection_contains_label(weaks, label) &&
                !vertex_equals(*vertex, *network->source) &&
                !vertex_equals(*vertex, *network->sink)
           ) {
            vertexcollection_push(weaks, vertex);
            tree_merge(network->root, vertex);
        }
    }
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
        unsigned int delta = networkvertex_excess(network, *strong_branch);
        
        merge(strong_branch, strong_vertex, weak_vertex);

        EdgeCollection path;
        path = network_edgepath_to_treeroot(network, strong_branch);

        size_t i;
        for (i = 0; i < edgecollection_length(path); i++) {
            EdgePointer edge = edgecollection_get(path, i);
            unsigned int residual_capacity = networkedge_residual_capacity(network, edge);
            if (residual_capacity >= delta) {
                networkedge_augment(network, edge, delta);
            } else {
                split(network, edge);
                delta = residual_capacity;
                if (networkedge_is_reverse(network, edge)) {
                    Edge reverse_edge = edge_swapped(*edge);
                    unsigned int index = edgecollection_index_of(network->graph.edges, reverse_edge);
                    EdgePointer reverse_edge_p = edgecollection_get_reference(network->graph.edges, reverse_edge);
                    int flow = *(network->flows + index);
                    networkedge_set_flow(network, reverse_edge_p, flow - residual_capacity);
                } else {
                    unsigned int capacity = networkedge_capacity(network, edge);
                    networkedge_set_flow(network, edge, capacity);
                }
            }
        }
        edgecollection_destroy(path);
        merger = merger_edge(network);
    }
    return;
}
