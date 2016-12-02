
#ifndef GRAPH_STRUCTS_H
#define GRAPH_STRUCTS_H

#include "edgeset.h"
#include "vertexset.h"

// An undirected graph
// Field edgeset:   The set of edges
// Field vertexset: The set of vertices
typedef struct graph {
    EdgeSet edgeset;
    VertexSet vertexset;
} Graph, *GraphPointer;


#endif
