
#include <stdlib.h>
#include "test.h"

char *utest_disjointset_make()
{
    TreeVertexPointer t1 = disjointset_make(vertex_p_make(7));
    TreeVertexPointer t2 = make_p_tree_vertex(vertex_p_make(7));
    mu_assert("should be the same...", vertex_equals(*t1->content, *t2->content));
    mu_assert("rank should be 0", t1->rank == 0);
    return NULL;
}

char *utest_disjointset_find()
{
    TreeVertexPointer t1 = disjointset_make(vertex_p_make(7)); 
    TreeVertexPointer t2 = disjointset_make(vertex_p_make(1)); 
    TreeVertexPointer tr = disjointset_find(t1);
    mu_assert("should be 7", tr->content->label == 7);
    mu_assert("1 should be 1", disjointset_find(t2)->content->label == 1);
    disjointset_union(t1, t2);
    tr = disjointset_find(t1);
    mu_assert("1 should be 7", tr->content->label == 7);
    tr = disjointset_find(t2);
    mu_assert("2 should be 7", tr->content->label == 7);
    return NULL;
}

char *utest_disjointset_union()
{
    TreeVertexPointer t1, t2, t3, t4;
    t1 = disjointset_make(vertex_p_make(1));
    t2 = disjointset_make(vertex_p_make(2));
    t3 = disjointset_make(vertex_p_make(3));
    t4 = disjointset_make(vertex_p_make(4));
    disjointset_union(t1, t2);
    disjointset_union(t3, t4);
    mu_assert("should be 1", disjointset_find(t1)->content->label == 1); 
    mu_assert("should be 1", disjointset_find(t2)->content->label == 1); 
    mu_assert("should be 3", disjointset_find(t3)->content->label == 3); 
    mu_assert("should be 3", disjointset_find(t4)->content->label == 3); 
    disjointset_union(t1, t3);
    mu_assert("should be 1", disjointset_find(t1)->content->label == 1); 
    mu_assert("should be 1", disjointset_find(t2)->content->label == 1); 
    mu_assert("should be 1", disjointset_find(t3)->content->label == 1); 
    mu_assert("should be 1", disjointset_find(t4)->content->label == 1); 
    mu_assert("rank should be 2", t1->rank == 2);
    mu_assert("rank of t3 should be 1", t3->rank == 1);
    mu_assert("rank of t4 should be 0", t4->rank == 0);
    t1 = disjointset_make(vertex_p_make(1));
    t2 = disjointset_make(vertex_p_make(2));
    t3 = disjointset_make(vertex_p_make(3));
    disjointset_union(t1, t2);
    disjointset_union(t1, t3);
    mu_assert("should be 1", disjointset_find(t1)->content->label == 1); 
    mu_assert("should be 1", disjointset_find(t2)->content->label == 1); 
    mu_assert("should be 1", disjointset_find(t3)->content->label == 1); 
    mu_assert("rank should be 1", t1->rank == 1);
    return NULL;
}

char *test_disjointset() {
    mu_message(UNIT, "disjointset_make\n");
    mu_run_utest(utest_disjointset_make);
    mu_message(UNIT, "dset find\n");
    mu_run_utest(utest_disjointset_find);
    mu_message(UNIT, "dset union\n");
    mu_run_utest(utest_disjointset_union);
    return NULL;
}
