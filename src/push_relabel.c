
#include "push_relabel.h"

void push_relabel(NetworkPointer network)
{
    push_relabel_initialize(network);
    VertexPointer active = networkvertex_active(network);
    while (active) {
        EdgePointer admissable = networkedge_admissable(network, *active);
        if (!admissable) {
            relabel(network, active);
        } else {
            push(network, admissable, active);
        }
        active = networkvertex_active(network);
    }
}

