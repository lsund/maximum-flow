
#include "treevertex.h"

TreeVertexPointer treevertex_p_make(VertexPointer vertex) {
    TreeVertexPointer ret = malloc(sizeof(TreeVertex));
    ret->content          = vertex;
    ret->parent           = NULL;
    ret->is_root          = false;
    ret->rank             = 0;
    ret->children         = collection_p_init(0);
    return ret;
}

TreeVertexPointer treevertex_p_make_label(const Label label) {
    return treevertex_p_make(vertex_p_make(label));
}

Result treevertex_insert(
        TreeVertexPointer tree_a, 
        const Label under, 
        TreeVertexPointer tree_b
    )
{
    size_t i;
    if (under != tree_b->content->label) {
        for (i = 0; i < tree_b->children->length; i++) {
            Result success = treevertex_insert(tree_a, under, collection_get(tree_b->children, i));
            if (success) {
                return SUCCESS;
            }
        }
        return FAIL;
    } else {
        collection_push(tree_b->children, tree_a);
        tree_a->parent = tree_b;
        return SUCCESS;
    }
}

void treevertex_odds_evens(TreeVertexPointer root, bool even, VertexCollectionPointer evens, VertexCollectionPointer odds)
{
    if (even && evens) {
        vertexcollection_push(*evens, root->content);
    } 
    if (!even && odds) {
        vertexcollection_push(*odds, root->content);
    }
    size_t i;
    for (i = 0; i < root->children->length; i++) {
        treevertex_odds_evens(collection_get(root->children, i), !even, evens, odds);
    }
}

TreeVertexPointer treevertex_subtree(TreeVertexPointer root, VertexPointer under)
{
    if (root->content->label == under->label) {
        return root;
    } else {
        size_t i;
        for (i = 0; i < root->children->length; i++) {
            TreeVertexPointer next = treevertex_subtree(collection_get(root->children, i), under);
            if (next) {
                return next;
            }
        }
        return NULL;
    }
}

size_t treevertex_size(TreeVertexPointer root)
{
    size_t i;
    size_t size = 0;
    for (i = 0; i < root->children->length; i++) {
        size += treevertex_size(collection_get(root->children, i));
    }
    return size + 1;
}

TreeVertexPointer treevertex_get(TreeVertexPointer root, VertexPointer content)
{
    if (vertex_equals(*root->content, *content)) {
        return root;
    }
    size_t i;
    for (i = 0; i < root->children->length; i++) {
        TreeVertexPointer cand = treevertex_get(collection_get(root->children, i), content);
        if (cand) {
            return cand;
        }
    }
    return NULL;
}

TreeVertexPointer treevertex_get_root_child(TreeVertexPointer of)
{
    if (of->is_root) {
        return NULL;
    } else {
        TreeVertexPointer cursor = (TreeVertexPointer) of->parent;
        TreeVertexPointer current = of;
        while (!cursor->is_root) {
            current = cursor;
            cursor = cursor->parent;
        }
        return current;
    }
}

void treevertex_vertices(TreeVertexPointer root, VertexCollection acc)
{
    vertexcollection_push(acc, root->content);
    size_t i;
    for (i = 0; i < root->children->length; i++) {
        treevertex_vertices(collection_get(root->children, i), acc);
    }
}

void treevertex_print(TreeVertexPointer root)
{
    printf("V: %d { ", root->content->label);
    size_t i;
    for (i = 0; i < root->children->length; i++) {
        treevertex_print(collection_get(root->children, i));
    }
    printf(" } ");
}

Result treevertex_destroy(TreeVertexPointer root) 
{
    if (!root) {
        return FAIL;
    }
    size_t i;
    for (i = 0; i < root->children->length; i++) {
        if (treevertex_destroy(collection_get(root->children, i)) == FAIL) {
            return FAIL;
        }
    }
    collection_destroy(root->children);
    return SUCCESS;
}

