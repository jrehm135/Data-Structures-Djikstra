// define your dynamic array list template class here
#ifndef _DYNAMIC_ARRAY_LIST_H_
#define _DYNAMIC_ARRAY_LIST_H_

#include "abstract_list.h"
#include <iostream>
#include <utility>
#include <stdexcept>

template <typename T>
class DynamicArrayList : public AbstractList<T>
{
public:

	// Constructor
	DynamicArrayList();

	// Destructor
	~DynamicArrayList();

	// copy constructor
	DynamicArrayList(const DynamicArrayList & x);

	// copy assignment
	DynamicArrayList& operator=(DynamicArrayList x);

	//for copy-swap idiom
	void swap(DynamicArrayList<T>& x, DynamicArrayList<T>& y);

	// returns true if the list is empty and false otherwise
	bool isEmpty();

	// returns the length of the list
	size_t getLength();

	//inserts item into position in the linked list
	void insert(std::size_t position, const T& item);

	//removes whatever is at position
	void remove(std::size_t position);

	// removes everything from the list
	void clear();

	//returns the value at position
	T getEntry(std::size_t position);

	//sets the entry at position to newValue
	void setEntry(std::size_t position, const T& newValue);

private:
	T * items;
	//initializes the array
	long int maxItems;
	long int itemCount;
};
#include "dynamic_array_list.txx"
#endif // _DYNAMIC_ARRAY_LIST_H_