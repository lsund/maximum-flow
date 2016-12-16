#ifndef ARRAY_H
#define ARRAY_H

#include "util.h"

#define ARRAY_MIN_SIZE 4

// A generic collection
// Field head:      The actual references to the element
// Field length:    Maximumm capacity of the collection
// Field length: The current number of initialized elements in the collection
typedef struct collection {
    void **head;
    size_t capacity;
    size_t length;
} Collection, *CollectionPointer;

// An collection with all fields set to 0 or NULL.
Collection collection_empty();

// Initializes a collection of length init_length. All elements get uninitialized
// values. 
Collection collection_init(const size_t init_length);

// same as collection_init, but returns a pointer to the collection 
CollectionPointer collection_p_init(const size_t init_length);

size_t collection_length(const CollectionPointer collection);

// Return the element in the collection at the specified position
void *collection_get(const CollectionPointer collection, const unsigned int position);

// Sets the element at the specified position in the collection
void collection_replace(const CollectionPointer collection, void *element, const unsigned int position);

// Sets the next uninitialized value to the specified element
Result collection_push(const CollectionPointer collection, void *element);

// get the last element of an collection
void *collection_pop(CollectionPointer collection);

// Returns true if the collection is considered empty
bool collection_is_empty(const CollectionPointer collection);

bool collection_equals(const CollectionPointer collection_a, const CollectionPointer collection_b);

// Frees the structure
Result collection_destroy(CollectionPointer collection);

#endif
