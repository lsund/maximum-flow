
#include <stdlib.h>
#include "test.h"

char *utest_init_array()
{
    Array array;
    array = init_array(7);
    mu_assert("should not be null", array.head != NULL);
    mu_assert("should be 0", array.nelements == 0);
    mu_assert("should be init length", array.length == 7);
    return NULL;
}

char *utest_empty_array() 
{
    Array array;
    array = empty_array();
    mu_assert("should be empty", array.head == NULL);
    mu_assert("should be empty", array.length == 0);
    mu_assert("should be empty", array.nelements == 0);
    return NULL;
}

char *utest_push_element()
{
    int *a = malloc(sizeof(int));
    int *b = malloc(sizeof(int));
    int *c = malloc(sizeof(int));
    ArrayPointer array = malloc(sizeof(Array));
    *a = 1;
    *b = 2;
    *c = 3;
    *array = init_array(2);
    mu_assert("1.should work", push_element(array, a) == SUCCESS);
    mu_assert("2.should work", push_element(array, b) == SUCCESS);
    mu_assert("3.should work", push_element(array, c) == SUCCESS);
    mu_assert("size should have doubled", array->length == 4); 
    mu_assert("elements should have increased ", array->nelements == 3); 
    mu_assert("should have the correct elements ", *((int *) get_element(array, 0)) == 1); 
    mu_assert("should have the correct elements ", *((int *) get_element(array, 1)) == 2); 
    mu_assert("should have the correct elements ", *((int *) get_element(array, 2)) == 3); 
    /* mu_assert("should not be able to add the same element", push_element(array, a) == FAIL); */
    free(array);
    array =  empty_p_array(0);
    mu_assert("4. should work", push_element(array, a) == SUCCESS);
    mu_assert("size should have been initialized", array->length == 4); 
    free(a);
    free(b);
    free(c);
    free(array);
    return NULL;
}

char *utest_pop_element()
{
    int a, b, c, d;
    a = 1;
    b = 0;
    c = 0;
    d = 1;
    ArrayPointer array;
    array = empty_p_array();
    push_element(array, &a);
    mu_assert("should be 1", array->nelements == 1);
    push_element(array, &b);
    push_element(array, &c);
    push_element(array, &d);
    mu_assert("should be 4", array->nelements == 4);
    mu_assert("should be 1", *((int *) get_last_element(array)) == 1);
    mu_assert("should be 1", *((int *) get_last_element(array)) == 1);
    pop_element(array);
    mu_assert("should be 0", *((int *) get_last_element(array)) == 0);
    mu_assert("should be 3", array->nelements == 3);
    pop_element(array);
    mu_assert("should be 0", *((int *) get_last_element(array)) == 0);
    pop_element(array);
    mu_assert("should be 1", *((int *) get_last_element(array)) == 1);
    mu_assert("should be 1", array->nelements == 1);
    pop_element(array);
    mu_assert("should be null", get_last_element(array) == 0);
    mu_assert("should be 0", array->nelements == 0);
    mu_assert("should be null", get_last_element(array) == 0);
    return NULL;
}

char *utest_is_empty_array() 
{
    ArrayPointer array;
    array = empty_p_array();
    mu_assert("should be successfull", array_is_empty(array) == true);
    return NULL;
}

char *utest_destroy_array()
{
    ArrayPointer array = init_p_array(0);
    mu_assert("should succeed", SUCCESS == destroy_array(array));
    ArrayPointer array2 = init_p_array(7);
    mu_assert("should succeed", SUCCESS == destroy_array(array2));
    array2 = init_p_array(7);
    *(array2->head + 3) = NULL;
    mu_assert("should succeed", SUCCESS == destroy_array(array2));
    return NULL;
}

char *utest_get_element()
{
    Array array = init_array(60);
    mu_assert("should fail", get_element(&array, 60) == NULL);
    return NULL;
}

char *test_array() {
    mu_message(UNIT, "empty_array\n");
    mu_run_utest(utest_empty_array);
    mu_message(UNIT, "init_array\n");
    mu_run_utest(utest_init_array);
    mu_message(UNIT, "push_element\n");
    mu_run_utest(utest_push_element);
    mu_message(UNIT, "get_element\n");
    mu_run_utest(utest_get_element);
    mu_message(UNIT, "is_empty_array\n");
    mu_run_utest(utest_is_empty_array);
    mu_message(UNIT, "destroy_array\n");
    mu_run_utest(utest_destroy_array);
    mu_message(UNIT, "pop_element\n");
    mu_run_utest(utest_pop_element);
    return NULL;
}
