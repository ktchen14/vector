/**
 * @file header/vector/insert.h
 *
 * Each operation in this module will increase the length of the @a vector. In
 * each case, if the increased length of the @a vector would overflow a @c
 * size_t then the operation will set @c errno to @c ENOMEM and fail. Otherwise,
 * it will call vector_ensure() on the @a vector with the resultant length. If
 * that call fails then the operation will fail, with the @a vector unmodified
 * and the value of @c errno set by realloc() retained.
 */

#ifndef VECTOR_INSERT_H
#define VECTOR_INSERT_H

#include <stddef.h>
#include "common.h"

/**
 * @brief Insert the object at @a elmt into the @a vector at index @a i
 *
 * @par Example
 * @code{.c}
 *   vector_on(int) vector = vector_create();
 *
 *   vector = vector_insert(vector, 0, &(int) { 1 });
 *   vector = vector_insert(vector, 0, &(int) { 2 });
 *   vector = vector_insert(vector, 0, &(int) { 3 });
 *
 *   // vector ≡ [3, 2, 1]
 * @endcode
 *
 * On success, the index of the inserted element will be @a i and the @length of
 * the @a vector will be incremented by 1; then the resultant vector is returned
 * and the original @a vector invalidated.
 *
 * If the incremented length of the @a vector would overflow a @c size_t then
 * this will set @c errno to @c ENOMEM and fail. Otherwise, this will call
 * vector_ensure() on the @a vector with the resultant length. If that call
 * fails then this operation will fail, with the @a vector unmodified and the
 * value of @c errno set by realloc() retained.
 *
 * Before the object at @a elmt is copied into the @a vector, each element at
 * index @a i or greater is displaced by one toward the tail of the @a vector,
 * such that the element at index @a i is moved to index <tt>i + 1</tt>, the
 * element at index <tt>i + 1</tt> is moved to index <tt>i + 2</tt>, and so on.
 * If @a i is the length of the @a vector then the object will instead be
 * appended to the @a vector. If @a elmt is @c NULL then the inserted element
 * will be uninitialized.
 *
 * If the @a vector didn't have an element type before this operation then the
 * type of the object at @a elmt will become the element type of the @a vector.
 *
 * @warning @parblock The behavior of this operation is undefined when:
 *
 *   - @a i is greater than the length of the @a vector
 *   - @a elmt isn't @c NULL and a read from @a elmt, of the same size as the
 *     element size of the @a vector, would access beyond the end of the object
 *     at @a elmt
 *   - @a elmt isn't @c NULL and the object at @a elmt is, or overlaps with, an
 *     element in the @a vector
 *
 *   A successful call to this operation will invalidate the original @a vector
 *   and any subsequent access to, or operation on, it is undefined behavior.
 * @endparblock
 *
 * @param vector the vector to operate on
 * @param i the index in the @a vector to insert the element, or its length
 * @param elmt a pointer to the element to insert, or @c NULL
 * @return the resultant vector on success; otherwise @c NULL
 *
 * @see vector_insert_z() - the explicit analogue of this operation
 */
//= vector_t vector_insert(
//=   restrict vector_t vector, size_t i, const void *restrict elmt)
#define vector_insert(v, ...) vector_insert_z((v), __VA_ARGS__, VECTOR_Z((v)))

/**
 * @brief Insert the object at @a elmt into the @a vector at index @a i
 *
 * @par Example
 * @code{.c}
 *   vector_on(int) vector = vector_create();
 *
 *   vector = vector_insert_z(vector, 0, &(int) { 1 }, sizeof(int));
 *   vector = vector_insert_z(vector, 0, &(int) { 2 }, sizeof(int));
 *   vector = vector_insert_z(vector, 0, &(int) { 3 }, sizeof(int));
 *
 *   // vector ≡ [3, 2, 1]
 * @endcode
 *
 * On success, the index of the inserted element will be @a i and the @length of
 * the @a vector will be incremented by 1; then the resultant vector is returned
 * and the original @a vector invalidated.
 *
 * If the incremented length of the @a vector would overflow a @c size_t then
 * this will set @c errno to @c ENOMEM and fail. Otherwise, this will call
 * vector_ensure_z() on the @a vector with the resultant length. If that call
 * fails then this operation will fail, with the @a vector unmodified and the
 * value of @c errno set by realloc() retained.
 *
 * Before the object at @a elmt is copied into the @a vector, each element at
 * index @a i or greater is displaced by one toward the tail of the @a vector,
 * such that the element at index @a i is moved to index <tt>i + 1</tt>, the
 * element at index <tt>i + 1</tt> is moved to index <tt>i + 2</tt>, and so on.
 * If @a i is the length of the @a vector then the object will instead be
 * appended to the @a vector. If @a elmt is @c NULL then the inserted element
 * will be uninitialized.
 *
 * If the @a vector didn't have an element type before this operation then the
 * type of the object at @a elmt will become the element type of the @a vector.
 *
 * @warning @parblock The behavior of this operation is undefined when:
 *
 *   - @a i is greater than the length of the @a vector
 *   - @a elmt isn't @c NULL and a read from @a elmt of size @a z would access
 *     beyond the end of the object at @a elmt
 *   - @a elmt isn't @c NULL and the object at @a elmt is, or overlaps with, an
 *     element in the @a vector
 *   - @a z isn't the element size of the @a vector
 *
 *   A successful call to this operation will invalidate the original @a vector
 *   and any subsequent access to, or operation on, it is undefined behavior.
 * @endparblock
 *
 * @param vector the vector to operate on
 * @param i the index in the @a vector to insert the element, or its length
 * @param elmt a pointer to the element to insert, or @c NULL
 * @param z the element size of the @a vector
 * @return the resultant vector on success; otherwise @c NULL
 *
 * @see vector_insert() - the implicit analogue of this operation
 */
__vector_inline__ vector_t vector_insert_z(
    restrict vector_t vector, size_t i, const void *restrict elmt, size_t z)
  __attribute__((nonnull(1), warn_unused_result));

/**
 * @brief Insert @a n elements from @a elmt into the @a vector at index @a i
 *
 * @par Example
 * @code{.c}
 *   vector_on(int) vector = vector_create();
 *
 *   vector = vector_inject(vector, 0, &(int[]) { 1, 2 }, 2);
 *   // vector ≡ [1, 2]
 *
 *   vector = vector_inject(vector, 0, &(int[]) { 3, 5 }, 2);
 *   // vector ≡ [3, 5, 1, 2]
 * @endcode
 *
 * On success, the indices of the inserted elements will be @a i to <tt>i + n -
 * 1</tt> and the @length of the @a vector will be increased by @a n; then the
 * resultant vector is returned and the original @a vector invalidated. This is
 * more efficient than @a n separate calls to vector_insert() as the elements
 * from @a i to <tt>i + n - 1</tt> will be moved only once.
 *
 * If the increased length of the @a vector would overflow a @c size_t then this
 * will set @c errno to @c ENOMEM and fail. Otherwise, this will call
 * vector_ensure() on the @a vector with the resultant length. If that call
 * fails then this operation will fail, with the @a vector unmodified and the
 * value of @c errno set by realloc() retained.
 *
 * Before the @a n elements at @a elmt are copied into the @a vector, each
 * element at index @a i or greater is displaced by @a n toward the tail of the
 * @a vector, such that the element at index @a i is moved to index <tt>i +
 * n</tt>, the element at index <tt>i + 1</tt> is moved to index <tt>i + n +
 * 1</tt>, and so on. If @a i is the length of the @a vector then the elements
 * will instead be appended to the @a vector. If @a elmt is @c NULL then the
 * inserted elements will be uninitialized.
 *
 * If the @a vector didn't have an element type before this operation then,
 * unless @a n is zero, the element type of @a elmt will become the element type
 * of the @a vector.
 *
 * @warning @parblock The behavior of this operation is undefined when:
 *
 *   - @a i is greater than the length of the @a vector
 *   - @a elmt isn't @c NULL and a read from @a elmt, of the same size as the
 *     element size of the @a vector multiplied by @a n, would access beyond the
 *     end of the object at @a elmt
 *   - @a elmt isn't @c NULL and any of the @a n elements at @a elmt are, or
 *     overlap with, an element in the @a vector
 *
 *   A successful call to this operation will invalidate the original @a vector
 *   and any subsequent access to, or operation on, it is undefined behavior.
 * @endparblock
 *
 * @param vector the vector to operate on
 * @param i the index in the @a vector to insert the elements, or its length
 * @param elmt a pointer to the elements to insert, or @c NULL
 * @param n the number of elements to insert from @a elmt
 * @return the resultant vector on success; otherwise @c NULL
 *
 * @see vector_inject_z() - the explicit analogue of this operation
 */
//= vector_t vector_inject(
//=   restrict vector_t vector, size_t i, const void *restrict elmt, size_t n)
#define vector_inject(v, ...) vector_inject_z((v), __VA_ARGS__, VECTOR_Z((v)))

/**
 * @brief Insert @a n elements from @a elmt into the @a vector at index @a i
 *
 * @par Example
 * @code{.c}
 *   vector_on(int) vector = vector_create();
 *
 *   vector = vector_inject_z(vector, 0, &(int[]) { 1, 2 }, 2, sizeof(int));
 *   // vector ≡ [1, 2]
 *
 *   vector = vector_inject_z(vector, 0, &(int[]) { 3, 5 }, 2, sizeof(int));
 *   // vector ≡ [3, 5, 1, 2]
 * @endcode
 *
 * On success, the indices of the inserted elements will be @a i to <tt>i + n -
 * 1</tt> and the @length of the @a vector will be increased by @a n; then the
 * resultant vector is returned and the original @a vector invalidated. This is
 * more efficient than @a n separate calls to vector_insert_z() as the elements
 * from @a i to <tt>i + n - 1</tt> will be moved only once.
 *
 * If the increased length of the @a vector would overflow a @c size_t then this
 * will set @c errno to @c ENOMEM and fail. Otherwise, this will call
 * vector_ensure_z() on the @a vector with the resultant length. If that call
 * fails then this operation will fail, with the @a vector unmodified and the
 * value of @c errno set by realloc() retained.
 *
 * Before the @a n elements at @a elmt are copied into the @a vector, each
 * element at index @a i or greater is displaced by @a n toward the tail of the
 * @a vector, such that the element at index @a i is moved to index <tt>i +
 * n</tt>, the element at index <tt>i + 1</tt> is moved to index <tt>i + n +
 * 1</tt>, and so on. If @a i is the length of the @a vector then the elements
 * will instead be appended to the @a vector. If @a elmt is @c NULL then the
 * inserted elements will be uninitialized.
 *
 * If the @a vector didn't have an element type before this operation then,
 * unless @a n is zero, the element type of @a elmt will become the element type
 * of the @a vector.
 *
 * @warning @parblock The behavior of this operation is undefined when:
 *
 *   - @a i is greater than the length of the @a vector
 *   - @a elmt isn't @c NULL and a read from @a elmt of size <tt>n * z</tt>
 *     would access beyond the end of the object at @a elmt
 *   - @a elmt isn't @c NULL and any of the @a n elements at @a elmt are, or
 *     overlap with, an element in the @a vector
 *   - @a z isn't the element size of the @a vector
 *
 *   A successful call to this operation will invalidate the original @a vector
 *   and any subsequent access to, or operation on, it is undefined behavior.
 * @endparblock
 *
 * @param vector the vector to operate on
 * @param i the index in the @a vector to insert the elements, or its length
 * @param elmt a pointer to the elements to insert, or @c NULL
 * @param n the number of elements to insert from @a elmt
 * @param z the element size of the @a vector
 * @return the resultant vector on success; otherwise @c NULL
 *
 * @see vector_inject() - the implicit analogue of this operation
 */
__vector_inline__ vector_t vector_inject_z(
    restrict vector_t vector,
    size_t i,
    const void *restrict elmt,
    size_t n,
    size_t z)
  __attribute__((nonnull(1), warn_unused_result));

/**
 * @brief Insert the object at @a elmt as the last element in the @a vector
 *
 * @par Example
 * @code{.c}
 *   vector_on(int) vector = vector_create();
 *
 *   vector = vector_append(vector, &(int) { 1 });
 *   vector = vector_append(vector, &(int) { 2 });
 *   vector = vector_append(vector, &(int) { 3 });
 *
 *   // vector ≡ [1, 2, 3]
 * @endcode
 *
 * On success, the object will be the last element in the @a vector and the
 * @length of the @a vector will be incremented by 1; then the resultant vector
 * is returned and the original @a vector invalidated.
 *
 * If the incremented length of the @a vector would overflow a @c size_t then
 * this will set @c errno to @c ENOMEM and fail. Otherwise, this will call
 * vector_ensure() on the @a vector with the resultant length. If that call
 * fails then this operation will fail, with the @a vector unmodified and the
 * value of @c errno set by realloc() retained.
 *
 * If @a elmt is @c NULL then the appended element will be uninitialized.
 *
 * If the @a vector didn't have an element type before this operation then the
 * type of the object at @a elmt will become the element type of the @a vector.
 *
 * @warning @parblock The behavior of this operation is undefined when:
 *
 *   - @a elmt isn't @c NULL and a read from @a elmt, of the same size as the
 *     element size of the @a vector, would access beyond the end of the object
 *     at @a elmt
 *   - @a elmt isn't @c NULL and the object at @a elmt is, or overlaps with, an
 *     element in the @a vector
 *
 *   A successful call to this operation will invalidate the original @a vector
 *   and any subsequent access to, or operation on, it is undefined behavior.
 * @endparblock
 *
 * @param vector the vector to operate on
 * @param elmt a pointer to the element to append, or @c NULL
 * @return the resultant vector on success; otherwise @c NULL
 *
 * @see vector_append_z() - the explicit analogue of this operation
 */
//= vector_t vector_append(restrict vector_t vector, const void *restrict elmt)
#define vector_append(v, ...) vector_append_z((v), __VA_ARGS__, VECTOR_Z((v)))

/**
 * @brief Insert the object at @a elmt as the last element in the @a vector
 *
 * @par Example
 * @code{.c}
 *   vector_on(int) vector = vector_create();
 *
 *   vector = vector_append_z(vector, &(int) { 1 }, sizeof(int));
 *   vector = vector_append_z(vector, &(int) { 2 }, sizeof(int));
 *   vector = vector_append_z(vector, &(int) { 3 }, sizeof(int));
 *
 *   // vector ≡ [1, 2, 3]
 * @endcode
 *
 * On success, the object will be the last element in the @a vector and the
 * @length of the @a vector will be incremented by 1; then the resultant vector
 * is returned and the original @a vector invalidated.
 *
 * If the incremented length of the @a vector would overflow a @c size_t then
 * this will set @c errno to @c ENOMEM and fail. Otherwise, this will call
 * vector_ensure_z() on the @a vector with the resultant length. If that call
 * fails then this operation will fail, with the @a vector unmodified and the
 * value of @c errno set by realloc() retained.
 *
 * If @a elmt is @c NULL then the appended element will be uninitialized.
 *
 * If the @a vector didn't have an element type before this operation then the
 * type of the object at @a elmt will become the element type of the @a vector.
 *
 * @warning @parblock The behavior of this operation is undefined when:
 *
 *   - @a elmt isn't @c NULL and a read from @a elmt, of the same size as the
 *     element size of the @a vector, would access beyond the end of the object
 *     at @a elmt
 *   - @a elmt isn't @c NULL and the object at @a elmt is, or overlaps with, an
 *     element in the @a vector
 *   - @a z isn't the element size of the @a vector
 *
 *   A successful call to this operation will invalidate the original @a vector
 *   and any subsequent access to, or operation on, it is undefined behavior.
 * @endparblock
 *
 * @param vector the vector to operate on
 * @param elmt a pointer to the element to append, or @c NULL
 * @param z the element size of the @a vector
 * @return the resultant vector on success; otherwise @c NULL
 *
 * @see vector_append() - the implicit analogue of this operation
 */
__vector_inline__ vector_t vector_append_z(
    restrict vector_t vector, const void *restrict elmt, size_t z)
  __attribute__((nonnull(1), warn_unused_result));

/**
 * @brief Append @a n elements from @a elmt to the tail of the @a vector
 *
 * @par Example
 * @code{.c}
 *   vector_on(int) vector = vector_create();
 *
 *   vector = vector_extend(vector, &(int[]) { 1, 2 }, 2);
 *   // vector ≡ [1, 2]
 *
 *   vector = vector_extend(vector, &(int[]) { 3, 5 }, 2);
 *   // vector ≡ [1, 2, 3, 5]
 * @endcode
 *
 * On success, the elements at @a elmt will form the suffix of the @a vector,
 * such that the element at <tt>elmt + n - 1</tt> will be at index <tt>length -
 * 1</tt>, the element at <tt>elmt + n - 2</tt> will be at index <tt>length -
 * 2</tt>, and so on. The @length of the @a vector will be increased by @a n.
 * Then the resultant vector is returned and the original @a vector invalidated.
 * This is more efficient than @a n separate calls to vector_append().
 *
 * If the increased length of the @a vector would overflow a @c size_t then this
 * will set @c errno to @c ENOMEM and fail. Otherwise, this will call
 * vector_ensure() on the @a vector with the resultant length. If that call
 * fails then this operation will fail, with the @a vector unmodified and the
 * value of @c errno set by realloc() retained.
 *
 * If @a elmt is @c NULL then the appended elements will be uninitialized.
 *
 * If the @a vector didn't have an element type before this operation then,
 * unless @a n is zero, the element type of @a elmt will become the element type
 * of the @a vector.
 *
 * @warning @parblock The behavior of this operation is undefined when:
 *
 *   - @a elmt isn't @c NULL and a read from @a elmt, of the same size as the
 *     element size of the @a vector multiplied by @a n, would access beyond the
 *     end of the object at @a elmt
 *   - @a elmt isn't @c NULL and any of the @a n elements at @a elmt are, or
 *     overlap with, an element in the @a vector
 *
 *   A successful call to this operation will invalidate the original @a vector
 *   and any subsequent access to, or operation on, it is undefined behavior.
 * @endparblock
 *
 * @param vector the vector to operate on
 * @param elmt a pointer to the elements to append, or @c NULL
 * @param n the number of elements to append from @a elmt
 * @return the resultant vector on success; otherwise @c NULL
 *
 * @see vector_extend_z() - the explicit analogue to this operation
 */
//= vector_t vector_extend(
//=   restrict vector_t vector, const void *restrict elmt, size_t n)
#define vector_extend(v, ...) vector_extend_z((v), __VA_ARGS__, VECTOR_Z((v)))

/**
 * @brief Append @a n elements from @a elmt to the tail of the @a vector
 *
 * @par Example
 * @code{.c}
 *   vector_on(int) vector = vector_create();
 *
 *   vector = vector_extend_z(vector, &(int[]) { 1, 2 }, 2, sizeof(int));
 *   // vector ≡ [1, 2]
 *
 *   vector = vector_extend_z(vector, &(int[]) { 3, 5 }, 2, sizeof(int));
 *   // vector ≡ [1, 2, 3, 5]
 * @endcode
 *
 * On success, the elements at @a elmt will form the suffix of the @a vector,
 * such that the element at <tt>elmt + n - 1</tt> will be at index <tt>length -
 * 1</tt>, the element at <tt>elmt + n - 2</tt> will be at index <tt>length -
 * 2</tt>, and so on. The @length of the @a vector will be increased by @a n.
 * Then the resultant vector is returned and the original @a vector invalidated.
 * This is more efficient than @a n separate calls to vector_append_z().
 *
 * If the increased length of the @a vector would overflow a @c size_t then this
 * will set @c errno to @c ENOMEM and fail. Otherwise, this will call
 * vector_ensure_z() on the @a vector with the resultant length. If that call
 * fails then this operation will fail, with the @a vector unmodified and the
 * value of @c errno set by realloc() retained.
 *
 * If @a elmt is @c NULL then the appended elements will be uninitialized.
 *
 * If the @a vector didn't have an element type before this operation then,
 * unless @a n is zero, the element type of @a elmt will become the element type
 * of the @a vector.
 *
 * @warning @parblock The behavior of this operation is undefined when:
 *
 *   - @a elmt isn't @c NULL and a read from @a elmt of size <tt>n * z</tt>
 *     would access beyond the end of the object at @a elmt
 *   - @a elmt isn't @c NULL and any of the @a n elements at @a elmt are, or
 *     overlap with, an element in the @a vector
 *   - @a z isn't the element size of the @a vector
 *
 *   A successful call to this operation will invalidate the original @a vector
 *   and any subsequent access to, or operation on, it is undefined behavior.
 * @endparblock
 *
 * @param vector the vector to operate on
 * @param elmt a pointer to the elements to append, or @c NULL
 * @param n the number of elements to append from @a elmt
 * @param z the element size of the @a vector
 * @return the resultant vector on success; otherwise @c NULL
 *
 * @see vector_extend() - the implicit analogue to this operation
 */
__vector_inline__ vector_t vector_extend_z(
    restrict vector_t vector, const void *restrict elmt, size_t n, size_t z)
  __attribute__((nonnull(1), warn_unused_result));

#endif /* VECTOR_INSERT_H */

#if (-1- __vector_inline__ -1)
#include "insert.c"
#endif /* __vector_inline__ */
