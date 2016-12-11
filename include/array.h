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
// Field nelements: The current number of initialized elements in the array
typedef struct array {
    void **head;
    size_t length;
    unsigned int nelements;
} Array, *ArrayPointer;

// A array with no capacity  
Array empty_array();

// Same as empty array, but returns a pointer to the array
ArrayPointer empty_p_array();

// Initializes a array of length init_length. All elements get uninitialized
// values. 
Array init_array(const size_t init_length);

// same as init_array, but returns a pointer to the array 
ArrayPointer init_p_array(const unsigned int init_length);

// Sets the next uninitialized value to the specified element
Result push_element(const ArrayPointer array, void *element);

// Remove the final element from an array
Result pop_element(ArrayPointer array);

// Has the array only uninitialized values?
bool array_is_empty(const ArrayPointer array);

bool arrays_equal(const ArrayPointer array_a, const ArrayPointer array_b);

// Return the element in the array at the specified position
void *get_element(const ArrayPointer array, const unsigned int position);

// Return the final element of an array
void *get_last_element(const ArrayPointer array);

void set_element(const ArrayPointer array, void *element, unsigned int position);

// Frees the structure
Result destroy_array(ArrayPointer array);

#endif
