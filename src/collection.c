
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

void *collection_get(
        const CollectionPointer collection,
        const unsigned int position
    )
{
    return *(collection->head + position);
}

void collection_push(const CollectionPointer collection, void *element)
{
    if (collection->length == collection->capacity) {
        Collection expandedcollection;
        if (collection->length == 0) {
            expandedcollection = collection_init(COLL_MIN_SIZE);
        } else {
            expandedcollection = collection_init(collection->capacity * 2);
        }
        size_t i;
        for (i = 0; i < collection->capacity; i++) {
            collection_push(&expandedcollection, collection_get(collection, i));
        }
        collection_set(&expandedcollection, element, expandedcollection.length);
        expandedcollection.length++;
        Collection temp = *collection;
        *collection = expandedcollection;
        free(temp.head);
    } else {
        collection_set(collection, element, collection->length);
        collection->length++;
    }
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

void collection_set(
        const CollectionPointer collection,
        void *element,
        const unsigned int position
    )
{
    *(collection->head + position) = element;    
}

void collection_remove(const CollectionPointer collection, const void *element)
{
    size_t i, n_elements = collection_length(collection);
    bool found = false;
    for (i = 0; i < n_elements; i++) {
        void *current = collection_get(collection, i);
        if (element != current) {
            if (found) {
                collection_set(collection, current, i - 1);
            } else {
                collection_set(collection, current, i);
            }
        } else {
            found = true;
        }
    }
}

bool collection_is_empty(const CollectionPointer collection)
{
    return !collection || !collection->head || collection->length == 0;
}

bool collection_equals(
        const CollectionPointer collection_a,
        const CollectionPointer collection_b
    )
{
    bool equal_length = collection_a->length == collection_b->length;
    bool equal_capacity = collection_a->capacity == collection_b->capacity;
    return equal_length && equal_capacity;
}

Result collection_destroy(CollectionPointer collection)
{
    free(collection->head);
    free(collection);
    return SUCCESS;
}


