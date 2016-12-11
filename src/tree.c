
#include "tree.h"

TreeVertexPointer make_p_tree_vertex(VertexPointer vertex) {
    TreeVertexPointer ret = malloc(sizeof(TreeVertex));
    ret->content          = vertex;
    ret->parent           = NULL;
    ret->is_root          = false;
    ret->rank             = 0;
    ret->children         = array_p_empty();
    return ret;
}

TreeVertexPointer make_p_tree_vertex_label(const Label label) {
    return make_p_tree_vertex(vertex_p_make(label));
}

Tree tree_empty() {
    Tree ret;
    ret.root = NULL;
    ret.contains = NULL;
    ret.nvertices = NULL;
    return ret;
}

TreePointer empty_p_tree() {
    TreePointer ret = malloc(sizeof(Tree));
    *ret = tree_empty();
    return ret;
}

bool is_emtpy_tree(Tree tree) {
    return tree.root == NULL || tree.contains == NULL; 
}

Tree tree_singleton(const VertexPointer vertex, const size_t maxsize)
{
    Tree ret;
    ret.root                    = make_p_tree_vertex(vertex);
    ret.root->is_root           = true;
    ret.maxsize                 = maxsize;
    ret.nvertices               = malloc(sizeof(size_t));
    *ret.nvertices              = 1;
    ret.contains                = calloc(sizeof(bool), maxsize);
    *(ret.contains + vertex->label) = true;
    return ret;
}

Tree tree_singleton_label(const Label rootlabel, const size_t maxsize)
{
    return tree_singleton(vertex_p_make(rootlabel), maxsize);
}

Tree tree_make(const TreeVertexPointer root, const size_t maxsize)
{
    Tree ret;
    ret.root = root;
    ret.maxsize = maxsize;
    ret.contains = calloc(sizeof(bool), maxsize);
    *(ret.contains + root->content->label) = true;
    return ret;
}

TreePointer make_p_tree(const TreeVertexPointer root)
{
    TreePointer ret = empty_p_tree();
    ret->root = root;
    return ret;
}

bool tree_contains_vertex(Tree tree, VertexPointer vertex)
{
    if (vertex->label > tree.maxsize) {
        return false;
    }
    return *(tree.contains + vertex->label);
}

Result tree_insert(TreeVertexPointer treevertex, const Label under, Tree tree)
{
    VertexSet inserted_vertices = vertexset_init(tree.maxsize);
    if (inserted_vertices.set->capacity == 0) {
        return FAIL;
    }
    if (treevertex_vertices(treevertex, inserted_vertices) == FAIL) {
        return FAIL;
    }
	if (treevertex_insert(treevertex, under, tree.root) == FAIL) {
        return FAIL;
    }
    size_t i;
    for (i = 0; i < inserted_vertices.set->length; i++) {
        VertexPointer vertex = vertexset_get(inserted_vertices, i);
            *(tree.contains + vertex->label) = true;
    }
    *(tree.nvertices) += inserted_vertices.set->length;
    vertexset_destroy(inserted_vertices);
    return SUCCESS;
}

void tree_evens_odds(Tree tree, VertexSetPointer evens, VertexSetPointer odds)
{
    treevertex_odds_evens(tree.root, true, evens, odds);
}

void tree_evens(Tree tree, VertexSetPointer evens)
{
    tree_evens_odds(tree, evens, NULL);
}

void tree_odds(Tree tree, VertexSetPointer odds)
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
    free(tree.contains);
    free(tree.nvertices);
    if (treevertex_destroy(tree.root) == FAIL) {
        return FAIL;
    } else {
        free(tree.root);
        return SUCCESS;
    }
}

