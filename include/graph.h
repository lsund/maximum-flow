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

// Constructs an instance of a graph using the vertexcollection and edgecollection and returns
// a pointer to this structure
GraphPointer graph_make(const VertexCollection vertexcollection, const EdgeCollection edgecollection);

VertexCollection graph_neighbors_of(const GraphPointer graph, const VertexPointer vertex);

EdgeCollection graph_incident_with(const GraphPointer graph, const VertexPointer vertex);

EdgeCollection graph_out_edges_from(const GraphPointer graph, const VertexPointer vertex);

// Frees the structure
Result graph_destroy(GraphPointer graph);

#endif
