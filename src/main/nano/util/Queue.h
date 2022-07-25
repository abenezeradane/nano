#ifndef QUEUE_H
#define QUEUE_H

typedef struct Queue {
  unsigned short front, rear, size;
  unsigned short capacity;
  float** array;
} Queue;

Queue* createQueue(unsigned short capacity) {
  Queue* queue = (Queue*) malloc(sizeof(Queue));
  queue -> capacity = capacity;
  queue -> front = queue -> size = 0;

  queue -> rear = capacity - 1;
  queue -> array = (float**) malloc(queue -> capacity * sizeof(float));
  return queue;
}

int isEmpty(Queue* queue) {
  return queue -> size == 0;
}

int isFull(Queue* queue) {
  return queue -> size == queue -> capacity;
}

float* rear(Queue* queue) {
  return isEmpty(queue) ? NULL : queue -> array[queue -> rear];
}

float* front(Queue* queue) {
  return isEmpty(queue) ? NULL : queue -> array[queue -> front];
}

void enqueue(Queue* queue, float* item) {
  if(isFull(queue))
    return;

  queue -> rear = ((queue -> rear) + 1) % queue -> capacity;
  queue -> array[queue -> rear] = item;
  queue -> size = (queue -> size) + 1;
}

float* dequeue(Queue* queue) {
  if (isEmpty(queue))
    return NULL;

  float* item = queue -> array[queue -> front];
  queue -> front = ((queue -> front) + 1) % queue -> capacity;
  queue -> size = (queue -> size) - 1;

  return item;
}

#endif
