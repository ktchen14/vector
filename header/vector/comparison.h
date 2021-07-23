/// @file header/vector/comparison.h

#ifndef VECTOR_COMPARISON_H
#define VECTOR_COMPARISON_H

#include <stddef.h>
#include "common.h"

/**
 * @brief Return whether vector @a va is equivalent to vector @a vb
 *
 * Here "equivalent" means that @a va and @a vb have the same length and @a eq
 * returns @c true when called on each element in @a va and the element at the
 * same index in @a vb.
 *
 * @param va a vector to operate on
 * @param vb a vector to operate on
 * @param eq @parblock
 *   The equality function that will be used to decide whether an element in
 *   @a va is equivalent to an element in @a vb. This will be called with the
 *   arguments:
 *
 *   - @a a as a pointer to an element from vector @a va
 *   - @a b as a pointer to an element from vector @a vb
 *
 *   And should return @c true if the elements are equivalent, or @c false
 *   otherwise.
 * @endparblock
 * @return whether vector @a va is equivalent to vector @a vb
 *
 * @see vector_eq_with() - the contextual variant of this operation
 * @see vector_eq_z() - the explicit analogue of this operation
 */
//= _Bool vector_eq(
//=     vector_c va, vector_c vb, _Bool (*eq)(const void *a, const void *b))
#define vector_eq(va, vb, ...) \
  vector_eq_z((va), (vb), __VA_ARGS__, VECTOR_Z((va)), VECTOR_Z((vb)))

/**
 * @brief Return whether vector @a va is equivalent to vector @a vb
 *
 * Here "equivalent" means that @a va and @a vb have the same length and @a eq
 * returns @c true when called on each element in @a va and the element at the
 * same index in @a vb.
 *
 * @param va a vector to operate on
 * @param vb a vector to operate on
 * @param eq @parblock
 *   The equality function that will be used to decide whether an element in
 *   @a va is equivalent to an element in @a vb. This will be called with the
 *   arguments:
 *
 *   - @a a as a pointer to an element from vector @a va
 *   - @a b as a pointer to an element from vector @a vb
 *
 *   And should return @c true if the elements are equivalent, or @c false
 *   otherwise.
 * @endparblock
 * @param za the element size of @a va
 * @param zb the element size of @a vb
 * @return whether vector @a va is equivalent to vector @a vb
 *
 * @see vector_eq_with_z() - the contextual variant of this operation
 * @see vector_eq() - the implicit analogue of this operation
 */
__vector_inline__ _Bool vector_eq_z(
    vector_c va,
    vector_c vb,
    _Bool (*eq)(const void *a, const void *b),
    size_t za,
    size_t zb)
  __attribute__((nonnull));

/**
 * @brief Return whether vector @a va is equivalent to vector @a vb
 *
 * Here "equivalent" means that @a va and @a vb have the same length and @a eq
 * returns @c true when called on each element in @a va and the element at the
 * same index in @a vb.
 *
 * @param va a vector to operate on
 * @param vb a vector to operate on
 * @param eq @parblock
 *   The equality function that will be used to decide whether an element in
 *   @a va is equivalent to an element in @a vb. This will be called with the
 *   arguments:
 *
 *   - @a a as a pointer to an element from vector @a va
 *   - @a b as a pointer to an element from vector @a vb
 *   - @a data as the contextual information
 *
 *   And should return @c true if the elements are equivalent, or @c false
 *   otherwise.
 * @endparblock
 * @param data contextual information to pass as the last argument to @a eq
 * @return whether vector @a va is equivalent to vector @a vb
 *
 * @see vector_eq() - the noncontextual variant of this operation
 * @see vector_eq_with_z() - the explicit analogue of this operation
 */
//= _Bool vector_eq_with(
//=     vector_c va,
//=     vector_c vb,
//=     _Bool (*eq)(const void *a, const void *b, void *data),
//=     void *data)
#define vector_eq_with(va, vb, ...) \
  vector_eq_with_z((va), (vb), __VA_ARGS__, VECTOR_Z((va)), VECTOR_Z((vb)))

/**
 * @brief Return whether vector @a va is equivalent to vector @a vb
 *
 * Here "equivalent" means that @a va and @a vb have the same length and @a eq
 * returns @c true when called on each element in @a va and the element at the
 * same index in @a vb.
 *
 * @param va a vector to operate on
 * @param vb a vector to operate on
 * @param eq @parblock
 *   The equality function that will be used to decide whether an element in
 *   @a va is equivalent to an element in @a vb. This will be called with the
 *   arguments:
 *
 *   - @a a as a pointer to an element from vector @a va
 *   - @a b as a pointer to an element from vector @a vb
 *   - @a data as the contextual information
 *
 *   And should return @c true if the elements are equivalent, or @c false
 *   otherwise.
 * @endparblock
 * @param data contextual information to pass as the last argument to @a eq
 * @param za the element size of @a va
 * @param zb the element size of @a vb
 * @return whether vector @a va is equivalent to vector @a vb
 *
 * @see vector_eq_z() - the noncontextual variant of this operation
 * @see vector_eq_with() - the implicit analogue of this operation
 */
__vector_inline__ _Bool vector_eq_with_z(
    vector_c va,
    vector_c vb,
    _Bool (*eq)(const void *a, const void *b, void *data),
    void *data,
    size_t za,
    size_t zb)
  __attribute__((nonnull(1, 2, 3)));

/**
 * @brief Compare vector @a va to vector @a vb
 *
 * This will compare each element in vector @a va to its corresponding element
 * (the element at the same index) in vector @a vb using the comparator @a cmp,
 * in sequence, until either vector is exhausted. As soon as the result of any
 * such comparison is nonzero (i.e. the elements are unequal), then that result
 * is returned for the entire operation. If all the elements compared in this
 * manner are equal, then the result will be equivalent to a comparison of the
 * vectors' @ref vector_length "length"s, such that this will return:
 *
 * - a negative result when <em>va</em>'s length is less then <em>vb</em>'s
 *   length
 * - a positive result when <em>va</em>'s length is greater than <em>vb</em>'s
 *   length
 * - zero when they have the same length
 *
 * Thus, the vectors will compare equal if, and only if, they have the same
 * length and each element in @a va is equal to its corresponding element in
 * @a vb.
 *
 * @param va a vector to compare
 * @param vb a vector to compare
 * @param cmp @parblock
 *   The comparator that will be used to compare each element in @a va to its
 *   corresponding element in @a vb. This will be called with the arguments:
 *
 *   - @a a as a pointer to an element from vector @a va
 *   - @a b as a pointer to an element from vector @a vb
 *
 *   And should return a negative integer when the element at @a a is less than
 *   the element at @a b, a positive integer when the element at @a a is greater
 *   than the element at @a b, and zero when they are equal.
 * @endparblock
 * @return a negative integer when @a va is less than @a vb, a positive integer
 *   when @a va is greater than @a vb, and zero when they are equal
 *
 * @see vector_cmp_with() - the contextual variant of this operation
 * @see vector_cmp_z() - the explicit analogue to this operation
 */
//= int vector_cmp(
//=     vector_c va, vector_c vb, int (*cmp)(const void *a, const void *b))
#define vector_cmp(va, vb, ...) \
  vector_cmp_z((va), (vb), __VA_ARGS__, VECTOR_Z((va)), VECTOR_Z((vb)))

/**
 * @brief Compare vector @a va to vector @a vb
 *
 * This will compare each element in vector @a va to its corresponding element
 * (the element at the same index) in vector @a vb using the comparator @a cmp,
 * in sequence, until either vector is exhausted. As soon as the result of any
 * such comparison is nonzero (i.e. the elements are unequal), then that result
 * is returned for the entire operation. If all the elements compared in this
 * manner are equal, then the result will be equivalent to a comparison of the
 * vectors' @ref vector_length "length"s, such that this will return:
 *
 * - a negative result when <em>va</em>'s length is less then <em>vb</em>'s
 *   length
 * - a positive result when <em>va</em>'s length is greater than <em>vb</em>'s
 *   length
 * - zero when they have the same length
 *
 * Thus, the vectors will compare equal if, and only if, they have the same
 * length and each element in @a va is equal to its corresponding element in
 * @a vb.
 *
 * @param va a vector to compare
 * @param vb a vector to compare
 * @param cmp @parblock
 *   The comparator that will be used to compare each element in @a va to its
 *   corresponding element in @a vb. This will be called with the arguments:
 *
 *   - @a a as a pointer to an element from vector @a va
 *   - @a b as a pointer to an element from vector @a vb
 *
 *   And should return a negative integer when the element at @a a is less than
 *   the element at @a b, a positive integer when the element at @a a is greater
 *   than the element at @a b, and zero when they are equal.
 * @endparblock
 * @param za the element size of @a va
 * @param zb the element size of @a vb
 * @return a negative integer when @a va is less than @a vb, a positive integer
 *   when @a va is greater than @a vb, and zero when they are equal
 *
 * @see vector_cmp_with_z() - the contextual variant of this operation
 * @see vector_cmp() - the implicit analogue to this operation
 */
__vector_inline__ int vector_cmp_z(
    vector_c va,
    vector_c vb,
    int (*cmp)(const void *a, const void *b),
    size_t za,
    size_t zb)
  __attribute__((nonnull));

/**
 * @brief Compare vector @a va to vector @a vb
 *
 * This will compare each element in vector @a va to its corresponding element
 * (the element at the same index) in vector @a vb using the comparator @a cmp,
 * in sequence, until either vector is exhausted. As soon as the result of any
 * such comparison is nonzero (i.e. the elements are unequal), then that result
 * is returned for the entire operation. If all the elements compared in this
 * manner are equal, then the result will be equivalent to a comparison of the
 * vectors' @ref vector_length "length"s, such that this will return:
 *
 * - a negative result when <em>va</em>'s length is less then <em>vb</em>'s
 *   length
 * - a positive result when <em>va</em>'s length is greater than <em>vb</em>'s
 *   length
 * - zero when they have the same length
 *
 * Thus, the vectors will compare equal if, and only if, they have the same
 * length and each element in @a va is equal to its corresponding element in
 * @a vb.
 *
 * @param va a vector to compare
 * @param vb a vector to compare
 * @param cmp @parblock
 *   The comparator that will be used to compare each element in @a va to its
 *   corresponding element in @a vb. This will be called with the arguments:
 *
 *   - @a a as a pointer to an element from vector @a va
 *   - @a b as a pointer to an element from vector @a vb
 *   - @a data as the contextual information
 *
 *   And should return a negative integer when the element at @a a is less than
 *   the element at @a b, a positive integer when the element at @a a is greater
 *   than the element at @a b, and zero when they are equal.
 * @endparblock
 * @param data contextual information to pass as the last argument to @a cmp
 * @return a negative integer when @a va is less than @a vb, a positive integer
 *   when @a va is greater than @a vb, and zero when they are equal
 *
 * @see vector_cmp() - the noncontextual variant of this operation
 * @see vector_cmp_with_z() - the explicit analogue to this operation
 */
//= int vector_cmp_with(
//=     vector_c va,
//=     vector_c vb,
//=     int (*cmp)(const void *a, const void *b, void *data),
//=     void *data)
#define vector_cmp_with(va, vb, ...) \
  vector_cmp_with_z((va), (vb), __VA_ARGS__, VECTOR_Z((va)), VECTOR_Z((vb)))

/**
 * @brief Compare vector @a va to vector @a vb
 *
 * This will compare each element in vector @a va to its corresponding element
 * (the element at the same index) in vector @a vb using the comparator @a cmp,
 * in sequence, until either vector is exhausted. As soon as the result of any
 * such comparison is nonzero (i.e. the elements are unequal), then that result
 * is returned for the entire operation. If all the elements compared in this
 * manner are equal, then the result will be equivalent to a comparison of the
 * vectors' @ref vector_length "length"s, such that this will return:
 *
 * - a negative result when <em>va</em>'s length is less then <em>vb</em>'s
 *   length
 * - a positive result when <em>va</em>'s length is greater than <em>vb</em>'s
 *   length
 * - zero when they have the same length
 *
 * Thus, the vectors will compare equal if, and only if, they have the same
 * length and each element in @a va is equal to its corresponding element in
 * @a vb.
 *
 * @param va a vector to compare
 * @param vb a vector to compare
 * @param cmp @parblock
 *   The comparator that will be used to compare each element in @a va to its
 *   corresponding element in @a vb. This will be called with the arguments:
 *
 *   - @a a as a pointer to an element from vector @a va
 *   - @a b as a pointer to an element from vector @a vb
 *   - @a data as the contextual information
 *
 *   And should return a negative integer when the element at @a a is less than
 *   the element at @a b, a positive integer when the element at @a a is greater
 *   than the element at @a b, and zero when they are equal.
 * @endparblock
 * @param data contextual information to pass as the last argument to @a cmp
 * @param za the element size of @a va
 * @param zb the element size of @a vb
 * @return a negative integer when @a va is less than @a vb, a positive integer
 *   when @a va is greater than @a vb, and zero when they are equal
 *
 * @see vector_cmp_z() - the noncontextual variant of this operation
 * @see vector_cmp_with() - the implicit analogue to this operation
 */
__vector_inline__ int vector_cmp_with_z(
    vector_c va,
    vector_c vb,
    int (*cmp)(const void *a, const void *b, void *data),
    void *data,
    size_t za,
    size_t zb)
  __attribute__((nonnull(1, 2, 3)));

#endif /* VECTOR_COMPARISON_H */

#if (-1- __vector_inline__ -1)
#include "comparison.c"
#endif /* __vector_inline__ */
