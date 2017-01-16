
#include "collection.h"

Collection collection_empty()
{
    Collection ret;
    ret.head     = NULL;
    ret.capacity = 0;
    ret.length   = 0;
    return ret;
}

Collection collection_init(const size_t init_length)
{
    Collection ret;
    ret.head     = calloc(init_length, sizeof(void *));
    ret.capacity = init_length;
    ret.length   = 0;
    return ret;
}

CollectionPointer collection_p_init(const size_t init_length)
{
    CollectionPointer ret = malloc(sizeof(Collection));
    *ret             = collection_init(init_length);
    return ret;
}

void collection_reset(CollectionPointer collection)
{
    collection->length = 0;
}

size_t collection_length(const CollectionPointer collection)
{
    return collection->length;
}

void *collection_get(const CollectionPointer collection, const unsigned int position)
{
    return *(collection->head + position);
}

void collection_replace(const CollectionPointer collection, void *element, const unsigned int position)
{
    if (!collection) {
        runtime_error("collection_get: argument is NULL");
    }
    *(collection->head + position) = element;
}

Result collection_push(const CollectionPointer collection, void *element)
{
    if (!collection) {
        runtime_error("collection_push: invalid argument");
    } 
    if (collection->length == collection->capacity) {
        Collection expandedcollection;
        if (collection->length == 0) {
            expandedcollection = collection_init(ARRAY_MIN_SIZE);
        } else {
            expandedcollection = collection_init(collection->capacity * 2);
        }
        size_t i;
        for (i = 0; i < collection->capacity; i++) {
            collection_push(&expandedcollection, collection_get(collection, i)); 
        }
        *(expandedcollection.head + expandedcollection.length) = element;
        expandedcollection.length++;
        Collection temp = *collection;
        *collection = expandedcollection;
        free(temp.head);
    } else {
        *(collection->head + collection->length) = element;
        collection->length++;
    }
    return SUCCESS;
}

void *collection_pop(const CollectionPointer collection)
{
    if (collection->length == 0) {
        return NULL;
    }
    void *temp = collection_get(collection, collection->length - 1);
    collection->length--; 
    return temp;
}

void collection_remove(CollectionPointer *collection, void *element)
{
    CollectionPointer collection_val = *collection;
    size_t i, n_elements = collection_length(collection_val);
    CollectionPointer temp = collection_p_init(n_elements);
    for (i = 0; i < n_elements; i++) {
        void *current = collection_get(collection_val, i);
        if (element != current) {
            collection_push(temp, element);
        }
    }
    collection_destroy(collection_val);
    *collection = temp;
}

bool collection_is_empty(const CollectionPointer collection)
{
    return !collection || !collection->head || collection->length == 0;
}

bool collection_equals(const CollectionPointer collection_a, const CollectionPointer collection_b)
{
    if (!collection_a || !collection_b) {
        runtime_error("collection_equals: argument is NULL");
        return false;
    } else if (collection_a->length != collection_b->length) {
        return false;
    } else if (collection_a->capacity != collection_b->capacity) {
        return false;
    } else {
        return true;
    }
}

Result collection_destroy(CollectionPointer collection)
{
    free(collection->head);
    free(collection);
    return SUCCESS;
}


