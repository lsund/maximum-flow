#ifndef NETWORK_H
#define NETWORK_H

#include "graph.h"

typedef struct network {
    GraphPointer    graph;
    GraphPointer    graph_all; 
    VertexPointer   source;
    VertexPointer   sink;
    unsigned int    *capacities;
    int             *flows;
    Label           *distance_labels;
} Network, *NetworkPointer;

NetworkPointer network_init();

NetworkPointer network_make(const GraphPointer graph, const VertexPointer source, const VertexPointer sink);
//// getters
unsigned int network_edge_capacity(const NetworkPointer network, const EdgePointer edge, const bool residual);

unsigned int network_edge_flow(const NetworkPointer network, const EdgePointer edge);

Label network_vertex_distance_label(const NetworkPointer network, const VertexPointer vertex);

unsigned int network_vertex_inflow(const NetworkPointer network, const VertexPointer vertex);

int network_vertex_exflow(const NetworkPointer network, const VertexPointer vertex);

VertexPointer network_active_vertex(const NetworkPointer network);

EdgePointer network_admissable_edge(const NetworkPointer network, const EdgeCollection edges);

unsigned int network_flow(const NetworkPointer network);

//// setters

void network_augment_edge(const NetworkPointer network, const EdgePointer edge, const unsigned int added_flow);

void network_vertex_set_flow(const NetworkPointer network, const VertexPointer vertex);

void network_vertex_set_distance_label(const NetworkPointer network, const VertexPointer vertex, const unsigned int label);

bool network_vertex_is_active(const NetworkPointer network, const VertexPointer vertex);

bool network_edge_is_admissable(const NetworkPointer network, const EdgePointer edge);

bool network_edge_is_residual(const NetworkPointer network, const EdgePointer edge);

void network_set_edge_capacity(
        const NetworkPointer network, 
        const EdgePointer edge, 
        const unsigned int capacity
    );

void network_set_edge_flow(
        const NetworkPointer network, 
        const EdgePointer edge, 
        const int flow
    );

bool network_edge_is_reverse(const NetworkPointer network, const EdgePointer edge);

Graph network_residual(const NetworkPointer network);

#endif
