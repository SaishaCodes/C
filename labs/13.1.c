//Write a C program to implement the variousoperations of max-heap data structure such as:
//a.Creating a heap
//b.Inserting element into the heap.
//c.Removing the max element from the heap.
//d.Extract max

#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 100

struct MaxHeap {
    int *arr;
    int size;
    int capacity;
};

struct MaxHeap* createHeap(int capacity) {
    struct MaxHeap* heap = (struct MaxHeap*)malloc(sizeof(struct MaxHeap));
    if (heap == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    heap->capacity = capacity;
    heap->size = 0;
    heap->arr = (int*)malloc(capacity * sizeof(int));
    if (heap->arr == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    return heap;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void upHeap(struct MaxHeap* heap, int index) {
    while (index > 0 && heap->arr[(index - 1) / 2] < heap->arr[index]) {
        swap(&heap->arr[(index - 1) / 2], &heap->arr[index]);
        index = (index - 1) / 2;
    }
}

void insert(struct MaxHeap* heap, int key) {
    if (heap->size == heap->capacity) {
        printf("Heap is full\n");
        return;
    }
    int i = heap->size;
    heap->arr[i] = key;
    heap->size++;
    upHeap(heap, i);
}

void downHeap(struct MaxHeap* heap, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;
    if (left < heap->size && heap->arr[left] > heap->arr[largest]) {
        largest = left;
    }
    if (right < heap->size && heap->arr[right] > heap->arr[largest]) {
        largest = right;
    }
    if (largest != index) {
        swap(&heap->arr[index], &heap->arr[largest]);
        downHeap(heap, largest);
    }
}

void removeMax(struct MaxHeap* heap) {
    if (heap->size == 0) {
        printf("Heap is empty\n");
        return;
    }
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    downHeap(heap, 0);
}

int extractMax(struct MaxHeap* heap) {
    if (heap->size == 0) {
        printf("Heap is empty\n");
        exit(1);
    }
    int max = heap->arr[0];
    removeMax(heap);
    return max;
}

void printHeap(struct MaxHeap* heap) {
    printf("Max Heap elements: ");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->arr[i]);
    }
    printf("\n");
}

int main() {
    struct MaxHeap* heap = createHeap(MAX_HEAP_SIZE);

    insert(heap, 10);
    insert(heap, 20);
    insert(heap, 15);
    insert(heap, 40);
    insert(heap, 50);
    insert(heap, 100);

  
    printHeap(heap);

    printf("Max element removed: %d\n", extractMax(heap));

    printf(heap);
    free(heap->arr);
    free(heap);

    return 0;

}
