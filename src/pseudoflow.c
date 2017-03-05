
#include "pseudoflow.h"

void pseudoflow(const NetworkPointer network)
{
    pseudoflow_initialize(network);
    EdgePointer merger = merger_edge(network);
    while (merger) {

        VertexPointer strong_vertex, weak_vertex;
        strong_vertex = merger->first;
        weak_vertex = merger->second;

        VertexPointer strong_branch;
        strong_branch = merge(strong_vertex, weak_vertex);
        
        unsigned int delta;
        delta = strong_branch->excess;

        EdgeCollection path;
        path = network_edgepath_to_treeroot(network, strong_branch);

        size_t i;
        for (i = 0; i < edgecollection_length(path); i++) {
            EdgePointer edge = edgecollection_get(path, i);
            delta = push_flow(network, edge, delta);
        }

        edgecollection_destroy(path);
        merger = merger_edge(network);
    }
    return;
}


