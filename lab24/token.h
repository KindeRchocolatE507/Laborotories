#ifndef LAB24_TOKEN_H
#define LAB24_TOKEN_H
#include <stdio.h>
#include <stdlib.h>
typedef struct Char_vector char_vector;
typedef union Item item;
typedef struct Token token;
typedef struct Token_vector token_vector;
union Item {
    int number;//0
    char variable_symbol;//1
    enum OperationType {
        Plus,
        Minus,
        Multiply,
        Divide,
        Power,
        UnaryPlus,
        UnaryMinus
    } action;//2
    enum BracketType {
        LeftBracket,
        RightBracket
    } bracket;//3
};
struct Token {
    item content;
    enum TokenType {
        Number,
        Variable,
        Operation,
        Bracket
    } flag;
};
struct Token_vector {
    token* data;
    size_t size;
    size_t capacity;
};
void token_vector_init(token_vector* vec);
void token_vector_push(token_vector* vec, token val);
void token_print(token tok);
void token_vector_clear(token_vector* vec);
void token_vector_print(token_vector* vec);
token make_zero_token();
#endif //LAB24_TOKEN_H