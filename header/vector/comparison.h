/// @file header/vector/comparison.h

#ifndef VECTOR_COMPARISON_H
#define VECTOR_COMPARISON_H

#include <stddef.h>
#include "common.h"

/**
 * @brief Return whether vector @a va is equivalent to vector @a vb
 *
 * Here "equivalent" means that both of @a va and @a vb are @c NULL, or neither
 * @a va or @a vb is @c NULL and:
 *
 * - @a va and @a vb have the same length, and
 * - @a eq returns @c true when called on each element in @a va and the element
 *   at the same index in @a vb
 *
 * @param va a vector to operate on
 * @param vb a vector to operate on
 * @param eq the equality function that will be used to decide whether an
 *   element in @a va is equivalent to an element in @a vb
 * @return whether vector @a va is equivalent to vector @a vb
 */
//= _Bool vector_eq(
//=     vector_c va, vector_c vb, _Bool (*eq)(const void *a, const void *b))
#define vector_eq(va, vb, ...) \
  vector_eq_z((va), (vb), __VA_ARGS__, VECTOR_Z((va)), VECTOR_Z((vb)))

/**
 * @brief Return whether vector @a va is equivalent to vector @a vb
 *
 * Here "equivalent" means that both of @a va and @a vb are @c NULL, or neither
 * @a va or @a vb is @c NULL and:
 *
 * - @a va and @a vb have the same length, and
 * - @a eq returns @c true when called on each element in @a va and the element
 *   at the same index in @a vb
 *
 * @param va a vector to operate on
 * @param vb a vector to operate on
 * @param eq the equality function that will be used to decide whether an
 *   element in @a va is equivalent to an element in @a vb
 * @param za the element size of @a va
 * @param zb the element size of @a vb
 * @return whether vector @a va is equivalent to vector @a vb
 */
__vector_inline__ _Bool vector_eq_z(
    vector_c va,
    vector_c vb,
    _Bool (*eq)(const void *a, const void *b),
    size_t za,
    size_t zb)
  __attribute__((nonnull(3)));

/**
 * @brief Return whether vector @a va is equivalent to vector @a vb with
 *   contextual information
 *
 * Here "equivalent" means that both of @a va and @a vb are @c NULL, or neither
 * @a va or @a vb is @c NULL and:
 *
 * - @a va and @a vb have the same length, and
 * - @a eq returns @c true when called on each element in @a va and the element
 *   at the same index in @a vb
 *
 * @param va a vector to operate on
 * @param vb a vector to operate on
 * @param eq the equality function that will be used to decide whether an
 *   element in @a va is equivalent to an element in @a vb
 * @param data contextual information to pass as the last argument to @a eq
 * @return whether vector @a va is equivalent to vector @a vb
 */
//= _Bool vector_eq_with(
//=     vector_c va,
//=     vector_c vb,
//=     _Bool (*eq)(const void *a, const void *b, void *data),
//=     void *data)
#define vector_eq_with(va, vb, ...) \
  vector_eq_with_z((va), (vb), __VA_ARGS__, VECTOR_Z((va)), VECTOR_Z((vb)))

/**
 * @brief Return whether vector @a va is equivalent to vector @a vb with
 *   contextual information
 *
 * Here "equivalent" means that both of @a va and @a vb are @c NULL, or neither
 * @a va or @a vb is @c NULL and:
 *
 * - @a va and @a vb have the same length, and
 * - @a eq returns @c true when called on each element in @a va and the element
 *   at the same index in @a vb
 *
 * @param va a vector to operate on
 * @param vb a vector to operate on
 * @param eq the equality function that will be used to decide whether an
 *   element in @a va is equivalent to an element in @a vb
 * @param data contextual information to pass as the last argument to @a eq
 * @param za the element size of @a va
 * @param zb the element size of @a vb
 * @return whether vector @a va is equivalent to vector @a vb
 */
__vector_inline__ _Bool vector_eq_with_z(
    vector_c va,
    vector_c vb,
    _Bool (*eq)(const void *a, const void *b, void *data),
    void *data,
    size_t za,
    size_t zb)
  __attribute__((nonnull(3)));

/**
 * @brief Compare vector @a va to vector @a vb
 *
 * When neither @a va or @a vb is @c NULL, then each element in vector @a va is
 * compared to its corresponding element (the element at the same index) in
 * vector @a vb with the comparator @a cmp. As soon as the result of any such
 * comparison is nonzero (i.e. the elements are unequal), then that result is
 * returned for the entire operation. If all such elements are equal, then the
 * result is equivalent to a numerical comparison of the vectors'
 * @ref vector_length "length"s. Thus, the vectors will compare "equal" if, and
 * only if, they have the same length and each element in vector @a va is equal
 * to its corresponding element in vector @a vb.
 *
 * Otherwise:
 *
 * - When @a va is @c NULL and @a vb isn't @c NULL, then @f$va < vb@f$ (@a va
 *   will compare "less than" @a vb)
 * - When @a va isn't @c NULL and @a vb is @c NULL, then @f$va > vb@f$ (@a va
 *   will compare "greater than" @a vb)
 * - When both @a va and @a vb are @c NULL, then @f$va = vb@f$ (@a va will
 *   compare "equal to" @a vb)
 *
 * @param va a vector to compare
 * @param vb a vector to compare
 * @param cmp The comparator that will be called to compare each element in
 *   @a va its corresponding element in @a vb. This must return a negative
 *   integer if @a a is less than @a b, a positive integer if @a a is greater
 *   than @a b, and zero if @a a and @a b are equal.
 * @return a negative integer when @a va is "less than" @a vb, a positive
 *   integer when @a va is "greater than" @a vb, and zero when @a va and @a vb
 *   are "equal"
 *
 * @see vector_cmp_z() - the explicit interface analogue
 */
//= int vector_cmp(
//=     vector_c va, vector_c vb, int (*cmp)(const void *a, const void *b))
#define vector_cmp(va, vb, ...) \
  vector_cmp_z((va), (vb), __VA_ARGS__, VECTOR_Z((va)), VECTOR_Z((vb)))

/**
 * @brief Compare vector @a va to vector @a vb
 *
 * When neither @a va or @a vb is @c NULL, then each element in vector @a va is
 * compared to its corresponding element (the element at the same index) in
 * vector @a vb with the comparator @a cmp. As soon as the result of any such
 * comparison is nonzero (i.e. the elements are unequal), then that result is
 * returned for the entire operation. If all such elements are equal, then the
 * result is equivalent to a numerical comparison of the vectors'
 * @ref vector_length "length"s. Thus, the vectors will compare "equal" if, and
 * only if, they have the same length and each element in vector @a va is equal
 * to its corresponding element in vector @a vb.
 *
 * Otherwise:
 *
 * - When @a va is @c NULL and @a vb isn't @c NULL, then @f$va < vb@f$ (@a va
 *   will compare "less than" @a vb)
 * - When @a va isn't @c NULL and @a vb is @c NULL, then @f$va > vb@f$ (@a va
 *   will compare "greater than" @a vb)
 * - When both @a va and @a vb are @c NULL, then @f$va = vb@f$ (@a va will
 *   compare "equal to" @a vb)
 *
 * @param va a vector to compare
 * @param vb a vector to compare
 * @param cmp The comparator that will be called to compare each element in
 *   @a va its corresponding element in @a vb. This must return a negative
 *   integer if @a a is less than @a b, a positive integer if @a a is greater
 *   than @a b, and zero if @a a and @a b are equal.
 * @param za the element size of @a va
 * @param zb the element size of @a vb
 * @return a negative integer when @a va is "less than" @a vb, a positive
 *   integer when @a va is "greater than" @a vb, and zero when @a va and @a vb
 *   are "equal"
 *
 * @see vector_cmp() - the implicit interface analogue
 */
__vector_inline__ int vector_cmp_z(
    vector_c va,
    vector_c vb,
    int (*cmp)(const void *a, const void *b),
    size_t za,
    size_t zb)
  __attribute__((nonnull(3)));

/**
 * @brief Compare vector @a va to vector @a vb with contextual information
 *
 * When neither @a va or @a vb is @c NULL, then each element in vector @a va is
 * compared to its corresponding element (the element at the same index) in
 * vector @a vb with the comparator @a cmp. As soon as the result of any such
 * comparison is nonzero (i.e. the elements are unequal), then that result is
 * returned for the entire operation. If all such elements are equal, then the
 * result is equivalent to a numerical comparison of the vectors'
 * @ref vector_length "length"s. Thus, the vectors will compare "equal" if, and
 * only if, they have the same length and each element in vector @a va is equal
 * to its corresponding element in vector @a vb.
 *
 * Otherwise:
 *
 * - When @a va is @c NULL and @a vb isn't @c NULL, then @f$va < vb@f$ (@a va
 *   will compare "less than" @a vb)
 * - When @a va isn't @c NULL and @a vb is @c NULL, then @f$va > vb@f$ (@a va
 *   will compare "greater than" @a vb)
 * - When both @a va and @a vb are @c NULL, then @f$va = vb@f$ (@a va will
 *   compare "equal to" @a vb)
 *
 * @param va a vector to compare
 * @param vb a vector to compare
 * @param cmp The comparator that will be called to compare each element in
 *   @a va its corresponding element in @a vb. This must return a negative
 *   integer if @a a is less than @a b, a positive integer if @a a is greater
 *   than @a b, and zero if @a a and @a b are equal.
 * @param data contextual information to pass as the last argument to @a cmp
 * @return a negative integer when @a va is "less than" @a vb, a positive
 *   integer when @a va is "greater than" @a vb, and zero when @a va and @a vb
 *   are "equal"
 *
 * @see vector_cmp_with_z() - the explicit interface analogue
 */
//= int vector_cmp_with(
//=     vector_c va,
//=     vector_c vb,
//=     int (*cmp)(const void *a, const void *b, void *data),
//=     void *data)
#define vector_cmp_with(va, vb, ...) \
  vector_cmp_with_z((va), (vb), __VA_ARGS__, VECTOR_Z((va)), VECTOR_Z((vb)))

/**
 * @brief Compare vector @a va to vector @a vb with contextual information
 *
 * When neither @a va or @a vb is @c NULL, then each element in vector @a va is
 * compared to its corresponding element (the element at the same index) in
 * vector @a vb with the comparator @a cmp. As soon as the result of any such
 * comparison is nonzero (i.e. the elements are unequal), then that result is
 * returned for the entire operation. If all such elements are equal, then the
 * result is equivalent to a numerical comparison of the vectors'
 * @ref vector_length "length"s. Thus, the vectors will compare "equal" if, and
 * only if, they have the same length and each element in vector @a va is equal
 * to its corresponding element in vector @a vb.
 *
 * Otherwise:
 *
 * - When @a va is @c NULL and @a vb isn't @c NULL, then @f$va < vb@f$ (@a va
 *   will compare "less than" @a vb)
 * - When @a va isn't @c NULL and @a vb is @c NULL, then @f$va > vb@f$ (@a va
 *   will compare "greater than" @a vb)
 * - When both @a va and @a vb are @c NULL, then @f$va = vb@f$ (@a va will
 *   compare "equal to" @a vb)
 *
 * @param va a vector to compare
 * @param vb a vector to compare
 * @param cmp The comparator that will be called to compare each element in
 *   @a va its corresponding element in @a vb. This must return a negative
 *   integer if @a a is less than @a b, a positive integer if @a a is greater
 *   than @a b, and zero if @a a and @a b are equal.
 * @param data contextual information to pass as the last argument to @a cmp
 * @param za the element size of @a va
 * @param zb the element size of @a vb
 * @return a negative integer when @a va is "less than" @a vb, a positive
 *   integer when @a va is "greater than" @a vb, and zero when @a va and @a vb
 *   are "equal"
 *
 * @see vector_cmp_with() - the implicit interface analogue
 */
__vector_inline__ int vector_cmp_with_z(
    vector_c va,
    vector_c vb,
    int (*cmp)(const void *a, const void *b, void *data),
    void *data,
    size_t za,
    size_t zb)
  __attribute__((nonnull(3)));

#endif /* VECTOR_COMPARISON_H */

#if (-1- __vector_inline__ -1)
#include "comparison.c"
#endif /* __vector_inline__ */
