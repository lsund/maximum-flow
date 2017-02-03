
#include <stdlib.h>
#include "test.h"

char *utest_collection_remove()
{
    VertexPointer t1 = vertex_p_make(1);
    VertexPointer t2 = vertex_p_make(2);
    VertexPointer t3 = vertex_p_make(3);
    CollectionPointer collection = collection_p_init(ARRAY_MIN_SIZE);
    collection_push(collection, t1);
    collection_push(collection, t2);
    collection_push(collection, t3);

    mu_assert("should be 1", ((VertexPointer) collection_get(collection, 0))->label == 1);
    mu_assert("should be 2", ((VertexPointer) collection_get(collection, 1))->label == 2);
    mu_assert("should be 3", ((VertexPointer) collection_get(collection, 2))->label == 3);

    collection_remove(collection, t2);

    mu_assert("should be 1", ((VertexPointer) collection_get(collection, 0))->label == 1);
    mu_assert("should be 3", ((VertexPointer) collection_get(collection, 1))->label == 3);

    collection_remove(collection, t1);

    mu_assert("should be 3", ((VertexPointer) collection_get(collection, 0))->label == 3);


    return NULL;
}

char *utest_collection_empty()
{
    Collection collection = collection_empty();
    mu_assert("should be empty", collection.head == NULL);
    mu_assert("should be empty", collection.capacity == 0);
    mu_assert("should be empty", collection.length == 0);
    return NULL;
}

char *utest_collection_init()
{
    Collection collection;
    collection = collection_init(7);
    mu_assert("should not be null", collection.head);
    mu_assert("should be 0", collection.length == 0);
    mu_assert("should be init length", collection.capacity == 7);
    return NULL;
}

char *utest_collection_p_init()
{
    CollectionPointer collection;
    collection = collection_p_init(7);
    mu_assert("should not be null", collection);
    mu_assert("should not be null", collection->head);
    mu_assert("should be 0", collection->length == 0);
    mu_assert("should be init length", collection->capacity == 7);
    return NULL;
}

char *utest_collection_equals()
{
    CollectionPointer collection_a = collection_p_init(4);
    CollectionPointer collection_b = collection_p_init(4);
    mu_assert("should equal", collection_equals(collection_a, collection_b));
    collection_a->capacity = 5;
    mu_assert("1 should not equal", !collection_equals(collection_a, collection_b));
    mu_assert("2 should not equal", !collection_equals(collection_b, collection_a));
    collection_b->length = 5;
    collection_b->capacity = 5;
    mu_assert("3 should not equal", !collection_equals(collection_a, collection_b));
    mu_assert("4 should not equal", !collection_equals(collection_b, collection_a));
    collection_a->length = 5;
    mu_assert("should equal", collection_equals(collection_a, collection_b));
    mu_assert("should equal", collection_equals(collection_b, collection_a));
    return NULL;
}

char *utest_collection_get()
{
    int x = 3;
    int y = 2;
    int z = 1;
    CollectionPointer collection_a = collection_p_init(4);
    collection_push(collection_a, &x);
    collection_push(collection_a, &y);
    collection_push(collection_a, &z);
    mu_assert("should be 3", *((int *) collection_get(collection_a, 0)) == 3);
    mu_assert("should be 2", *((int *) collection_get(collection_a, 1)) == 2);
    mu_assert("should be 1", *((int *) collection_get(collection_a, 2)) == 1);
    return NULL;
}

char *utest_collection_set()
{
    int x = 3;
    int y = 2;
    int z = 1;
    CollectionPointer collection_a = collection_p_init(4);
    collection_push(collection_a, &x);
    collection_push(collection_a, &y);
    collection_push(collection_a, &z);
    collection_set(collection_a, &x, 0);
    collection_set(collection_a, &x, 1);
    collection_set(collection_a, &x, 2);
    mu_assert("should be 3", *((int *) collection_get(collection_a, 0)) == 3);
    mu_assert("should be 2", *((int *) collection_get(collection_a, 1)) == 3);
    mu_assert("should be 1", *((int *) collection_get(collection_a, 2)) == 3);
    mu_assert("should still be 3", collection_a->length == 3);
    mu_assert("should still be 4", collection_a->capacity == 4);
    return NULL;
}

char *utest_collection_push()
{
    int *a = malloc(sizeof(int));
    int *b = malloc(sizeof(int));
    int *c = malloc(sizeof(int));
    CollectionPointer collection = malloc(sizeof(Collection));
    *a = 1;
    *b = 2;
    *c = 3;
    *collection = collection_init(2);
    collection_push(collection, a);
    collection_push(collection, b);
    collection_push(collection, c);
    mu_assert("size should have doubled", collection->capacity == 4); 
    mu_assert("elements should have increased ", collection->length == 3); 
    mu_assert("should have the correct elements ", *((int *) collection_get(collection, 0)) == 1); 
    mu_assert("should have the correct elements ", *((int *) collection_get(collection, 1)) == 2); 
    mu_assert("should have the correct elements ", *((int *) collection_get(collection, 2)) == 3); 
    free(collection);
    collection =  collection_p_init(0);
    collection_push(collection, a);
    mu_assert("size should have been initialized", collection->capacity == 4); 
    free(a);
    free(b);
    free(c);
    free(collection);
    return NULL;
}

char *utest_collection_pop()
{
    int a, b, c, d;
    a = 1;
    b = 0;
    c = 0;
    d = 1;
    CollectionPointer collection;
    collection = collection_p_init(0);
    collection_push(collection, &a);
    mu_assert("0 should be 1", collection->length == 1);
    collection_push(collection, &b);
    collection_push(collection, &c);
    collection_push(collection, &d);
    mu_assert("1 should be 4", collection->length == 4);
    mu_assert("2 should be 1", *((int *) collection_pop(collection)) == 1);
    mu_assert("3 should be 1", *((int *) collection_pop(collection)) == 0);
    mu_assert("4 should be 3", collection->length == 2);
    mu_assert("5 should be 0", *((int *) collection_pop(collection)) == 0);
    mu_assert("6 should be 1", *((int *) collection_pop(collection)) == 1);
    mu_assert("7 should be 1", collection->length == 0);
    mu_assert("8 should be 1", collection_pop(collection) == NULL);
    mu_assert("9 should be 0", collection->length == 0);
    return NULL;
}

char *utest_collection_is_empty()
{
    return NULL; 
}

char *utest_collection_destroy()
{
    CollectionPointer collection = collection_p_init(0);
    mu_assert("should succeed", SUCCESS == collection_destroy(collection));
    CollectionPointer collection2 = collection_p_init(7);
    mu_assert("should succeed", SUCCESS == collection_destroy(collection2));
    collection2 = collection_p_init(7);
    *(collection2->head + 3) = NULL;
    mu_assert("should succeed", SUCCESS == collection_destroy(collection2));
    return NULL;
}

char *test_collection() {
    mu_message(UNIT, "collection_empty\n");
    mu_run_utest(utest_collection_empty);
    mu_message(UNIT, "collection_init\n");
    mu_run_utest(utest_collection_init);
    mu_message(UNIT, "collection_push\n");
    mu_run_utest(utest_collection_push);
    mu_message(UNIT, "collection_get\n");
    mu_run_utest(utest_collection_get);
    mu_message(UNIT, "collection_destroy\n");
    mu_run_utest(utest_collection_destroy);
    mu_message(UNIT, "collection_pop\n");
    mu_run_utest(utest_collection_pop);
    mu_message(UNIT, "collection_is_empty\n");
    mu_run_utest(utest_collection_is_empty);
    mu_message(UNIT, "collection_equals\n");
    mu_run_utest(utest_collection_equals);
    mu_message(UNIT, "collection_set\n");
    mu_run_utest(utest_collection_set);
    mu_message(UNIT, "collection_remove\n");
    mu_run_utest(utest_collection_remove);
    return NULL;
}
