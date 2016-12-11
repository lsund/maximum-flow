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
    unsigned int length;
} Array, *ArrayPointer;

// A array with no capacity  
Array array_empty();

// Same as empty array, but returns a pointer to the array
ArrayPointer array_p_empty();

// Initializes a array of length init_length. All elements get uninitialized
// values. 
Array array_init(const size_t init_length);

// same as array_init, but returns a pointer to the array 
ArrayPointer array_p_init(const unsigned int init_length);

// Sets the next uninitialized value to the specified element
Result array_push(const ArrayPointer array, void *element);

// Remove the final element from an array
Result array_pop(ArrayPointer array);

// Has the array only uninitialized values?
bool array_is_empty(const ArrayPointer array);

bool array_equals(const ArrayPointer array_a, const ArrayPointer array_b);

// Return the element in the array at the specified position
void *array_get(const ArrayPointer array, const unsigned int position);

// Return the final element of an array
void *array_get_last(const ArrayPointer array);

// Sets the element at the specified position in the array
void array_set(const ArrayPointer array, void *element, unsigned int position);

// Frees the structure
Result array_destroy(ArrayPointer array);

#endif
