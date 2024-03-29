/// @file header/vector/create.c

#ifndef VECTOR_CREATE_C
#define VECTOR_CREATE_C

#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "create.h"

__vector_inline__ vector_t vector_create(void) {
  struct __vector_header_t *header;

  if ((header = malloc(sizeof(*header))) == NULL)
    return NULL;

  header->volume = 0;
  header->length = 0;
  return header->data;
}

__vector_inline__
vector_t vector_import_z(const void *data, size_t length, size_t z) {
  struct __vector_header_t *header;

  // Doesn't overflow because this is the size of data
  size_t size = length * z;
  if (__builtin_add_overflow(size, sizeof(*header), &size))
    return errno = ENOMEM, NULL;
  if ((header = malloc(size)) == NULL)
    return NULL;

  header->volume = length;
  header->length = length;
  return memcpy(header->data, data, length * z);
}

__vector_inline__ vector_t vector_duplicate_z(vector_c source, size_t z) {
  struct __vector_header_t *header;

  size_t volume = vector_volume(source);
  size_t length = vector_length(source);

  if ((header = malloc(sizeof(*header) + volume * z)) == NULL) {
    if (length == volume)
      return NULL;
    if ((header = malloc(sizeof(*header) + length * z)) == NULL)
      return NULL;
    header->volume = length;
  } else
    header->volume = volume;

  header->length = length;

  return memcpy(header->data, source, length * z);
}

#endif /* VECTOR_CREATE_C */
