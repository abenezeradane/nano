#ifndef QUEUE_H
#define QUEUE_H

#define NULL_ITEM 65536

typedef struct Queue {
  unsigned int front, rear, size;
  unsigned int capacity;
  unsigned int* array;
} Queue;

Queue* queue(unsigned int capacity) {
  Queue* queue = (Queue*) malloc(sizeof(Queue));
  queue -> capacity = capacity;
  queue -> front = queue -> size = 0;

  queue -> rear = capacity - 1;
  queue -> array = (unsigned int*) calloc(queue -> capacity, sizeof(unsigned int));
  return queue;
}

unsigned int isFull(Queue* queue) {return ((queue -> size) == (queue -> capacity));}
unsigned int isEmpty(Queue* queue) {return queue -> size == 0;}
unsigned int front(Queue* queue) {return isEmpty(queue) ? NULL_ITEM : (queue -> array)[queue -> front];}
unsigned int rear(Queue* queue) {return isEmpty(queue) ? NULL_ITEM : (queue -> array)[queue -> rear];}

void enqueue(Queue* queue, unsigned int item) {
  if(isFull(queue))
    return;

  queue -> rear = ((queue -> rear) + 1) % queue -> capacity;
  queue -> array[queue -> rear] = item;
  queue -> size = (queue -> size) + 1;
}

void dequeue(Queue* queue) {
  if (isEmpty(queue))
    return;

  queue -> front = ((queue -> front) + 1) % queue -> capacity;
  queue -> size = (queue -> size) - 1;
}

void empty(Queue* queue) {
  if (isEmpty(queue))
    return;

  for (int itr = 0; itr < queue -> size; itr++)
    dequeue(queue);
}

#endif
