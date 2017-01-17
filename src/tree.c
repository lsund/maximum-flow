
#include "tree.h"


Tree tree_empty() {
    Tree ret;
    ret.root = NULL;
    return ret;
}

TreePointer empty_p_tree() {
    TreePointer ret = malloc(sizeof(Tree));
    *ret = tree_empty();
    return ret;
}

bool is_emtpy_tree(Tree tree) {
    return tree.root == NULL;
}

Tree tree_singleton(const VertexPointer vertex)
{
    Tree ret;
    ret.root                    = treevertex_p_make(vertex);
    ret.root->is_root           = true;
    return ret;
}

Tree tree_singleton_label(const Label rootlabel)
{
    return tree_singleton(vertex_p_make(rootlabel));
}

Tree tree_make(const TreeVertexPointer root)
{
    Tree ret;
    ret.root = root;
    return ret;
}

TreePointer make_p_tree(const TreeVertexPointer root)
{
    TreePointer ret = empty_p_tree();
    ret->root = root;
    return ret;
}

Result tree_get_branch(Tree tree, VertexPointer vertex, TreeVertexPointer *result)
{
    TreeVertexPointer subtree = treevertex_get(tree.root, vertex);
    TreeVertexPointer ret = treevertex_get_root_child(subtree);
    if (ret == NULL) {
        return FAIL;
    } else {
        *result = ret;
        return SUCCESS;
    }
}

size_t tree_size(Tree tree)
{
    return treevertex_size(tree.root);
}

Result tree_attach(Tree tree, TreeVertexPointer treevertex, const Label under)
{
	if (treevertex_insert(treevertex, under, tree.root) == FAIL) {
        return FAIL;
    } else {
        return SUCCESS;
    }
}

Result tree_insert(Tree tree, VertexPointer vertex, const Label under)
{
    TreeVertexPointer inserted = treevertex_p_make(vertex);
	if (treevertex_insert(inserted, under, tree.root) == FAIL) {
        return FAIL;
    } else {
        return SUCCESS;
    }
}

Result tree_insert_under_root(Tree tree, VertexPointer vertex)
{
    Label rootlabel = tree.root->content->label;
    if (tree_insert(tree, vertex, rootlabel) == FAIL) {
        return FAIL;
    } else {
        return SUCCESS;
    }
}

Result tree_deattach(Tree tree, VertexPointer vertex)
{
    TreeVertexPointer subtree = treevertex_get(tree.root, vertex);
    if (subtree && subtree->parent) {
        collection_remove(subtree->parent, subtree);
        subtree->parent = NULL;
        return SUCCESS;
    } else {
        return FAIL;
    }
}

void tree_evens_odds(Tree tree, VertexCollectionPointer evens, VertexCollectionPointer odds)
{
    treevertex_odds_evens(tree.root, true, evens, odds);
}

void tree_evens(Tree tree, VertexCollectionPointer evens)
{
    tree_evens_odds(tree, evens, NULL);
}

void tree_odds(Tree tree, VertexCollectionPointer odds)
{
    tree_evens_odds(tree, NULL, odds);
}

EdgeCollection tree_path(Tree tree, VertexPointer vertex)
{
    EdgeCollection ret = edgecollection_init(ARRAY_MIN_SIZE);
    /* TreeVertexPointer t_vertex = treevertex_get(tree.root, vertex); */
    /* while (t_vertex->parent) { */
    /*     Edge edge = edge_make_vertices(t_vertex->content, t_vertex->parent); */
    /*     /1* t_vertex = t_vertex->parent; *1/ */
    /* } */
    // tbi
    return ret;
}

void tree_set_root(Tree tree, VertexPointer vertex)
{
    TreeVertexPointer t_vertex = treevertex_get(tree.root, vertex);    
    while (t_vertex->parent) {
        TreeVertexPointer parent = (TreeVertexPointer) t_vertex->parent;
        collection_push(t_vertex->children, parent);
        collection_remove(parent->children, t_vertex);



        Edge edge = edge_make_vertices(*t_vertex->content, *parent->content);
        edge_print(edge);
        t_vertex = t_vertex->parent;
    }
}

void tree_print(Tree tree)
{
    treevertex_print(tree.root);
    printf("\n");
}

Result tree_destroy(Tree tree)
{
    if (treevertex_destroy(tree.root) == FAIL) {
        return FAIL;
    } else {
        free(tree.root);
        return SUCCESS;
    }
}

