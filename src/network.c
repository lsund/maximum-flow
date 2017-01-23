
#include "network.h"

static EdgeCollection vertexcollection_to_edgecollection(
        const NetworkPointer network,
        const VertexCollection vertices
    )
{
    size_t i;
    EdgeCollection epath = edgecollection_init(ARRAY_MIN_SIZE);
    for (i = 0; i < vertexcollection_length(vertices) - 1; i++) {
        VertexPointer first = vertexcollection_get(vertices, i);
        VertexPointer second = vertexcollection_get(vertices, i + 1);
        if (vertex_equals(*second, *network->source)) {
            second = network->sink;
        }
        Edge edge = edge_make_vertices(*first, *second);
        EdgePointer edge_p;
        edge_p = edgecollection_get_reference(network->graph.edges, edge);
        if (!edge_p) {
            runtime_error("vertexcollection_to_edgecollection: got null reference");
        }
        edgecollection_push(epath, edge_p);
    }
    return epath;
    /* if (reverse) { */
    /*     EdgeCollection epath_rev = edgecollection_init(ARRAY_MIN_SIZE); */
    /*     for (i = edgecollection_length(epath); i > 0; i--) { */
    /*         EdgePointer edge = edgecollection_get(epath, i - 1); */
    /*         edgecollection_push(epath_rev, edge); */
    /*     } */
    /*     return epath_rev; */
    /* } else { */
    /*     return epath; */
    /* } */
}

NetworkPointer network_init(NetworkType type)
{
    NetworkPointer ret   = malloc(sizeof(Network));
    ret->graph           = graph_init();
    ret->reverse_edges   = edgecollection_empty();
    ret->source          = NULL;
    ret->sink            = NULL;
    ret->capacities      = NULL;
    ret->flows           = NULL;
    ret->inflows         = NULL;
    ret->outflows        = NULL;
    ret->residual_edges  = NULL;
    ret->is_reverse      = map_create();
    ret->type            = type;

    ret->active_vertices = vertexcollection_empty();
    ret->distance_labels = NULL;

    ret->excesses        = NULL;
    ret->strong_vertices = vertexcollection_empty();
    ret->weak_vertices   = vertexcollection_empty();

    return ret;
}

EdgeCollection network_edgepath_to_treeroot(const NetworkPointer network, const VertexPointer vertex)
{
    VertexCollection path = tree_path_to_root(vertex);
    return vertexcollection_to_edgecollection(network, path);
}

unsigned int network_flow(const NetworkPointer network)
{
    if (network->type == PS) {
        EdgeCollection edges = network->graph.edges;
        unsigned int sum;
        size_t i;
        for (i = 0, sum = 0; i < edgecollection_length(edges); i++) {
            EdgePointer edge = edgecollection_get(edges, i);
            if (vertex_equals(edge->second, *network->sink)) {
                sum += networkvertex_inflow(network, edge->first);
            }
        }
        return sum;
    } else {
        return networkvertex_inflow(network, *network->sink);
    }
}

void network_destroy(NetworkPointer network)
{
    if (network->type == PR) {
        free(network->distance_labels);
        vertexcollection_destroy(network->active_vertices);
    }
    free(network->flows);
    free(network->capacities);
    free(network->inflows);
    free(network->outflows);
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
    for (i = 1; i <= vertexcollection_length(network->graph.vertices); i++) {
        edgecollection_destroy(*(network->residual_edges + i));
    }
    free(network->residual_edges);
    edgecollection_destroy(network->reverse_edges);
    graph_destroy(network->graph);
    free(network);
}


/* static EdgeCollection vertexcollection_to_edgecollection( */
/*         const NetworkPointer network, */
/*         const VertexCollection vertices, */ 
/*         bool reverse */
/*     ) */
/* { */
/*     size_t i; */
/*     EdgeCollection epath = edgecollection_init(ARRAY_MIN_SIZE); */
/*     for (i = 0; i < vertexcollection_length(vertices) - 1; i++) { */
/*         VertexPointer first = vertexcollection_get(vertices, i); */
/*         VertexPointer second = vertexcollection_get(vertices, i + 1); */
/*         Edge edge = edge_make_vertices(*first, *second); */
/*         EdgePointer edge_p; */
/*         if (reverse) { */
/*             edge_p = edgecollection_get_reference(network->reverse_edges, edge_swapped(edge)); */
/*         } else { */
/*             edge_p = edgecollection_get_reference(network->graph.edges, edge); */
/*         } */
/*         if (!edge_p) { */
/*             runtime_error("vertexcollection_to_edgecollection: got null reference"); */
/*         } */
/*         edgecollection_push(epath, edge_p); */
/*     } */
/*     if (reverse) { */
/*         EdgeCollection epath_rev = edgecollection_init(ARRAY_MIN_SIZE); */
/*         for (i = edgecollection_length(epath); i > 0; i--) { */
/*             EdgePointer edge = edgecollection_get(epath, i - 1); */
/*             edgecollection_push(epath_rev, edge); */
/*         } */
/*         return epath_rev; */
/*     } else { */
/*         return epath; */
/*     } */
/* } */
