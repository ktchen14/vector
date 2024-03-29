/// @file header/vector/comparison.c

#ifndef VECTOR_COMPARISON_C
#define VECTOR_COMPARISON_C

#include <stddef.h>

#include "common.h"
#include "comparison.h"
#include "access.h"

__vector_inline__ _Bool vector_eq_z(
    vector_c va,
    vector_c vb,
    _Bool (*eq)(const void *a, const void *b),
    size_t za,
    size_t zb) {
  if (vector_length(va) != vector_length(vb))
    return 0;

  for (size_t i = 0; i < vector_length(va); i++) {
    if (!eq(vector_at(va, i, za), vector_at(vb, i, zb)))
      return 0;
  }
  return 1;
}

__vector_inline__ _Bool vector_eq_with_z(
    vector_c va,
    vector_c vb,
    _Bool (*eq)(const void *a, const void *b, void *data),
    void *data,
    size_t za,
    size_t zb) {
  if (vector_length(va) != vector_length(vb))
    return 0;

  for (size_t i = 0; i < vector_length(va); i++) {
    if (!eq(vector_at(va, i, za), vector_at(vb, i, zb), data))
      return 0;
  }
  return 1;
}

__vector_inline__ int vector_cmp_z(
    vector_c va,
    vector_c vb,
    int (*cmp)(const void *a, const void *b),
    size_t za,
    size_t zb) {
  size_t length[] = { vector_length(vb), vector_length(va) };
  size_t j = length[1] < length[0];

  for (size_t i = 0; i < length[j]; i++) {
    int result;
    if ((result = cmp(vector_at(va, i, za), vector_at(vb, i, zb))) != 0)
      return result;
  }

  return j ? -1 : length[0] < length[1];
}

__vector_inline__ int vector_cmp_with_z(
    vector_c va,
    vector_c vb,
    int (*cmp)(const void *a, const void *b, void *data),
    void *data,
    size_t za,
    size_t zb) {
  size_t length[] = { vector_length(vb), vector_length(va) };
  size_t j = length[1] < length[0];

  for (size_t i = 0; i < length[j]; i++) {
    int result;
    if ((result = cmp(vector_at(va, i, za), vector_at(vb, i, zb), data)) != 0)
      return result;
  }

  return j ? -1 : length[0] < length[1];
}

#endif /* VECTOR_COMPARISON_C */
