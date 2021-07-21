/// @file header/vector/delete.h

#ifndef VECTOR_DELETE_H
#define VECTOR_DELETE_H

#include "common.h"

/// Deallocate the @a vector and return @c NULL
__vector_inline__ void *vector_delete(vector_t vector) __attribute__((nonnull));

#endif /* VECTOR_DELETE_H */

#if (-1- __vector_inline__ -1)
#include "delete.c"
#endif /* __vector_inline__ */
