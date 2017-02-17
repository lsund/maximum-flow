
#include "push_relabel_helpers.h"

Label find_min(const NetworkPointer network, const Vertex vertex)
{
    Label min = INT_MAX;
    size_t i;
    EdgeCollection edges = network_get_out_edges(network, vertex);
    for (i = 0; i < edgecollection_length(edges); i++) {
        EdgePointer edge = edgecollection_get(edges, i);
        Label label      = vertex_distance_label(edge->second_ref) + 1;
        Label rev_label  = vertex_distance_label(edge->reverse->second_ref) + 1;
        if (vertex_equals(edge->first, vertex) && label < min && edge_is_residual(edge)) {
            min = label;
        } else if (vertex_equals(edge->first, vertex) && rev_label < min && edge_is_residual(edge->reverse)) {
            min = rev_label;
        }
    }
    if (i == 0) {
        runtime_error("find_min: vertex should have at least one outgoing edge");
    }
    return min;
}

void push(const EdgePointer edge, const VertexPointer vertex)
{
    unsigned int exflow = vertex_exflow(vertex);
    unsigned int capacity = edge_residual_capacity(edge);
    unsigned int gamma = smaller(exflow, capacity);
    edge_augment(edge, gamma);
}

void relabel(const NetworkPointer network, const VertexPointer vertex)
{
    Label min_label = find_min(network, *vertex);
    vertex_set_distance_label(vertex, min_label);
}

static bool is_active(const NetworkPointer network, const VertexPointer vertex)
{
    bool is_graph_vertex = !vertex_equals(*vertex, *network->source) && !vertex_equals(*vertex, *network->sink);
    return (vertex_exflow(vertex) > 0 && is_graph_vertex);
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

void discharge(const NetworkPointer network, const VertexPointer vertex)
{
    do {
        EdgeCollection out_edges = network_get_out_edges(network, *vertex);
        // let e be the edge to which curr points
        EdgePointer edge = edgecollection_get(out_edges, *out_edges.curr);
        // if e is admissable then 
        if (edge_is_admissable(edge)) {
        //      push(e) 
            push(edge, vertex);
        }
        // else
        else {
        //      if e is the last list of out_edges(v) then
            if (*out_edges.curr == edgecollection_length(out_edges) - 1) {
        //          relabel(v)
                relabel(network, vertex);
        //          let curr(v) point to the first element of out_edges(v)
                *out_edges.curr = 0;
                return;
            } 
        //      else
            else {
        //          let curr(v) point to the next edge in out_edges(v)
                *out_edges.curr = *out_edges.curr + 1;
            }
        }
    // if exflow(v) > 0 go to start
    } while (vertex_exflow(vertex) > 0);
}

VertexPointer networkvertex_active(const NetworkPointer network)
{
    size_t i;
    for (i = 0; i < vertexcollection_length(network->graph.vertices); i++) {
        VertexPointer vertex = vertexcollection_get(network->graph.vertices, i);
        if (is_active(network, vertex)) {
            return vertex;
        }
    }
    return NULL;
}

EdgePointer admissable_edge(
        const NetworkPointer network, 
        const Vertex active
    )
{
    size_t i;
    EdgeCollection edges = network_get_out_edges(network, active);
    for (i = 0; i < edgecollection_length(edges); i++) {
        EdgePointer edge = edgecollection_get(edges, i);
        if (vertex_equals(edge->first, active)) {
            if (edge_is_admissable(edge)) {
                return edge;
            }
        } else if (vertex_equals(edge->second, active)) {
            if (edge_is_admissable(edge->reverse)) {
                return edge->reverse;
            }
        }
    }
    return NULL;
}

