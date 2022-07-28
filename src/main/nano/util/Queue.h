#ifndef QUEUE_H
#define QUEUE_H

#define NULL_ITEM 65535

typedef struct Queue {
  unsigned short front, rear, size;
  unsigned short capacity;
  unsigned short* array;
} Queue;

Queue* queue(unsigned short capacity) {
  Queue* queue = (Queue*) malloc(sizeof(Queue));
  queue -> capacity = capacity;
  queue -> front = queue -> size = 0;

  queue -> rear = capacity - 1;
  queue -> array = (unsigned short*) malloc((queue -> capacity) * sizeof(unsigned short));
  return queue;
}

unsigned short isFull(Queue* queue) {return ((queue -> size) == (queue -> capacity));}
unsigned short isEmpty(Queue* queue) {return queue -> size == 0;}
unsigned short front(Queue* queue) {return isEmpty(queue) ? NULL_ITEM : (queue -> array)[queue -> front];}
unsigned short rear(Queue* queue) {return isEmpty(queue) ? NULL_ITEM : (queue -> array)[queue -> rear];}

void enqueue(Queue* queue, unsigned short item) {
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
