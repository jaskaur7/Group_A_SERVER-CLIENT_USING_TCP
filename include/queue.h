/** @file queue.h
 *  @brief Function prototypes for queueing
 *
 *  
 * This function is used to build a queue for multi-connections request for the server.
 *
 */

#ifndef QUEUE_H_
#define QUEUE_H_

struct Queue; 

struct Queue* createQueue(unsigned capacity);

int isFull(struct Queue* queue);

int isEmpty(struct Queue* queue);

void enqueue(struct Queue* queue, int item);

int dequeue(struct Queue* queue);

int front(struct Queue* queue);

int rear(struct Queue* queue);

#endif /* QUEUE_H_ */