
#include "tree.h"

static Result insert_aux(
        TreeVertexPointer tree_a, 
        const Label under, 
        TreeVertexPointer tree_b
    )
{
    size_t i;
    if (under != tree_b->content->label) {
        for (i = 0; i < tree_b->children->nelements; i++) {
            Result success = insert_aux(tree_a, under, get_element(tree_b->children, i));
            if (success) {
                return SUCCESS;
            }
        }
        return FAIL;
    } else {
        push_element(tree_b->children, tree_a);
        tree_a->parent = tree_b;
        return SUCCESS;
    }
}

static void tree_evens_odds_aux(TreeVertexPointer root, bool even, VertexSetPointer evens, VertexSetPointer odds)
{
    if (even && evens) {
        push_vertex(*evens, root->content);
    } 
    if (!even && odds) {
        push_vertex(*odds, root->content);
    }
    size_t i;
    for (i = 0; i < root->children->nelements; i++) {
        tree_evens_odds_aux(get_element(root->children, i), !even, evens, odds);
    }
}

static void traverse_aux(TreeVertexPointer root)
{
    printf("V: %d { ", root->content->label);
    size_t i;
    for (i = 0; i < root->children->nelements; i++) {
        traverse_aux(get_element(root->children, i));
    }
    printf(" } ");
}

/* static TreeVertexPointer subtree(TreeVertexPointer root, VertexPointer under) */
/* { */
/*     if (root->content->label == under->label) { */
/*         return root; */
/*     } else { */
/*         size_t i; */
/*         for (i = 0; i < root->children->nelements; i++) { */
/*             TreeVertexPointer next = subtree(get_element(root->children, i), under); */
/*             if (next) { */
/*                 return next; */
/*             } */
/*         } */
/*         return NULL; */
/*     } */
/* } */

TreeVertexPointer make_p_tree_vertex(VertexPointer vertex) {
    TreeVertexPointer ret = malloc(sizeof(TreeVertex));
    ret->content          = vertex;
    ret->parent           = NULL;
    ret->is_root          = false;
    ret->rank             = 0;
    ret->children         = empty_p_array();
    return ret;
}

TreeVertexPointer make_p_tree_vertex_label(const Label label) {
    return make_p_tree_vertex(make_p_vertex(label));
}

Result destroy_tree_vertex(TreeVertexPointer root) 
{
    if (!root) {
        return FAIL;
    }
    size_t i;
    for (i = 0; i < root->children->nelements; i++) {
        if (destroy_tree_vertex(get_element(root->children, i)) == FAIL) {
            return FAIL;
        }
    }
    destroy_array(root->children);
    return SUCCESS;
}

Tree empty_tree() {
    Tree ret;
    ret.root = NULL;
    ret.contains = NULL;
    ret.nvertices = NULL;
    return ret;
}

TreePointer empty_p_tree() {
    TreePointer ret = malloc(sizeof(Tree));
    *ret = empty_tree();
    return ret;
}

bool is_emtpy_tree(Tree tree) {
    return tree.root == NULL || tree.contains == NULL; 
}

Tree make_singleton_tree(const VertexPointer vertex, const size_t maxsize)
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

Tree make_singleton_tree_label(const Label rootlabel, const size_t maxsize)
{
    return make_singleton_tree(make_p_vertex(rootlabel), maxsize);
}

Tree make_tree(const TreeVertexPointer root, const size_t maxsize)
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

Result tree_vertices(TreeVertexPointer root, VertexSet acc)
{
    if (push_vertex(acc, root->content)) {
        size_t i;
        for (i = 0; i < root->children->nelements; i++) {
            tree_vertices(get_element(root->children, i), acc);
        }
    } else {
        return FAIL;
    }
    return SUCCESS;
}

bool tree_contains_vertex(Tree tree, VertexPointer vertex)
{
    if (vertex->label > tree.maxsize) {
        return false;
    }
    return *(tree.contains + vertex->label);
}

Result insert(TreeVertexPointer treevertex, const Label under, Tree tree)
{
    VertexSet inserted_vertices = init_vertexset(tree.maxsize);
    if (inserted_vertices.set->length == 0) {
        return FAIL;
    }
    if (tree_vertices(treevertex, inserted_vertices) == FAIL) {
        return FAIL;
    }
	if (insert_aux(treevertex, under, tree.root) == FAIL) {
        return FAIL;
    }
    size_t i;
    for (i = 0; i < inserted_vertices.set->nelements; i++) {
        VertexPointer vertex = get_vertex(inserted_vertices, i);
            *(tree.contains + vertex->label) = true;
    }
    *(tree.nvertices) += inserted_vertices.set->nelements;
    destroy_vertexset(inserted_vertices);
    return SUCCESS;
}

void tree_evens_odds(Tree tree, VertexSetPointer evens, VertexSetPointer odds)
{
    tree_evens_odds_aux(tree.root, true, evens, odds);
}

void tree_evens(Tree tree, VertexSetPointer evens)
{
    tree_evens_odds(tree, evens, NULL);
}

void tree_odds(Tree tree, VertexSetPointer odds)
{
    tree_evens_odds(tree, NULL, odds);
}

TreeVertexPointer get_tree_vertex(TreeVertexPointer root, VertexPointer content)
{
    if (vertices_equal(root->content, content)) {
        return root;
    }
    size_t i;
    for (i = 0; i < root->children->nelements; i++) {
        TreeVertexPointer cand = get_tree_vertex(get_element(root->children, i), content);
        if (cand) {
            return cand;
        }
    }
    return NULL;
}

void traverse(Tree tree) {
    traverse_aux(tree.root);
    printf("\n");
}

Result destroy_tree(Tree tree)
{
    free(tree.contains);
    free(tree.nvertices);
    if (destroy_tree_vertex(tree.root) == FAIL) {
        return FAIL;
    } else {
        free(tree.root);
        return SUCCESS;
    }
}

/* testing exports ************************************************************ */ 

Result (*t_insert_aux)(
        TreeVertexPointer tree_a, 
        const Label under, 
        TreeVertexPointer tree_b
    ) = insert_aux;

