
#include "graph.h"

GraphPointer graph_init()
{
    return calloc(1, sizeof(Graph));;
}

Result graph_make(const TokenTablePointer table, GraphPointer graph)
{
    if (!table || !graph) {
        errno = EFAULT;
        return FAIL;
    }
    Point table_dim;
    table_dim = graph_cardinality(table);
    
    graph->vertexset = vertexset_init(table_dim.x);
    if (!graph->vertexset.set) {
        return FAIL;
    }
    graph->edgeset = edgeset_init(table_dim.y);
    if (!graph->edgeset.set) {
        return FAIL;
    }
    
    return parse(table, graph);
}

Result graph_make_reversed(const Graph graph, GraphPointer reversed)
{
    reversed->vertexset = graph.vertexset;  
    EdgeSet reversed_edgeset = edgeset_init(graph.edgeset.set->length);
    size_t i;
    for (i = 0; i < graph.edgeset.set->length; i++) {
        Edge graph_edge = *edgeset_get(graph.edgeset, i);
        EdgePointer reversed_edge = edge_p_edge_make(edge_swapped(graph_edge));
        edgeset_push(reversed_edgeset, reversed_edge);
    }
    reversed->edgeset = reversed_edgeset;
    return SUCCESS;
}

Result graph_destroy(GraphPointer graph)
{
    if (!graph || !graph->edgeset.set || !graph->vertexset.set) {
        errno = EFAULT;
        return FAIL;
    }
    if (!graph->edgeset.set->head || !graph->vertexset.set->head) {
        errno = EFAULT;
        return FAIL;
    }
    vertexset_destroy(graph->vertexset);
    edgeset_destroy(graph->edgeset);
    free(graph);
    graph = NULL;
    return SUCCESS;
}

