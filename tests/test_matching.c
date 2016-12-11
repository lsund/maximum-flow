

#include <stdlib.h>
#include "test.h"
/* char *utest_matching_is_perfect() */
/* { */
/*     EdgeSet edgeset = edgeset_init(9); */

/*     edgeset_push(edgeset, edge_p_make_label(1, 2)); */
/*     edgeset_push(edgeset, edge_p_make_label(2, 4)); */
/*     edgeset_push(edgeset, edge_p_make_label(3, 4)); */
/*     edgeset_push(edgeset, edge_p_make_label(1, 3)); */

/*     edgeset_push(edgeset, edge_p_make_label(1, 5)); */
/*     edgeset_push(edgeset, edge_p_make_label(2, 6)); */
/*     edgeset_push(edgeset, edge_p_make_label(4, 8)); */
/*     edgeset_push(edgeset, edge_p_make_label(3, 7)); */

/*     edgeset_push(edgeset, edge_p_make_label(5, 6)); */
/*     edgeset_push(edgeset, edge_p_make_label(5, 7)); */
/*     edgeset_push(edgeset, edge_p_make_label(6, 8)); */
/*     edgeset_push(edgeset, edge_p_make_label(7, 8)); */

/*     EdgeSet matching = edgeset_init(9); */

/*     mu_assert("1 should work", edgeset_push(matching, edge_p_make_label(1, 5)) == SUCCESS); */
/*     mu_assert("2 should work", edgeset_push(matching, edge_p_make_label(2, 6)) == SUCCESS); */
/*     mu_assert("3 should work", edgeset_push(matching, edge_p_make_label(4, 8)) == SUCCESS); */
/*     mu_assert("should be a matching", is_matching(matching)); */ 
/*     mu_assert("1 should not be a perfect matching", !matching_is_perfect(matching, edgeset.vertices)); */
/*     mu_assert("should work", edgeset_push(matching, edge_p_make_label(3, 7))); */
/*     mu_assert("should now be a perfect matching", matching_is_perfect(matching, edgeset.vertices)); */
/*     edgeset_destroy(matching); */

    /* matching = edgeset_init(8); */
    /* edgeset_push(matching, edge_p_make_label(5, 6)); */
    /* edgeset_push(matching, edge_p_make_label(5, 7)); */
    /* edgeset_push(matching, edge_p_make_label(6, 8)); */
    /* edgeset_push(matching, edge_p_make_label(7, 8)); */
    /* mu_assert("should not be a matching", !is_matching(matching)); */ 
    /* mu_assert("or a perfect matching", !matching_is_perfect(matching, edgeset.vertices)); */

    /* edgeset_destroy(edgeset); */
    /* edgeset_destroy(matching); */


    /* return NULL; */
/* } */

char *utest_matching_exposing()
{
    EdgeSet edgeset = edgeset_init(3);
    edgeset_push(edgeset, edge_p_make_label(0, 1));
    edgeset_push(edgeset, edge_p_make_label(0, 2));
    edgeset_push(edgeset, edge_p_make_label(1, 2));
    mu_assert("should be true", matching_exposing(vertex_p_make(4), edgeset));
    mu_assert("should be false", !matching_exposing(vertex_p_make(2), edgeset));
    mu_assert("should be false", !matching_exposing(vertex_p_make(1), edgeset));

    edgeset_destroy(edgeset);
    return NULL;
}

char *utest_is_matching() 
{
    EdgeSet edgeset = edgeset_init(4);
    edgeset_push(edgeset, edge_p_make_label(0, 1));
    edgeset_push(edgeset, edge_p_make_label(2, 3));
    mu_assert("1: should be a matching", is_matching(edgeset) == true); 

    edgeset_push(edgeset, edge_p_make_label(0, 1));
    edgeset_push(edgeset, edge_p_make_label(1, 3));
    mu_assert("2: should not be a matching", !is_matching(edgeset)); 

    edgeset_push(edgeset, edge_p_make_label(0, 1));
    edgeset_push(edgeset, edge_p_make_label(2, 0));
    mu_assert("should not be a matching", !is_matching(edgeset)); 

    edgeset_push(edgeset, edge_p_make_label(0, 1));
    edgeset_push(edgeset, edge_p_make_label(0, 1));
    mu_assert("should not be a matching", !is_matching(edgeset)); 

    edgeset_destroy(edgeset);
    return NULL;
}

char *utest_matching_perfect_odd_path()
{
    EdgeSet edgeset = edgeset_init(4);
    edgeset_push(edgeset, edge_p_make_label(1,3));
    edgeset_push(edgeset, edge_p_make_label(3,2));
    edgeset_push(edgeset, edge_p_make_label(2,1));
    EdgeSet ret = edgeset_init(4);
    matching_perfect_odd_path(edgeset, vertex_p_make(2), &ret);
    mu_assert("should have 1 vertex", ret.set->length == 1);
    return NULL;
}

char *test_matching() {
    mu_message(UNIT, "is_matching\n");
    mu_run_utest(utest_is_matching);
    /* mu_message(UNIT, "matching_is_perfect\n"); */
    /* mu_run_utest(utest_matching_is_perfect); */
    mu_message(UNIT, "matching_exposing\n");
    mu_run_utest(utest_matching_exposing);
    mu_message(UNIT, "matching_perfect_odd_path\n");
    mu_run_utest(utest_matching_perfect_odd_path);
    return NULL;
}

