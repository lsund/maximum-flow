
#include "array.h"

Array array_empty()
{
    Array ret;
    ret.head     = NULL;
    ret.capacity = 0;
    ret.length   = 0;
    return ret;
}

Array array_init(const size_t init_length)
{
    Array ret;
    ret.head     = calloc(init_length, sizeof(void *));
    ret.capacity = init_length;
    ret.length   = 0;
    return ret;
}

ArrayPointer array_p_init(const size_t init_length)
{
    ArrayPointer ret = malloc(sizeof(Array));
    *ret             = array_init(init_length);
    return ret;
}

size_t array_length(const ArrayPointer array)
{
    return array->length;
}

void *array_get(const ArrayPointer array, const unsigned int position)
{
    if (!array) {
        runtime_error("array_get: argument is NULL");
    }
    if (position >= array->length) {
        return NULL;
    }
    return *(array->head + position);
}

void array_set(const ArrayPointer array, void *element, const unsigned int position)
{
    if (!array) {
        runtime_error("array_get: argument is NULL");
    }
    *(array->head + position) = element;
}

Result array_push(const ArrayPointer array, void *element)
{
    if (!array) {
        runtime_error("array_push: invalid argument");
    } 
    if (array->length == array->capacity) {
        Array expandedarray;
        if (array->length == 0) {
            expandedarray = array_init(ARRAY_MIN_SIZE);
        } else {
            expandedarray = array_init(array->capacity * 2);
        }
        size_t i;
        for (i = 0; i < array->capacity; i++) {
            array_push(&expandedarray, array_get(array, i)); 
        }
        *(expandedarray.head + expandedarray.length) = element;
        expandedarray.length++;
        Array temp = *array;
        *array = expandedarray;
        free(temp.head);
    } else {
        *(array->head + array->length) = element;
        array->length++;
    }
    return SUCCESS;
}

void *array_pop(const ArrayPointer array)
{
    if (array->length == 0) {
        return NULL;
    }
    void *temp = array_get(array, array->length - 1);
    array->length--; 
    return temp;
}

bool array_is_empty(const ArrayPointer array)
{
    return !array || !array->head || array->length == 0;
}

bool array_equals(const ArrayPointer array_a, const ArrayPointer array_b)
{
    if (!array_a || !array_b) {
        runtime_error("array_equals: argument is NULL");
        return false;
    } else if (array_a->length != array_b->length) {
        return false;
    } else if (array_a->capacity != array_b->capacity) {
        return false;
    } else {
        return true;
    }
}

Result array_destroy(ArrayPointer array)
{
    free(array->head);
    free(array);
    return SUCCESS;
}


