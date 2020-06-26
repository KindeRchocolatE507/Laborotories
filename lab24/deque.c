#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "deque.h"
void d_init(deque* d) {
d->size = d->capacity = d->shift = 0;
d->data = NULL;
}
bool d_empty(deque* d) {
return d->size == 0;
}
size_t d_size(deque* d) {
return d->size;
}
token d_front(deque* d) {
if (!d_empty(d)) {
return d->data[d->shift];
}
}
token d_back(deque* d) {
if (!d_empty(d)) {
return d->data[(d->size - 1 + d->shift) % d->capacity];
}
}
/*token d_get(deque* d) {
}*/
void d_pop_front(deque* d) {
if(d == 0 || d_empty(d)) {
return;
}
d->size--;
d->shift = (d->shift + 1) % d->capacity;
if (d->size * 2 <= d->capacity && d->size != 0) {
token* temp = malloc(d->size * sizeof(int));
for (int i = 0; i < d->size; ++i) {
temp[i] = d->data[(d->shift + i) % d->capacity];
}
d->capacity = d->size;
d->shift = 0;
free(d->data);
d->data = temp;
} else if (d->size == 0){
free(d->data);
d->data = NULL;
d->capacity = 0;
d->shift = 0;
}
}
void d_pop_back(deque* d) {
if(d == 0 || d_empty(d)) {
return;}
d->size--;
}
void d_push_front(deque* d, token val) {
if (d == 0) {
return;
}
if (d->capacity == d->size) {
size_t old_cap = d->capacity;
d->capacity = d->capacity == 0 ? 1 : d->capacity * 2;
token* temp = malloc(sizeof(token) * d->capacity);
if (d->data != NULL) {
for (int i = 0; i < d->shift; ++i) {
temp[i] = d->data[i];
}
d->shift += d->capacity - old_cap;
for (int i = 0; i < d->capacity - d->shift; ++i) {
temp[d->capacity - 1 - i] = d->data[old_cap - 1 - i];
}
}
free(d->data);
d->data = temp;
}
d->shift = ((d->shift + d->capacity) - 1) % d->capacity;
d->data[d->shift] = val;
d->size++;
}
void d_push_back(deque* d, token val) {
if (d == 0) {
return;
}
if (d->capacity == d->size) {
size_t old_cap = d->capacity;
d->capacity = d->capacity == 0 ? 1 : d->capacity * 2;
token* temp = malloc(sizeof(token) * d->capacity);
if (d->data != NULL) {
for (int i = 0; i < d->shift; ++i) {
temp[i] = d->data[i];
}
d->shift += d->capacity - old_cap;
for (int i = 0; i < d->capacity - d->shift; ++i) {
temp[d->capacity - 1 - i] = d->data[old_cap - 1 - i];
}
}
free(d->data);
d->data = temp;
}
d->data[(d->shift + d->size) % d->capacity] = val;
d->size++;
}
token d_get(deque* d, int index) {
if (index < d->size) {
return d->data[(d->shift + index) % d->capacity];
}
}void d_clear(deque* d) {
free(d->data);
d->capacity = d->shift = d->size = 0;
d->data = NULL;
}
void d_print(deque* d) {
if (d == 0) {
printf("null\n");
return;
}
if (d_empty(d)) {
printf("empty\n");
return;
}
for (int i = 0; i < d->size; ++i) {
token_print(d->data[(d->shift + i) % d->capacity]);
}
printf("\n");
}
void print_mem(deque* d) {
for (int i = 0; i < d->capacity; ++i) {
printf("%d ", d->data[i]);
}
printf("\n");
}