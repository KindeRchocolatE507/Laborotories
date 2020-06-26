#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include "deque.h"
#include "token.h"
#include "tree.h"
struct Char_vector {
char* data;
int size;
int capacity;
};
void char_vector_init(char_vector* vec) {
vec->size = vec->capacity = 0;
vec->data = 0;
vec->capacity = 0;
}
void char_vector_push(char_vector* vec, char val) {
if (vec->size == vec->capacity) {
vec->capacity = vec->capacity == 0 ? 1 : vec->capacity * 2;
vec->data = realloc(vec->data, sizeof(char) * vec->capacity);
}
vec->data[vec->size] = val;
vec->size++;
}
void char_vector_clear(char_vector* vec) {
free(vec->data);
vec->data = 0;
vec->size = 0;
vec->capacity = 0;
}
int make_int(char_vector* vec) {
    int power = 0;
    int result = 0;
    for (int i = vec->size - 1; i >= 0; --i) {
        result += (vec->data[i] - 48)/* * (int)pow(10,power)*/;
        power++;
    }
    return result;
}

void parse_expression(token_vector* tokens) {
char cur_symbol = getchar();
int temp = 0;
char_vector number;
char_vector_init(&number);
bool parsing_number = false;
bool next_unary = true;
token new_token;
while(true) {
if (cur_symbol == '\n' || cur_symbol == ' ') {
if (parsing_number == true) {
new_token.content.number = make_int(&number);
new_token.flag = Number;
token_vector_push(tokens, new_token);
char_vector_clear(&number);
next_unary = false;
}
break;
}
if (isdigit(cur_symbol)) {
parsing_number = true;
char_vector_push(&number, cur_symbol);
} else {
if (parsing_number == true) {
parsing_number = false;
next_unary = false;
new_token.content.number = make_int(&number);
new_token.flag = Number;
token_vector_push(tokens, new_token);
char_vector_clear(&number);
}
if (isalpha(cur_symbol)) {
new_token.content.variable_symbol = (char)tolower(cur_symbol);
new_token.flag = Variable;
token_vector_push(tokens, new_token);
next_unary = false;
} else if (cur_symbol == '(') {
new_token.content.bracket = LeftBracket;
new_token.flag = Bracket;
token_vector_push(tokens, new_token);
next_unary = true;
} else if(cur_symbol == ')') {
new_token.content.bracket = RightBracket;new_token.flag = Bracket;
token_vector_push(tokens, new_token);
next_unary = false;
} else if(cur_symbol == '+') {
if (next_unary) {
new_token.content.action = UnaryPlus;
new_token.flag = Operation;
} else {
new_token.content.action = Plus;
new_token.flag = Operation;
}
token_vector_push(tokens,new_token);
next_unary = false;
} else if(cur_symbol == '^') {
new_token.content.action = Power;
new_token.flag = Operation;
token_vector_push(tokens,new_token);
next_unary = true;
} else if(cur_symbol == '-') {
if (next_unary) {
new_token.content.action = UnaryMinus;
new_token.flag = Operation;
} else {
new_token.content.action = Minus;
new_token.flag = Operation;
}
token_vector_push(tokens,new_token);
next_unary = false;
} else if(cur_symbol == '*') {
new_token.content.action = Multiply;
new_token.flag = Operation;
token_vector_push(tokens, new_token);
next_unary = true;
} else if(cur_symbol == '/') {
new_token.content.action = Divide;
new_token.flag = Operation;
token_vector_push(tokens, new_token);
next_unary = true;
}
}
cur_symbol = getchar();
}
}
token_vector shunting_yard(token_vector* v) {
token_vector result_queue;
token_vector_init(&result_queue);
deque stack;
d_init(&stack);
for (int i = 0; i < v->size; ++i) {
if (v->data[i].flag == Number || v->data[i].flag == Variable) {
token_vector_push(&result_queue,v->data[i]);
} else if (v->data[i].flag == Operation) {
//if (!(!d_empty(&stack) && !(d_back(&stack).flag == Bracket && d_back(&stack).content.bracket ==LeftBracket))) {}
while (!d_empty(&stack) && d_back(&stack).flag == Operation &&
((v->data[i].content.action != Power && v->data[i].content.action <=
d_back(&stack).content.action) ||(v->data[i].content.action == Power && v->data[i].content.action <
d_back(&stack).content.action))) {
token_vector_push(&result_queue,d_back(&stack));
d_pop_back(&stack);
}
d_push_back(&stack, v->data[i]);
} else if (v->data[i].flag == Bracket) {
if (v->data[i].content.bracket == LeftBracket) {
d_push_back(&stack, v->data[i]);
} else {
    while (!d_empty(&stack) && !(d_back(&stack).flag == Bracket && d_back(&stack).content.bracket
== LeftBracket) ) {
token_vector_push(&result_queue, d_back(&stack));
d_pop_back(&stack);
}
if (d_empty(&stack)) {
printf("Problem with entered expression: some bracked was missed\n");
exit(1);
}
d_pop_back(&stack);
}
}
}
while (!d_empty(&stack)) {
if (d_back(&stack).flag == Bracket) {
printf("Problem with entered expression: extra bracket in the expression\n");
exit(1);
}
token_vector_push(&result_queue, d_back(&stack));
d_pop_back(&stack);
}
return result_queue;
}
int main() {
token_vector v;
printf("enter expression\n");
token_vector_init(&v);
parse_expression(&v);
printf("entered expression:\n");
token_vector_print(&v);
token_vector postfix_notation = shunting_yard(&v);
printf("postfix notation:\n");
token_vector_print(&postfix_notation);
tree expression_tree;
tree_fill(&expression_tree, &postfix_notation);
printf("abstract syntax tree:\n");
tree_print(&expression_tree);
transform_tree(&expression_tree);
printf("transformed syntax tree:\n");
tree_print(&expression_tree);
printf("result expression:\n");
tree_get_expression(&expression_tree);
return 0;
}