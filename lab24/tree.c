#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "tree.h"
#include "token.h"
int gcd(int a, int b) {
if (a < b) {
gcd(b, a);
}
if (b == 0) {
return a;
}
return gcd(b, a % b);
}
void tree_item_(tree_item* item) {
item->left = 0;
item->right = 0;
}
void tree_fill_pvt(tree_item* item,token_vector* v, size_t* index) {
if (*index == 0) {
return;
}
*index = *index - 1;
item->right = 0;item->left = 0;
if (v->data[*index].flag == Number || v->data[*index].flag == Variable) {
item->value = v->data[*index];
} else {
item->value = v->data[*index];
item->left = malloc(sizeof(tree_item));
item->right = malloc(sizeof(tree_item));
if (v->data[*index].flag == Operation &&
(v->data[*index].content.action == UnaryMinus || v->data[*index].content.action == UnaryPlus)) {
if (v->data[*index].content.action == UnaryMinus) {
item->value.content.action = Minus;
} else {
item->value.content.action = Plus;
}
item->left->value = make_zero_token();
item->left->right = 0;
item->left->left = 0;
tree_fill_pvt(item->right,v , index);
} else {
tree_fill_pvt(item->right, v, index);
tree_fill_pvt(item->left, v, index);
}
}
}
void tree_fill(tree* tree, token_vector* v) {
if (v->size == 0) {
tree->head = 0;
}
tree->head = malloc(sizeof(tree_item));
if (v->data[v->size - 1].flag == Number || v->data[v->size - 1].flag == Variable) {
tree->head->value = v->data[v->size - 1];
tree->head->left = 0;
tree->head->right = 0;
} else {
size_t index = v->size;
tree_fill_pvt(tree->head, v, &index);
}
}
void tree_print_pvt(tree_item* item, int shift) {
if (item == 0) {
return;
}
for (int i = 0; i < shift; ++i) {
printf(" ");
}
token_print(item->value);
printf("\n");
tree_print_pvt(item->right, shift + 2);
tree_print_pvt(item->left, shift + 2);
}
void tree_print(tree* tree) {
tree_print_pvt(tree->head,0);
}
double evaluate_tree_pvt(tree_item* item) {
    if (item->value.flag == Number) {
        return item->value.content.number;
    } else {
        switch (item->value.content.action) {
            case Plus:
            return evaluate_tree_pvt(item->left) + (double)evaluate_tree_pvt(item->right);
            case Minus:
            return evaluate_tree_pvt(item->left) - (double)evaluate_tree_pvt(item->right);
            case Multiply:
            return evaluate_tree_pvt(item->left) * (double)evaluate_tree_pvt(item->right);
            case Divide:
            return evaluate_tree_pvt(item->left) / (double)evaluate_tree_pvt(item->right);
            case Power:
            return pow(evaluate_tree_pvt(item->left),evaluate_tree_pvt(item->right));
        }
    }
}
double evaluate_tree(tree* tree) {
return evaluate_tree_pvt(tree->head);
}
bool is_minus(tree_item* item) {
return item->value.flag == Operation && item->value.content.action == Minus;
}
bool is_multiply(tree_item* item) {
return item->value.flag == Operation && item->value.content.action == Multiply;
}
typedef struct Tree_item_vector tree_item_vector;
struct Tree_item_vector {
tree_item** data;
size_t size;
size_t capacity;
};
void tree_item_vector_init(tree_item_vector* vec) {
vec->data = 0;
vec->size = vec->capacity = 0;
}
void tree_item_vector_push(tree_item_vector* vec, tree_item* val) {
if (vec->size == vec->capacity) {
vec->capacity = vec->capacity == 0 ? 1 : vec->capacity * 2;
vec->data = realloc(vec->data, sizeof(tree_item*) * vec->capacity);
}
vec->data[vec->size] = val;
vec->size++;
}
void tree_item_vector_pop(tree_item_vector* vec, tree_item* val) {
if (vec->size != 0) {
vec->size--;
}
}
int tree_item_vector_not_null_size(tree_item_vector* vec) {
int result = 0;for (int i = 0; i < vec->size; ++i) {
if (vec->data[i]){
result++;
}
}
return result;
}
bool tree_item_vector_find(tree_item_vector* v, tree_item* value) {
bool found = false;
for (int i = 0; i < v->size; ++i) {
if (v->data[i] == value) {
found = true;
break;
}
}
return found;
}
void tree_item_vector_erase(tree_item_vector* vec, int index) {
if (index < 0 || index >= vec->size) {
return;
}
for (int i = index; i < vec->size - 1; ++i) {
vec->data[i] = vec->data[i + 1];
}
vec->size--;
}
void tree_item_vector_clear(tree_item_vector* vec) {
free(vec->data);
vec->data = 0;
vec->size = 0;
vec->capacity = 0;
}
void fill_multipliers_vector(tree_item_vector* v, tree_item* item) {
if (!item) {
return;
}
if (is_multiply(item)) {
fill_multipliers_vector(v, item->left);
fill_multipliers_vector(v, item->right);
} else {
tree_item_vector_push(v, item);
}
}
bool is_same_item(tree_item* lhs, tree_item* rhs) {
if (!lhs || !rhs) {
return !lhs && !rhs;
}
if (lhs->value.flag == rhs->value.flag) {
if(lhs->value.flag == Operation) {
if (lhs->value.content.action == rhs->value.content.action) {
if (lhs->value.content.action == Multiply || lhs->value.content.action == Plus) {
return (is_same_item(lhs->left, rhs->left) && is_same_item(lhs->right, rhs->right))
|| (is_same_item(lhs->right, rhs->left) && is_same_item(lhs->left, rhs->right));
} else {return (is_same_item(lhs->left, rhs->left) && is_same_item(lhs->right, rhs->right));
}
}
return false;
} else if (lhs->value.flag == Variable) {
return lhs->value.content.variable_symbol == rhs->value.content.variable_symbol;
} else if (lhs->value.flag == Number) {
return lhs->value.content.number == rhs->value.content.number;
}
}
return false;
}
tree_item* create_operation_node(enum OperationType op) {
tree_item* new_item = malloc(sizeof(tree_item));
new_item->value.flag = Operation;
new_item->value.content.action = op;
new_item->left = 0;
new_item->right = 0;
return new_item;
}
tree_item* create_number(int number) {
tree_item* new_item = malloc(sizeof(tree_item));
new_item->value.flag = Number;
new_item->value.content.number = number;
new_item->left = 0;
new_item->right = 0;
return new_item;
}
tree_item* create_multiply_subtree(tree_item_vector* v) {
tree_item_vector temp;
tree_item_vector_init(&temp);
for (int i = 0; i < v->size; ++i) {
if (v->data[i]) {
tree_item_vector_push(&temp, v->data[i]);
}
}
if (temp.size == 0) {
tree_item_vector_clear(&temp);
return NULL;
} else if (temp.size == 1) {
tree_item* return_value = temp.data[0];
tree_item_vector_clear(&temp);
return return_value;
}
tree_item* subtree_root = create_operation_node(Multiply);
tree_item* cur_node = subtree_root;
for (int i = 0; i < (int)temp.size - 2; ++i) {
cur_node->left = temp.data[i];
cur_node->right = create_operation_node(Multiply);
cur_node = cur_node->right;
}
cur_node->left = temp.data[temp.size - 2];
cur_node->right = temp.data[temp.size - 1];
tree_item_vector_clear(&temp);
return subtree_root;}
void transform_clear(tree_item* item, tree_item_vector* v) {
if (!item) {
return;
}
if (tree_item_vector_find(v, item)) {
return;
} else {
transform_clear(item->left, v);
transform_clear(item->right, v);
free(item);
}
}
void transform_tree_replace(tree_item* item) {
tree_item_vector left_multipliers;
tree_item_vector right_multipliers;
tree_item_vector intersection;
tree_item_vector not_to_free;
tree_item_vector_init(&left_multipliers);
tree_item_vector_init(&right_multipliers);
tree_item_vector_init(&intersection);
tree_item_vector_init(&not_to_free);
fill_multipliers_vector(&left_multipliers, item->left);
fill_multipliers_vector(&right_multipliers, item->right);
int left_number = 1;
int right_number = 1;
for (int i = 0; i < left_multipliers.size; ++i) {
if (left_multipliers.data[i]->value.flag == Number) {
left_number *= left_multipliers.data[i]->value.content.number;
left_multipliers.data[i] = NULL;
}
}
for (int i = 0; i < right_multipliers.size; ++i) {
if (right_multipliers.data[i]->value.flag == Number) {
right_number *= right_multipliers.data[i]->value.content.number;
right_multipliers.data[i] = NULL;
}
}
for (int i = 0; i < left_multipliers.size; ++i) {
for (int j = 0; j < right_multipliers.size; ++j) {
if (left_multipliers.data[i] != NULL && is_same_item(left_multipliers.data[i],
right_multipliers.data[j])) {
tree_item_vector_push(&intersection, left_multipliers.data[i]);
tree_item_vector_push(&not_to_free, left_multipliers.data[i]);
left_multipliers.data[i] = NULL;
right_multipliers.data[j] = NULL;
break;
}
}
}
int gcd_num = gcd(left_number, right_number);
if (gcd_num != 1) {
tree_item_vector_push(&intersection, create_number(gcd_num));}
if (left_number / gcd_num != 1) {
tree_item_vector_push(&left_multipliers, create_number(left_number / gcd_num));
}
if (right_number / gcd_num != 1) {
tree_item_vector_push(&right_multipliers, create_number(right_number / gcd_num));
}
for (int i = 0; i < left_multipliers.size; ++i) {
if (left_multipliers.data[i]) {
tree_item_vector_push(&not_to_free, left_multipliers.data[i]);
}
}
for (int i = 0; i < right_multipliers.size; ++i) {
if (right_multipliers.data[i]) {
tree_item_vector_push(&not_to_free, right_multipliers.data[i]);
}
}
tree_item* old_left = item->left;
tree_item* old_right = item->right;
tree_item* intersection_tree = create_multiply_subtree(&intersection);
if (intersection_tree == NULL) {
tree_item_vector_clear(&left_multipliers);
tree_item_vector_clear(&right_multipliers);
tree_item_vector_clear(&intersection);
tree_item_vector_clear(&not_to_free);
return;
}
tree_item* left_tree = create_multiply_subtree(&left_multipliers);
if (left_tree == NULL) {
left_tree = create_number(1);
}
tree_item* right_tree = create_multiply_subtree(&right_multipliers);
if (right_tree == NULL) {
right_tree = create_number(1);
}
item->value.flag = Operation;
item->value.content.action = Multiply;
item->left = intersection_tree;
item->right = create_operation_node(Minus);
item->right->left = left_tree;
item->right->right = right_tree;
transform_clear(old_right, &not_to_free);
transform_clear(old_left, &not_to_free);
tree_item_vector_clear(&left_multipliers);
tree_item_vector_clear(&right_multipliers);
tree_item_vector_clear(&intersection);
tree_item_vector_clear(&not_to_free);
}void transform_tree_search(tree_item* item) {
if (!item) {
return;
}
if (is_minus(item)) {
transform_tree_replace(item);
}
transform_tree_search(item->left);
transform_tree_search(item->right);
}
void transform_tree(tree* tree) {
transform_tree_search(tree->head);
}
void tree_get_expression_pvt(tree_item* item) {
if (item == 0) {
return;
}
if (item->value.flag != Number && item->value.flag != Variable) {
printf("( ");
}
tree_get_expression_pvt(item->left);
token_print(item->value);
tree_get_expression_pvt(item->right);
if (item->value.flag != Number && item->value.flag != Variable) {
printf(") ");
}
}
void tree_get_expression(tree* tree) {
tree_get_expression_pvt(tree->head);
}
