/// @file header/vector/common.h

#ifndef VECTOR_COMMON_H
#define VECTOR_COMMON_H

#include <stddef.h>

/**
 * @brief Construct the name of a vector type with element type as the operand
 *
 * @par Example
 * @code{.c}
 *   vector_on(int)                // element type is int
 *   vector_on(const int)          // element type is const int
 *   vector_on(int[4])             // element type is int[4]
 *   vector_on(int *)              // element type is int *
 *   vector_on(int (*)(void))      // element type is int (*)(void)
 *   vector_on(vector_on(int))     // element type is int *
 *   vector_on(struct { int i; })  // element type is struct { int i; }
 *   vector_on(enum E { A, B })    // element type is enum E
 * @endcode
 *
 * The type of a vector with element type @c T is just <tt>T *</tt>, so
 * functionally, this just constructs the type of pointer-to-operand, such that
 * these are equivalent:
 *
 * @code{.c}
 *   int           *vector;
 *   vector_on(int) vector;
 * @endcode
 *
 * However, this is useful as a form of in-band documentation to differentiate
 * an object intended to be used as a normal pointer from one intended to be
 * used as a vector. In addition, the resultant name is the type of the vector
 * itself, such that these are equivalent:
 *
 * @code{.c}
 *   int           *a, *b, *c;
 *   vector_on(int) a,  b,  c;
 * @endcode
 *
 * The operand must be the name of a complete object type; otherwise the
 * behavior is undefined, though this macro will attempt to fail compilation in
 * this case. Any identifiers introduced in the operand, as part of a
 * definition, are subsequently declared in the enclosing scope. The operand is
 * evaluated for its side effects if and only if it's the name of a variably
 * modified type. No implicit conversions are performed on the operand, so type
 * qualifiers are preserved in the resultant element type:
 *
 * @code{.c}
 *   // undefined behavior as the operand isn't an object type
 *   vector_on(int (void))
 *
 *   // undefined behavior as the operand is an incomplete type
 *   vector_on(int[])
 *
 *   // undefined behavior as the operand is an expression
 *   vector_on(sizeof(int))
 *
 *   vector_on(struct S { enum { A, B } i; }) vector;
 *   struct S object;             // struct S is defined here
 *   int x = A, y = B;            // A and B are defined here
 *
 *   size_t n = 1;
 *   vector_on(int[n++]) vector;  // vector will have element type int[1]
 *   assert(n == 2);
 *
 *   // vector will have element type int *restrict
 *   vector_on(int *restrict) vector;
 *
 *   // vector will have element type const volatile _Atomic int
 *   vector_on(const volatile _Atomic int) vector;
 * @endcode
 *
 * On the rare occassion that it's useful to declare a vector with an incomplete
 * or indeterminate element type, declare the vector as a normal pointer or with
 * ::vector_t:
 *
 * @code{.c}
 *   int (*vector)[];  // vector will have element type int[]
 *   vector_t vector;  // vector will have an indeterminate element type
 * @endcode
 *
 * @param ... the name of a complete object type
 * @return the name of a vector type with element type as the operand @a ...
 */
#define vector_on(...) __typeof__( \
    &(__typeof__(__attribute__(()) __VA_ARGS__) []) { }[0] \
)

/**
 * @brief Used to indicate a vector with an indeterminate element type
 *
 * This is intended to be used strictly when the element type of a vector is
 * indeterminate (such as when implementing this library) and shouldn't be used
 * otherwise. Instead use vector_on() when the element type is a complete object
 * type, or a normal pointer otherwise. For example a vector with element type
 * @c size_t should be declared and created with either of:
 *
 * @code{.c}
 *   size_t           *v_size = vector_create();
 *   vector_on(size_t) v_size = vector_create();
 * @endcode
 */
typedef void * vector_t;

/// A @ref vector_t with a @c const element type
typedef void const * vector_c;

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
