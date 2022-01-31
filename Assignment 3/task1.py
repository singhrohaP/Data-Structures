#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

void tree_insert(Tree_Node** tree, char data){
    if(!(*tree)){
        printf("%c",data);
        *tree = create_bst(&data);
    }

    else{
        if ((int)((*tree)->data)>(int)data)
            tree_insert(&(*tree)->left,data);
        else
            tree_insert(&(*tree)->right,data);
    }
}

Tree_Node* create_bst (char data[]){
    struct Tree_Node* result = malloc(sizeof(Tree_Node));
    if(result != NULL){
        result->left = NULL;
        result->right = NULL;
        result->data = *data;
    }
    return result;
}

Tree_Node* tree_search(Tree_Node* root, char data){
    if(root==NULL || root->data==data)
            return root;
    else if(data>root->data)
        return tree_search(root->right, data);
    else
        return tree_search(root->left,data);

}

void tree_print_sorted(Tree_Node* root){
    if (root!= NULL)
        {
            tree_print_sorted(root->left);
            printf("%c",root->data);
            tree_print_sorted(root->right);
        }
}

void tree_delete(Tree_Node* root){
    if (root == NULL) return;
    tree_delete(root->left);
    tree_delete(root->right);
    printf("%c", root->data);
    free(root);

}


