#ifndef LAB24_QUEUE_H
#define LAB24_QUEUE_H
#include <stdbool.h>
#include <stdlib.h>
#include "token.h"
typedef struct Deque deque;
struct Deque {
    size_t size;
    size_t capacity;
    size_t shift;
    token* data;
};
void d_init(deque* d);
bool d_empty(deque* d);
token d_front(deque* d);
token d_back(deque* d);void d_pop_back(deque* d);
void d_pop_front(deque* d);
void d_push_front(deque* d, token val);
void d_push_back(deque* d, token val);
void d_clear(deque* d);
void d_print(deque* d);
void print_mem(deque* d);
#endif //LAB24_QUEUE_H