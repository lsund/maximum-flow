
#include "push_relabel.h"

void push_relabel(NetworkPointer network)
{
    push_relabel_initialize(network);
    // GBT algorithm:
    //
    // for all v, set curr(v) to the first edge of its outgoing edges
    // set Q = the set of all active vertices, if Q is empty then stop
    VertexCollection actives = active_vertices(network);
    while (!vertexcollection_is_empty(actives)) {
    // call discharge() for all vertices in Q
        size_t i;
        for (i = 0; i < vertexcollection_length(actives); i++) {
            VertexPointer vertex = vertexcollection_get(actives, i);
            discharge(network, vertex);
        }
        actives = active_vertices(network);
    }
    // reiterate Q
    /* VertexPointer active = networkvertex_active(network); */
    /* while (active) { */
        /* EdgePointer admissable = admissable_edge(network, *active); */
        /* if (!admissable) { */
            /* relabel(network, active); */
        /* } else { */
            /* push(admissable, active); */
        /* } */
        /* active = networkvertex_active(network); */
    /* } */
}

