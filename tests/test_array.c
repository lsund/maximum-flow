
#include <stdlib.h>
#include "test.h"

char *utest_array_init()
{
    Array array;
    array = array_init(7);
    mu_assert("should not be null", array.head);
    mu_assert("should be 0", array.length == 0);
    mu_assert("should be init length", array.capacity == 7);
    return NULL;
}

char *utest_array_p_init()
{
    ArrayPointer array;
    array = array_p_init(7);
    mu_assert("should not be null", array);
    mu_assert("should not be null", array->head);
    mu_assert("should be 0", array->length == 0);
    mu_assert("should be init length", array->capacity == 7);
    return NULL;
}

char *utest_array_equals()
{
    ArrayPointer array_a = array_p_init(4);
    ArrayPointer array_b = array_p_init(4);
    mu_assert("should equal", array_equals(array_a, array_b));
    array_a->capacity = 5;
    mu_assert("1 should not equal", !array_equals(array_a, array_b));
    mu_assert("2 should not equal", !array_equals(array_b, array_a));
    array_b->length = 5;
    array_b->capacity = 5;
    mu_assert("3 should not equal", !array_equals(array_a, array_b));
    mu_assert("4 should not equal", !array_equals(array_b, array_a));
    array_a->length = 5;
    mu_assert("should equal", array_equals(array_a, array_b));
    mu_assert("should equal", array_equals(array_b, array_a));
    return NULL;
}

char *utest_array_get()
{
    int x = 3;
    int y = 2;
    int z = 1;
    ArrayPointer array_a = array_p_init(4);
    array_push(array_a, &x);
    array_push(array_a, &y);
    array_push(array_a, &z);
    mu_assert("should be 3", *((int *) array_get(array_a, 0)) == 3);
    mu_assert("should be 2", *((int *) array_get(array_a, 1)) == 2);
    mu_assert("should be 1", *((int *) array_get(array_a, 2)) == 1);
    return NULL;
}

char *utest_array_set()
{
    int x = 3;
    int y = 2;
    int z = 1;
    ArrayPointer array_a = array_p_init(4);
    array_push(array_a, &x);
    array_push(array_a, &y);
    array_push(array_a, &z);
    array_set(array_a, &x, 0);
    array_set(array_a, &x, 1);
    array_set(array_a, &x, 2);
    mu_assert("should be 3", *((int *) array_get(array_a, 0)) == 3);
    mu_assert("should be 2", *((int *) array_get(array_a, 1)) == 3);
    mu_assert("should be 1", *((int *) array_get(array_a, 2)) == 3);
    mu_assert("should still be 3", array_a->length == 3);
    mu_assert("should still be 4", array_a->capacity == 4);
    return NULL;
}

char *utest_array_push()
{
    int *a = malloc(sizeof(int));
    int *b = malloc(sizeof(int));
    int *c = malloc(sizeof(int));
    ArrayPointer array = malloc(sizeof(Array));
    *a = 1;
    *b = 2;
    *c = 3;
    *array = array_init(2);
    mu_assert("1.should work", array_push(array, a) == SUCCESS);
    mu_assert("2.should work", array_push(array, b) == SUCCESS);
    mu_assert("3.should work", array_push(array, c) == SUCCESS);
    mu_assert("size should have doubled", array->capacity == 4); 
    mu_assert("elements should have increased ", array->length == 3); 
    mu_assert("should have the correct elements ", *((int *) array_get(array, 0)) == 1); 
    mu_assert("should have the correct elements ", *((int *) array_get(array, 1)) == 2); 
    mu_assert("should have the correct elements ", *((int *) array_get(array, 2)) == 3); 
    free(array);
    array =  array_p_init(0);
    mu_assert("4. should work", array_push(array, a) == SUCCESS);
    mu_assert("size should have been initialized", array->capacity == 4); 
    free(a);
    free(b);
    free(c);
    free(array);
    return NULL;
}

char *utest_array_pop()
{
    int a, b, c, d;
    a = 1;
    b = 0;
    c = 0;
    d = 1;
    ArrayPointer array;
    array = array_p_init(0);
    array_push(array, &a);
    mu_assert("0 should be 1", array->length == 1);
    array_push(array, &b);
    array_push(array, &c);
    array_push(array, &d);
    mu_assert("1 should be 4", array->length == 4);
    mu_assert("2 should be 1", *((int *) array_pop(array)) == 1);
    mu_assert("3 should be 1", *((int *) array_pop(array)) == 0);
    mu_assert("4 should be 3", array->length == 2);
    mu_assert("5 should be 0", *((int *) array_pop(array)) == 0);
    mu_assert("6 should be 1", *((int *) array_pop(array)) == 1);
    mu_assert("7 should be 1", array->length == 0);
    mu_assert("8 should be 1", array_pop(array) == NULL);
    mu_assert("9 should be 0", array->length == 0);
    return NULL;
}

char *utest_array_destroy()
{
    ArrayPointer array = array_p_init(0);
    mu_assert("should succeed", SUCCESS == array_destroy(array));
    ArrayPointer array2 = array_p_init(7);
    mu_assert("should succeed", SUCCESS == array_destroy(array2));
    array2 = array_p_init(7);
    *(array2->head + 3) = NULL;
    mu_assert("should succeed", SUCCESS == array_destroy(array2));
    return NULL;
}

char *test_array() {
    mu_message(UNIT, "array_init\n");
    mu_run_utest(utest_array_init);
    mu_message(UNIT, "array_push\n");
    mu_run_utest(utest_array_push);
    mu_message(UNIT, "array_get\n");
    mu_run_utest(utest_array_get);
    mu_message(UNIT, "array_destroy\n");
    mu_run_utest(utest_array_destroy);
    mu_message(UNIT, "array_pop\n");
    mu_run_utest(utest_array_pop);
    mu_message(UNIT, "array_equals\n");
    mu_run_utest(utest_array_equals);
    mu_message(UNIT, "array_set\n");
    mu_run_utest(utest_array_set);
    return NULL;
}
