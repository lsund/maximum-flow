
#include "push_relabel_helpers.h"

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


Label find_min(const NetworkPointer network, const Vertex vertex)
{
    Label min = INT_MAX;
    size_t i;
    EdgeCollection edges = network->graph.edges;
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

VertexPointer networkvertex_active(const NetworkPointer network)
{
    size_t i;
    for (i = 0; i < vertexcollection_length(network->graph.vertices); i++) {
        VertexPointer vertex = vertexcollection_get(network->graph.vertices, i);
        bool is_graph_vertex = !vertex_equals(*vertex, *network->source) && !vertex_equals(*vertex, *network->sink);
        if (vertex_exflow(vertex) > 0 && is_graph_vertex) {
            return vertex;
        }
    }
    return NULL;
}

void activate_vertices(
        const NetworkPointer network, 
        const Edge edge, 
        const unsigned int first_exflow_before,
        const unsigned int second_exflow_before,
        const unsigned int first_exflow,
        const unsigned int second_exflow)
{
    if (first_exflow_before > 0 && first_exflow == 0) {
        vertexcollection_remove(&network->active_vertices, edge.first);
    }
    if (second_exflow_before > 0 && second_exflow == 0) {
        vertexcollection_remove(&network->active_vertices, edge.second);
    }
    VertexPointer vertex;
    if (first_exflow_before == 0 && first_exflow > 0) {
        if (edge.first.label != network->source->label) {
            vertex = edge.first_ref;
            vertexcollection_push(network->active_vertices, vertex);
        }
    }
    if (second_exflow_before == 0 && second_exflow > 0) {
        if (edge.second.label != network->sink->label) {
            vertex = edge.second_ref;
            vertexcollection_push(network->active_vertices, vertex);
        }
    }
}

EdgePointer admissable_edge(
        const NetworkPointer network, 
        const Vertex active
    )
{
    size_t i;
    EdgeCollection edges = network->graph.edges;
    unsigned int label_first, label_second;
    for (i = 0; i < edgecollection_length(edges); i++) {
        EdgePointer edge = edgecollection_get(edges, i);
        label_first = vertex_distance_label(edge->first_ref);
        label_second = vertex_distance_label(edge->second_ref);
        if (vertex_equals(edge->first, active)) {
            if (label_first == label_second + 1 && edge_is_residual(edge)) {
                return edge;
            }
        }  else {
            bool is_residual = edge_is_residual(edge->reverse);
            bool from_active = vertex_equals(edge->second, active);
            bool label_successor = label_second == label_first + 1;
            if (is_residual && from_active && label_successor) {
                    return edge->reverse;
            }
        }
    }
    return NULL;
}

