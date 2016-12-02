
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

Result make_reversed_graph(const Graph graph, GraphPointer reversed)
{
    reversed->vertexset = graph.vertexset;  
    EdgeSet reversed_edgeset = init_edgeset(graph.vertexset.maxvertices + 1);
    size_t i;
    for (i = 0; i < graph.edgeset.set->nelements; i++) {
        if (add_edge(reversed_edgeset, swapped(*get_edge_at_position(graph.edgeset, i))) == FAIL) {
            return FAIL;
        }
    }
    reversed->edgeset = reversed_edgeset;
    return SUCCESS;
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

