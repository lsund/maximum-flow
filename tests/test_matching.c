

#include <stdlib.h>
#include "test.h"
/* char *utest_is_perfect() */
/* { */
/*     EdgeSet edgeset = init_edgeset(9); */

/*     push_edge(edgeset, make_p_edge_label(1, 2)); */
/*     push_edge(edgeset, make_p_edge_label(2, 4)); */
/*     push_edge(edgeset, make_p_edge_label(3, 4)); */
/*     push_edge(edgeset, make_p_edge_label(1, 3)); */

/*     push_edge(edgeset, make_p_edge_label(1, 5)); */
/*     push_edge(edgeset, make_p_edge_label(2, 6)); */
/*     push_edge(edgeset, make_p_edge_label(4, 8)); */
/*     push_edge(edgeset, make_p_edge_label(3, 7)); */

/*     push_edge(edgeset, make_p_edge_label(5, 6)); */
/*     push_edge(edgeset, make_p_edge_label(5, 7)); */
/*     push_edge(edgeset, make_p_edge_label(6, 8)); */
/*     push_edge(edgeset, make_p_edge_label(7, 8)); */

/*     EdgeSet matching = init_edgeset(9); */

/*     mu_assert("1 should work", push_edge(matching, make_p_edge_label(1, 5)) == SUCCESS); */
/*     mu_assert("2 should work", push_edge(matching, make_p_edge_label(2, 6)) == SUCCESS); */
/*     mu_assert("3 should work", push_edge(matching, make_p_edge_label(4, 8)) == SUCCESS); */
/*     mu_assert("should be a matching", is_matching(matching)); */ 
/*     mu_assert("1 should not be a perfect matching", !is_perfect(matching, edgeset.vertices)); */
/*     mu_assert("should work", push_edge(matching, make_p_edge_label(3, 7))); */
/*     mu_assert("should now be a perfect matching", is_perfect(matching, edgeset.vertices)); */
/*     destroy_edgeset(matching); */

    /* matching = init_edgeset(8); */
    /* push_edge(matching, make_p_edge_label(5, 6)); */
    /* push_edge(matching, make_p_edge_label(5, 7)); */
    /* push_edge(matching, make_p_edge_label(6, 8)); */
    /* push_edge(matching, make_p_edge_label(7, 8)); */
    /* mu_assert("should not be a matching", !is_matching(matching)); */ 
    /* mu_assert("or a perfect matching", !is_perfect(matching, edgeset.vertices)); */

    /* destroy_edgeset(edgeset); */
    /* destroy_edgeset(matching); */


    /* return NULL; */
/* } */

char *utest_is_exposed()
{
    EdgeSet edgeset = init_edgeset(3);
    push_edge(edgeset, make_p_edge_label(0, 1));
    push_edge(edgeset, make_p_edge_label(0, 2));
    push_edge(edgeset, make_p_edge_label(1, 2));
    mu_assert("should be true", is_exposed(make_p_vertex(4), edgeset));
    mu_assert("should be false", !is_exposed(make_p_vertex(2), edgeset));
    mu_assert("should be false", !is_exposed(make_p_vertex(1), edgeset));

    destroy_edgeset(edgeset);
    return NULL;
}

char *utest_is_matching() 
{
    EdgeSet edgeset = init_edgeset(4);
    push_edge(edgeset, make_p_edge_label(0, 1));
    push_edge(edgeset, make_p_edge_label(2, 3));
    mu_assert("1: should be a matching", is_matching(edgeset) == true); 

    push_edge(edgeset, make_p_edge_label(0, 1));
    push_edge(edgeset, make_p_edge_label(1, 3));
    mu_assert("2: should not be a matching", !is_matching(edgeset)); 

    push_edge(edgeset, make_p_edge_label(0, 1));
    push_edge(edgeset, make_p_edge_label(2, 0));
    mu_assert("should not be a matching", !is_matching(edgeset)); 

    push_edge(edgeset, make_p_edge_label(0, 1));
    push_edge(edgeset, make_p_edge_label(0, 1));
    mu_assert("should not be a matching", !is_matching(edgeset)); 

    destroy_edgeset(edgeset);
    return NULL;
}

char *utest_perfect_matching_odd_path()
{
    EdgeSet edgeset = init_edgeset(4);
    push_edge(edgeset, make_p_edge_label(1,3));
    push_edge(edgeset, make_p_edge_label(3,2));
    push_edge(edgeset, make_p_edge_label(2,1));
    EdgeSet ret = init_edgeset(4);
    perfect_matching_odd_path(edgeset, make_p_vertex(2), &ret);
    mu_assert("should have 1 vertex", ret.set->nelements == 1);
    return NULL;
}

char *test_matching() {
    mu_message(UNIT, "is_matching\n");
    mu_run_utest(utest_is_matching);
    /* mu_message(UNIT, "is_perfect\n"); */
    /* mu_run_utest(utest_is_perfect); */
    mu_message(UNIT, "is_exposed\n");
    mu_run_utest(utest_is_exposed);
    mu_message(UNIT, "perfect_matching_odd_path\n");
    mu_run_utest(utest_perfect_matching_odd_path);
    return NULL;
}

