
#include <stdlib.h>
#include "test.h"

char *utest_array_init()
{
    Array array;
    array = array_init(7);
    mu_assert("should not be null", array.head != NULL);
    mu_assert("should be 0", array.length == 0);
    mu_assert("should be init length", array.capacity == 7);
    return NULL;
}

char *utest_array_empty() 
{
    Array array;
    array = array_empty();
    mu_assert("should be empty", array.head == NULL);
    mu_assert("should be empty", array.capacity == 0);
    mu_assert("should be empty", array.length == 0);
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
    /* mu_assert("should not be able to add the same element", array_push(array, a) == FAIL); */
    free(array);
    array =  array_p_empty(0);
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
    array = array_p_empty();
    array_push(array, &a);
    mu_assert("should be 1", array->length == 1);
    array_push(array, &b);
    array_push(array, &c);
    array_push(array, &d);
    mu_assert("should be 4", array->length == 4);
    mu_assert("should be 1", *((int *) array_get_last(array)) == 1);
    mu_assert("should be 1", *((int *) array_get_last(array)) == 1);
    array_pop(array);
    mu_assert("should be 0", *((int *) array_get_last(array)) == 0);
    mu_assert("should be 3", array->length == 3);
    array_pop(array);
    mu_assert("should be 0", *((int *) array_get_last(array)) == 0);
    array_pop(array);
    mu_assert("should be 1", *((int *) array_get_last(array)) == 1);
    mu_assert("should be 1", array->length == 1);
    array_pop(array);
    mu_assert("should be null", array_get_last(array) == 0);
    mu_assert("should be 0", array->length == 0);
    mu_assert("should be null", array_get_last(array) == 0);
    return NULL;
}

char *utest_is_array_empty() 
{
    ArrayPointer array;
    array = array_p_empty();
    mu_assert("should be successfull", array_is_empty(array) == true);
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

char *utest_array_get()
{
    Array array = array_init(60);
    mu_assert("should fail", array_get(&array, 60) == NULL);
    return NULL;
}

char *test_array() {
    mu_message(UNIT, "array_empty\n");
    mu_run_utest(utest_array_empty);
    mu_message(UNIT, "array_init\n");
    mu_run_utest(utest_array_init);
    mu_message(UNIT, "array_push\n");
    mu_run_utest(utest_array_push);
    mu_message(UNIT, "array_get\n");
    mu_run_utest(utest_array_get);
    mu_message(UNIT, "is_array_empty\n");
    mu_run_utest(utest_is_array_empty);
    mu_message(UNIT, "array_destroy\n");
    mu_run_utest(utest_array_destroy);
    mu_message(UNIT, "array_pop\n");
    mu_run_utest(utest_array_pop);
    return NULL;
}
