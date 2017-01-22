
#include "pseudoflow.h"

typedef enum vertextype { STRONG, WEAK } VertexType; 

static void split(
        const NetworkPointer network,
        const EdgePointer edge,
        const unsigned int diff
    ) 
{
    // take the first vertex of edge.
    // set its parent to root.
    VertexPointer vertex = vertexcollection_get_reference(network->graph.vertices, edge->first);
    vertex->parent = network->source;
    // excess(a) = f_ar = diff
    *(network->excesses + edge->first.label) = diff;
    // remove (a, b) from the residual edges and add (b, a)
    // maybe this happens automatically?
}

static void initialize_vertex(
        const NetworkPointer network, 
        const EdgePointer edge, 
        const size_t i,
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
        *(network->excesses + i) = capacity;
        vertex = vertexcollection_get_reference(vertices, edge->second);
        vertexcollection_push(strongs, vertex);
    } else {
        weaks = network->weak_vertices;
        capacity = networkedge_capacity(network, edge);
        networkedge_augment(network, edge, capacity);
        *(network->excesses + i) = -capacity;
        vertex = vertexcollection_get_reference(vertices, edge->first);
        vertexcollection_push(weaks, vertex);
    }
    tree_merge(network->sink, vertex);
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
            initialize_vertex(network, edge, edge->second.label, STRONG);
        } else if (vertex_equals(edge->second, *network->sink)) {
            initialize_vertex(network, edge, edge->first.label, WEAK);
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
            *(network->excesses + i) = 0;
            vertexcollection_push(weaks, vertex);
            tree_merge(network->sink, vertex);
        }
    }
}

void pseudoflow(NetworkPointer network)
{
    pseudoflow_initialize(network);
    EdgePointer merger = merger_edge(network);
    VertexPointer strong_vertex, weak_vertex;
    while (merger) {
        strong_vertex = vertexcollection_get_reference(
                network->strong_vertices,
                merger->first
        );
        weak_vertex = vertexcollection_get_reference(
                network->weak_vertices,
                merger->second
        );
        VertexPointer strong_branch = tree_find_branch(strong_vertex);
        // Disconnect the strong branch
        strong_branch->parent = NULL;
        // make s the root of the tree
        tree_invert(strong_vertex);
        // Connect it to the weak vertex
        tree_merge(weak_vertex, strong_vertex);

        EdgeCollection path;
        path = tree_edgepath_to_root(strong_vertex, network->graph.edges);

        unsigned int delta = *(network->excesses + strong_vertex->label);
        size_t i;
        for (i = 0; i < edgecollection_length(path); i++) {
            EdgePointer edge = edgecollection_get(path, i);
            unsigned int residual_capacity = networkedge_residual_capacity(network, edge);
            // capacity - flow for forward arcs
            if (residual_capacity >= delta) {
                networkedge_augment(network, edge, delta);
            } else {
                split(network, edge, delta - residual_capacity);
                // reset delta
                // delta gets the value of the residual capacity
                delta = residual_capacity;
                // flow of this edge gets the value of capacity
                networkedge_set_flow(network, edge, networkedge_capacity(network, edge));
            }
        }
        merger = merger_edge(network);
    }
    // blah
    return;
}
