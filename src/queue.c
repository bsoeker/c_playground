#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

queue_t *queue_create(size_t cap) {
    queue_t *q = malloc(sizeof(*q));
    if (!q)
        return NULL;

    q->data = malloc(sizeof(int) * cap);
    if (!q->data) {
        free(q);
        return NULL;
    }

    q->size = 0;
    q->cap = cap;
    q->front = 0;
    q->end = 0;
    return q;
}

static int resize(queue_t *q, size_t new_cap) { // cache friendly via repacking
    int *temp = malloc(new_cap * sizeof(int));
    if (!temp) {
        printf("malloc() failed!\n");
        return 0;
    }

    for (int i = 0; i < q->size; i++) {
        temp[i] = q->data[(q->front + i) % q->cap];
    }

    free(q->data);
    q->data = temp;
    q->cap = new_cap;
    q->front = 0;
    q->end = q->size;
    return 1;
}

void queue_enqueue(queue_t *q, int value) {
    if (q->size == q->cap)
        if (!resize(q, 2 * q->cap))
            return;

    q->data[q->end++ % q->cap] = value;
    q->size++;
}

int queue_dequeue(queue_t *q) {
    if (queue_is_empty(q)) {
        printf("Queue underflow!!!\n");
        exit(EXIT_FAILURE);
    }

    q->size--;
    return q->data[q->front++ % q->cap];
}

void queue_free(queue_t *q) {
    free(q->data);
    free(q);
}
