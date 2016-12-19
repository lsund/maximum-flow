#ifndef GRAPH_H
#define GRAPH_H

#include "util.h"
#include "edgecollection.h"
#include "vertexcollection.h"

// An undirected graph
// Field edgecollection:   The set of edges
// Field vertexcollection: The set of vertices
typedef struct graph {
    EdgeCollection edges;
    VertexCollection vertices;
} Graph, *GraphPointer;

Graph graph_init();

// Constructs an instance of a graph using the vertexcollection and edgecollection and returns
// a pointer to this structure
Graph graph_make(const VertexCollection vertexcollection, const EdgeCollection edgecollection);

void graph_reset(Graph graph);

VertexCollection graph_neighbors_of(const Graph graph, const VertexPointer vertex);

void graph_out_edges_from(
        const Graph graph, 
        const VertexPointer vertex,
        EdgeCollectionPointer ret);

// Frees the structure
Result graph_destroy(Graph graph);

#endif
