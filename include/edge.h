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
    Vertex first;
    Vertex second;
    VertexPointer first_ref, second_ref;
    unsigned int capacity, flow;
    EdgePointer reverse;
    bool is_reverse;
    bool *incident_with;
};

// Constructs an edge from two vertices
Edge edge_make(const Vertex first, const Vertex second);

// Same as edge_make, but returns a pointer to an edge
EdgePointer edge_p_make(const VertexPointer first, const VertexPointer second);

// Returns an edge, where the first and the second vertex are swapped
Edge edge_swapped(const Edge edge);

// Returns true if the edge contains the given vertex, false otherwise
bool edge_incident_with(const Edge edge, const Vertex vertex);

// Returns true if the two edges are considered equal, false otherwise
bool edge_equals(const Edge edge_a, const Edge edge_b);

// Returns true if edge_b equals the reverse edge of b
bool edge_equals_reverse(const Edge edge_a, const Edge edge_b);

// Ruterns an unique integer for each unique edge
unsigned int edge_hash(const Edge edge);

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

// Print an edge as "(v, w)" to stdout
void edge_print(const Edge edge);

#endif
