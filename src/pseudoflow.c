
#include "pseudoflow.h"

typedef enum vertextype { STRONG, WEAK } VertexType; 

static void split(
        const NetworkPointer network,
        const EdgePointer edge
    ) 
{
    // take the first vertex of edge.
    // set its parent to root.
    VertexPointer vertex = vertexcollection_get_reference(network->graph.vertices, edge->first);
    tree_merge(network->root, vertex);
    // remove (a, b) from the residual edges and add (b, a)
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
        VertexPointer weak_branch = tree_find_branch(weak_vertex);
        unsigned int delta = networkvertex_excess(network, *strong_branch);
        /* printf("delta: %d\n", delta); */
        // Disconnect the strong branch
        strong_branch->parent = NULL;
        // make s the root of the tree
        tree_invert(strong_vertex);
        // Connect it to the weak vertex
        tree_merge(weak_vertex, strong_vertex);

        EdgeCollection path;
        path = network_edgepath_to_treeroot(network, strong_branch);
        /* edge_print(*merger); */
        /* edgecollection_print(path); */
        /* printf("strong branch %d weak branch %d\n", strong_branch->label, weak_branch->label); */
        /* printf("strong vertex %d weak vertex %d\n", strong_vertex->label, weak_vertex->label); */
        /* printf("%d <- %d, weak <- strong\n", weak_vertex->label, strong_vertex->label); */
        /* printf("strong excess: %d weak excess: %d\n", networkvertex_excess(network, *strong_branch), networkvertex_excess(network, *weak_branch)); */
        /* printf("strong parent %d\n", strong_vertex->parent->label); */
        size_t i;
        for (i = 0; i < edgecollection_length(path); i++) {
            EdgePointer edge = edgecollection_get(path, i);
            unsigned int residual_capacity = networkedge_residual_capacity(network, edge);
            /* if (residual_capacity == 0) { */
            /*     size_t i; */
            /*     for (i = 0; i < edgecollection_length(network->graph.edges); i++) { */
            /*         EdgePointer edge = edgecollection_get(network->graph.edges, i); */
            /*         printf("%d %d, %d\n", edge->first.label, edge->second.label, networkedge_flow(network, edge)); */
            /*     } */
            /* } */
            // capacity - flow for forward arcs
            if (residual_capacity >= delta) {
                networkedge_augment(network, edge, delta);
            } else {
                /* printf("splitting at\n"); */
                /* edge_print(*edge); */
                split(network, edge);
                // reset delta
                // delta gets the value of the residual capacity
                delta = residual_capacity;
                /* printf("delta: %d, res cap: %d\n", delta, residual_capacity); */
                if (networkedge_is_reverse(network, edge)) {
                    Edge reverse_edge = edge_swapped(*edge);
                    unsigned int index = edgecollection_index_of(network->graph.edges, reverse_edge);
                    EdgePointer reverse_edge_p = edgecollection_get_reference(network->graph.edges, reverse_edge);
                    int flow = *(network->flows + index);
                    networkedge_set_flow(network, reverse_edge_p, flow - residual_capacity);
                } else {
                    // flow of this edge gets the value of capacity
                    // TODO should not be possible that edge is residual
                    unsigned int capacity = networkedge_capacity(network, edge);
                    /* printf("filled up capacity: %d\n", capacity); */
                    networkedge_set_flow(network, edge, capacity);
                }
            }
            /* printf("--\n"); */
        }
        /* printf("------------\n"); */
        edgecollection_destroy(path);
        merger = merger_edge(network);
    }
    return;
}
                /* if (networkvertex_excess(network, edge->first) <= 0 && !vertexcollection_contains_label(network->weak_vertices, edge->first.label)) { */
                /*     VertexPointer vertex = vertexcollection_get_reference(network->strong_vertices, edge->first); */
                /*     vertexcollection_remove(&network->strong_vertices, *vertex); */
                /*     vertexcollection_push(network->weak_vertices, vertex); */
                /*     printf("1 moved vertex %d to weak_vertexes\n", vertex->label); */
                /* } */
                /* if (networkvertex_excess(network, edge->first) > 0 && !vertexcollection_contains_label(network->strong_vertices, edge->first.label)) { */
                /*     VertexPointer vertex = vertexcollection_get_reference(network->weak_vertices, edge->first); */
                /*     vertexcollection_remove(&network->weak_vertices, *vertex); */
                /*     vertexcollection_push(network->strong_vertices, vertex); */
                /*     printf("1 moved vertex %d to strong vertexes\n", vertex->label); */
                /* } */
                /* if (networkvertex_excess(network, edge->second) > 0 && !vertexcollection_contains_label(network->strong_vertices, edge->second.label)) { */
                /*     VertexPointer vertex = vertexcollection_get_reference(network->weak_vertices, edge->second); */
                /*     vertexcollection_remove(&network->weak_vertices, *vertex); */
                /*     vertexcollection_push(network->strong_vertices, vertex); */
                /*     printf("2 moved vertex %d to strong vertexes\n", vertex->label); */
                /* } */
                /* if (networkvertex_excess(network, edge->second) <= 0 && !vertexcollection_contains_label(network->weak_vertices, edge->second.label)) { */
                /*     VertexPointer vertex = vertexcollection_get_reference(network->strong_vertices, edge->second); */
                /*     vertexcollection_remove(&network->strong_vertices, *vertex); */
                /*     vertexcollection_push(network->weak_vertices, vertex); */
                /* } */
                /* if (networkvertex_excess(network, edge->first) <= 0 && !vertexcollection_contains_label(network->weak_vertices, edge->first.label)) { */
                /*     VertexPointer vertex = vertexcollection_get_reference(network->strong_vertices, edge->first); */
                /*     vertexcollection_remove(&network->strong_vertices, *vertex); */
                /*     vertexcollection_push(network->weak_vertices, vertex); */
                /* } */
                /* if (networkvertex_excess(network, edge->first) > 0 && !vertexcollection_contains_label(network->strong_vertices, edge->first.label)) { */
                /*     VertexPointer vertex = vertexcollection_get_reference(network->weak_vertices, edge->first); */
                /*     vertexcollection_remove(&network->weak_vertices, *vertex); */
                /*     vertexcollection_push(network->strong_vertices, vertex); */
                /* } */
                /* if (networkvertex_excess(network, edge->second) > 0 && !vertexcollection_contains_label(network->strong_vertices, edge->second.label)) { */
                /*     VertexPointer vertex = vertexcollection_get_reference(network->weak_vertices, edge->second); */
                /*     vertexcollection_remove(&network->weak_vertices, *vertex); */
                /*     vertexcollection_push(network->strong_vertices, vertex); */
                /* } */
                /* if (networkvertex_excess(network, edge->second) <= 0 && !vertexcollection_contains_label(network->weak_vertices, edge->second.label)) { */
                /*     VertexPointer vertex = vertexcollection_get_reference(network->strong_vertices, edge->second); */
                /*     vertexcollection_remove(&network->strong_vertices, *vertex); */
                /*     vertexcollection_push(network->weak_vertices, vertex); */
                /* } */
