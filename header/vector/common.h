/// @file header/vector/common.h

#ifndef VECTOR_COMMON_H
#define VECTOR_COMMON_H

#include <stddef.h>

/**
 * @brief Used to indicate a vector with an indeterminate element type
 *
 * This is intended to be used strictly when the element type of a vector is
 * indeterminate (such as when implementing this file) and shouldn't be used
 * otherwise. Instead a normal C pointer should be used. For example a vector
 * with element type @c size_t should be declared and created with either of:
 *
 * @code{.c}
 *   size_t          *v_size = vector_create();
 *   vector_t(size_t) v_size = vector_create();
 * @endcode
 */
typedef void * vector_t;

/**
 * @brief Construct the type name of a vector with element type @a type
 *
 * @note This function-like macro is used to construct the type name of a vector
 *   with a determinate element type and is invoked as <tt>vector_t(type)</tt>.
 *   With no arguments, @ref vector_t is a real type name (it doesn't invoke
 *   this macro) and is used to indicate a vector with an indeterminate element
 *   type, i.e. <tt>void *</tt>.
 *
 * Functionally, this doesn't do much more than adding a <tt>*</tt> to its
 * argument, such that these are equivalent:
 *
 * @code{.c}
 *   size_t          *vector;
 *   vector_t(size_t) vector;
 * @endcode
 *
 * However, this is useful as a form of inline documentation to differentiate an
 * object that's intended to be used as a normal pointer to a type from an
 * object that's intended to be used as a vector with a certain element type.
 * For example:
 *
 * @code{.c}
 *   vector_t(int) vector = vector_define(int, ...);
 *   for (size_t i = 0; i < vector_length(vector); i++) {
 *     int *number = vector + i;
 *     ...
 *   }
 * @endcode
 *
 * In addition, the resultant type name is of a vector type itself, such that
 * these are equivalent (note the repeated asterisk):
 *
 * @code{.c}
 *   size_t          *a, *b, *c;
 *   vector_t(size_t) a,  b,  c;
 * @endcode
 *
 * This should accept any complete or incomplete type name, except an enumerated
 * type declaration or type name that introduces a new enumerated type.
 */
#define vector_t(type) __typeof__(( \
  /* Fail unless the argument is an actual type. Otherwise the compiler is */ \
  /* silent on this kind of mistake: */ \
  /*   int8_t time; vector_t(time) vector;  => (int8_t *) */ \
  /* When this was intended: */ \
  /*   vector_t(time_t) vector;             => (time_t *) */ \
  /* A call to __builtin_types_compatible_p() doesn't evaluate either */ \
  /* operand, even if it's the name of a variably modified type. If */ \
  /* the argument isn't a type, this won't compile with "expected a type". */ \
  (void) __builtin_types_compatible_p(type, void), \
  /* Make an expression such that its type is a pointer to `type` */ \
  (__typeof__(type) *) NULL \
))

/// A @ref vector_t with a @c const element type
typedef void const * vector_c;

/**
 * @brief Construct the type name of a vector with @c const element type @a type
 *
 * @note This function-like macro is used to construct the type name of a vector
 *   with a determinate element type and is invoked as <tt>vector_c(type)</tt>.
 *   With no arguments, @ref vector_t is a real type name (it doesn't invoke
 *   this macro) and is used to indicate a vector with an indeterminate element
 *   type, i.e. <tt>const void *</tt>.
 *
 * Functionally, this doesn't do much more than adding a <tt>const *</tt> to its
 * argument, such that these are equivalent:
 *
 * @code{.c}
 *   const int    *vector;
 *   vector_c(int) vector;
 * @endcode
 *
 * However, this is useful as a form of inline documentation to differentiate an
 * object that's intended to be used as a normal pointer to a type from an
 * object that's intended to be used as a vector with a certain element type. In
 * addition, the resultant type name is of a vector type itself, such that these
 * are equivalent:
 *
 * @code{.c}
 *   const int    *a, *b, *c;
 *   vector_c(int) a,  b,  c;
 * @endcode
 *
 * This should accept any complete or incomplete type name, except an enumerated
 * type declaration or type name that introduces a new enumerated type.
 */
#define vector_c(type) __typeof__(( \
  /* Fail unless the argument is an actual type. Otherwise the compiler is */ \
  /* silent on this kind of mistake: */ \
  /*   int8_t time; vector_c(time) vector;  => (const int8_t *) */ \
  /* When this was intended: */ \
  /*   vector_c(time_t) vector;             => (const time_t *) */ \
  /* A call to __builtin_types_compatible_p() doesn't evaluate either */ \
  /* operand, even if it's the name of a variably modified type. If */ \
  /* the argument isn't a type, this won't compile with "expected a type". */ \
  (void) __builtin_types_compatible_p(type, void), \
  /* Make an expression such that its type is a pointer to const `type` */ \
  (const __typeof__(type) *) NULL \
))

/**
 * @brief Return the volume of the @a vector
 *
 * A vector's volume is the number of elements that it can hold without a
 * reallocation and should always be greater than or equal to the vector's
 * @length.
 */
inline size_t vector_volume(vector_c vector) __attribute__((nonnull, pure));

/// Return the length of (the number of elements in) the @a vector
inline size_t vector_length(vector_c vector) __attribute__((nonnull, pure));

/// @cond INTERNAL

/**
 * @brief Return the element size of the @a vector
 *
 * The element size is determined from the type of @a vector itself with a
 * calculation similar to <code>sizeof((vector)[0])</code>. As such to use this
 * @a vector must already be a pointer to a complete type.
 *
 * The element size of a vector isn't recorded in the vector itself. This
 * calculates the element size of the @a vector from the pointer type of the @a
 * vector itself (similar to <code>sizeof((vector)[0])</code>). Thus @a vector
 * must be a pointer to a complete type.
 *
 * This is almost identical to <code>sizeof((vector)[0])</code>. However in GNU
 * C (and similar implementations) the @c sizeof(void) is @c 1 (despite the fact
 * that @c void is an incomplete type). Because a @ref vector_t is defined as
 * <code>void *</code> this raises a compiler error when @a vector is a
 * @ref vector_t.
 *
 * This macro doesn't evaluate @a vector.
 */
#define VECTOR_Z(vector) sizeof({ __typeof__((vector)[0]) __x; __x; })

/// The header of a @ref vector_t or @ref vector_c
struct __vector_header_t {
  size_t volume;
  size_t length;
  _Alignas(max_align_t) char data[];
};

/**
 * @brief Return the header associated with the @a vector
 *
 * This function is @a const qualified on the @a vector. That is if the element
 * type of the @a vector is @c const qualified (@a vector is compatible with a
 * @ref vector_c), this will return a <tt>const struct __vector_header_t *</tt>.
 * Otherwise this will return a <tt>struct __vector_header_t *</tt>.
 */
#define __vector_to_header(vector) ({ \
  _Pragma("GCC diagnostic push"); \
  _Pragma("GCC diagnostic ignored \"-Wcast-align\""); \
  _Pragma("GCC diagnostic ignored \"-Wcast-qual\""); \
  _Generic((vector), vector_t: (struct __vector_header_t *) ( \
      (/* */ char *) (vector) - offsetof(struct __vector_header_t, data) \
    ), vector_c: (const struct __vector_header_t *) ( \
      (const char *) (vector) - offsetof(struct __vector_header_t, data) \
    )); \
  _Pragma("GCC diagnostic pop") \
})

// Define __vector_inline__ to `inline`, if it isn't already defined, to inline
// most vector code. If __vector_inline__ is defined to `` (the zero length
// identifier) before this, then most vector code won't be inlined; this is
// useful to make function interposition work. Note that if __vector_inline__ is
// defined, its definition must be `` or `inline`; otherwise the behavior is
// undefined.
#ifndef __vector_inline__
#define __vector_inline__ inline
#endif /* __vector_inline__ */

/// @endcond

inline size_t vector_volume(vector_c vector) {
  return __vector_to_header(vector)->volume;
}

inline size_t vector_length(vector_c vector) {
  return __vector_to_header(vector)->length;
}

#endif /* VECTOR_COMMON_H */

#if (-1- __vector_inline__ -1)
#include "common.c"
#endif /* __vector_inline__ */
