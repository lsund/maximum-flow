
#include "goldberg_tarjan.h"

void goldberg_tarjan(NetworkPointer network)
{
    goldberg_tarjan_initialize(network);
    VertexCollection actives = active_vertices(network);
    while (!vertexcollection_is_empty(actives)) {
        size_t i;
        for (i = 0; i < vertexcollection_length(actives); i++) {
            VertexPointer vertex = vertexcollection_get(actives, i);
            discharge(network, vertex);
        }
        vertexcollection_destroy(actives);
        actives = active_vertices(network);
    }
    vertexcollection_destroy(actives);
}

