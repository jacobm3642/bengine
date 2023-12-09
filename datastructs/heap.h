#ifndef HEAP_H_
#define HEAP_H_

#include <stddef.h>

typedef struct Heap{
  int *array;
  size_t size;
} Heap;

void min_heapafy(Heap *heap, int i);
void max_heapafy(Heap *heap, int i);

#endif
