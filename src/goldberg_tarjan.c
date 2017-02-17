
#include "goldberg_tarjan.h"

void push_relabel(NetworkPointer network)
{
    push_relabel_initialize(network);
    VertexCollection actives = active_vertices(network);
    while (!vertexcollection_is_empty(actives)) {
        size_t i;
        for (i = 0; i < vertexcollection_length(actives); i++) {
            VertexPointer vertex = vertexcollection_get(actives, i);
            discharge(network, vertex);
        }
        actives = active_vertices(network);
    }
}

