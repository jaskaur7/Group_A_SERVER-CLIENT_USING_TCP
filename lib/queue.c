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