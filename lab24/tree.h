#ifndef LAB24_TREE_H
#define LAB24_TREE_H
#include "token.h"
typedef struct Tree tree;
typedef struct Tree_item tree_item ;
struct Tree_item { // в дереве операции слева направо: 5-3 -> head == minus, left == 5, right == 3
token value;
struct Tree_item* left;
struct Tree_item* right;
};
struct Tree {
tree_item* head;
};
enum ins_place {
Left,Right
};
double evaluate_tree(tree* tree);
void tree_fill(tree* tree, token_vector* v);
void tree_print(tree* tree);
void transform_tree(tree* tree);
void tree_get_expression(tree* tree);
#endif //LAB24_TREE_H