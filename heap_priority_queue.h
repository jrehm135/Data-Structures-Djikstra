#ifndef HEAP_PRIORITY_QUEUE_H
#define HEAP_PRIORITY_QUEUE_H

#include "abstract_priority_queue.h"
#include "dynamic_array_list.h"

// define the class here
template <typename T>
class HeapPriorityQueue : public AbstractPriorityQueue<T>
{
public:
	// Constructor
	HeapPriorityQueue();
	
	//Checks if the Queue is empty
	bool isEmpty();

	//Adds item to the queue
	void add(const T& item);

	//If queue is not empty, removes the root node from the queue
	void remove();

	//If queue is not empty, returns the root node from the queue
	T peek();

private: 
	DynamicArrayList<T> Queue;
	long count;
	//initializes the queue and the count

	void siftUp(int position);
	void siftDown(int position);
	//Helper functions for add and remove
};
#include "heap_priority_queue.txx"
#endif
