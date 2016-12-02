

#include <stdlib.h>
#include "test.h"

char *test_edges_equal()
{
    Edge a = make_edge(make_vertex(0), make_vertex(0));
    Edge b = make_edge(make_vertex(0), make_vertex(0));
    Edge c = make_edge(make_vertex(0), make_vertex(1));
    Edge d = make_edge(make_vertex(1), make_vertex(0));
    mu_assert("should be equal", edges_equal(a, b));
    mu_assert("should not be equal", !edges_equal(a, c));
    mu_assert("2 should be equal", edges_equal(c, d));
    mu_assert("2 should not be equal", !edges_equal(c, a));
    return NULL;
}

char *test_edge_to_bitpos()
{
    /* int nvertices = 3; */
    /* Edge a = make_edge(make_vertex(0), make_vertex(0)); */
    /* Edge b = make_edge(make_vertex(0), make_vertex(1)); */
    /* Edge c = make_edge(make_vertex(0), make_vertex(2)); */
    /* Edge d = make_edge(make_vertex(0), make_vertex(3)); */
    /* Edge e = make_edge(make_vertex(1), make_vertex(0)); */
    /* Edge f = make_edge(make_vertex(1), make_vertex(1)); */
    return NULL;
}

char *test_edge() {
    mu_message(UNIT, "edges_equal\n");
    mu_run_utest(test_edges_equal);
    return NULL;
}
