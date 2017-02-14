
#include "push_relabel_helpers.h"

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

EdgePointer networkedge_admissable(
        const NetworkPointer network, 
        const Vertex active
    )
{
    size_t i;
    /* EdgeCollection edges = *(network->residual_edges + active.label); */
    EdgeCollection edges = network->graph.edges;
    unsigned int label_first, label_second;
    for (i = 0; i < edgecollection_length(edges); i++) {
        EdgePointer edge = edgecollection_get(edges, i);
        if (vertex_equals(edge->first, active)) {
            label_first = vertex_distance_label(edge->first_ref);
            label_second = vertex_distance_label(edge->second_ref);
            if (label_first == label_second + 1 && edge_is_residual(edge)) {
                return edge;
            }
        }
    }
    for (i = 0; i < edgecollection_length(edges); i++) {
        EdgePointer rev_edge = edgecollection_get(edges, i)->reverse;
        if (vertex_equals(rev_edge->first, active)) {
            label_first = vertex_distance_label(rev_edge->first_ref);
            label_second = vertex_distance_label(rev_edge->second_ref);
            if (label_first == label_second + 1 && edge_is_residual(rev_edge)) {
                return rev_edge;
            }
        }
    }
    return NULL;
}

