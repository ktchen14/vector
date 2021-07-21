/// @file header/vector/debug.h

#ifndef VECTOR_DEBUG_H
#define VECTOR_DEBUG_H

#include <stddef.h>
#include "common.h"

/**
 * @brief Print debugging information about the @a vector to @c stderr
 *
 * @param vector the vector to operate on
 * @param elmt_debug the function that will be called to print debugging
 *   information about each element in the @a vector
 */
//= void vector_debug(vector_c vector, void (*elmt_debug)(const void *elmt))
#define vector_debug(v, ...) vector_debug_z((v), __VA_ARGS__, VECTOR_Z((v)))

/**
 * @brief Print debugging information about the @a vector to @c stderr
 *
 * @param vector the vector to operate on
 * @param elmt_debug the function that will be called to print debugging
 *   information about each element in the @a vector
 * @param z the element size of the @a vector
 */
__vector_inline__ void vector_debug_z(
    vector_c vector,
    void (*elmt_debug)(const void *elmt),
    size_t z)
  __attribute__((nonnull));

#endif /* VECTOR_DEBUG_H */

#if (-1- __vector_inline__ -1)
#include "debug.c"
#endif /* __vector_inline__ */
