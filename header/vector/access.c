/// @file header/vector/access.c

#ifndef VECTOR_ACCESS_C
#define VECTOR_ACCESS_C

#include <stddef.h>
#include <string.h>

#include "common.h"
#include "access.h"

__vector_inline__
size_t vector_index(vector_c vector, const void *elmt, size_t z) {
  // TODO: handle PTRDIFF_MAX
  return (size_t) ((const char *) elmt - (const char *) vector) / z;
}

__vector_inline__
void vector_get(vector_c vector, size_t i, void *elmt, size_t z) {
  // This comparison is well defined regardless of whether elmt is an object in
  // the vector
  if (elmt == vector_at(vector, i, z))
    return;
  memcpy(elmt, vector_at(vector, i, z), z);
}

__vector_inline__
void vector_set(vector_t vector, size_t i, const void *elmt, size_t z) {
  // This comparison is well defined regardless of whether elmt is an object in
  // the vector
  if (elmt == vector_at(vector, i, z))
    return;
  memcpy(vector_at(vector, i, z), elmt, z);
}

#endif /* VECTOR_ACCESS_C */
