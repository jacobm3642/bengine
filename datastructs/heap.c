#include "heap.h"
#include <stdlib.h>
#include <stddef.h> 

void swap(int i, int j, Heap *heap) {
  int *array = heap->array;
  int temp;
  temp = array[i];
  array[i] = array[j];
  array[j] = temp;
}

void min_sift_down(int i, Heap *heap) {
  int *array = heap->array;
  int size = heap->size;
  int kid1, kid2;
  kid1 = 2*i+1;
  kid2 = 2*i+2;
  if (kid1 < size && array[i] > array[kid1]) {
    swap(i, kid1, heap);
  }
  if (kid2 < size && array[i] > array[kid2]) {
    swap(i, kid2, heap);
  }
}

void max_sift_down(int i, Heap *heap) {
  int *array = heap->array;
  int size = heap->size;
  int kid1, kid2;
  kid1 = 2*i+1;
  kid2 = 2*i+2;
  if (kid1 < size && array[i] < array[kid1]) {
    swap(i, kid1, heap);
  }
  if (kid2 < size && array[i] < array[kid2]) {
    swap(i, kid2, heap);
  }
}


void min_heapafy(Heap *heap, int i) { 
  int *array = heap->array;
  int size = heap->size;
  for (int i = size; i != -1; i--){
    min_sift_down(i, heap);
  }
}