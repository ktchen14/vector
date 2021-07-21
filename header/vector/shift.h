/// @file header/vector/shift.h

#ifndef VECTOR_SHIFT_H
#define VECTOR_SHIFT_H

#include <stddef.h>
#include "common.h"

/**
 * @copybrief vector_append()
 *
 * This is just vector_append().
 *
 * @see vector_push_z() - the explicit interface analogue
 */
#define vector_push vector_append

/**
 * @copybrief vector_append_z()
 *
 * This is just vector_append_z().
 *
 * @see vector_push() - the implicit interface analogue
 */
#define vector_push_z vector_append_z

/**
 * @brief Copy the last element in the @a vector to @a elmt and remove it
 *
 * If @a elmt is @c NULL then the element won't be copied before it's removed.
 *
 * Once the element is removed, if the @length of the @a vector is reduced such
 * that <code>length <= (volume - 1) / 2</code>, a vector_resize() will be
 * attempted to reduce the @volume to:
 *   @f[ volume = \frac{length \times 6 + 4}{5} @f]
 * On success the shrunk vector will be returned. Otherwise the vector will be
 * returned as is (without the element).
 *
 * If no last element is in the @a vector (the @a vector's length is zero) then
 * the behavior is undefined.
 *
 * @param vector the vector to operate on
 * @param elmt the location to copy the element to or @c NULL
 * @return the resultant vector
 */
//= vector_t vector_pull(vector_t vector, void *elmt)
#define vector_pull(v, ...) vector_pull_z((v), __VA_ARGS__, VECTOR_Z((v)))

/**
 * @brief Copy the last element in the @a vector to @a elmt and remove it
 *
 * If @a elmt is @c NULL then the element won't be copied before it's removed.
 *
 * Once the element is removed, if the @length of the @a vector is reduced such
 * that <code>length <= (volume - 1) / 2</code>, a vector_resize_z() will be
 * attempted to reduce the @volume to:
 *   @f[ volume = \frac{length \times 6 + 4}{5} @f]
 * On success the shrunk vector will be returned. Otherwise the vector will be
 * returned as is (without the element).
 *
 * If no last element is in the @a vector (the @a vector's length is zero) then
 * the behavior is undefined.
 *
 * @param vector the vector to operate on
 * @param elmt the location to copy the element to or @c NULL
 * @param z the element size of the @a vector
 * @return the resultant vector
 */
__vector_inline__ vector_t vector_pull_z(vector_t vector, void *elmt, size_t z)
  __attribute__((nonnull(1), warn_unused_result));

/**
 * @brief Insert the data at @a elmt as the last element in the @a vector
 *
 * If @a elmt is @c NULL then the inserted element will be uninitialized.
 *
 * If the resultant length of the @a vector would overflow a @c size_t then this
 * will set @c errno to @c ENOMEM and return @c NULL. Otherwise this will call
 * vector_ensure(). If that fails then the @a vector will be unmodified and the
 * value of @c errno set by realloc() will be retained.
 *
 * If @a elmt isn't @c NULL and its type is incompatible with the element type
 * of the @a vector then the behavior is undefined. If @a elmt is a location in
 * the @a vector itself then the behavior is undefined.
 *
 * @param vector the vector to operate on
 * @param elmt the location of the element to unshift
 * @return the resultant vector on success; otherwise @c NULL
 *
 * @see vector_unshift_z() - the explicit interface analogue
 */
//= vector_t vector_unshift(restrict vector_t vector, const void *restrict elmt)
#define vector_unshift(v, ...) vector_unshift_z((v), __VA_ARGS__, VECTOR_Z((v)))

/**
 * @brief Insert the data at @a elmt as the first element in the @a vector
 *
 * If @a elmt is @c NULL then the inserted element will be uninitialized.
 *
 * If the resultant length of the @a vector would overflow a @c size_t then this
 * will set @c errno to @c ENOMEM and return @c NULL. Otherwise this will call
 * vector_ensure(). If that fails then the @a vector will be unmodified and the
 * value of @c errno set by realloc() will be retained.
 *
 * If @a elmt isn't @c NULL and its type is incompatible with the element type
 * of the @a vector then the behavior is undefined. If @a elmt is a location in
 * the @a vector itself then the behavior is undefined.
 *
 * @param vector the vector to operate on
 * @param elmt the location of the element to unshift
 * @param z the element size of the @a vector
 * @return the resultant vector on success; otherwise @c NULL
 *
 * @see vector_unshift() - the implicit interface analogue
 */
__vector_inline__ vector_t vector_unshift_z(
    restrict vector_t vector,
    const void *restrict elmt,
    size_t z)
  __attribute__((nonnull(1), warn_unused_result));

/**
 * @brief Copy the first element in the @a vector to @a elmt and remove it
 *
 * All elements after the first are shifted one element toward the head of the
 * @a vector.
 *
 * If @a elmt is @c NULL then the element won't be copied before it's removed.
 *
 * Once the element is removed and subsequent elements are shifted, if the
 * @length of the @a vector is reduced such that <code>length <= (volume - 1) /
 * 2</code>, a vector_resize_z() will be attempted to reduce the @volume to:
 *   @f[ volume = \frac{length \times 6 + 4}{5} @f]
 * On success the shrunk vector will be returned. Otherwise the vector will be
 * returned as is (without the element).
 *
 * If no first element is in the @a vector (the @a vector's length is zero) then
 * the behavior is undefined.
 *
 * @param vector the vector to operate on
 * @param elmt the location to copy the element to or @c NULL
 * @return the resultant vector
 */
//= vector_t vector_shift(vector_t vector, void *elmt)
#define vector_shift(v, ...) vector_shift_z((v), __VA_ARGS__, VECTOR_Z((v)))

/**
 * @brief Copy the first element in the @a vector to @a elmt and remove it
 *
 * All elements after the first are shifted one element toward the head of the
 * @a vector.
 *
 * If @a elmt is @c NULL then the element won't be copied before it's removed.
 *
 * Once the element is removed and subsequent elements are shifted, if the
 * @length of the @a vector is reduced such that <code>length <= (volume - 1) /
 * 2</code>, a vector_resize_z() will be attempted to reduce the @volume to:
 *   @f[ volume = \frac{length \times 6 + 4}{5} @f]
 * On success the shrunk vector will be returned. Otherwise the vector will be
 * returned as is (without the element).
 *
 * If no first element is in the @a vector (the @a vector's length is zero) then
 * the behavior is undefined.
 *
 * @param vector the vector to operate on
 * @param elmt the location to copy the element to or @c NULL
 * @param z the element size of the @a vector
 * @return the resultant vector
 */
__vector_inline__ vector_t vector_shift_z(vector_t vector, void *elmt, size_t z)
  __attribute__((nonnull(1), warn_unused_result));

#endif /* VECTOR_SHIFT_H */

#if (-1- __vector_inline__ -1)
#include "shift.c"
#endif /* __vector_inline__ */
