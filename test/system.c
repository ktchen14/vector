#include <assert.h>
#include <vector.h>

int main() {
  vector_t(size_t) vector = vector_create();

  for (size_t i = 0; i < 20; i++)
    vector = vector_append(vector, &i);

  assert(vector_length(vector) == 20);

  for (size_t i = 0; i < vector_length(vector); i++)
    assert(vector[i] == i);

  return 0;
}
