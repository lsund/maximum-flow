
#include "push_relabel_network.h"

Result networkvertex_active(const NetworkPointer network, VertexPointer vertex)
{
    VertexPointer first_active = vertexcollection_get_first(network->active_vertices);
    if (first_active) {
        *vertex = *first_active;
        return SUCCESS;
    } else {
        return FAIL;
    }
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

Label networkvertex_distance_label(const NetworkPointer network, const Vertex vertex)
{
    unsigned int index = vertexcollection_index_of(network->graph.vertices, vertex);
    return *(network->distance_labels + index);
}

void networkvertex_set_distance_label(
        const NetworkPointer network, 
        const Vertex vertex, 
        const unsigned int label
    )
{
    if (!network) {
        runtime_error("networkvertex_set_distance_label: null argument");
    }
    unsigned int index = vertexcollection_index_of(network->graph.vertices, vertex);
    *(network->distance_labels + index) = label; 
}

EdgePointer networkedge_admissable(
        const NetworkPointer network, 
        const Vertex active
    )
{
    size_t i;
    EdgeCollection edges = *(network->residual_edges + active.label);
    unsigned int label_first, label_second;
    for (i = 0; i < edgecollection_length(edges); i++) {
        EdgePointer edge = edgecollection_get(edges, i);
        label_first = networkvertex_distance_label(network, edge->first);
        label_second = networkvertex_distance_label(network, edge->second);
        if (label_first == label_second + 1) {
            return edge;
        }
    }
    return NULL;
}

