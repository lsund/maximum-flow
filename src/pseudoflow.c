
#include "pseudoflow.h"

typedef enum vertextype { STRONG, WEAK } VertexType; 

static void initialize_vertex(
        NetworkPointer network, 
        EdgePointer edge, 
        size_t i,
        VertexType type
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

void pseudoflow_initialize(NetworkPointer network)
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
            initialize_vertex(network, edge, i, STRONG);
        } else if (vertex_equals(edge->second, *network->sink)) {
            initialize_vertex(network, edge, i, WEAK);
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
        edge_print(*merger_edge(network));
        strong_vertex = vertexcollection_get_reference(
                network->strong_vertices,
                merger->first
        );
        weak_vertex = vertexcollection_get_reference(
                network->strong_vertices,
                merger->second
        );
        VertexPointer strong_branch = tree_find_branch(strong_vertex);
        // Disconnect the strong branch
        strong_branch->parent = NULL;
        // make s the root of the tree
        tree_invert(strong_vertex);
        // Connect it to the weak vertex
        tree_merge(weak_vertex, strong_vertex);
        
        unsigned int delta = *(network->excesses + strong_vertex->label);
        EdgeCollection spath = tree_edgepath_from_branch(strong_vertex, network->graph.edges);
        EdgeCollection wpath = tree_edgepath_to_branch(weak_vertex, network->graph.edges);
        edgecollection_link(spath, wpath);
        /* edgecollection_push(path, root); */

        merger = merger_edge(network);
    }
    // blah
    return;
}
