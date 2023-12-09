#ifndef HEAP_H_
#define HEAP_H_

#ifdef _WIN32
  #define EXPORT __declspec(dllexport)
#else
  #define EXPORT __attribute__((visibility("default")))
#endif

#include <stddef.h>

typedef struct Heap{
  int *array;
  size_t size;
} Heap;


#endif
