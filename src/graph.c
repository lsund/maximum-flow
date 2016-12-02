
#include "graph.h"

GraphPointer init_graph()
{
    return calloc(1, sizeof(Graph));;
}

Result make_graph(const TokenTablePointer table, GraphPointer graph)
{
    if (!table || !graph) {
        errno = EFAULT;
        return FAIL;
    }
    Point table_dim;
    table_dim = graph_cardinality(table);
    
    graph->vertexset = init_vertexset(table_dim.x);
    if (!graph->vertexset.set) {
        return FAIL;
    }
    graph->edgeset = init_edgeset(table_dim.x + 1);
    if (!graph->edgeset.set) {
        return FAIL;
    }
    
    return parse(table, graph);
}

Result destroy_graph(GraphPointer graph)
{
    if (!graph || !graph->edgeset.set || !graph->vertexset.set) {
        errno = EFAULT;
        return FAIL;
    }
    if (!graph->edgeset.set->head || !graph->vertexset.set->head) {
        errno = EFAULT;
        return FAIL;
    }
    destroy_vertexset(graph->vertexset);
    destroy_edgeset(graph->edgeset);
    free(graph);
    graph = NULL;
    return SUCCESS;
}

