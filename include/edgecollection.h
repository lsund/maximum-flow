
#ifndef EDGE_COLLECTION_H
#define EDGE_COLLECTION_H

#include "edge.h"
#include "vertexcollection.h"
#include "map.h"

// An edgecollection is a collection of edges, allowing duplicates.
// Field members:   The underlying collection
// Field indices:   a int -> int function. Maps an edge's unique hash-value to
//                  the index of the edge in the collection.
typedef struct edgecollection {
    CollectionPointer members;
    Map indices;
} EdgeCollection, *EdgeCollectionPointer;

// Returns an empty edgecollection, no allocations.
EdgeCollection edgecollection_empty();

// Returns the edgecollection with its internal fields initialized, and with the
// specified starting length.
EdgeCollection edgecollection_init(const size_t size);

// Returns the edgecollection with its internal fields initialized, and with a
// minimum starting length.
EdgeCollection edgecollection_init_min();

// Return the number of elements currently in this collection
size_t edgecollection_length(const EdgeCollection edges);

// Get the edge at the specified position
EdgePointer edgecollection_get(
        const EdgeCollection edges,
        const unsigned int position
    );

// Returns a reference to the edge in edges that has the same content as edge,
// NULL otherwise
EdgePointer edgecollection_get_reference(
        const EdgeCollection edges,
        const Edge edge
    );

// The index of the edge in the edgecollection that equals the specified edge.
// If no such edge exists, then -1.
int edgecollection_index_of(const EdgeCollection edges, const Edge edge);

// The vertices of this edgecollection
VertexCollection edgecollection_vertices(const EdgeCollection edges);

// Sets the last element to the specified edge, and increments the number of
// elements
Result edgecollection_push(const EdgeCollection edges, const EdgePointer edge);

// Removes the element from the edgecollection
/* void edgecollection_remove(EdgeCollection edges, const EdgePointer edge); */
void edgecollection_remove(EdgeCollectionPointer edges, const Edge edge);

// Returns true if the edgecollection contains every edge in the list of edges
// specified by edges, false otherwise
bool edgecollection_contains_edge(
        const EdgeCollection edges,
        const Edge edge
    );

// Print the collection to stdout
void edgecollection_print(const EdgeCollection edges);

// Free the structure
void edgecollection_destroy(EdgeCollection edges);

#endif
