#include "test.h"

char *utest_stree_singleton()
{
    STreePointer tree = stree_singleton_label(3);
    mu_assert("label should be 3", tree->vertex->label == 3);
    mu_assert("should have no parent", tree->parent == NULL);
    return NULL;
}

char *utest_stree_merge()
{
    STreePointer tree1 = stree_singleton_label(1);
    STreePointer tree2 = stree_singleton_label(2);
    STreePointer tree3 = stree_singleton_label(3);
    stree_merge(tree1, tree2);
    stree_merge(tree1, tree3);

    STreePointer tree4 = stree_singleton_label(4);
    STreePointer tree5 = stree_singleton_label(5);
    STreePointer tree6 = stree_singleton_label(6);
    stree_merge(tree4, tree5);
    stree_merge(tree4, tree6);

    stree_merge(tree2, tree4);

    mu_assert("2 should have 1 as parent", tree2->parent->vertex->label == 1);
    mu_assert("3 should have 1 as parent", tree3->parent->vertex->label == 1);
    mu_assert("4 should have 2 as parent", tree4->parent->vertex->label == 2);
    mu_assert("5 should have 4 as parent", tree5->parent->vertex->label == 4);
    mu_assert("1 should have no parent", tree1->parent == NULL);

    return NULL;
}

char *test_tree_simple()
{
    mu_message(UNIT, "stree_singleton\n");
    mu_run_utest(utest_stree_singleton);
    mu_message(UNIT, "stree_merge\n");
    mu_run_utest(utest_stree_merge);
    return NULL;
}
