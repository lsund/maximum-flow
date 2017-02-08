
#include "graph.h"

Graph graph_init()
{
    Graph ret;
    ret.vertices = vertexcollection_init(COLL_MIN_SIZE);
    ret.edges = edgecollection_init_min();
    return ret;
}

Graph graph_make(const VertexCollection vertexcollection, const EdgeCollection edgecollection)
{
    Graph ret;
    ret.vertices = vertexcollection;
    ret.edges = edgecollection;
    return ret;
}

Result graph_destroy(Graph graph)
{
    vertexcollection_destroy(graph.vertices);
    edgecollection_destroy(graph.edges);
    return SUCCESS;
}

