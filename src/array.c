
#include "array.h"

Array init_array(const size_t init_length)
{
    Array ret;
    ret.head      = calloc(init_length, sizeof(void *));
    ret.length    = init_length;
    ret.nelements = 0;
    return ret;
}

ArrayPointer init_p_array(const unsigned int init_length)
{
    ArrayPointer ret = malloc(sizeof(Array));
    *ret             = init_array(init_length);
    return ret;
}

bool array_is_empty(const ArrayPointer array) 
{
    return array->nelements == 0;
}

Array empty_array() 
{
    Array ret;
    ret.head = NULL;
    ret.length = 0;
    ret.nelements = 0;
    return ret;
}

ArrayPointer empty_p_array()
{
    ArrayPointer ret = malloc(sizeof(Array));
    *ret = empty_array();
    return ret;
}

bool arrays_equal(ArrayPointer array_a, ArrayPointer array_b)
{
    if (array_a->nelements != array_b->nelements) {
        return false;
    }
    if (array_a->length != array_b->length) {
        return false;
    }
    size_t i;
    for (i = 0; i < array_a->nelements; i++) {
        if (get_element(array_a, i) != get_element(array_b, i)) {
            return false;
        }
    }
    return true;
}

void *get_element(const ArrayPointer array, const unsigned int position)
{
    if (position > array->length) {
        errno = EFAULT;
        return NULL;
    }
    return *(array->head + position);
}

void *get_last_element(const ArrayPointer array)
{
    return get_element(array, array->nelements - 1);
}

void set_element(const ArrayPointer array, void *element, unsigned int position)
{
    *(array->head + position) = element;
}

Result push_element(const ArrayPointer array, void *element)
{
    if (!array) {
        errno = EFAULT;
        return FAIL;
    }
    if (array->nelements == array->length) {
        Array expandedarray;
        if (array->nelements == 0) {
            expandedarray = init_array(ARRAY_MIN_SIZE);
        } else {
            expandedarray = init_array(array->length * 2);
        }
        size_t i;
        for (i = 0; i < array->length; i++) {
            push_element(&expandedarray, get_element(array, i)); 
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

Result pop_element(ArrayPointer array)
{
    void *head = get_element(array, array->nelements - 1);
    if (!head) {
        errno = EFAULT;
        return FAIL;
    } else {
        array->nelements--; 
        return SUCCESS;
    }
}

Result destroy_array(ArrayPointer array)
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


