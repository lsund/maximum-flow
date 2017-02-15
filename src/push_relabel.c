
#include "push_relabel.h"

void push_relabel(NetworkPointer network)
{
    push_relabel_initialize(network);
    VertexPointer active = networkvertex_active(network);
    while (active) {
        EdgePointer admissable = admissable_edge(network, *active);
        if (!admissable) {
            relabel(network, active);
        } else {
            push(admissable, active);
        }
        active = networkvertex_active(network);
    }
}

