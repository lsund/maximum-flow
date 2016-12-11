
#include <stdlib.h>
#include "test.h"

char *utest_make_singleton_tree_label()
{
    Tree tree = make_singleton_tree_label(3, 10);
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

char *utest_tree_vertices()
{
    Tree tree = make_singleton_tree_label(0, 10);
    insert(make_p_tree_vertex_label(1), 0, tree);
    insert(make_p_tree_vertex_label(2), 0, tree);
    insert(make_p_tree_vertex_label(3), 2, tree);
    insert(make_p_tree_vertex_label(4), 2, tree);
    VertexSet vertexset = init_vertexset(10);
    tree_vertices(tree.root, vertexset);
    mu_assert("should contain 1", vertexset_contains_vertex(vertexset, make_p_vertex(1)));
    mu_assert("should contain 2", vertexset_contains_vertex(vertexset, make_p_vertex(2)));
    mu_assert("should contain 3", vertexset_contains_vertex(vertexset, make_p_vertex(3)));
    mu_assert("should contain 4", vertexset_contains_vertex(vertexset, make_p_vertex(4)));
    return NULL;
}

char *utest_insert_aux()
{
    Tree tree = make_singleton_tree_label(1, 5);
    TreeVertexPointer root = tree.root;
    mu_assert("should be root", root->is_root);
    mu_assert("should contain 1", tree_contains_vertex(make_tree(root, 10), make_p_vertex(1)));
    mu_assert("parent should be null", root->parent == NULL); 
    mu_assert("should succed", t_insert_aux(make_p_tree_vertex_label(2), 1, root) == SUCCESS);
    mu_assert("root should exist", root);
    mu_assert("root should exist", root->content->label == 1);
    mu_assert("the maxlength of roots children should be 4", root->children->length == 4);
    mu_assert("the length of roots children should be 1", root->children->nelements == 1);
    mu_assert("should be 2", ((TreeVertexPointer) get_element(root->children, 0))->content->label == 2);
    mu_assert("should not be root", ((TreeVertexPointer) get_element(root->children, 0))->is_root == false);
    TreeVertexPointer parent = ((TreeVertexPointer) get_element(root->children, 0))->parent;
    mu_assert("parent should be 1",  ((TreeVertexPointer) parent)->content->label == 1);
    mu_assert("should succeed", t_insert_aux(make_p_tree_vertex_label(3), 2, root) == SUCCESS);
    mu_assert("should succeed", t_insert_aux(make_p_tree_vertex_label(4), 2, root) == SUCCESS);
    mu_assert("should fail", t_insert_aux(make_p_tree_vertex_label(5), 6, root) == FAIL);
    mu_assert("should still be 1", root->children->nelements == 1); 

    TreeVertexPointer subroot = make_p_tree_vertex_label(5); 
    t_insert_aux(make_p_tree_vertex_label(6), 5, subroot);
    t_insert_aux(make_p_tree_vertex_label(7), 5, subroot);
    mu_assert("should succeed", t_insert_aux(subroot, 1, root) == SUCCESS);
    mu_assert("root children should now be 2", root->children->nelements == 2); 
    TreeVertexPointer secondchild = get_element(root->children, 1);
    TreeVertexPointer firstchild = get_element(root->children, 0);
    mu_assert("first child of root should still be 2", firstchild->content->label == 2);
    mu_assert("second child of root should be 5", secondchild->content->label == 5);
    TreeVertexPointer secondchildchild1 = get_element(secondchild->children, 0);
    TreeVertexPointer secondchildchild2 = get_element(secondchild->children, 1);
    mu_assert("level 2: first child should be 6", secondchildchild1->content->label == 6); 
    mu_assert("level 2: second child should be 7", secondchildchild2->content->label == 7); 
    TreeVertexPointer tv = get_element(root->children, 0); 
    mu_assert("should be 2", tv->children->nelements == 2); 
    return NULL;
}

char *utest_insert()
{
    Tree tree = make_singleton_tree_label(1, 10);
    mu_assert("should contain 1", tree_contains_vertex(tree, make_p_vertex(1)));
    mu_assert("should work", insert(make_p_tree_vertex_label(2), 1, tree) == SUCCESS);
    mu_assert("should contain 2", tree_contains_vertex(tree, make_p_vertex(2)));
    mu_assert("should still contain 1", tree_contains_vertex(tree, make_p_vertex(1)));
    mu_assert("but not 0 or 3", !tree_contains_vertex(tree, make_p_vertex(0)));
    mu_assert("but not 0 or 3", !tree_contains_vertex(tree, make_p_vertex(3)));
    mu_assert("should have 2 vertex", *tree.nvertices == 2);
    destroy_tree(tree);
    tree = make_singleton_tree_label(1, 10);
    Tree tree2 = make_singleton_tree_label(3, 10);
    insert(make_p_tree_vertex_label(2), 1, tree);
    insert(make_p_tree_vertex_label(4), 3, tree2);
    insert(make_p_tree_vertex_label(5), 3, tree2);
    mu_assert("should have 3 vertices", *tree2.nvertices == 3);
    mu_assert("tree contains one and two", tree_contains_vertex(tree, make_p_vertex(1)));
    mu_assert("tree contains one and two", tree_contains_vertex(tree, make_p_vertex(2)));
    mu_assert("tree2 contains 3,4,5", tree_contains_vertex(tree2, make_p_vertex(3)));
    mu_assert("tree2 contains 3,4,5", tree_contains_vertex(tree2, make_p_vertex(4)));
    mu_assert("tree2 contains 3,4,5", tree_contains_vertex(tree2, make_p_vertex(5)));
    mu_assert("should succed", insert(tree2.root, 1, tree) == SUCCESS); 
    mu_assert("tree contains 1", tree_contains_vertex(tree, make_p_vertex(1)));
    mu_assert("tree contains 2", tree_contains_vertex(tree, make_p_vertex(2)));
    mu_assert("tree contains 3", tree_contains_vertex(tree, make_p_vertex(3)));
    mu_assert("tree contains 4", tree_contains_vertex(tree, make_p_vertex(4)));
    mu_assert("tree contains 5", tree_contains_vertex(tree, make_p_vertex(5)));
    return NULL;
}


char *utest_tree_evens_odds()
{
    Tree root = make_singleton_tree_label(0, 10);
    insert(make_p_tree_vertex_label(1), 0, root);
    insert(make_p_tree_vertex_label(2), 0, root);
    insert(make_p_tree_vertex_label(3), 1, root);
    insert(make_p_tree_vertex_label(4), 1, root);
    VertexSet evens, odds;
    evens = init_vertexset(5);
    odds = init_vertexset(5);
    tree_evens_odds(root, &evens, &odds);
    mu_assert("First even should be 0", ((VertexPointer) get_vertex(evens, 0))->label == 0);
    mu_assert("second even should be 3", ((VertexPointer) get_vertex(evens, 1))->label == 3);
    mu_assert("Third even should be 4", ((VertexPointer) get_vertex(evens, 2))->label == 4);
    mu_assert("First odd should be 1", ((VertexPointer) get_vertex(odds, 0))->label == 1);
    mu_assert("second odd should be 2", ((VertexPointer) get_vertex(odds, 1))->label == 2);
    destroy_vertexset(evens);
    destroy_vertexset(odds);
    evens = init_vertexset(5);
    tree_evens_odds(root, &evens, NULL);
    mu_assert("First even should be 0", ((VertexPointer) get_vertex(evens, 0))->label == 0);
    mu_assert("second even should be 3", ((VertexPointer) get_vertex(evens, 1))->label == 3);
    mu_assert("Third even should be 4", ((VertexPointer) get_vertex(evens, 2))->label == 4);
    return NULL;
}

char *utest_evens()
{
    Tree root = make_singleton_tree_label(0, 10);
    insert(make_p_tree_vertex_label(1), 0, root);
    insert(make_p_tree_vertex_label(2), 0, root);
    insert(make_p_tree_vertex_label(3), 1, root);
    insert(make_p_tree_vertex_label(4), 1, root);
    VertexSet evens;
    evens = init_vertexset(6);
    tree_evens(root, &evens);
    mu_assert("First even should be 0", ((VertexPointer) get_vertex(evens, 0))->label == 0);
    mu_assert("second even should be 3", ((VertexPointer) get_vertex(evens, 1))->label == 3);
    mu_assert("Third even should be 4", ((VertexPointer) get_vertex(evens, 2))->label == 4);

    insert(make_p_tree_vertex_label(5), 2, root);
    insert(make_p_tree_vertex_label(6), 2, root);
    tree_evens(root, &evens);
    mu_assert("fourth even should be 5", ((VertexPointer) get_vertex(evens, 3))->label == 5);
    mu_assert("fifth even should be 6", ((VertexPointer) get_vertex(evens, 4))->label == 6);
    return NULL;
}

char *utest_odds()
{
    Tree root = make_singleton_tree_label(0, 10);
    insert(make_p_tree_vertex_label(1), 0, root);
    insert(make_p_tree_vertex_label(2), 0, root);
    insert(make_p_tree_vertex_label(3), 1, root);
    insert(make_p_tree_vertex_label(4), 3, root);
    VertexSet odds;
    odds = init_vertexset(6);
    tree_odds(root, &odds);
    mu_assert("First odd should be 1", ((VertexPointer) get_vertex(odds, 0))->label == 1);
    mu_assert("second odd should be 4", ((VertexPointer) get_vertex(odds, 1))->label == 4);
    mu_assert("third odd should be 2", ((VertexPointer) get_vertex(odds, 2))->label == 2);

    insert(make_p_tree_vertex_label(5), 2, root);
    insert(make_p_tree_vertex_label(6), 5, root);
    tree_odds(root, &odds);
    mu_assert("fourth odd should be 6", ((VertexPointer) get_vertex(odds, 3))->label == 6);
    return NULL;
}

char *utest_destroy_tree()
{
    mu_assert("null pointer", destroy_tree(empty_tree()) == FAIL);
    return NULL;
}

char *test_is_frustrated()
{
    //todo
    return NULL;
}

char *utest_get_tree_vertex()
{
    Tree tree = make_singleton_tree_label(0, 5);
    VertexPointer a = make_p_vertex(1);
    VertexPointer b = make_p_vertex(2);
    VertexPointer c = make_p_vertex(3);
    TreeVertexPointer ta = make_p_tree_vertex(a);
    TreeVertexPointer tb = make_p_tree_vertex(b);
    TreeVertexPointer tc = make_p_tree_vertex(c);
    insert(ta, 0, tree);
    insert(tb, 0, tree);
    insert(tc, 1, tree);

    TreeVertexPointer taprime = get_tree_vertex(tree.root, a);
    TreeVertexPointer tbprime = get_tree_vertex(tree.root, b);
    TreeVertexPointer tcprime = get_tree_vertex(tree.root, c);

    mu_assert("should not be null", taprime);
    mu_assert("should not be null", tbprime);
    mu_assert("should not be null", tcprime);
    return NULL;
}

char *test_tree() {
    mu_message(UNIT, "make_p_tree_vertex_label\n");
    mu_run_utest(utesmake_p_tree_vertex_label);
    mu_message(UNIT, "make_singleton_tree_label\n");
    mu_run_utest(utest_make_singleton_tree_label);
    mu_message(UNIT, "insert aux\n");
    mu_run_utest(utest_insert_aux);
    mu_message(UNIT, "insert\n");
    mu_run_utest(utest_insert);
    mu_message(UNIT, "tree_evens_odds\n");
    mu_run_utest(utest_tree_evens_odds);
    mu_message(UNIT, "evens\n");
    mu_run_utest(utest_evens);
    mu_message(UNIT, "odds\n");
    mu_run_utest(utest_odds);
    mu_message(UNIT, "tree_vertices\n");
    mu_run_utest(utest_tree_vertices);
    mu_message(UNIT, "destroy_tree\n");
    mu_run_utest(utest_destroy_tree);
    mu_message(UNIT, "insert\n");
    mu_run_utest(utest_insert);
    mu_message(UNIT, "get_tree_vertex\n");
    mu_run_utest(utest_get_tree_vertex);
    return NULL;
}
