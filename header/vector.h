/**
 * @file header/vector.h
 *
 * A vector is a dynamic array that behaves similar to a C array. In fact a
 * vector and a C array.
 *
 * The operations available on a vector are roughly split into two interfaces:
 * an implicit interface and an explicit interface.
 *
 * Most operations in the explicit interface have a @c _z suffix and have an
 * equivalent operation in the implicit interface without that suffix.
 *
 * Implicit interface operations
 *
 * When the element type of a vector is determinate at compile the the implicit
 * interface should be used.
 *
 * Most vector operations have two forms. One with a @c _z suffix and one
 * without. The one with a @c _z suffix has an explicit @c z argument that
 * specifies the element size of the vector. The one without the suffix
 * automatically deduces the element size of the vector.
 *
 * Most operations take a vector as an argument. Unless otherwise specified in
 * the documentation of a specific operation, if the given vector is @a NULL
 * then the behavior is undefined.
 */

#ifndef VECTOR_H
#define VECTOR_H

#include "vector/common.h"
#include "vector/access.h"
#include "vector/comparison.h"
#include "vector/create.h"
#include "vector/debug.h"
#include "vector/delete.h"
#include "vector/insert.h"
#include "vector/move.h"
#include "vector/remove.h"
#include "vector/resize.h"
#include "vector/search.h"
#include "vector/shift.h"
#include "vector/sort.h"

#endif /* VECTOR_H */
