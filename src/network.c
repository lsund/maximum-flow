
#include "network.h"

NetworkPointer network_make(
        NetworkType type,
        const unsigned int nv
    )
{
    NetworkPointer ret = malloc(sizeof(Network));
    ret->type                  = type;
    ret->graph                 = graph_init();
    ret->source                = NULL;
    ret->sink                  = NULL;

    ret->neighbors             = malloc(sizeof(EdgeCollection) * (nv + 2));
    size_t i;
    for (i = 0; i < nv + 2; i++) {
        *(ret->neighbors + i) = edgecollection_init_min();
    }
    if (type == PR) {
    } else {
        ret->root              = vertex_make(nv + 1);
    }
    return ret;
}

EdgePointer network_get_out_edge(
        const NetworkPointer network,
        const Vertex first, 
        const Vertex second
    )
{
    EdgeCollection out_edges = network_get_out_edges(network, first);
    size_t i;
    for (i = 0; i < edgecollection_length(out_edges); i++) {
        EdgePointer edge = edgecollection_get(out_edges, i);
        if (vertex_equals(edge->second, second)) {
            return edge;
        }
    }
    return NULL;
}

EdgeCollection network_edgepath_to_treeroot(const NetworkPointer network, const VertexPointer vertex)
{
    EdgeCollection ret = edgecollection_init_min();
    if (!vertex->parent) {
        return ret;
    }
    VertexPointer previous = vertex;
    VertexPointer current = vertex->parent;
    EdgePointer edge = network_get_out_edge(network, *previous, *current);
    edgecollection_push(ret, edge);
    while (current->parent) {
        if (current == current->parent->parent) {
            runtime_error("tree_path_to_root: both are eachothers parents");
        }
        previous = current;
        current = current->parent;
        if (current == network->root) {
            break;
        }
        EdgePointer edge = network_get_out_edge(network, *previous, *current);
        if (!edge) {
            runtime_error("tree_path_to_root: got null pointer to edge");
        } else {
            edgecollection_push(ret, edge);
        }
    }
    return ret;
}

static unsigned int networkvertex_inflow(
        const NetworkPointer network,
        const Vertex vertex)
{
    if (network->type == PS) {
        EdgeCollection edges = network->graph.edges;
        unsigned int sum;
        size_t i;
        for (i = 0, sum = 0; i < edgecollection_length(edges); i++) {
            EdgePointer edge = edgecollection_get(edges, i);
            if (vertex_equals(edge->second, vertex)) {
                sum += edge_flow(edge);
            }
        }
        return sum;
    } else {
        runtime_error("not supported for pr");
        return 0;
    }
}

void network_add_out_edge(
        const NetworkPointer network,
        const Vertex vertex,
        const EdgePointer edge
    )
{
    edgecollection_push(*(network->neighbors + vertex.label), edge);
}

EdgeCollection network_get_out_edges(
        const NetworkPointer network,
        const Vertex vertex
    )
{
    return *(network->neighbors + vertex.label);
}


unsigned int recover_flow(const NetworkPointer network)
{
    if (network->type == PS) {
        EdgeCollection edges = network->graph.edges;
        int sum;
        size_t i;
        for (i = 0, sum = 0; i < edgecollection_length(edges); i++) {
            EdgePointer edge = edgecollection_get(edges, i);
            if (vertex_equals(edge->second, *network->sink)) {
                sum += networkvertex_inflow(network, edge->first);
            }
        }
        return sum;
    } else {
        return vertex_exflow(network->sink);
    }
}

void network_destroy(NetworkPointer network)
{
    if (network->type == PR) {
    } else {
        free(network->root);
    }
    size_t i;
    for (i = 0; i < edgecollection_length(network->graph.edges); i++) {
        EdgePointer edge = edgecollection_get(network->graph.edges, i);
        free(edge->reverse);
        free(edge);
    }
    for (i = 0; i < vertexcollection_length(network->graph.vertices); i++) {
        VertexPointer vertex = vertexcollection_get(network->graph.vertices, i);
        free(vertex);
    }
    for (i = 0; i < vertexcollection_length(network->graph.vertices) + 2; i++) {
        edgecollection_destroy(*(network->neighbors + i));
    }
    free(network->neighbors);
    graph_destroy(network->graph);
    free(network);
}

