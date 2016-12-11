
#include <stdlib.h>
#include "test.h"

char *utest_make_dset()
{
    TreeVertexPointer t1 = make_dset(make_p_vertex(7));
    TreeVertexPointer t2 = make_p_tree_vertex(make_p_vertex(7));
    mu_assert("should be the same...", vertices_equal(t1->content, t2->content));
    mu_assert("rank should be 0", t1->rank == 0);
    return NULL;
}

char *utest_dset_find()
{
    TreeVertexPointer t1 = make_dset(make_p_vertex(7)); 
    TreeVertexPointer t2 = make_dset(make_p_vertex(1)); 
    TreeVertexPointer tr = dset_find(t1);
    mu_assert("should be 7", tr->content->label == 7);
    mu_assert("1 should be 1", dset_find(t2)->content->label == 1);
    dset_union(t1, t2);
    tr = dset_find(t1);
    mu_assert("1 should be 7", tr->content->label == 7);
    tr = dset_find(t2);
    mu_assert("2 should be 7", tr->content->label == 7);

    return NULL;
}

char *utest_dset_union()
{
    TreeVertexPointer t1, t2, t3, t4;
    t1 = make_dset(make_p_vertex(1));
    t2 = make_dset(make_p_vertex(2));
    t3 = make_dset(make_p_vertex(3));
    t4 = make_dset(make_p_vertex(4));
    dset_union(t1, t2);
    dset_union(t3, t4);
    mu_assert("should be 1", dset_find(t1)->content->label == 1); 
    mu_assert("should be 1", dset_find(t2)->content->label == 1); 
    mu_assert("should be 3", dset_find(t3)->content->label == 3); 
    mu_assert("should be 3", dset_find(t4)->content->label == 3); 
    dset_union(t1, t3);
    mu_assert("should be 1", dset_find(t1)->content->label == 1); 
    mu_assert("should be 1", dset_find(t2)->content->label == 1); 
    mu_assert("should be 1", dset_find(t3)->content->label == 1); 
    mu_assert("should be 1", dset_find(t4)->content->label == 1); 
    mu_assert("rank should be 2", t1->rank == 2);
    mu_assert("rank of t3 should be 1", t3->rank == 1);
    mu_assert("rank of t4 should be 0", t4->rank == 0);

    t1 = make_dset(make_p_vertex(1));
    t2 = make_dset(make_p_vertex(2));
    t3 = make_dset(make_p_vertex(3));
    dset_union(t1, t2);
    dset_union(t1, t3);
    mu_assert("should be 1", dset_find(t1)->content->label == 1); 
    mu_assert("should be 1", dset_find(t2)->content->label == 1); 
    mu_assert("should be 1", dset_find(t3)->content->label == 1); 
    mu_assert("rank should be 1", t1->rank == 1);


    return NULL;
}

char *test_disjointset() {
    mu_message(UNIT, "make_dset\n");
    mu_run_utest(utest_make_dset);
    mu_message(UNIT, "dset find\n");
    mu_run_utest(utest_dset_find);
    mu_message(UNIT, "dset union\n");
    mu_run_utest(utest_dset_union);
    return NULL;
}
