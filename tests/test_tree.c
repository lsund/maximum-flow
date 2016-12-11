
#include <stdlib.h>
#include "test.h"

char *utest_tree_singleton_label()
{
    Tree tree = tree_singleton_label(3, 10);
    mu_assert("label should be 3", tree.root->content->label == 3);
    mu_assert("contains should be initialized", tree.contains); 
    mu_assert("tree should contain vertex 3", *(tree.contains + 3)); 
    mu_assert("should not contain anything else", !*(tree.contains + 1)); 
    mu_assert("should not contain anything else", !*(tree.contains + 2)); 
    mu_assert("max size should be set", tree.maxsize == 10); 
    return NULL;
}

char *utesmake_p_tree_vertex_label()
{
    TreeVertexPointer x = make_p_tree_vertex_label(7);
    mu_assert("should be empty", x->content->label == 7);
    mu_assert("should be empty", array_is_empty(x->children));
    return NULL;
}

char *utest_treevertex_vertices()
{
    Tree tree = tree_singleton_label(0, 10);
    tree_insert(make_p_tree_vertex_label(1), 0, tree);
    tree_insert(make_p_tree_vertex_label(2), 0, tree);
    tree_insert(make_p_tree_vertex_label(3), 2, tree);
    tree_insert(make_p_tree_vertex_label(4), 2, tree);
    VertexSet vertexset = vertexset_init(10);
    treevertex_vertices(tree.root, vertexset);
    mu_assert("should contain 1", vertexset_contains_label(vertexset, 1));
    mu_assert("should contain 2", vertexset_contains_label(vertexset, 2));
    mu_assert("should contain 3", vertexset_contains_label(vertexset, 3));
    mu_assert("should contain 4", vertexset_contains_label(vertexset, 4));
    return NULL;
}

char *utest_treevertex_insert()
{
    Tree tree = tree_singleton_label(1, 5);
    TreeVertexPointer root = tree.root;
    mu_assert("should be root", root->is_root);
    mu_assert("should contain 1", tree_contains_vertex(tree_make(root, 10), vertex_p_make(1)));
    mu_assert("parent should be null", root->parent == NULL); 
    mu_assert("should succed", treevertex_insert(make_p_tree_vertex_label(2), 1, root) == SUCCESS);
    mu_assert("root should exist", root);
    mu_assert("root should exist", root->content->label == 1);
    mu_assert("the maxlength of roots children should be 4", root->children->capacity == 4);
    mu_assert("the length of roots children should be 1", root->children->length == 1);
    mu_assert("should be 2", ((TreeVertexPointer) array_get(root->children, 0))->content->label == 2);
    mu_assert("should not be root", ((TreeVertexPointer) array_get(root->children, 0))->is_root == false);
    TreeVertexPointer parent = ((TreeVertexPointer) array_get(root->children, 0))->parent;
    mu_assert("parent should be 1",  ((TreeVertexPointer) parent)->content->label == 1);
    mu_assert("should succeed", treevertex_insert(make_p_tree_vertex_label(3), 2, root) == SUCCESS);
    mu_assert("should succeed", treevertex_insert(make_p_tree_vertex_label(4), 2, root) == SUCCESS);
    mu_assert("should fail", treevertex_insert(make_p_tree_vertex_label(5), 6, root) == FAIL);
    mu_assert("should still be 1", root->children->length == 1); 

    TreeVertexPointer subroot = make_p_tree_vertex_label(5); 
    treevertex_insert(make_p_tree_vertex_label(6), 5, subroot);
    treevertex_insert(make_p_tree_vertex_label(7), 5, subroot);
    mu_assert("should succeed", treevertex_insert(subroot, 1, root) == SUCCESS);
    mu_assert("root children should now be 2", root->children->length == 2); 
    TreeVertexPointer secondchild = array_get(root->children, 1);
    TreeVertexPointer firstchild = array_get(root->children, 0);
    mu_assert("first child of root should still be 2", firstchild->content->label == 2);
    mu_assert("second child of root should be 5", secondchild->content->label == 5);
    TreeVertexPointer secondchildchild1 = array_get(secondchild->children, 0);
    TreeVertexPointer secondchildchild2 = array_get(secondchild->children, 1);
    mu_assert("level 2: first child should be 6", secondchildchild1->content->label == 6); 
    mu_assert("level 2: second child should be 7", secondchildchild2->content->label == 7); 
    TreeVertexPointer tv = array_get(root->children, 0); 
    mu_assert("should be 2", tv->children->length == 2); 
    return NULL;
}

char *utest_insert()
{
    Tree tree = tree_singleton_label(1, 10);
    mu_assert("should contain 1", tree_contains_vertex(tree, vertex_p_make(1)));
    mu_assert("should work", tree_insert(make_p_tree_vertex_label(2), 1, tree) == SUCCESS);
    mu_assert("should contain 2", tree_contains_vertex(tree, vertex_p_make(2)));
    mu_assert("should still contain 1", tree_contains_vertex(tree, vertex_p_make(1)));
    mu_assert("but not 0 or 3", !tree_contains_vertex(tree, vertex_p_make(0)));
    mu_assert("but not 0 or 3", !tree_contains_vertex(tree, vertex_p_make(3)));
    mu_assert("should have 2 vertex", *tree.nvertices == 2);
    tree_destroy(tree);
    tree = tree_singleton_label(1, 10);
    Tree tree2 = tree_singleton_label(3, 10);
    tree_insert(make_p_tree_vertex_label(2), 1, tree);
    tree_insert(make_p_tree_vertex_label(4), 3, tree2);
    tree_insert(make_p_tree_vertex_label(5), 3, tree2);
    mu_assert("should have 3 vertices", *tree2.nvertices == 3);
    mu_assert("tree contains one and two", tree_contains_vertex(tree, vertex_p_make(1)));
    mu_assert("tree contains one and two", tree_contains_vertex(tree, vertex_p_make(2)));
    mu_assert("tree2 contains 3,4,5", tree_contains_vertex(tree2, vertex_p_make(3)));
    mu_assert("tree2 contains 3,4,5", tree_contains_vertex(tree2, vertex_p_make(4)));
    mu_assert("tree2 contains 3,4,5", tree_contains_vertex(tree2, vertex_p_make(5)));
    mu_assert("should succed", tree_insert(tree2.root, 1, tree) == SUCCESS); 
    mu_assert("tree contains 1", tree_contains_vertex(tree, vertex_p_make(1)));
    mu_assert("tree contains 2", tree_contains_vertex(tree, vertex_p_make(2)));
    mu_assert("tree contains 3", tree_contains_vertex(tree, vertex_p_make(3)));
    mu_assert("tree contains 4", tree_contains_vertex(tree, vertex_p_make(4)));
    mu_assert("tree contains 5", tree_contains_vertex(tree, vertex_p_make(5)));
    return NULL;
}


char *utest_tree_evens_odds()
{
    Tree root = tree_singleton_label(0, 10);
    tree_insert(make_p_tree_vertex_label(1), 0, root);
    tree_insert(make_p_tree_vertex_label(2), 0, root);
    tree_insert(make_p_tree_vertex_label(3), 1, root);
    tree_insert(make_p_tree_vertex_label(4), 1, root);
    VertexSet evens, odds;
    evens = vertexset_init(5);
    odds = vertexset_init(5);
    tree_evens_odds(root, &evens, &odds);
    mu_assert("First even should be 0", ((VertexPointer) vertexset_get(evens, 0))->label == 0);
    mu_assert("second even should be 3", ((VertexPointer) vertexset_get(evens, 1))->label == 3);
    mu_assert("Third even should be 4", ((VertexPointer) vertexset_get(evens, 2))->label == 4);
    mu_assert("First odd should be 1", ((VertexPointer) vertexset_get(odds, 0))->label == 1);
    mu_assert("second odd should be 2", ((VertexPointer) vertexset_get(odds, 1))->label == 2);
    vertexset_destroy(evens);
    vertexset_destroy(odds);
    evens = vertexset_init(5);
    tree_evens_odds(root, &evens, NULL);
    mu_assert("First even should be 0", ((VertexPointer) vertexset_get(evens, 0))->label == 0);
    mu_assert("second even should be 3", ((VertexPointer) vertexset_get(evens, 1))->label == 3);
    mu_assert("Third even should be 4", ((VertexPointer) vertexset_get(evens, 2))->label == 4);
    return NULL;
}

char *utest_evens()
{
    Tree root = tree_singleton_label(0, 10);
    tree_insert(make_p_tree_vertex_label(1), 0, root);
    tree_insert(make_p_tree_vertex_label(2), 0, root);
    tree_insert(make_p_tree_vertex_label(3), 1, root);
    tree_insert(make_p_tree_vertex_label(4), 1, root);
    VertexSet evens;
    evens = vertexset_init(6);
    tree_evens(root, &evens);
    mu_assert("First even should be 0", ((VertexPointer) vertexset_get(evens, 0))->label == 0);
    mu_assert("second even should be 3", ((VertexPointer) vertexset_get(evens, 1))->label == 3);
    mu_assert("Third even should be 4", ((VertexPointer) vertexset_get(evens, 2))->label == 4);

    tree_insert(make_p_tree_vertex_label(5), 2, root);
    tree_insert(make_p_tree_vertex_label(6), 2, root);
    tree_evens(root, &evens);
    mu_assert("fourth even should be 5", ((VertexPointer) vertexset_get(evens, 3))->label == 5);
    mu_assert("fifth even should be 6", ((VertexPointer) vertexset_get(evens, 4))->label == 6);
    return NULL;
}

char *utest_odds()
{
    Tree root = tree_singleton_label(0, 10);
    tree_insert(make_p_tree_vertex_label(1), 0, root);
    tree_insert(make_p_tree_vertex_label(2), 0, root);
    tree_insert(make_p_tree_vertex_label(3), 1, root);
    tree_insert(make_p_tree_vertex_label(4), 3, root);
    VertexSet odds;
    odds = vertexset_init(6);
    tree_odds(root, &odds);
    mu_assert("First odd should be 1", ((VertexPointer) vertexset_get(odds, 0))->label == 1);
    mu_assert("second odd should be 4", ((VertexPointer) vertexset_get(odds, 1))->label == 4);
    mu_assert("third odd should be 2", ((VertexPointer) vertexset_get(odds, 2))->label == 2);

    tree_insert(make_p_tree_vertex_label(5), 2, root);
    tree_insert(make_p_tree_vertex_label(6), 5, root);
    tree_odds(root, &odds);
    mu_assert("fourth odd should be 6", ((VertexPointer) vertexset_get(odds, 3))->label == 6);
    return NULL;
}

char *utest_tree_destroy()
{
    mu_assert("null pointer", tree_destroy(tree_empty()) == FAIL);
    return NULL;
}

char *test_is_frustrated()
{
    //todo
    return NULL;
}

char *utest_treevertex_get()
{
    Tree tree = tree_singleton_label(0, 5);
    VertexPointer a = vertex_p_make(1);
    VertexPointer b = vertex_p_make(2);
    VertexPointer c = vertex_p_make(3);
    TreeVertexPointer ta = make_p_tree_vertex(a);
    TreeVertexPointer tb = make_p_tree_vertex(b);
    TreeVertexPointer tc = make_p_tree_vertex(c);
    tree_insert(ta, 0, tree);
    tree_insert(tb, 0, tree);
    tree_insert(tc, 1, tree);

    TreeVertexPointer taprime = treevertex_get(tree.root, a);
    TreeVertexPointer tbprime = treevertex_get(tree.root, b);
    TreeVertexPointer tcprime = treevertex_get(tree.root, c);

    mu_assert("should not be null", taprime);
    mu_assert("should not be null", tbprime);
    mu_assert("should not be null", tcprime);
    return NULL;
}

char *test_tree() {
    mu_message(UNIT, "make_p_tree_vertex_label\n");
    mu_run_utest(utesmake_p_tree_vertex_label);
    mu_message(UNIT, "tree_singleton_label\n");
    mu_run_utest(utest_tree_singleton_label);
    mu_message(UNIT, "tree_insert aux\n");
    mu_run_utest(utest_treevertex_insert);
    mu_message(UNIT, "tree_insert\n");
    mu_run_utest(utest_insert);
    mu_message(UNIT, "tree_evens_odds\n");
    mu_run_utest(utest_tree_evens_odds);
    mu_message(UNIT, "evens\n");
    mu_run_utest(utest_evens);
    mu_message(UNIT, "odds\n");
    mu_run_utest(utest_odds);
    mu_message(UNIT, "treevertex_vertices\n");
    mu_run_utest(utest_treevertex_vertices);
    mu_message(UNIT, "tree_destroy\n");
    mu_run_utest(utest_tree_destroy);
    mu_message(UNIT, "tree_insert\n");
    mu_run_utest(utest_insert);
    mu_message(UNIT, "treevertex_get\n");
    mu_run_utest(utest_treevertex_get);
    return NULL;
}
