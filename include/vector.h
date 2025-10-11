#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef struct {
  void* data;
  size_t size;
  size_t cap;
  size_t elem_size;
} vector_t;

vector_t* vector_create(size_t cap, size_t elem_size);
void vector_free(vector_t* v);

void vector_push_back(vector_t* v, const void* value);
void* vector_pop_back(vector_t* v);
void* vector_at(vector_t* v, size_t index);

static inline size_t vector_get_size(vector_t* v) { return v->size; }
static inline int vector_is_empty(vector_t* v) { return v->size == 0; }

#endif // VECTOR_H
