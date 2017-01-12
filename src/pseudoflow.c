
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
    tree_insert_under_root(vertex, network->tree);
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
        if (vertex_equals(edge->first, network->source)) {
            initialize_vertex(network, edge, i, STRONG);
        } else if (vertex_equals(edge->second, network->sink)) {
            initialize_vertex(network, edge, i, WEAK);
        }
    }
    for (i = 0; i < vertexcollection_length(network->graph.vertices); i++) {
        vertex = vertexcollection_get(network->graph.vertices, i);
        Label label = vertex->label;
        if (
                !vertexcollection_contains_label(strongs, label) && 
                !vertexcollection_contains_label(weaks, label) &&
                !vertex_equals(*vertex, network->source) &&
                !vertex_equals(*vertex, network->sink)
           ) {
            *(network->excesses + i) = 0;
            vertexcollection_push(weaks, vertex);
            tree_insert_under_root(vertex, network->tree);
        }
    }
}

void pseudoflow(NetworkPointer network)
{
    pseudoflow_initialize(network);
    // blah
    return;
}
