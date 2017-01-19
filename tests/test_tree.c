#include "test.h"

bool contains_labels(VertexCollection collection, Label *labels, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        VertexPointer vertex = vertexcollection_get(collection, i);
        if (vertex->label != labels[i]) {
            return false;
        }
    }
    return true;
}

char *utest_tree_singleton()
{
    VertexPointer tree = vertex_p_make(3);
    mu_assert("label should be 3", tree->label == 3);
    mu_assert("should have no parent", tree->parent == NULL);
    return NULL;
}

char *utest_tree_merge()
{
    VertexPointer tree1 = vertex_p_make(1);
    VertexPointer tree2 = vertex_p_make(2);
    VertexPointer tree3 = vertex_p_make(3);
    tree_merge(tree1, tree2);
    tree_merge(tree1, tree3);

    VertexPointer tree4 = vertex_p_make(4);
    VertexPointer tree5 = vertex_p_make(5);
    VertexPointer tree6 = vertex_p_make(6);
    tree_merge(tree4, tree5);
    tree_merge(tree4, tree6);

    tree_merge(tree2, tree4);
    mu_assert("2 should have 1 as parent", tree2->parent->label == 1);
    mu_assert("3 should have 1 as parent", tree3->parent->label == 1);
    mu_assert("4 should have 2 as parent", tree4->parent->label == 2);
    mu_assert("5 should have 4 as parent", tree5->parent->label == 4);
    mu_assert("1 should have no parent", tree1->parent == NULL);

    return NULL;
}

char *utest_tree_find_root()
{
    VertexPointer tree1 = vertex_p_make(1);
    VertexPointer tree2 = vertex_p_make(2);
    VertexPointer tree3 = vertex_p_make(3);
    tree_merge(tree1, tree2);
    tree_merge(tree1, tree3);
    VertexPointer tree4 = vertex_p_make(4);
    VertexPointer tree5 = vertex_p_make(5);
    VertexPointer tree6 = vertex_p_make(6);
    tree_merge(tree4, tree5);
    tree_merge(tree4, tree6);
    tree_merge(tree2, tree4);

    mu_assert("should be 1", tree_find_root(tree6)->label == 1);
    mu_assert("should be 1", tree_find_root(tree1)->label == 1);
    mu_assert("should be 1", tree_find_root(tree5)->label == 1);
    return NULL;
}

char *utest_tree_invert()
{
    VertexPointer tree1 = vertex_p_make(1);
    VertexPointer tree2 = vertex_p_make(2);
    VertexPointer tree3 = vertex_p_make(3);
    tree_merge(tree1, tree2);
    tree_merge(tree1, tree3);
    VertexPointer tree4 = vertex_p_make(4);
    VertexPointer tree5 = vertex_p_make(5);
    VertexPointer tree6 = vertex_p_make(6);
    tree_merge(tree4, tree5);
    tree_merge(tree4, tree6);
    tree_merge(tree2, tree4);
    tree_invert(tree4);
    mu_assert("6: should be 4", tree_find_root(tree6)->label == 4);
    mu_assert("1: should be 4", tree_find_root(tree1)->label == 4);
    mu_assert("5: should be 4", tree_find_root(tree5)->label == 4);
    mu_assert("4: should be 4", tree_find_root(tree4)->label == 4);
    tree_invert(tree5);
    mu_assert("6: should be 5", tree_find_root(tree6)->label == 5);
    mu_assert("1: should be 5", tree_find_root(tree1)->label == 5);
    mu_assert("5: should be 5", tree_find_root(tree5)->label == 5);
    mu_assert("4: should be 5", tree_find_root(tree4)->label == 5);
    tree_invert(tree1);
    mu_assert("6: should be 1", tree_find_root(tree6)->label == 1);
    mu_assert("1: should be 1", tree_find_root(tree1)->label == 1);
    mu_assert("5: should be 1", tree_find_root(tree5)->label == 1);
    mu_assert("4: should be 1", tree_find_root(tree4)->label == 1);

    return NULL;
}

char *utest_tree_find_branch()
{
    VertexPointer tree1 = vertex_p_make(1);
    VertexPointer tree2 = vertex_p_make(2);
    VertexPointer tree3 = vertex_p_make(3);
    tree_merge(tree1, tree2);
    tree_merge(tree1, tree3);
    VertexPointer tree4 = vertex_p_make(4);
    VertexPointer tree5 = vertex_p_make(5);
    VertexPointer tree6 = vertex_p_make(6);
    tree_merge(tree4, tree5);
    tree_merge(tree4, tree6);
    tree_merge(tree2, tree4);
    mu_assert("6: should be 2", tree_find_branch(tree6)->label == 2);
    mu_assert("5: should be 5", tree_find_branch(tree5)->label == 2);
    mu_assert("4: should be 5", tree_find_branch(tree4)->label == 2);
    mu_assert("3: should be 3", tree_find_branch(tree3)->label == 3);
    return NULL;
}

char *utest_tree_path_to_root()
{
    NetworkPointer network = network_init(PS);
    parse("/home/lsund/Data/graphs/data/networks/set/gen3x3.dmx", network);

    VertexPointer tree1 = vertexcollection_get_reference(network->graph.vertices, vertex_make(2));
    VertexPointer tree2 = vertexcollection_get_reference(network->graph.vertices, vertex_make(5));
    VertexPointer tree3 = vertexcollection_get_reference(network->graph.vertices, vertex_make(4));
    tree_merge(tree1, tree2);
    tree_merge(tree1, tree3);
    VertexPointer tree4 = vertexcollection_get_reference(network->graph.vertices, vertex_make(9));
    VertexPointer tree5 = vertexcollection_get_reference(network->graph.vertices, vertex_make(6));
    VertexPointer tree6 = vertexcollection_get_reference(network->graph.vertices, vertex_make(11));
    tree_merge(tree4, tree5);
    tree_merge(tree4, tree6);
    tree_merge(tree2, tree4);
    VertexCollection path = tree_path_to_root(tree6);
    Label labels[4] = { 11, 9, 5, 2 };
    mu_assert("should contain these vertices", contains_labels(path, labels, 4));
    EdgeCollection epath = tree_edgepath_from_branch(tree6, network->graph.edges);
    EdgeCollection epath2 = tree_edgepath_to_branch(tree6, network->reverse_edges);
    edgecollection_print(epath);
    edgecollection_print(epath2);
    return NULL;
}

char *test_tree()
{
    mu_message(UNIT, "tree_singleton\n");
    mu_run_utest(utest_tree_singleton);
    mu_message(UNIT, "tree_merge\n");
    mu_run_utest(utest_tree_merge);
    mu_message(UNIT, "tree_find_root\n");
    mu_run_utest(utest_tree_find_root);
    mu_message(UNIT, "tree_find_branch\n");
    mu_run_utest(utest_tree_find_branch);
    mu_message(UNIT, "tree_invert\n");
    mu_run_utest(utest_tree_invert);
    mu_message(UNIT, "tree_path_to_root\n");
    mu_run_utest(utest_tree_path_to_root);
    return NULL;
}

