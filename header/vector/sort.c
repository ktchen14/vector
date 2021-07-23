/// @file header/vector/sort.c

#ifndef VECTOR_SORT_C
#define VECTOR_SORT_C

#include <stddef.h>
#include <stdlib.h>

#include "common.h"
#include "sort.h"

__vector_inline__ void vector_sort_z(
    vector_t vector, int (*cmp)(const void *a, const void *b), size_t z) {
  qsort(vector, vector_length(vector), z, cmp);
}

#endif /* VECTOR_SORT_C */
