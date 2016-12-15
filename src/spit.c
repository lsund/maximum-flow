
#include "spit.h"

Result DIMACS_print(const GraphPointer graph) {

    int i, n, m;
    m = edgeset_length(graph->edgeset);
    n = vertexset_length(graph->vertexset);

    printf("p edge %d %d\n", n, m);
    for (i = 0; i < m; i++) { 
        EdgePointer edge = edgeset_get(graph->edgeset, i);
        printf("e %d %d\n", edge->first->label, edge->second->label);
    }
    return SUCCESS;
}
