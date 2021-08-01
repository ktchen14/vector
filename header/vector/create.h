/// @file header/vector/create.h

#ifndef VECTOR_CREATE_H
#define VECTOR_CREATE_H

#include <stddef.h>
#include "common.h"

/**
 * @brief Allocate and initialize a vector with zero @length and @volume
 *
 * @par Example
 * @code{.c}
 *   vector_on(int) vector = vector_create();
 * @endcode
 *
 * The created vector has no element type and will be suitably aligned for
 * elements of any object type with fundamental alignment. On failure the value
 * of @c errno set by malloc() will be retained.
 *
 * @return the created vector on success; otherwise @c NULL
 */
__vector_inline__ vector_t vector_create(void) __attribute__((__malloc__));

/**
 * @brief Allocate and initialize a vector from @a length elements of @a data
 *
 * @par Example
 * @code{.c}
 *   vector_on(int) vector = vector_import((int[]) { 1, 2 }, 2);
 *   // vector ≡ [1, 2]
 * @endcode
 *
 * On success, this will create and return a vector with @a length elements
 * copied from @a data and with @length and @volume equivalent to @a length. The
 * element type of the created vector is the same as the element type of @a data
 * unless @a length is zero, in which case it has no element type but will be
 * suitably aligned for elements of any object type with fundamental alignment.
 *
 * On failure the value of @c errno set by malloc() will be retained.
 *
 * @warning @parblock The behavior of this operation is undefined when:
 *   - The element type of @a data is overaligned
 *   - A read of @a length elements from @a data would access beyond the end of
 *     the object at @a data
 * @endparblock
 *
 * @param data a pointer to the elements used to initialize the vector
 * @param length the number of elements from @a data to copy into the vector
 * @return the created vector on success; otherwise @c NULL
 *
 * @see vector_import_z() - the explicit analogue to this operation
 */
//= vector_t vector_import(const void *data, size_t length)
#define vector_import(d, ...) vector_import_z((d), __VA_ARGS__, VECTOR_Z((d)))

/**
 * @brief Allocate and initialize a vector from @a length elements of @a data
 *
 * @par Example
 * @code{.c}
 *   vector_on(int) vector = vector_import((int[]) { 1, 2 }, 2, sizeof(int));
 *   // vector ≡ [1, 2]
 * @endcode
 *
 * On success, this will create and return a vector with @a length elements
 * copied from @a data and with @length and @volume equivalent to @a length. The
 * element type of the created vector is the same as the element type of @a data
 * unless @a length is zero, in which case it has no element type but will be
 * suitably aligned for elements of any object type with fundamental alignment.
 *
 * On failure the value of @c errno set by malloc() will be retained.
 *
 * @warning @parblock The behavior of this operation is undefined when:
 *   - The element type of @a data is overaligned
 *   - A read from @a data of size <tt>length * z</tt> would access beyond the
 *     end of the object at @a data
 *   - @a z isn't the element size of @a data
 * @endparblock
 *
 * @param data a pointer to the elements used to initialize the vector
 * @param length the number of elements from @a data to copy into the vector
 * @param z the element size of @a data
 * @return the created vector on success; otherwise @c NULL
 *
 * @see vector_import() - the implicit analogue to this operation
 */
__attribute__((__malloc__, nonnull))
__vector_inline__
vector_t vector_import_z(const void *data, size_t length, size_t z);

/**
 * @brief Allocate and initialize a vector from the argument list
 *
 * @par Example
 * @code{.c}
 *   vector_on(int) vector = vector_define(int, 1, 2, 3, 5);
 *   // vector ≡ [1, 2, 3, 5]
 * @endcode
 *
 * This is vector_import() with @a data constructed and @a length calculated
 * from the argument list. @a type must be a complete object type compatible
 * with the type of each argument in <em>...</em>.
 *
 * On success, this will create and return a vector with elements @a ... and
 * with @length and @volume equivalent to the number of arguments in the
 * <em>...</em>. Its element type is @a type, unless no arguments are passed as
 * part of @a ..., in which case it has no element type but will be suitably
 * aligned for elements of any object type with fundamental alignment.
 *
 * On failure the value of @c errno set by malloc() will be retained.
 *
 * @warning @parblock The behavior of this operation is undefined when:
 *   - @a type, or the type of any argument in <em>...</em>, is overaligned
 *   - The type of an argument in @a ... is incompatible with @a type
 * @endparblock
 *
 * @param type a complete object type
 * @param ... a sequence of elements used to initialize the vector
 * @return the created vector on success; otherwise @c NULL
 */
#define vector_define(type, ...) ({ \
  /* Fail unless type is an actual type before we declare __data with */ \
  /* __typeof__(type). Otherwise the compiler is silent on this kind of */ \
  /* mistake: */ \
  /*   vector_define(1, 2, 3, 4)       => (int[])    { 2, 3, 4 } */ \
  /* When this was intended: */ \
  /*   vector_define(int, 1, 2, 3, 4)  => (int[]) { 1, 2, 3, 4 } */ \
  (void) __builtin_types_compatible_p(type, void); \
  /* We must take the __typeof__(type) here so that a strange type like */ \
  /* int[2] or void (*)(void) is syntactically acceptable. */ \
  __typeof__(type) __data[] = { __VA_ARGS__ }; \
  vector_import(__data, sizeof(__data) / sizeof(__data[0])); \
})

/**
 * @brief Allocate and initialize a vector by duplicating @a source
 *
 * @par Example
 * @code{.c}
 *   vector_on(int) source = vector_define(int, 1, 2, 3, 5);
 *   // source ≡ [1, 2, 3, 5]
 *
 *   vector_on(int) target = vector_duplicate(source);
 *   // target ≡ [1, 2, 3, 5]
 * @endcode
 *
 * This will attempt to create a vector with the same @length and @volume as the
 * @a source. If that fails and the length of @a source is less than its volume,
 * then this will attempt to create a vector with just the same length as @a
 * source. If either attempt is successful, then this will memcpy() each element
 * in @a source into the created vector. Its element type is the same as the
 * element type of @a source and it will be suitably aligned for elements of any
 * object type with fundamental alignment.
 *
 * On failure the value of @c errno set by malloc() will be retained.
 *
 * @param source the source vector to duplicate
 * @return the created vector on success; otherwise @c NULL
 *
 * @see vector_duplicate_z() - the explicit analogue to this operation
 */
//= vector_t vector_duplicate(vector_c source)
#define vector_duplicate(v) vector_duplicate_z((v), VECTOR_Z((v)))

/**
 * @brief Allocate and initialize a vector by duplicating @a source
 *
 * @par Example
 * @code{.c}
 *   vector_on(int) source = vector_define(int, 1, 2, 3, 5);
 *   // source ≡ [1, 2, 3, 5]
 *
 *   vector_on(int) target = vector_duplicate_z(source, sizeof(int));
 *   // target ≡ [1, 2, 3, 5]
 * @endcode
 *
 * This will attempt to create a vector with the same @length and @volume as the
 * @a source. If that fails and the length of @a source is less than its volume,
 * then this will attempt to create a vector with just the same length as @a
 * source. If either attempt is successful, then this will memcpy() each element
 * in @a source into the created vector. Its element type is the same as the
 * element type of @a source and it will be suitably aligned for elements of any
 * object type with fundamental alignment.
 *
 * On failure the value of @c errno set by malloc() will be retained.
 *
 * @warning The behavior of this operation is undefined when @a z isn't the
 *   element size of the @a source
 *
 * @param source the source vector to duplicate
 * @param z the element size of the @a source
 * @return the created vector on success; otherwise @c NULL
 *
 * @see vector_duplicate() - the implicit analogue to this operation
 */
__attribute__((__malloc__, nonnull))
__vector_inline__
vector_t vector_duplicate_z(vector_c source, size_t z);

#endif /* VECTOR_CREATE_H */

#if (-1- __vector_inline__ -1)
#include "create.c"
#endif /* __vector_inline__ */
