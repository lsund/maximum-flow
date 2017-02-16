
#include "network.h"

static EdgeCollection vertexcollection_to_edgecollection(
        const NetworkPointer network,
        const VertexCollection vertices
    )
{
    size_t i, j;
    EdgeCollection epath = edgecollection_init_min();
    for (i = 0; i < vertexcollection_length(vertices) - 1; i++) {
        VertexPointer first = vertexcollection_get(vertices, i);
        VertexPointer second = vertexcollection_get(vertices, i + 1);
        EdgeCollection out_edges = network_get_out_edges(network, *first);
        for (j = 0; j < edgecollection_length(out_edges); j++) {
            EdgePointer edge = edgecollection_get(out_edges, j);
            if (vertex_equals(edge->second, *network->root)) {
                break;
            }
            if (vertex_equals(edge->first, *first)) {
                if (vertex_equals(edge->second, *second)) {
                    edgecollection_push(epath, edge);
                }
            }
            if (vertex_equals(edge->reverse->first, *first)) {
                if (vertex_equals(edge->reverse->second, *second)) {
                    edgecollection_push(epath, edge->reverse);
                }
            }
        }
    }
    return epath;
}

void network_init(
        NetworkPointer network,
        NetworkType type,
        const unsigned int nv
    )
{
    network->type                  = type;
    network->graph                 = graph_init();
    network->source                = NULL;
    network->sink                  = NULL;

    network->neighbors             = malloc(sizeof(EdgeCollection) * (nv + 2));
    size_t i;
    for (i = 0; i < nv + 2; i++) {
        *(network->neighbors + i) = edgecollection_init_min();
    }
    if (type == PR) {
        network->active_vertices   = vertexcollection_init(COLL_MIN_SIZE);
    } else {
        network->excesses          = calloc(nv, sizeof(int));
        network->root              = vertex_p_make(nv + 1);
        network->strong_vertices   = vertexcollection_init_min();
        network->weak_vertices     = vertexcollection_init_min();
        network->source_neighbours = vertexcollection_init_min();
        network->sink_neighbours   = vertexcollection_init_min();
        network->source_edges      = edgecollection_init_min();
        network->sink_edges        = edgecollection_init_min();
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


