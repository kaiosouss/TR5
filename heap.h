#include "heap.h"

HEAP* HEAP_create(int n, COMP* compara) {
	HEAP* heap = malloc(sizeof(HEAP));
	heap->elems = malloc(n * sizeof(void*));
	heap->N = n;
	heap->P = 0;
	heap->comparador = compara;

	return heap;
}

void HEAP_add(HEAP* heap, void* newelem) {
  if (heap->P < heap->N) {
    heap->elems[heap->P] = newelem;
	int pos = heap->P;

	while (heap->comparador(heap->elems[pos], heap->elems[(pos - 1) / 2]) > 0) {
		void* aux = heap->elems[pos];
		heap->elems[pos] = heap->elems[(pos - 1) / 2];
		heap->elems[(pos - 1) / 2] = aux;	
		pos = (pos - 1) / 2;
	}	

	heap->P++;
  }
}

void* HEAP_remove(HEAP* heap) {
	if (heap->P > 0) {
		void* min = heap->elems[0];
		heap->P--;

		heap->elems[0] = heap->elems[heap->P];
		heap->elems[heap->P] = min;

		int father = 0;
		int son = father * 2 + 1;
		
		while (son < heap->P) {
			if (son + 1 < heap->P) {
				if (heap->comparador(heap->elems[son], heap->elems[son + 1]) < 0) {
					son += 1;
				}
			}

			if (heap->comparador(heap->elems[father], heap->elems[son]) < 0) {
				void* aux = heap->elems[father];
				heap->elems[father] = heap->elems[son];
				heap->elems[son] = aux;

				father = son;
				son = father * 2 + 1;
			} else {
				break;
			}
		}

		return min;
	}
}