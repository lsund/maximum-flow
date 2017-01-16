
#include <stdlib.h>
#include "test.h"

char *utest_tree_deattach()
{
    Tree tree = tree_singleton_label(0);
    VertexPointer v1 = vertex_p_make(1);
    VertexPointer v2 = vertex_p_make(2);
    VertexPointer v3 = vertex_p_make(3);
    VertexPointer v4 = vertex_p_make(4);
    VertexPointer v5 = vertex_p_make(5);
    tree_insert(v1, 0, tree);
    tree_insert(v2, 0, tree);
    tree_insert(v3, 2, tree);
    tree_insert(v4, 2, tree);
    tree_insert(v5, 3, tree);
    mu_assert("should have 6 nodes", tree_size(tree) == 6);
    tree_deattach(tree, v2);
    mu_assert("should have 2 nodes", tree_size(tree) == 2);
    return NULL;
}

char *utest_tree_singleton_label()
{
    Tree tree = tree_singleton_label(3);
    mu_assert("label should be 3", tree.root->content->label == 3);
    return NULL;
}

char *utesmake_p_tree_vertex_label()
{
    TreeVertexPointer x = make_p_tree_vertex_label(7);
    mu_assert("should be empty", x->content->label == 7);
    mu_assert("should be empty", x->children->capacity == 0);
    return NULL;
}

char *utest_treevertex_vertices()
{
    Tree tree = tree_singleton_label(0);
    tree_insert(vertex_p_make(1), 0, tree);
    tree_insert(vertex_p_make(2), 0, tree);
    tree_insert(vertex_p_make(3), 2, tree);
    tree_insert(vertex_p_make(4), 2, tree);
    VertexCollection vertexcollection = vertexcollection_init(10);
    treevertex_vertices(tree.root, vertexcollection);
    mu_assert("should contain 1", vertexcollection_contains_label(vertexcollection, 1));
    mu_assert("should contain 2", vertexcollection_contains_label(vertexcollection, 2));
    mu_assert("should contain 3", vertexcollection_contains_label(vertexcollection, 3));
    mu_assert("should contain 4", vertexcollection_contains_label(vertexcollection, 4));
    return NULL;
}

char *utest_treevertex_insert()
{
    Tree tree = tree_singleton_label(1);
    TreeVertexPointer root = tree.root;
    mu_assert("should be root", root->is_root);
    mu_assert("parent should be null", root->parent == NULL); 
    mu_assert("should succed", treevertex_insert(make_p_tree_vertex_label(2), 1, root) == SUCCESS);
    mu_assert("root should exist", root);
    mu_assert("root should exist", root->content->label == 1);
    mu_assert("the maxlength of roots children should be 4", root->children->capacity == 4);
    mu_assert("the length of roots children should be 1", root->children->length == 1);
    mu_assert("should be 2", ((TreeVertexPointer) collection_get(root->children, 0))->content->label == 2);
    mu_assert("should not be root", ((TreeVertexPointer) collection_get(root->children, 0))->is_root == false);
    TreeVertexPointer parent = ((TreeVertexPointer) collection_get(root->children, 0))->parent;
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
    TreeVertexPointer secondchild = collection_get(root->children, 1);
    TreeVertexPointer firstchild = collection_get(root->children, 0);
    mu_assert("first child of root should still be 2", firstchild->content->label == 2);
    mu_assert("second child of root should be 5", secondchild->content->label == 5);
    TreeVertexPointer secondchildchild1 = collection_get(secondchild->children, 0);
    TreeVertexPointer secondchildchild2 = collection_get(secondchild->children, 1);
    mu_assert("level 2: first child should be 6", secondchildchild1->content->label == 6); 
    mu_assert("level 2: second child should be 7", secondchildchild2->content->label == 7); 
    TreeVertexPointer tv = collection_get(root->children, 0); 
    mu_assert("should be 2", tv->children->length == 2); 
    return NULL;
}

char *utest_tree_size()
{
    Tree tree = tree_singleton_label(1);
    mu_assert("should have size 1", tree_size(tree) == 1);
    tree_insert(vertex_p_make(2), 1, tree);
    mu_assert("should have size 1", tree_size(tree) == 2);
    tree_insert(vertex_p_make(3), 1, tree);
    mu_assert("should have size 1", tree_size(tree) == 3);
    Tree tree2 = tree_singleton_label(77);
    tree_insert(vertex_p_make(78), 77, tree2);
    tree_insert(vertex_p_make(79), 77, tree2);
    tree_attach(tree2.root, 2, tree);
    mu_assert("should have size 6", tree_size(tree) == 6);
    return NULL;
}

char *utest_tree_get_branch()
{
    Tree tree = tree_singleton_label(1);
    TreeVertexPointer placeholder;
    tree_insert(vertex_p_make(2), 1, tree);
    tree_insert(vertex_p_make(3), 2, tree);
    tree_insert(vertex_p_make(5), 1, tree);
    tree_insert(vertex_p_make(6), 5, tree);
    tree_insert(vertex_p_make(7), 5, tree);
    mu_assert("should not succeed", FAIL == tree_get_branch(tree, vertex_p_make(1), NULL));
    mu_assert("should succeed", SUCCESS == tree_get_branch(tree, vertex_p_make(2), &placeholder));
    mu_assert("should be 2", 2 == placeholder->content->label);
    mu_assert("should succeed", SUCCESS == tree_get_branch(tree, vertex_p_make(3), &placeholder));
    mu_assert("should be 2", 2 == placeholder->content->label);
    mu_assert("size should be 6", tree_size(tree) == 6);
    mu_assert("should succeed", SUCCESS == tree_get_branch(tree, vertex_p_make(7), &placeholder));
    mu_assert("should be 5", 5 == placeholder->content->label);
    return NULL;
}

char *utest_insert()
{
    Tree tree = tree_singleton_label(1);
    mu_assert("should work", tree_insert(vertex_p_make(2), 1, tree) == SUCCESS);
    tree_destroy(tree);
    tree = tree_singleton_label(1);
    Tree tree2 = tree_singleton_label(3);
    tree_insert(vertex_p_make(2), 1, tree);
    tree_insert(vertex_p_make(4), 3, tree2);
    tree_insert(vertex_p_make(5), 3, tree2);
    mu_assert("should succed", tree_attach(tree2.root, 1, tree) == SUCCESS); 
    return NULL;
}


char *utest_tree_evens_odds()
{
    Tree root = tree_singleton_label(0);
    tree_insert(vertex_p_make(1), 0, root);
    tree_insert(vertex_p_make(2), 0, root);
    tree_insert(vertex_p_make(3), 1, root);
    tree_insert(vertex_p_make(4), 1, root);
    VertexCollection evens, odds;
    evens = vertexcollection_init(5);
    odds = vertexcollection_init(5);
    tree_evens_odds(root, &evens, &odds);
    mu_assert("First even should be 0", ((VertexPointer) vertexcollection_get(evens, 0))->label == 0);
    mu_assert("second even should be 3", ((VertexPointer) vertexcollection_get(evens, 1))->label == 3);
    mu_assert("Third even should be 4", ((VertexPointer) vertexcollection_get(evens, 2))->label == 4);
    mu_assert("First odd should be 1", ((VertexPointer) vertexcollection_get(odds, 0))->label == 1);
    mu_assert("second odd should be 2", ((VertexPointer) vertexcollection_get(odds, 1))->label == 2);
    vertexcollection_destroy(evens);
    vertexcollection_destroy(odds);
    evens = vertexcollection_init(5);
    tree_evens_odds(root, &evens, NULL);
    mu_assert("First even should be 0", ((VertexPointer) vertexcollection_get(evens, 0))->label == 0);
    mu_assert("second even should be 3", ((VertexPointer) vertexcollection_get(evens, 1))->label == 3);
    mu_assert("Third even should be 4", ((VertexPointer) vertexcollection_get(evens, 2))->label == 4);
    return NULL;
}

char *utest_evens()
{
    Tree root = tree_singleton_label(0);
    tree_insert(vertex_p_make(1), 0, root);
    tree_insert(vertex_p_make(2), 0, root);
    tree_insert(vertex_p_make(3), 1, root);
    tree_insert(vertex_p_make(4), 1, root);
    VertexCollection evens;
    evens = vertexcollection_init(6);
    tree_evens(root, &evens);
    mu_assert("First even should be 0", ((VertexPointer) vertexcollection_get(evens, 0))->label == 0);
    mu_assert("second even should be 3", ((VertexPointer) vertexcollection_get(evens, 1))->label == 3);
    mu_assert("Third even should be 4", ((VertexPointer) vertexcollection_get(evens, 2))->label == 4);

    tree_insert(vertex_p_make(5), 2, root);
    tree_insert(vertex_p_make(6), 2, root);
    tree_evens(root, &evens);
    mu_assert("fourth even should be 5", ((VertexPointer) vertexcollection_get(evens, 3))->label == 5);
    mu_assert("fifth even should be 6", ((VertexPointer) vertexcollection_get(evens, 4))->label == 6);
    return NULL;
}

char *utest_odds()
{
    Tree root = tree_singleton_label(0);
    tree_insert(vertex_p_make(1), 0, root);
    tree_insert(vertex_p_make(2), 0, root);
    tree_insert(vertex_p_make(3), 1, root);
    tree_insert(vertex_p_make(4), 3, root);
    VertexCollection odds;
    odds = vertexcollection_init(6);
    tree_odds(root, &odds);
    mu_assert("First odd should be 1", ((VertexPointer) vertexcollection_get(odds, 0))->label == 1);
    mu_assert("second odd should be 4", ((VertexPointer) vertexcollection_get(odds, 1))->label == 4);
    mu_assert("third odd should be 2", ((VertexPointer) vertexcollection_get(odds, 2))->label == 2);

    tree_insert(vertex_p_make(5), 2, root);
    tree_insert(vertex_p_make(6), 5, root);
    tree_odds(root, &odds);
    mu_assert("fourth odd should be 6", ((VertexPointer) vertexcollection_get(odds, 3))->label == 6);
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
    Tree tree = tree_singleton_label(0);
    VertexPointer a = vertex_p_make(1);
    VertexPointer b = vertex_p_make(2);
    VertexPointer c = vertex_p_make(3);
    tree_insert(a, 0, tree);
    tree_insert(b, 0, tree);
    tree_insert(c, 1, tree);

    TreeVertexPointer taprime = treevertex_get(tree.root, a);
    TreeVertexPointer tbprime = treevertex_get(tree.root, b);
    TreeVertexPointer tcprime = treevertex_get(tree.root, c);

    mu_assert("should not be null", taprime);
    mu_assert("should not be null", tbprime);
    mu_assert("should not be null", tcprime);
    return NULL;
}

char *test_tree() {
    mu_message(UNIT, "VertexPointer\n");
    mu_run_utest(utesmake_p_tree_vertex_label);
    mu_message(UNIT, "tree_singleton_label\n");
    mu_run_utest(utest_tree_singleton_label);
    mu_message(UNIT, "tree_insert aux\n");
    mu_run_utest(utest_treevertex_insert);
    mu_message(UNIT, "tree_insert\n");
    mu_run_utest(utest_insert);
    mu_message(UNIT, "tree_size\n");
    mu_run_utest(utest_tree_size);
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
    mu_message(UNIT, "tree_get_branch\n");
    mu_run_utest(utest_tree_get_branch);
    return NULL;
}
