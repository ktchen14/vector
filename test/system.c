#include <assert.h>
#include <vector.h>

int main() {
  vector_on(size_t) vector = vector_create();

  for (size_t i = 0; i < 20; i++)
    vector = vector_append(vector, &i);

  for (size_t i = 0; i < vector_length(vector); i++)
    assert(vector[i] == i);
  assert(vector_length(vector) == 20);

  return 0;
}
