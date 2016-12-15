#ifndef GRAPH_H
#define GRAPH_H

#include "util.h"
#include "edgeset.h"
#include "vertexset.h"

// An undirected graph
// Field edgeset:   The set of edges
// Field vertexset: The set of vertices
typedef struct graph {
    EdgeSet edgeset;
    VertexSet vertexset;
} Graph, *GraphPointer;

// Constructs an instance of a graph using the vertexset and edgeset and returns
// a pointer to this structure
GraphPointer graph_make(const VertexSet vertexset, const EdgeSet edgeset);

// Frees the structure
Result graph_destroy(GraphPointer graph);

#endif
