
#include <stdlib.h>
#include "test.h"
#include "collection.h"

char *utest_edgecollection_remove()
{
    EdgePointer a = edge_p_make_label(0, 1);
    EdgePointer b = edge_p_make_label(1, 2);
    EdgePointer c = edge_p_make_label(2, 3);
    EdgeCollection edgecollection = edgecollection_init(ARRAY_MIN_SIZE);
    edgecollection_push(edgecollection, a);
    edgecollection_push(edgecollection, b);
    edgecollection_push(edgecollection, c);
    edgecollection_remove(&edgecollection, b);

    mu_assert("should have a", edgecollection_contains_edge(edgecollection, a));
    mu_assert("should not have b", !edgecollection_contains_edge(edgecollection, b));
    mu_assert("should have c", edgecollection_contains_edge(edgecollection, c));
    edgecollection_remove(&edgecollection, c);
    mu_assert("should not have c", !edgecollection_contains_edge(edgecollection, c));
    mu_assert("should have a", edgecollection_contains_edge(edgecollection, a));
    edgecollection_remove(&edgecollection, a);
    mu_assert("should not have a", !edgecollection_contains_edge(edgecollection, a));
    edgecollection_push(edgecollection, a);
    edgecollection_push(edgecollection, b);
    edgecollection_push(edgecollection, c);
    mu_assert("should have a", edgecollection_contains_edge(edgecollection, a));
    mu_assert("should have b", edgecollection_contains_edge(edgecollection, b));
    mu_assert("should have c", edgecollection_contains_edge(edgecollection, c));
    edgecollection_remove(&edgecollection, a);
    mu_assert("should not have a", !edgecollection_contains_edge(edgecollection, a));
    mu_assert("should have b", edgecollection_contains_edge(edgecollection, b));
    mu_assert("should have c", edgecollection_contains_edge(edgecollection, c));

    return NULL;
}

char *utest_edgecollection_empty()
{
    EdgeCollection edgecollection = edgecollection_empty();
    mu_assert("should be null", edgecollection_is_empty(edgecollection));
    return NULL;
}

char *utest_edgecollection_init()
{
    EdgeCollection edgecollection = edgecollection_init(3);
    mu_assert("should have length 9", edgecollection.members->capacity == 3);
    mu_assert("should be empty", edgecollection_is_empty(edgecollection));
    mu_assert("should not contain any vertex", !edgecollection_contains_vertex(edgecollection, vertex_p_make(0)));
    mu_assert("should not contain any vertex", !edgecollection_contains_vertex(edgecollection, vertex_p_make(1)));
    return NULL;
}

char *utest_edgecollection_p_init()
{
    EdgeCollectionPointer edgecollection = edgecollection_p_init(3);
    mu_assert("should have length 9", edgecollection->members->capacity == 3);
    mu_assert("should be empty", edgecollection_is_empty(*edgecollection));
    mu_assert("should not contain any vertex", !edgecollection_contains_vertex(*edgecollection, vertex_p_make(0)));
    mu_assert("should not contain any vertex", !edgecollection_contains_vertex(*edgecollection, vertex_p_make(1)));
    return NULL;
}

char *utest_edgecollection_get()
{
    EdgeCollection edgecollection;
    edgecollection = edgecollection_init(4);
    mu_assert("should succeed", edgecollection_push(edgecollection, edge_p_make_label(0, 1)) == SUCCESS);
    EdgePointer edge = edgecollection_get(edgecollection, 0);
    mu_assert("should be 0", edge->first.label == 0);
    mu_assert("should be 1", edge->second.label == 1);
    edge = edgecollection_get(edgecollection, 1);
    mu_assert("should be null", !edge);
    edgecollection_destroy(edgecollection);
    return NULL;
}

char *utest_edgecollection_vertex_count()
{
    EdgeCollection edgecollection;
    edgecollection = edgecollection_init(4);
    edgecollection_push(edgecollection, edge_p_make_label(0, 1));
    edgecollection_push(edgecollection, edge_p_make_label(2, 1));
    edgecollection_push(edgecollection, edge_p_make_label(1, 2));
    edgecollection_push(edgecollection, edge_p_make_label(3, 4));
    mu_assert("should have 5 vertices", edgecollection_vertex_count(edgecollection) == 5);
    return NULL;
}

char *utest_edgecollection_vertices()
{
    EdgeCollection edgecollection;
    edgecollection = edgecollection_init(4);
    edgecollection_push(edgecollection, edge_p_make_label(0, 2));
    edgecollection_push(edgecollection, edge_p_make_label(2, 1));
    edgecollection_push(edgecollection, edge_p_make_label(1, 2));
    edgecollection_push(edgecollection, edge_p_make_label(3, 4));
    VertexCollection vertexcollection = edgecollection_vertices(edgecollection);
    mu_assert("should be", vertexcollection_get(vertexcollection, 0)->label == 0);
    mu_assert("should be", vertexcollection_get(vertexcollection, 1)->label == 2);
    mu_assert("should be", vertexcollection_get(vertexcollection, 2)->label == 1);
    mu_assert("should be", vertexcollection_get(vertexcollection, 3)->label == 3);
    mu_assert("should be", vertexcollection_get(vertexcollection, 4)->label == 4);
    return NULL;
}

char *utest_edgecollection_destroy()
{
    EdgeCollection edgecollection = edgecollection_init(2);
    mu_assert("should succeed", edgecollection_destroy(edgecollection) == SUCCESS);
    edgecollection = edgecollection_init(2);
    edgecollection.members->head = NULL;
    mu_assert("should succeed", edgecollection_destroy(edgecollection) == SUCCESS);
    return NULL;
}

char *utest_edgecollection_push()
{
    EdgeCollection edgecollection;
    edgecollection = edgecollection_init(4);
    EdgePointer a = edge_p_make_label(2, 3);
    EdgePointer b = edge_p_make_label(2, 4);
    mu_assert("should not contain vertex 2", !edgecollection_contains_vertex(edgecollection, vertex_p_make(2)));
    mu_assert("1 should succeed", edgecollection_push(edgecollection, a) == SUCCESS);
    mu_assert("should get 0 as index", edgecollection_index_of(edgecollection, *a) == 0);
    mu_assert("should be 2", edgecollection_get(edgecollection, 0)->first.label == 2);
    mu_assert("should contain vertex 2", edgecollection_contains_vertex(edgecollection, vertex_p_make(2)));
    mu_assert("should contain vertex 3", edgecollection_contains_vertex(edgecollection, vertex_p_make(3)));
    VertexCollection vertices = edgecollection_vertices(edgecollection);
    mu_assert("vertexcollection should also contain 2", vertexcollection_contains_label(vertices, 2));
    mu_assert("vertexcollection should also contain 3", vertexcollection_contains_label(vertices, 3));
    mu_assert("capacity still 4", edgecollection.members->capacity == 4);
    mu_assert("length 1", edgecollection.members->length == 1);
    mu_assert("1 should succeed", edgecollection_push(edgecollection, b) == SUCCESS);
    mu_assert("b should get 1 as index", edgecollection_index_of(edgecollection, *b) == 1);
    return NULL;
}

char *utest_edgecollection_is_empty()
{
    EdgeCollection edgecollection = edgecollection_empty();
    mu_assert("should be empty", edgecollection_is_empty(edgecollection));
    return NULL;
}

char *utest_edgecollection_equals()
{
    EdgeCollection edgecollection, edgecollection2;
    edgecollection = edgecollection_init(5);
    edgecollection2 = edgecollection_init(5);
    edgecollection_push(edgecollection, edge_p_make_label(0, 2));
    edgecollection_push(edgecollection, edge_p_make_label(2, 1));
    edgecollection_push(edgecollection, edge_p_make_label(1, 2));
    edgecollection_push(edgecollection, edge_p_make_label(3, 4));
    edgecollection_push(edgecollection2, edge_p_make_label(0, 2));
    edgecollection_push(edgecollection2, edge_p_make_label(2, 1));
    edgecollection_push(edgecollection2, edge_p_make_label(1, 2));
    edgecollection_push(edgecollection2, edge_p_make_label(3, 4));
    mu_assert("should equal", edgecollection_equals(edgecollection, edgecollection2));
    edgecollection_push(edgecollection2, edge_p_make_label(5, 6));
    mu_assert("should not equal", !edgecollection_equals(edgecollection, edgecollection2));
    edgecollection_push(edgecollection, edge_p_make_label(5, 6));
    mu_assert("should equal", edgecollection_equals(edgecollection, edgecollection2));
    edgecollection.members->capacity = 10;
    mu_assert("should not equal", !edgecollection_equals(edgecollection, edgecollection2));
    return NULL;
}

char *utest_edgecollection_is_super()
{
    EdgeCollection edgecollection, edgecollection2;
    edgecollection = edgecollection_init(5);
    edgecollection2 = edgecollection_init(5);
    edgecollection_push(edgecollection, edge_p_make_label(0, 2));
    edgecollection_push(edgecollection, edge_p_make_label(2, 1));
    edgecollection_push(edgecollection, edge_p_make_label(1, 2));
    edgecollection_push(edgecollection, edge_p_make_label(3, 4));
    edgecollection_push(edgecollection2, edge_p_make_label(0, 2));
    edgecollection_push(edgecollection2, edge_p_make_label(2, 1));
    edgecollection_push(edgecollection2, edge_p_make_label(1, 2));
    edgecollection_push(edgecollection2, edge_p_make_label(3, 4));
    mu_assert("1: should be super", edgecollection_is_super(edgecollection, edgecollection2));
    edgecollection_push(edgecollection2, edge_p_make_label(5, 6));
    mu_assert("2: should be super", edgecollection_is_super(edgecollection2, edgecollection));
    mu_assert("should not be super", !edgecollection_is_super(edgecollection, edgecollection2));
    mu_assert("3: should be super", edgecollection_is_super(edgecollection_empty(), edgecollection_empty()));
    mu_assert("4: should be super", edgecollection_is_super(edgecollection, edgecollection_empty()));
    return NULL;
}

char *utest_edgecollection_is_sub()
{
    EdgeCollection edgecollection, edgecollection2;
    edgecollection = edgecollection_init(5);
    edgecollection2 = edgecollection_init(5);
    edgecollection_push(edgecollection, edge_p_make_label(0, 2));
    edgecollection_push(edgecollection, edge_p_make_label(2, 1));
    edgecollection_push(edgecollection, edge_p_make_label(1, 2));
    edgecollection_push(edgecollection, edge_p_make_label(3, 4));
    edgecollection_push(edgecollection2, edge_p_make_label(0, 2));
    edgecollection_push(edgecollection2, edge_p_make_label(2, 1));
    edgecollection_push(edgecollection2, edge_p_make_label(1, 2));
    edgecollection_push(edgecollection2, edge_p_make_label(3, 4));
    mu_assert("1: should be sub", edgecollection_is_sub(edgecollection, edgecollection2));
    edgecollection_push(edgecollection2, edge_p_make_label(5, 6));
    mu_assert("2: should be sub", edgecollection_is_sub(edgecollection, edgecollection2));
    mu_assert("should not be super", !edgecollection_is_sub(edgecollection2, edgecollection));
    mu_assert("3: should be sub", edgecollection_is_sub(edgecollection_empty(), edgecollection_empty()));
    mu_assert("4: should be sub", !edgecollection_is_sub(edgecollection, edgecollection_empty()));
    mu_assert("5: should be sub", edgecollection_is_sub(edgecollection_empty(), edgecollection));
    return NULL;
}

char *utest_edgecollection_complement()
{
    EdgeCollection edgecollection_a = edgecollection_init(4);
    EdgeCollection edgecollection_b = edgecollection_init(4);
    edgecollection_push(edgecollection_a, edge_p_make_label(0, 1));
    edgecollection_push(edgecollection_a, edge_p_make_label(1, 2));
    edgecollection_push(edgecollection_a, edge_p_make_label(2, 3));
    edgecollection_push(edgecollection_b, edge_p_make_label(1, 2));
    EdgeCollection edgecollection_c, edgecollection_d;
    edgecollection_c = edgecollection_init(4);
    edgecollection_d = edgecollection_init(4);
    edgecollection_complement(edgecollection_a, edgecollection_b, &edgecollection_c);
    edgecollection_complement(edgecollection_b, edgecollection_a, &edgecollection_d);
    mu_assert("should have length 4", edgecollection_c.members->capacity == 4);
    mu_assert("should have 2 elements", edgecollection_c.members->length == 2);
    mu_assert("and should be these edges", edgecollection_get(edgecollection_c, 0)->first.label == 0);
    mu_assert("and should be these edges", edgecollection_get(edgecollection_c, 0)->second.label == 1);
    mu_assert("and should be these edges", edgecollection_get(edgecollection_c, 1)->first.label == 2);
    mu_assert("and should be these edges", edgecollection_get(edgecollection_c, 1)->second.label == 3);
    mu_assert("should have length 4", edgecollection_d.members->capacity == 4);
    mu_assert("should be empty", edgecollection_d.members->length == 0);
    edgecollection_destroy(edgecollection_a);
    edgecollection_destroy(edgecollection_b);
    edgecollection_destroy(edgecollection_c);
    edgecollection_a = edgecollection_init(4);
    edgecollection_b = edgecollection_init(4);
    edgecollection_c = edgecollection_init(4);
    edgecollection_complement(edgecollection_a, edgecollection_b, &edgecollection_c);
    mu_assert("should be empty", edgecollection_is_empty(edgecollection_c));
    edgecollection_destroy(edgecollection_a);
    edgecollection_destroy(edgecollection_b);
    edgecollection_destroy(edgecollection_c);
    edgecollection_a = edgecollection_init(4);
    edgecollection_b = edgecollection_init(4);
    edgecollection_c = edgecollection_init(4);
    edgecollection_push(edgecollection_a, edge_p_make_label(1, 3));
    edgecollection_push(edgecollection_a, edge_p_make_label(3, 2));
    edgecollection_push(edgecollection_a, edge_p_make_label(2, 1));
    edgecollection_push(edgecollection_b, edge_p_make_label(1, 3));
    edgecollection_complement(edgecollection_b, edgecollection_a, &edgecollection_c);
    mu_assert("should be empty", edgecollection_is_empty(edgecollection_c));

    return NULL;
}

char *utest_edgecollection_symmetric_difference()
{
    EdgeCollection graph = edgecollection_init(8);
    EdgeCollection matching = edgecollection_init(8);
    EdgeCollection path = edgecollection_init(8);
    edgecollection_push(graph, edge_p_make_label(0, 1));
    edgecollection_push(graph, edge_p_make_label(1, 2));
    edgecollection_push(graph, edge_p_make_label(2, 3));
    edgecollection_push(graph, edge_p_make_label(3, 4));
    edgecollection_push(graph, edge_p_make_label(2, 5));
    edgecollection_push(graph, edge_p_make_label(2, 6));
    edgecollection_push(graph, edge_p_make_label(6, 7));
    mu_assert("should not be a matching", !is_matching(graph));
    edgecollection_push(matching, edge_p_make_label(0, 1));
    edgecollection_push(matching, edge_p_make_label(2, 6));
    edgecollection_push(matching, edge_p_make_label(3, 4));
    mu_assert("should be amatching", is_matching(matching));
    edgecollection_push(path, edge_p_make_label(2, 5));
    edgecollection_push(path, edge_p_make_label(2, 6));
    edgecollection_push(path, edge_p_make_label(6, 7));
    EdgeCollection matching_augment = edgecollection_init(8);
    mu_assert("should succeed", edgecollection_symmetric_difference(matching, path, &matching_augment));
    mu_assert("should be amatching", is_matching(matching_augment));
    mu_assert("should be of one larger size", matching_augment.members->length == matching.members->length + 1);
    mu_assert("should contain this edge",
            edgecollection_contains_edge(matching_augment, edge_p_make_label(6, 7)));
    mu_assert("should contain this edge", 
            edgecollection_contains_edge(matching_augment, edge_p_make_label(2, 5)));
    mu_assert("should contain this edge", 
            edgecollection_contains_edge(matching_augment, edge_p_make_label(3, 4)));
    mu_assert("should contain this edge", 
            edgecollection_contains_edge(matching_augment, edge_p_make_label(0, 1)));

    return NULL;
}


char *utest_edgecollection_union()
{
    EdgeCollection edgecollection_a = edgecollection_init(4);
    EdgeCollection edgecollection_b = edgecollection_init(4);
    edgecollection_push(edgecollection_a, edge_p_make_label(0, 1));
    edgecollection_push(edgecollection_a, edge_p_make_label(1, 2));
    edgecollection_push(edgecollection_a, edge_p_make_label(2, 3));
    edgecollection_push(edgecollection_b, edge_p_make_label(1, 2));
    EdgeCollection edgecollection_c;
    edgecollection_c = edgecollection_union(edgecollection_a, edgecollection_b);
    mu_assert("should have capacity 8", edgecollection_c.members->capacity == 8);
    mu_assert("should have 3 elements", edgecollection_c.members->length == 3);
    mu_assert("and should be these edges", edgecollection_get(edgecollection_c, 0)->first.label == 0);
    mu_assert("and should be these edges", edgecollection_get(edgecollection_c, 0)->second.label == 1);
    mu_assert("and should be these edges", edgecollection_get(edgecollection_c, 1)->first.label == 1);
    mu_assert("and should be these edges", edgecollection_get(edgecollection_c, 1)->second.label == 2);
    mu_assert("and should be these edges", edgecollection_get(edgecollection_c, 2)->first.label == 2);
    mu_assert("and should be these edges", edgecollection_get(edgecollection_c, 2)->second.label == 3);
    edgecollection_destroy(edgecollection_a);
    edgecollection_destroy(edgecollection_b);
    edgecollection_destroy(edgecollection_c);
    edgecollection_a = edgecollection_init(4);
    edgecollection_b = edgecollection_init(4);
    edgecollection_c = edgecollection_init(4);
    edgecollection_complement(edgecollection_a, edgecollection_b, &edgecollection_c);
    mu_assert("should be empty", edgecollection_is_empty(edgecollection_c));
    edgecollection_destroy(edgecollection_a);
    edgecollection_destroy(edgecollection_b);
    edgecollection_destroy(edgecollection_c);
    return NULL;
}

char *utest_edgecollection_contains_edge()
{
    EdgeCollection edgecollection = edgecollection_init(3);
    EdgePointer a = edge_p_make_label(0, 1);
    EdgePointer b = edge_p_make_label(0, 2);
    EdgePointer c = edge_p_make_label(1, 2);
    EdgePointer d = edge_p_make_label(0, 3);
    edgecollection_push(edgecollection, a);
    edgecollection_push(edgecollection, b);
    edgecollection_push(edgecollection, c);
    mu_assert("1 should have this edge", edgecollection_contains_edge(edgecollection, a));
    mu_assert("2 should have this edge", edgecollection_contains_edge(edgecollection, b));
    mu_assert("3 should have this edge", edgecollection_contains_edge(edgecollection, c));
    mu_assert("4 should not be able to add this edge", edgecollection_push(edgecollection, d) == SUCCESS);
    mu_assert("3 should have this edge", !edgecollection_contains_edge(edgecollection, edge_p_make_label(0, 5)));
    mu_assert("3 should have this edge", edgecollection_contains_edge(edgecollection, edge_p_make_label(0, 3)));
    edgecollection_destroy(edgecollection);
    return NULL;
}

char *utest_edgecollection_contains_vertex()
{
    EdgeCollection edgecollection;
    edgecollection = edgecollection_init(4);
    edgecollection_push(edgecollection, edge_p_make_label(0, 2));
    edgecollection_push(edgecollection, edge_p_make_label(2, 1));
    edgecollection_push(edgecollection, edge_p_make_label(1, 2));
    edgecollection_push(edgecollection, edge_p_make_label(3, 4));
    mu_assert("should contain", edgecollection_contains_vertex(edgecollection, vertex_p_make(0)));
    mu_assert("should contain", edgecollection_contains_vertex(edgecollection, vertex_p_make(1)));
    mu_assert("should contain", edgecollection_contains_vertex(edgecollection, vertex_p_make(2)));
    mu_assert("should contain", edgecollection_contains_vertex(edgecollection, vertex_p_make(3)));
    mu_assert("should contain", edgecollection_contains_vertex(edgecollection, vertex_p_make(4)));
    return NULL;
}

char *utest_edgecollection_covered_by()
{
    EdgeCollection edgecollection = edgecollection_init(5);
    EdgePointer a = edge_p_make_label(0, 1);
    EdgePointer b = edge_p_make_label(1, 2);
    EdgePointer c = edge_p_make_label(2, 3);
    EdgePointer d = edge_p_make_label(1, 2);
    EdgePointer e = edge_p_make_label(3, 4);
    edgecollection_push(edgecollection, a);
    edgecollection_push(edgecollection, b);
    edgecollection_push(edgecollection, c);
    edgecollection_push(edgecollection, d);
    edgecollection_push(edgecollection, e);
    EdgePointer ret = malloc(sizeof(Edge));
    edgecollection_covered_by(edgecollection, vertex_p_make(1), &ret);
    mu_assert("should be", edge_equals(ret, edge_p_make_label(0, 1)));
    edgecollection_covered_by(edgecollection, vertex_p_make(2), &ret);
    mu_assert("should be", edge_equals(ret, edge_p_make_label(1, 2)));
    edgecollection_covered_by(edgecollection, vertex_p_make(3), &ret);
    mu_assert("should be", edge_equals(ret, edge_p_make_label(2, 3)));
    mu_assert("should succeed", SUCCESS == edgecollection_covered_by(edgecollection, vertex_p_make(4), &ret));
    mu_assert("should be", edge_equals(ret, edge_p_make_label(3, 4)));
    return NULL;
}

char *utest_is_matching() 
{
    EdgeCollection edgecollection = edgecollection_init(4);
    edgecollection_push(edgecollection, edge_p_make_label(0, 1));
    edgecollection_push(edgecollection, edge_p_make_label(2, 3));
    mu_assert("1: should be a matching", is_matching(edgecollection) == true); 

    edgecollection_push(edgecollection, edge_p_make_label(0, 1));
    edgecollection_push(edgecollection, edge_p_make_label(1, 3));
    mu_assert("2: should not be a matching", !is_matching(edgecollection)); 

    edgecollection_push(edgecollection, edge_p_make_label(0, 1));
    edgecollection_push(edgecollection, edge_p_make_label(2, 0));
    mu_assert("should not be a matching", !is_matching(edgecollection)); 

    edgecollection_push(edgecollection, edge_p_make_label(0, 1));
    edgecollection_push(edgecollection, edge_p_make_label(0, 1));
    mu_assert("should not be a matching", !is_matching(edgecollection)); 

    edgecollection_destroy(edgecollection);
    return NULL;
}

char *test_edgecollection() {
    mu_message(UNIT, "edgecollection_empty\n");
    mu_run_utest(utest_edgecollection_empty);
    mu_message(UNIT, "edgecollection_is_empty\n");
    mu_run_utest(utest_edgecollection_is_empty);
    mu_message(UNIT, "edgecollection_equals\n");
    mu_run_utest(utest_edgecollection_equals);
    mu_message(UNIT, "edgecollection_vertex_count\n");
    mu_run_utest(utest_edgecollection_vertex_count);
    mu_message(UNIT, "edgecollection_vertices\n");
    mu_run_utest(utest_edgecollection_vertices);
    mu_message(UNIT, "edgecollection_push\n");
    mu_run_utest(utest_edgecollection_push);
    mu_message(UNIT, "edgecollection_init\n");
    mu_run_utest(utest_edgecollection_init);
    mu_message(UNIT, "edgecollection_complement\n");
    mu_run_utest(utest_edgecollection_complement);
    mu_message(UNIT, "edgecollection_union\n");
    mu_run_utest(utest_edgecollection_union);
    mu_message(UNIT, "symmetric difference\n");
    mu_run_utest(utest_edgecollection_symmetric_difference);
    mu_message(UNIT, "edgecollection_destroy\n");
    mu_run_utest(utest_edgecollection_destroy);
    mu_message(UNIT, "edgecollection_get\n");
    mu_run_utest(utest_edgecollection_get);
    mu_message(UNIT, "edgecollection_contains_edge\n");
    mu_run_utest(utest_edgecollection_contains_edge);
    mu_message(UNIT, "Covered_by\n");
    mu_run_utest(utest_edgecollection_covered_by);
    mu_message(UNIT, "is_super\n");
    mu_run_utest(utest_edgecollection_is_super);
    mu_message(UNIT, "is_sub\n");
    mu_run_utest(utest_edgecollection_is_sub);
    mu_message(UNIT, "contains_vertex\n");
    mu_run_utest(utest_edgecollection_contains_vertex);
    mu_message(UNIT, "is_matching\n");
    mu_run_utest(utest_is_matching);
    mu_message(UNIT, "edgecollection_remove\n");
    mu_run_utest(utest_edgecollection_remove);
    return NULL;
}
