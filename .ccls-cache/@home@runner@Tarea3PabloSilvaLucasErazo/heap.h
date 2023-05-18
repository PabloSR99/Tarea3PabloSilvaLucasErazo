#ifndef Heap_h
#define Heap_h

typedef struct Heap Heap;

Heap* createHeap();
void* heap_top(Heap* pq);
int get_size(Heap* pq);
void* get_data(Heap* pq, int pos);
void heap_push(Heap* pq, void* data, int priority);
void heap_pop(Heap* pq);
void minus_size(Heap* pq);

#endif /* Heap_h */

