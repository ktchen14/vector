/// @file header/vector/move.h

#ifndef VECTOR_MOVE_H
#define VECTOR_MOVE_H

#include <stddef.h>
#include "common.h"

/**
 * @brief Swap the element at index @a i with the element at index @a j in the
 * @a vector
 *
 * @note Though this is implemented as a macro it's documented as a function to
 * clarify its intended usage.
 *
 * If either @a i or @a j isn't an index in the @a vector then the behavior of
 * this operation is undefined.
 *
 * @param vector the vector to operate on
 * @param i the index of an element in the @a vector to swap
 * @param j the index of an element in the @a vector to swap
 *
 * @see vector_swap_z() - the explicit interface analogue
 */
//= void vector_swap(vector_t vector, size_t i, size_t j)
#define vector_swap(v, ...) vector_swap_z((v), __VA_ARGS__, VECTOR_Z((v)))

/**
 * @brief Swap the element at index @a i with the element at index @a j in the
 * @a vector
 *
 * If either @a i or @a j isn't an index in the @a vector then the behavior of
 * this operation is undefined.
 *
 * @param vector the vector to operate on
 * @param i the index of an element in the @a vector to swap
 * @param j the index of an element in the @a vector to swap
 * @param z the element size of the @a vector
 *
 * @see vector_swap() - the implicit interface analogue
 */
__attribute__((nonnull))
__vector_inline__
void vector_swap_z(vector_t vector, size_t i, size_t j, size_t z);

/**
 * @brief Move the element at index @a source to index @a target in the
 * @a vector
 *
 * This will move the element at index @a source to be at index @a target, the
 * element previously at index @a target to index <code>target + 1</code>, and
 * so on. When complete the length of the @a vector is unchanged and (with the
 * exception of the element at @a source) the relative order of each element in
 * the @a vector is unchanged. For example:
 *
 * \code{.c}
 * int *sample = vector_define(int, 2, 4, 6, 8, 10, 12);
 * vector_move(sample, 4, 2);
 * sample == { 2, 4, 10, 6, 8, 12 };
 * \endcode
 *
 * If @a target or @a source isn't an index in the @a vector then the behavior
 * is undefined.
 *
 * @param vector the vector to operate on
 * @param target the index in the @a vector to move the element to
 * @param source the index of the element in the @a vector to move
 *
 * @see vector_move_z() - the explicit interface analogue
 */
//= void vector_move(vector_t vector, size_t target, size_t source)
#define vector_move(v, ...) vector_move_z((v), __VA_ARGS__, VECTOR_Z((v)))

/**
 * @brief Move the element at index @a source to index @a target in the
 * @a vector
 *
 * This will move the element at index @a source to be at index @a target, the
 * element previously at index @a target to index <code>target + 1</code>, and
 * so on. When complete the length of the @a vector is unchanged and (with the
 * exception of the element at @a source) the relative order of each element in
 * the @a vector is unchanged. For example:
 *
 * \code{.c}
 * int *sample = vector_define(int, 2, 4, 6, 8, 10, 12);
 * vector_move(sample, 4, 2);
 * sample == { 2, 4, 10, 6, 8, 12 };
 * \endcode
 *
 * If @a target or @a source isn't an index in the @a vector then the behavior
 * is undefined.
 *
 * @param vector the vector to operate on
 * @param target the index in the @a vector to move the element to
 * @param source the index of the element in the @a vector to move
 * @param z the element size of the @a vector
 *
 * @see vector_move() - the implicit interface analogue
 */
__attribute__((nonnull))
__vector_inline__
void vector_move_z(vector_t vector, size_t target, size_t source, size_t z);

#endif /* VECTOR_MOVE_H */

#if (-1- __vector_inline__ -1)
#include "move.c"
#endif /* __vector_inline__ */
