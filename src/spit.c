
#include "spit.h"

Result DIMACS_print(const GraphPointer graph) {

    int i, n, m;
    m = edgecollection_length(graph->edges);
    n = vertexcollection_length(graph->vertices);

    printf("p edge %d %d\n", n, m);
    for (i = 0; i < m; i++) { 
        EdgePointer edge = edgecollection_get(graph->edges, i);
        printf("e %d %d\n", edge->first->label, edge->second->label);
    }
    return SUCCESS;
}
