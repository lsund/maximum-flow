
#include "network.h"

static EdgeCollection vertexcollection_to_edgecollection(
        const NetworkPointer network,
        const VertexCollection vertices
    )
{
    size_t i;
    EdgeCollection epath = edgecollection_init_min();
    for (i = 0; i < vertexcollection_length(vertices) - 1; i++) {
        VertexPointer first = vertexcollection_get(vertices, i);
        VertexPointer second = vertexcollection_get(vertices, i + 1);
        Edge edge = edge_make_vertices(*first, *second);
        EdgePointer edge_p;
        if (vertex_equals(*network->root, edge.second)) {
            break;
        }
        edge_p = edgecollection_get_reference(network->graph.edges, edge);
        if (!edge_p) {
            edge_p = edgecollection_get_reference(network->reverse_edges, edge);
        }
        if (!edge_p) {
            runtime_error("vertexcollection_to_edgecollection: got null reference");
        }
        edgecollection_push(epath, edge_p);
    }
    return epath;
}

void network_init(
        NetworkPointer network,
        NetworkType type,
        const unsigned int n_vertices
    )
{
    network->type                      = type;
    network->graph                     = graph_init();
    network->reverse_edges             = edgecollection_init_min();
    network->source                    = NULL;
    network->sink                      = NULL;

    if (type == PR) {
        network->active_vertices       = vertexcollection_init(COLL_MIN_SIZE);
    } else {
        network->excesses              = calloc(n_vertices, sizeof(int));
        network->root                  = vertex_p_make(n_vertices + 1);
        network->strong_vertices       = vertexcollection_init_min();
        network->weak_vertices         = vertexcollection_init_min();
        network->source_neighbours     = vertexcollection_init_min();
        network->sink_neighbours       = vertexcollection_init_min();
        network->source_edges          = edgecollection_init_min();
        network->sink_edges            = edgecollection_init_min();
    }
}

EdgeCollection network_edgepath_to_treeroot(const NetworkPointer network, const VertexPointer vertex)
{
    VertexCollection path = tree_path_to_root(vertex);
    EdgeCollection ret = vertexcollection_to_edgecollection(network, path);
    vertexcollection_destroy(path);
    return ret;
}

unsigned int network_flow(const NetworkPointer network)
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
        vertexcollection_destroy(network->active_vertices);
    } else {
        free(network->excesses);
        vertexcollection_destroy(network->strong_vertices);
        vertexcollection_destroy(network->weak_vertices);
        vertexcollection_destroy(network->source_neighbours);
        vertexcollection_destroy(network->sink_neighbours);
        edgecollection_destroy(network->source_edges);
        edgecollection_destroy(network->sink_edges);
        free(network->root);
    }
    size_t i;
    for (i = 0; i < edgecollection_length(network->graph.edges); i++) {
        EdgePointer edge = edgecollection_get(network->graph.edges, i);
        EdgePointer rev_edge = edgecollection_get(network->reverse_edges, i);
        free(edge);
        free(rev_edge);
    }
    for (i = 0; i < vertexcollection_length(network->graph.vertices); i++) {
        VertexPointer vertex = vertexcollection_get(network->graph.vertices, i);
        free(vertex);
    }
    edgecollection_destroy(network->reverse_edges);
    graph_destroy(network->graph);
    free(network);
}

EdgePointer networkedge_get_source_edge(
        const NetworkPointer network,
        const VertexPointer vertex
    )
{
    EdgeCollection edges = network->source_edges;
    size_t i;
    for (i = 0; i < edgecollection_length(edges); i++) {
        EdgePointer edge = edgecollection_get(edges, i);
        if (vertex_equals(edge->second, *vertex)) {
            return edge;
        }
    }
    runtime_error("networkedge_get_source_edge: vertex not adjacent to source");
    return NULL;
}

EdgePointer networkedge_get_sink_edge(
        const NetworkPointer network,
        const VertexPointer vertex
    )
{
    EdgeCollection edges = network->sink_edges;
    size_t i;
    for (i = 0; i < edgecollection_length(edges); i++) {
        EdgePointer edge = edgecollection_get(edges, i);
        if (vertex_equals(edge->first, *vertex)) {
            return edge;
        }
    }
    runtime_error("networkedge_get_sink_edge: vertex not adjacent to sink");
    return NULL;
}


