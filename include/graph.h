#ifndef GRAPH_H
#define GRAPH_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "tokenizer.h"
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

GraphPointer graph_make(const VertexSet vertexset, const EdgeSet edgeset);

// Frees the structure
Result graph_destroy(GraphPointer graph);

Result graph_make_reversed(const Graph graph, GraphPointer reversed);

#endif
