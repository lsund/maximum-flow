
#include "tree.h"

TreeVertexPointer make_p_tree_vertex(VertexPointer vertex) {
    TreeVertexPointer ret = malloc(sizeof(TreeVertex));
    ret->content          = vertex;
    ret->parent           = NULL;
    ret->is_root          = false;
    ret->rank             = 0;
    ret->children         = collection_p_init(0);
    return ret;
}

TreeVertexPointer make_p_tree_vertex_label(const Label label) {
    return make_p_tree_vertex(vertex_p_make(label));
}

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
    ret.root                    = make_p_tree_vertex(vertex);
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

Result tree_attach(TreeVertexPointer treevertex, const Label under, Tree tree)
{
	if (treevertex_insert(treevertex, under, tree.root) == FAIL) {
        return FAIL;
    } else {
        return SUCCESS;
    }
}

Result tree_insert(VertexPointer vertex, const Label under, Tree tree)
{
    TreeVertexPointer inserted = make_p_tree_vertex(vertex);
	if (treevertex_insert(inserted, under, tree.root) == FAIL) {
        return FAIL;
    } else {
        return SUCCESS;
    }
}

Result tree_insert_under_root(VertexPointer vertex, Tree tree)
{
    Label rootlabel = tree.root->content->label;
    if (tree_insert(vertex, rootlabel, tree) == FAIL) {
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

