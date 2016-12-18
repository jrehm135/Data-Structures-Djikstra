// implement the class here
#include "heap_priority_queue.h"

template <typename T>
HeapPriorityQueue<T>::HeapPriorityQueue() : Queue(), count(0)
{}

template <typename T>
bool HeapPriorityQueue<T>::isEmpty()
{
	return Queue.isEmpty();
	//returns true if nothing is in the queue
}

template <typename T>
void HeapPriorityQueue<T>::add(const T& item)
{
	count = Queue.getLength();
	Queue.insert(count,item);
	siftUp(count);
	count++;
	//Inserts item at the last index in the array, the re-sorts the values
}

template <typename T>
void HeapPriorityQueue<T>::remove()
{
	count = Queue.getLength();
	if (Queue.isEmpty())
		throw std::logic_error("Heap is empty");
	//If queue is empty throws an error
	else {
		count--;
		T temp = Queue.getEntry(count);
		Queue.remove(count);
		//stores the value of count before deleting it
		if (count > 0)
		{
			Queue.setEntry(0, temp);
			siftDown(0);
			//If there were at least 2 things in the heap, sets the root node to the last value, then re-sorts the heap
		}
	}
}

template <typename T>
T HeapPriorityQueue<T>::peek()
{
	if (Queue.isEmpty())
		throw std::logic_error("Array is Empty");
	//If queue is empty throws error
	else
	{
		return Queue.getEntry(0);
		//Otherwise displays the root node
	}
}

template <typename T>
void HeapPriorityQueue<T>::siftUp(int position)
{
	int parent;
	T temp;
	if (position != 0) {
		parent = (position - 1) / 2;
		//parent index
		if (Queue.getEntry(parent) > Queue.getEntry(position)) {
			//compares the values of parent and child nodes
			temp = Queue.getEntry(parent);
			Queue.setEntry(parent, Queue.getEntry(position));
			Queue.setEntry(position, temp);
			//if child is greater than parent, swaps them
			siftUp(parent);
			//recursively calls itself on parent node
		}
	}
}

template <typename T>
void HeapPriorityQueue<T>::siftDown(int position) {
	int leftChildIndex;
	int rightChildIndex;
	int biggerNum;
	T temp;
	leftChildIndex = 2 * position + 1;
	rightChildIndex = 2 * position + 2;
	//indices for the left and right child nodes
	if (rightChildIndex >= count) {
		if (leftChildIndex >= count)
			return;
		//returns if indices are out of range
		else
			biggerNum = leftChildIndex;
		//if right child is out of bounds, then there can only be one child, the left child
	}
	else {
		if (Queue.getEntry(leftChildIndex) <= Queue.getEntry(rightChildIndex))
			biggerNum = leftChildIndex;
		else
			biggerNum = rightChildIndex;
		//sets biggerNum to whichever value is larger
	}
	if (Queue.getEntry(position) < Queue.getEntry(biggerNum)) {
		//compares the values of parent and child nodes
		temp = Queue.getEntry(biggerNum);
		Queue.setEntry(biggerNum, Queue.getEntry(position));
		Queue.setEntry(position, temp);
		//if child is greater than parent, swaps them
		siftDown(biggerNum);
		//recursively calls itself on parent node
	}
}