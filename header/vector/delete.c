/// @file header/vector/delete.c

#ifndef VECTOR_DELETE_C
#define VECTOR_DELETE_C

#include <stdlib.h>

#include "common.h"
#include "delete.h"

__vector_inline__ void *vector_delete(vector_t vector) {
  return free(__vector_to_header(vector)), NULL;
}

#endif /* VECTOR_DELETE_C */
