
#include "goldberg_tarjan_helpers.h"

static Label find_min(const NetworkPointer network, const Vertex vertex)
{
    Label min = INT_MAX;
    size_t i;
    EdgeCollection edges = network_get_out_edges(network, vertex);
    for (i = 0; i < edgecollection_length(edges); i++) {
        EdgePointer edge = edgecollection_get(edges, i);
        Label label      = vertex_distance_label(edge->second_ref) + 1;
        Label rev_label  = vertex_distance_label(edge->reverse->second_ref) + 1;
        if (vertex_equals(edge->first, vertex)) {
            if (label < min && edge_is_residual(edge)) {
                min = label;
            }
        } else if (vertex_equals(edge->first, vertex)) {
            if (rev_label < min && edge_is_residual(edge->reverse)) {
                min = rev_label;
            }
        }
    }
    return min;
}

static void push(const EdgePointer edge, const VertexPointer vertex)
{
    unsigned int exflow = vertex_exflow(vertex);
    unsigned int capacity = edge_residual_capacity(edge);
    unsigned int gamma = smaller(exflow, capacity);
    edge_augment(edge, gamma);
}

static void relabel(const NetworkPointer network, const VertexPointer vertex)
{
    Label min_label = find_min(network, *vertex);
    vertex_set_distance_label(vertex, min_label);
}

void discharge(const NetworkPointer network, const VertexPointer vertex)
{
    do {
        EdgeCollection out_edges = network_get_out_edges(network, *vertex);
        EdgePointer edge = edgecollection_current(out_edges);
        if (edge_is_admissable(edge)) {
            push(edge, vertex);
        } else {
            if (edgecollection_current_is_last(out_edges)) {
                relabel(network, vertex);
                *out_edges.curr = 0;
                return;
            } else {
                edgecollection_current_next(out_edges);
            }
        }
    } while (vertex_exflow(vertex) > 0);
}

static bool is_active(const NetworkPointer network, const VertexPointer vertex)
{
    bool pos_exflow = vertex_exflow(vertex) > 0;
    bool not_sink   = !vertex_equals(*vertex, *network->sink);
    bool not_source = !vertex_equals(*vertex, *network->source);
    return pos_exflow && not_sink && not_source;
}

VertexCollection active_vertices(const NetworkPointer network)
{
    size_t i;
    VertexCollection vertices, actives;
    vertices = network->graph.vertices;
    actives = vertexcollection_init_min();
    for (i = 0; i < vertexcollection_length(vertices); i++) {
        VertexPointer vertex = vertexcollection_get(vertices, i);
        if (is_active(network, vertex)) {
            vertexcollection_push(actives, vertex);
        }
    }
    return actives;
}

