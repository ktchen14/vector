/// @file header/vector/debug.c

#ifndef VECTOR_DEBUG_C
#define VECTOR_DEBUG_C

#include <stddef.h>
#include <stdio.h>
#include "debug.h"
#include "access.h"

__vector_inline__ void vector_debug_z(
    vector_c vector,
    void (*elmt_debug)(const void *elmt),
    size_t z) {
  putc('[', stderr);
  for (size_t i = 0; i < vector_length(vector); i++) {
    if (i > 0)
      fputs(", ", stderr);
    elmt_debug(vector_at(vector, i, z));
  }
  fputs("]\n", stderr);
}

#endif /* VECTOR_DEBUG_C */
