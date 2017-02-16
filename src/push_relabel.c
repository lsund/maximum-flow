
#include "push_relabel.h"

void discharge()
{
    // let e be the edge to which curr points
    // if e is admissable then 
    //      push(e) 
    // else
    //      if e is the last list of out_edges(v) then
    //          relabel(v)
    //          let curr(v) point to the first element of out_edges(v)
    //          return
    //      else
    //          let curr(v) point to the next edge in out_edges(v)
    // if exflow(v) > 0 go to start
}

void push_relabel(NetworkPointer network)
{
    push_relabel_initialize(network);
    // GBT algorithm:
    //
    // for all v, set curr(v) to the first edge of its outgoing edges
    // set Q = the set of all active vertices, if Q is empty then stop
    // call discharge() for all vertices in Q
    // reiterate Q
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

