#include "token.h"
void token_vector_init(token_vector* vec) {
vec->size = vec->capacity = 0;
vec->data = 0;
}
token make_zero_token() {
token result_token;
result_token.flag = Number;
result_token.content.number = 0;
return result_token;
}
void token_vector_push(token_vector* vec, token val) {
if (vec->size == vec->capacity) {
vec->capacity = vec->capacity == 0 ? 1 : vec->capacity * 2;
vec->data = realloc(vec->data, sizeof(token) * vec->capacity);
}
vec->data[vec->size] = val;
vec->size++;}
void token_print(token tok) {
if (tok.flag == Number) {
printf("%d ", tok.content.number);
} else if (tok.flag == Variable) {
printf("%c ", tok.content.variable_symbol);
} else if(tok.flag == Operation) {
switch (tok.content.action) {
case Plus:
printf("+ ");
break;
case Minus:
printf("- ");
break;
case Multiply:
printf("* ");
break;
case Divide:
printf("/ ");
break;
case Power:
printf("^ ");
break;
case UnaryPlus:
printf("un+ ");
break;
case UnaryMinus:
printf("un- ");
break;
}
} else if(tok.flag == Bracket) {
switch (tok.content.bracket) {
case LeftBracket:
printf("( ");
break;
case RightBracket:
printf(") ");
break;
}
}
}
void token_vector_clear(token_vector* vec) {
free(vec->data);
vec->data = 0;
vec->size = 0;
}
void token_vector_print(token_vector* vec) {
for (int i = 0; i < vec->size; ++i) {
token_print(vec->data[i]);
}
printf("\n");
}