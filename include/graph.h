#ifndef GRAPH_H
#define GRAPH_H

#include "edgecollection.h"
#include "vertexcollection.h"

// An undirected graph defined over a set of vertices and a set of edges.
// Field edgecollection:   The set of edges
// Field vertexcollection: The set of vertices
typedef struct graph {
    EdgeCollection edges;
    VertexCollection vertices;
} Graph, *GraphPointer;

// Initializes the structure and sets all fields to default values
Graph graph_init();

// Constructs an instance of a graph using the vertexcollection and
// edgecollection and returns a pointer to this structure
Graph graph_make(
        const VertexCollection vertexcollection,
        const EdgeCollection edgecollection
    );

// Frees the structure
Result graph_destroy(Graph graph);

#endif
