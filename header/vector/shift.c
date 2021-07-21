/// @file header/vector/shift.c

#ifndef VECTOR_SHIFT_C
#define VECTOR_SHIFT_C

#include <stddef.h>

#include "common.h"
#include "access.h"
#include "insert.h"
#include "remove.h"

__vector_inline__
vector_t vector_pull_z(vector_t vector, void *elmt, size_t z) {
  if (elmt != NULL)
    vector_get(vector, vector_length(vector) - 1, elmt, z);
  return vector_remove_z(vector, vector_length(vector) - 1, z);
}

__vector_inline__ vector_t vector_unshift_z(
    restrict vector_t vector,
    const void *restrict elmt,
    size_t z) {
  return vector_insert_z(vector, 0, elmt, z);
}

__vector_inline__
vector_t vector_shift_z(vector_t vector, void *elmt, size_t z) {
  if (elmt != NULL)
    vector_get(vector, 0, elmt, z);
  return vector_remove_z(vector, 0, z);
}

#endif /* VECTOR_SHIFT_C */
