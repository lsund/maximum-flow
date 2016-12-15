#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

#include "util.h"

#define ARRAY_MIN_SIZE 4

// A generic array
// Field head:      The actual references to the element
// Field length:    Maximumm capacity of the array
// Field length: The current number of initialized elements in the array
typedef struct array {
    void **head;
    size_t capacity;
    size_t length;
} Array, *ArrayPointer;

// An array with all fields set to 0 or NULL.
Array array_empty();

// Initializes a array of length init_length. All elements get uninitialized
// values. 
Array array_init(const size_t init_length);

// same as array_init, but returns a pointer to the array 
ArrayPointer array_p_init(const size_t init_length);

size_t array_length(const ArrayPointer array);

// Return the element in the array at the specified position
void *array_get(const ArrayPointer array, const unsigned int position);

// Sets the element at the specified position in the array
void array_set(const ArrayPointer array, void *element, const unsigned int position);

// Sets the next uninitialized value to the specified element
Result array_push(const ArrayPointer array, void *element);

// get the last element of an array
void *array_pop(ArrayPointer array);

// Returns true if the array is considered empty
bool array_is_empty(const ArrayPointer array);

bool array_equals(const ArrayPointer array_a, const ArrayPointer array_b);

// Frees the structure
Result array_destroy(ArrayPointer array);

#endif
