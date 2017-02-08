#ifndef ARRAY_H
#define ARRAY_H

#include "util.h"
#include "map.h"

#define COLL_MIN_SIZE 4

// A collection of generic pointers, allows duplicates
// Field head:      The actual references to the element
// Field capacity:  Maximum capacity of the collection
// Field length:    The current number of initialized elements in the collection
typedef struct collection {
    void **head;
    size_t capacity;
    size_t length;
} Collection, *CollectionPointer;

// An initialized collection with no heap-allocated memory
Collection collection_empty();

// Initializes a collection of length init_length.
Collection collection_init(const size_t init_length);

// Same as collection_init, but returns a pointer to the collection 
CollectionPointer collection_p_init(const size_t init_length);

// Resets the collection, forget any values that was previously stored
void collection_reset(CollectionPointer collection);

// The number of elements currently stored in this collection
size_t collection_length(const CollectionPointer collection);

// The element in the collection stored at the specified position
void *collection_get(
        const CollectionPointer collection,
        const unsigned int position
    );

// Sets the element at the specified position in the collection to a new value
void collection_set(
        const CollectionPointer collection,
        void *element,
        const unsigned int position
    );

// Adds the element to the collection. Will double the collection-size if
// capacity is too small
void collection_push(const CollectionPointer collection, void *element);

// The last element of an collection, that is also removed from the collection.
// O(1)
void *collection_pop(CollectionPointer collection);

// Removes the specified element from the collection.
// O(n)
void collection_remove(const CollectionPointer collection, const void *element);

// True if the collection is considered empty
bool collection_is_empty(const CollectionPointer collection);

// True if the collections has thee same elements, length and capacity
bool collection_equals(
        const CollectionPointer collection_a,
        const CollectionPointer collection_b
    );

// Frees all allocated heap
Result collection_destroy(CollectionPointer collection);

#endif
