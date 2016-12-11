
#include "array.h"

Array array_init(const size_t init_length)
{
    Array ret;
    ret.head      = calloc(init_length, sizeof(void *));
    ret.length    = init_length;
    ret.nelements = 0;
    return ret;
}

ArrayPointer array_p_init(const unsigned int init_length)
{
    ArrayPointer ret = malloc(sizeof(Array));
    *ret             = array_init(init_length);
    return ret;
}

bool array_is_empty(const ArrayPointer array) 
{
    return array->nelements == 0;
}

Array array_empty() 
{
    Array ret;
    ret.head = NULL;
    ret.length = 0;
    ret.nelements = 0;
    return ret;
}

ArrayPointer array_p_empty()
{
    ArrayPointer ret = malloc(sizeof(Array));
    *ret = array_empty();
    return ret;
}

bool array_equals(ArrayPointer array_a, ArrayPointer array_b)
{
    if (array_a->nelements != array_b->nelements) {
        return false;
    }
    if (array_a->length != array_b->length) {
        return false;
    }
    size_t i;
    for (i = 0; i < array_a->nelements; i++) {
        if (array_get(array_a, i) != array_get(array_b, i)) {
            return false;
        }
    }
    return true;
}

void *array_get(const ArrayPointer array, const unsigned int position)
{
    if (position > array->length) {
        errno = EFAULT;
        return NULL;
    }
    return *(array->head + position);
}

void *array_get_last(const ArrayPointer array)
{
    return array_get(array, array->nelements - 1);
}

void array_set(const ArrayPointer array, void *element, unsigned int position)
{
    *(array->head + position) = element;
}

Result array_push(const ArrayPointer array, void *element)
{
    if (!array) {
        errno = EFAULT;
        return FAIL;
    }
    if (array->nelements == array->length) {
        Array expandedarray;
        if (array->nelements == 0) {
            expandedarray = array_init(ARRAY_MIN_SIZE);
        } else {
            expandedarray = array_init(array->length * 2);
        }
        size_t i;
        for (i = 0; i < array->length; i++) {
            array_push(&expandedarray, array_get(array, i)); 
        }
        *(expandedarray.head + expandedarray.nelements) = element;
        expandedarray.nelements++;
        Array temp = *array;
        *array = expandedarray;
        free(temp.head);
    } else {
        *(array->head + array->nelements) = element;
        array->nelements++;
    }
    return SUCCESS;
}

Result array_pop(ArrayPointer array)
{
    void *head = array_get(array, array->nelements - 1);
    if (!head) {
        errno = EFAULT;
        return FAIL;
    } else {
        array->nelements--; 
        return SUCCESS;
    }
}

Result array_destroy(ArrayPointer array)
{
    if (array->head != NULL) {
        unsigned int i;
        for (i = 0; i < array->length; i++) {
            free(*(array->head + i));
        }
    } 
    free(array->head);
    free(array);
    return SUCCESS;
}


