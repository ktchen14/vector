#include <stdbool.h>
#include <assert.h>

#include <vector.h>
#include "test.h"

// vector_eq(), vector_eq_z()

static bool eqintlongp(const void *a, const void *b) {
  return *(const int *) a == *(const long *) b;
}

static bool fail_next;
static bool eqintlongp_failer(const void *a, const void *b) {
  bool result = *(const int *) a != *(const long *) b;
  assert(!fail_next);
  if (!result)
    fail_next = true;
  return result;
}

static size_t last_eq_za, last_eq_zb;
bool vector_eq_z(
    vector_c va,
    vector_c vb,
    bool (*eq)(const void *a, const void *b),
    size_t za,
    size_t zb) {
  last_eq_za = za;
  last_eq_zb = zb;
  return REAL(vector_eq_z)(va, vb, eq, za, zb);
}

void test_vector_eq(void) {
  vector_t(int) va = vector_define(int, 1, 2, 3, 5, 8, 13, 21);
  vector_t(long) vb = vector_define(long, 1, 2, 3, 5, 8, 13, 21);
  vector_t(int) vector;
  int number = 0;

  // It evaluates each argument once
  vector_eq((number++, va), vb, eqintlongp);
  assert(number == 1);
  vector_eq(va, (number++, vb), eqintlongp);
  assert(number == 2);
  vector_eq(va, vb, (number++, eqintlongp));
  assert(number == 3);

  // It calls vector_eq_z() with the element sizes of the vectors
  vector_eq(va, vb, eqintlongp);
  assert(last_eq_za == sizeof(va[0]));
  assert(last_eq_zb == sizeof(vb[0]));

  // Its expansion is an expression
  assert(vector_eq(va, vb, eqintlongp));

  // When the lengths of va and vb differ it returns false before calling eq
  vector = vector_define(int, 2, 3, 5, 8);
  fail_next = true;
  assert(!vector_eq(va, vector, eqintlongp_failer));
  vector_delete(vector);

  // When the lengths of va and vb are equal it returns whether eq returns true
  // when called on each element in va and its corresponding element in vb
  assert(vector_eq(va, vb, eqintlongp));

  // When an element in va isn't equivalent to its corresponding element in vb
  // it returns false before calling eq on the next pair of elements
  fail_next = false;
  assert(!vector_eq(va, vb, eqintlongp_failer));

  vector_delete(va);
  vector_delete(vb);
}

// vector_eq_with(), vector_eq_with_z()

static bool eqintlongp_data(const void *a, const void *b, void *data) {
  (void) data;
  return *(const int *) a == *(const long *) b;
}

static bool eqintlongp_data_failer(const void *a, const void *b, void *data) {
  bool *fail_next = data;
  bool result = *(const int *) a != *(const long *) b;
  assert(!*fail_next);
  if (!result)
    *fail_next = true;
  return result;
}

static size_t last_eq_with_za, last_eq_with_zb;
bool vector_eq_with_z(
    vector_c va,
    vector_c vb,
    bool (*eq)(const void *a, const void *b, void *data),
    void *data,
    size_t za,
    size_t zb) {
  last_eq_with_za = za;
  last_eq_with_zb = zb;
  return REAL(vector_eq_with_z)(va, vb, eq, data, za, zb);
}

void test_vector_eq_with(void) {
  vector_t(int) va = vector_define(int, 1, 2, 3, 5, 8, 13, 21);
  vector_t(long) vb = vector_define(long, 1, 2, 3, 5, 8, 13, 21);
  vector_t(int) vector;
  bool data;
  bool *fail_next = &data;
  int number = 0;

  // It evaluates each argument once
  vector_eq_with((number++, va), vb, eqintlongp_data, &data);
  assert(number == 1);
  vector_eq_with(va, (number++, vb), eqintlongp_data, &data);
  assert(number == 2);
  vector_eq_with(va, vb, (number++, eqintlongp_data), &data);
  assert(number == 3);
  vector_eq_with(va, vb, eqintlongp_data, (number++, &data));
  assert(number == 4);

  // It calls vector_eq_with_z() with the element sizes of the vectors
  vector_eq_with(va, vb, eqintlongp_data, &data);
  assert(last_eq_with_za == sizeof(va[0]));
  assert(last_eq_with_zb == sizeof(vb[0]));

  // Its expansion is an expression
  assert(vector_eq_with(va, vb, eqintlongp_data, &data));

  // When the lengths of va and vb differ it returns false before calling eq
  vector = vector_define(int, 2, 3, 5, 8);
  *fail_next = true;
  assert(!vector_eq_with(va, vector, eqintlongp_data_failer, fail_next));
  vector_delete(vector);

  // When the lengths of va and vb are equal it returns whether eq returns true
  // when called on each element in va and its corresponding element in vb
  assert(vector_eq_with(va, vb, eqintlongp_data, &data));

  // When an element in va isn't equivalent to its corresponding element in vb
  // it returns false before calling eq on the next pair of elements
  *fail_next = false;
  assert(!vector_eq_with(va, vb, eqintlongp_data_failer, fail_next));

  vector_delete(va);
  vector_delete(vb);
}

// vector_cmp(), vector_cmp_z()

static int cmpintlongp(const void *a, const void *b) {
  const int *ra = a, *rb = b;
  return *ra < *rb ? -1 : *ra > *rb;
}

static bool fail_next;
static int cmpintlongp_failer(const void *a, const void *b) {
  const int *ra = a, *rb = b;
  int result = *ra < *rb ? -1 : *ra > *rb;
  assert(!fail_next);
  if (result)
    fail_next = true;
  return result;
}

static size_t last_cmp_za, last_cmp_zb;
int vector_cmp_z(
    vector_c va,
    vector_c vb,
    int (*cmp)(const void *a, const void *b),
    size_t za,
    size_t zb) {
  last_cmp_za = za;
  last_cmp_zb = zb;
  return REAL(vector_cmp_z)(va, vb, cmp, za, zb);
}

void test_vector_cmp(void) {
  vector_t(int) va = vector_define(int, 1, 2, 3, 5, 8, 13, 21);
  vector_t(long) vb = vector_define(long, 1, 2, 3, 5, 8, 13, 21);
  int number = 0;

  // It evaluates each argument once
  vector_cmp((number++, va), vb, cmpintlongp);
  assert(number == 1);
  vector_cmp(va, (number++, vb), cmpintlongp);
  assert(number == 2);
  vector_cmp(va, vb, (number++, cmpintlongp));
  assert(number == 3);

  // It calls vector_cmp_z() with the element sizes of the vectors
  vector_cmp(va, vb, cmpintlongp);
  assert(last_cmp_za == sizeof(va[0]));
  assert(last_cmp_zb == sizeof(vb[0]));

  // Its expansion is an expression
  assert(!vector_cmp(va, vb, cmpintlongp));

  // When an element in va is unequal to its corresponding element in vb it
  // returns the result of the comparison before calling cmp on the next pair of
  // elements
  fail_next = false;
  vb[4] = va[4] + 1;
  assert(vector_cmp(va, vb, cmpintlongp_failer) == -1);

  fail_next = false;
  va[4] = vb[4] + 1;
  assert(vector_cmp(va, vb, cmpintlongp_failer) == +1);

  va[4] = vb[4];

  // When va and vb are equal it returns 0
  assert(!vector_cmp(va, vb, cmpintlongp));

  // When va is exhausted before vb it returns -1
  va = vector_truncate(va, vector_length(vb) - 1);
  assert(vector_cmp(va, vb, cmpintlongp) == -1);

  // When vb is exhausted before vb it returns +1
  vb = vector_truncate(vb, vector_length(va) - 1);
  assert(vector_cmp(va, vb, cmpintlongp) == +1);

  vector_delete(va);
  vector_delete(vb);
}

// vector_cmp_with(), vector_cmp_with_z()

static int cmpintlongp_data(const void *a, const void *b, void *data) {
  const int *ra = a, *rb = b;
  (void) data;
  return *ra < *rb ? -1 : *ra > *rb;
}

static int cmpintlongp_data_failer(const void *a, const void *b, void *data) {
  bool *fail_next = data;
  const int *ra = a, *rb = b;
  int result = *ra < *rb ? -1 : *ra > *rb;
  assert(!*fail_next);
  if (result)
    *fail_next = true;
  return result;
}

static size_t last_cmp_with_za, last_cmp_with_zb;
int vector_cmp_with_z(
    vector_c va,
    vector_c vb,
    int (*cmp)(const void *a, const void *b, void *data),
    void *data,
    size_t za,
    size_t zb) {
  last_cmp_with_za = za;
  last_cmp_with_zb = zb;
  return REAL(vector_cmp_with_z)(va, vb, cmp, data, za, zb);
}

void test_vector_cmp_with(void) {
  vector_t(int) va = vector_define(int, 1, 2, 3, 5, 8, 13, 21);
  vector_t(long) vb = vector_define(long, 1, 2, 3, 5, 8, 13, 21);
  bool data;
  bool *fail_next = &data;
  int number = 0;

  // It evaluates each argument once
  vector_cmp_with((number++, va), vb, cmpintlongp_data, &data);
  assert(number == 1);
  vector_cmp_with(va, (number++, vb), cmpintlongp_data, &data);
  assert(number == 2);
  vector_cmp_with(va, vb, (number++, cmpintlongp_data), &data);
  assert(number == 3);
  vector_cmp_with(va, vb, cmpintlongp_data, (number++, &data));
  assert(number == 4);

  // It calls vector_cmp_with_z() with the element sizes of the vectors
  vector_cmp_with(va, vb, cmpintlongp_data, &data);
  assert(last_cmp_with_za == sizeof(va[0]));
  assert(last_cmp_with_zb == sizeof(vb[0]));

  // Its expansion is an expression
  assert(!vector_cmp_with(va, vb, cmpintlongp_data, &data));

  // When an element in va is unequal to its corresponding element in vb it
  // returns the result of the comparison before calling cmp on the next pair of
  // elements
  *fail_next = false;
  vb[4] = va[4] + 1;
  assert(vector_cmp_with(va, vb, cmpintlongp_data_failer, fail_next) == -1);

  *fail_next = false;
  va[4] = vb[4] + 1;
  assert(vector_cmp_with(va, vb, cmpintlongp_data_failer, fail_next) == +1);

  va[4] = vb[4];

  // When va and vb are equal it returns 0
  assert(!vector_cmp_with(va, vb, cmpintlongp_data, &data));

  // When va is exhausted before vb it returns -1
  va = vector_truncate(va, vector_length(vb) - 1);
  assert(vector_cmp_with(va, vb, cmpintlongp_data, &data) == -1);

  // When vb is exhausted before vb it returns +1
  vb = vector_truncate(vb, vector_length(va) - 1);
  assert(vector_cmp_with(va, vb, cmpintlongp_data, &data) == +1);

  vector_delete(va);
  vector_delete(vb);
}

int main() {
  test_vector_eq();
  test_vector_eq_with();
  test_vector_cmp();
  test_vector_cmp_with();
}
