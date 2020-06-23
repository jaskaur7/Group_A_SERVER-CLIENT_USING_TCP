

/**
*\functions: struct Queue* createQueue(unsigned capacity) ,int isFull(struct Queue* queue),int isEmpty(struct Queue* queue)
*
*\author:Prerit Sikerwal
*
*\brief:C program for array implementation of queue.
*
*@param[in]:queue
*
*/

#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
#include "../include/queue.h"

/* A structure to represent a queue */ 
struct Queue 
{ 
    int front, rear, size; 
    unsigned capacity; 
    int* array; 
}; 
  




/* function to create a queue of given capacity */  
/* It initializes size of queue as 0 */
struct Queue* createQueue(unsigned capacity) 
{ 
    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue)); 
    queue->capacity = capacity;
    queue->rear = capacity - 1;  
    queue->front = queue->size = 0;  
    queue->array = (int*) malloc(queue->capacity * sizeof(int)); 
    return queue; 
} 



  
/* Queue is full when size becomes equal to the capacity  */
int isFull(struct Queue* queue) {
    if (queue->size == queue->capacity){
    return 1;
    }
    return 0; 
} 


  
/* Queue is empty when size is 0 */
int isEmpty(struct Queue* queue){  
    if (queue->size == 0){
    return 1;
    }
    return 0; 
} 
  





/**
* \function: void enqueue(struct Queue* queue, int item) 
*
* \autor: Saksham Mal
*
* \brief:  The function is used to add an item to the queue and also changes rear and size.
*
* @param[in] int 
*
*/
 
void enqueue(struct Queue* queue, int item) 
{ 
    if (isFull(queue)) 
        return; 
    queue->rear = (queue->rear + 1)%queue->capacity; 
    queue->array[queue->rear] = item; 
    queue->size = queue->size + 1; 
} 
  
  /**
* \function: int dequeue(struct Queue* queue)
*
* \autor: Saksham Mal
*
* \brief:  The function is used to remove an item from the queue and also changes front and size
*
* @param[in] queue
*
*/
 
int dequeue(struct Queue* queue) 
{ 
    if (isEmpty(queue)) 
        return INT_MIN; 
    int item = queue->array[queue->front]; 
    queue->front = (queue->front + 1)%queue->capacity; 
    queue->size = queue->size - 1; 
    return item; 
} 
  
  /**
* \function: int front(struct Queue* queue)
*
* \autor: Saksham Mal
*
* \brief:  The function is used to get front of queue
*
* @param[in] queue
*
*/

int front(struct Queue* queue) 
{ 
    if (isEmpty(queue)) 
        return INT_MIN; 
    return queue->array[queue->front]; 
} 
  
  /**
* \function: int rear(struct Queue* queue) 
*
* \autor: Saksham Mal
*
* \brief:  The function is used to get rear of queue
*
* @param[in] queue.
*
*/
 
int rear(struct Queue* queue) 
{ 
    if (isEmpty(queue)) 
        return INT_MIN; 
    return queue->array[queue->rear]; 
}