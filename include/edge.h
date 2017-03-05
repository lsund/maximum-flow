#ifndef EDGE_H
#define EDGE_H

#include <stdbool.h>

#include "vertex.h"
#include "util.h"

// An edge is a set containing two vertices
// An edge is therefore assumed to be non-looping. Modules that uses this
// structure is assumed to treat the edges as unique, that is this structure
// should not be used in multi-graphs.
//
// Field first:     The first vertex
// Field second:    The second vertex
typedef struct edge Edge, *EdgePointer;

typedef enum EdgeType { FORWARD, REVERSE } EdgeType;

struct edge {
    VertexPointer first, second;
    unsigned int capacity, flow;
    EdgePointer reverse;
    bool is_reverse;
    bool *incident_with;
};

// Constructs an edge and returns a pointer to it
EdgePointer edge_make(const VertexPointer first, const VertexPointer second);

// Returns true if the edge contains the given vertex, false otherwise
bool edge_incident_with(const Edge edge, const Vertex vertex);

unsigned int edge_capacity(const EdgePointer edge);

void edge_set_capacity(const EdgePointer edge, const unsigned int capacity);

unsigned int edge_residual_capacity(const EdgePointer edge);

unsigned int edge_flow(const EdgePointer edge);

void edge_set_flow(const EdgePointer edge, int flow);

void edge_add_flow(const EdgePointer edge, const int added_flow);

void edge_fill_flow(
        const EdgePointer edge,
        const unsigned int capacity,
        const EdgeType type
    );

void edge_augment(const EdgePointer edge, const unsigned int added_flow);

bool edge_is_residual(const EdgePointer edge);

bool edge_is_admissable(const EdgePointer edge);

// Print an edge as "(v, w)" to stdout
void edge_print(const Edge edge);

#endif
