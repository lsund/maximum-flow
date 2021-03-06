
#ifndef EDGE_COLLECTION_H
#define EDGE_COLLECTION_H

#include "edge.h"
#include "vertexcollection.h"

// An edgecollection is a collection of edges, allowing duplicates.
// Field members:   The underlying collection
typedef struct edgecollection {
    CollectionPointer members;
    unsigned int *curr;
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

// Sets the last element to the specified edge, and increments the number of
// elements
void edgecollection_push(const EdgeCollection edges, const EdgePointer edge);

EdgePointer edgecollection_current(const EdgeCollection edges);

void edgecollection_current_next(const EdgeCollection edges);

bool edgecollection_current_is_last(const EdgeCollection edges);

    // Print the collection to stdout
void edgecollection_print(const EdgeCollection edges);

// Free the structure
void edgecollection_destroy(EdgeCollection edges);

#endif
