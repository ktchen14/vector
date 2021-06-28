#include <assert.h>

#include <vector.h>
#include "test.h"

void test_vector_at(void) {
  vector_t(int) vector = vector_define(int, 1, 2, 3, 4, 5, 6, 7, 8);
  int number = 0;

  // It evaluates each argument once
  vector_at((number++, vector), 1, sizeof(vector[0]));
  assert(number == 1);
  vector_at(vector, (number++, 1), sizeof(vector[0]));
  assert(number == 2);
  vector_at(vector, 1, (number++, sizeof(vector[0])));
  assert(number == 3);

  // Its expansion is an expression
  assert(vector_at(vector, 0, sizeof(vector[0])));

  // Its result is equivalent to pointer addition on the vector
  assert(vector_at(vector, 0, sizeof(vector[0])) == vector + 0);
  assert(vector_at(vector, 4, sizeof(vector[0])) == vector + 4);
  assert(vector_at(vector, 8, sizeof(vector[0])) == vector + 8);

  vector_delete(vector);

  // With a const int * its result type is const int *
  const int *c_vector = vector_define(const int, 1, 2, 3, 4);
  static_assert(_Generic(vector_at(c_vector, 1, sizeof(c_vector[0])),
      const int *: 1, int *: 0),
    "result type should be const int *");

  // With a const void * its result type is const void *
  const void *c_void_vector = c_vector;
  static_assert(_Generic(vector_at(c_void_vector, 1, sizeof(c_void_vector[0])),
      const void *: 1, void *: 0),
    "result type should be const void *");

  vector_delete((int *) c_vector);

  // With an int * its result type is int *
  int *m_vector = vector_define(int, 1, 2, 3, 4);
  static_assert(_Generic(vector_at(m_vector, 1, sizeof(m_vector[0])),
      const int *: 0, int *: 1),
    "result type should be int *");

  // With a void * its result type is void *
  void *m_void_vector = m_vector;
  static_assert(_Generic(vector_at(m_void_vector, 1, sizeof(m_void_vector[0])),
      const void *: 0, void *: 1),
    "result type should be void *");

  vector_delete(m_vector);
}

void test_vector_get(void) {
  vector_t(int) vector = vector_define(int, 1, 2, 3, 5, 8, 13);

  // It copies the element at the index in the vector to elmt
  int data = 0;
  vector_get(vector, 2, &data, sizeof(vector[0]));
  assert(data == 3);

  // When elmt is an element in the vector itself, it copies the element at the
  // index in the vector to elmt
  vector_get(vector, 2, vector + 1, sizeof(vector[0]));
  assert_vector_data(vector, 1, 3, 3, 5, 8, 13);

  // When elmt is the element at the index in the vector it doesn't modify the
  // vector
  vector_get(vector, 4, vector + 4, sizeof(vector[0]));
  assert_vector_data(vector, 1, 3, 3, 5, 8, 13);

  vector_delete(vector);
}

void test_vector_set(void) {
  int *vector = vector_define(int, 1, 2, 3, 5, 8, 13);

  // It copies elmt to the element at the index in the vector. No other elements
  // in the vector are modified.
  vector_set(vector, 2, &(int) {9}, sizeof(vector[0]));
  assert_vector_data(vector, 1, 2, 9, 5, 8, 13);

  // When elmt is an element in the vector itself, it copes the elmt to the
  // element at the index in the vector. No other elements in the vector are
  // modified.
  vector_set(vector, 2, vector + 3, sizeof(vector[0]));
  assert_vector_data(vector, 1, 2, 5, 5, 8, 13);

  // When elmt is the element at the index in the vector it doesn't modify the
  // vector
  vector_set(vector, 4, vector + 4, sizeof(vector[0]));
  assert_vector_data(vector, 1, 2, 5, 5, 8, 13);

  vector_delete(vector);
}

int main() {
  test_vector_at();
  test_vector_get();
  test_vector_set();
}
