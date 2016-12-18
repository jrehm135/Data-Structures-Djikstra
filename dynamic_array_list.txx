// implement your dynamic array list template class here
#include "dynamic_array_list.h"

template <typename T>
DynamicArrayList<T>::DynamicArrayList() : items(nullptr), maxItems(0), itemCount(0)
{}

template <typename T>
DynamicArrayList<T>::~DynamicArrayList()
{
	if (items != nullptr) delete[] items;
}

template <typename T>
DynamicArrayList<T>::DynamicArrayList(const DynamicArrayList<T> & x)
{
	maxItems = x.maxItems;
	itemCount = x.itemCount;
	items = maxItems ? new T[maxItems] : nullptr;
	std::copy(x.items, x.items + x.maxItems, items);
}

template <typename T>
DynamicArrayList<T>& DynamicArrayList<T>::operator=(DynamicArrayList<T> x)
{
	swap(*this, x);

	return *this;
}

template <typename T>
void DynamicArrayList<T>::swap(DynamicArrayList<T>& x, DynamicArrayList<T>& y)
{
	std::swap(x.maxItems, y.maxItems);
	std::swap(x.itemCount, y.itemCount);
	std::swap(x.items, y.items);
}

template <typename T>
bool DynamicArrayList<T>::isEmpty()
{
	return (itemCount == 0);
}


template <typename T>
std::size_t DynamicArrayList<T>::getLength()
{
	return itemCount;
}

template <typename T>
void DynamicArrayList<T>::insert(std::size_t position, const T& item)
{
		if (position >= 0 && position < itemCount + 1) //is it a valid insert?
		{
			if (itemCount == maxItems) //do we have room to insert?
			{
				if (maxItems == 0)
				{
					maxItems = 1;
					items = new T[maxItems]; //doesn't overwrite old array
				}
				else
				{
					//grow the items array

					maxItems *= 2;

					T * oldItems = items; //get addr of items array

					items = new T[maxItems]; //doesn't overwrite old array

					for (int i = 0; i < maxItems/2; i++)
						items[i] = oldItems[i];

					if (oldItems != nullptr)
						delete[] oldItems;
				}
			}

			if (position != itemCount) //do we need to shift entries?
			{
				//shift all entries right by one 
				for (long int i = itemCount; i > position; i--)
					items[i] = items[i - 1];
			}


			// insert
			items[position] = item;

			itemCount++;

			return;
		}

		throw std::range_error("Entry reference greater than list length.");
		return;
}

template <typename T>
void DynamicArrayList<T>::remove(std::size_t position)
{
	if (itemCount == 0 || position >= itemCount) //is anything in the list and is there an entry at that position
	{
		throw std::range_error("Entry reference greater than list length.");
		return;
	}
		
	else //shift items left, starting at position
	{
		for (long int i = position; i < itemCount; i++)
		{
			items[i] = items[i + 1];
		}
		--itemCount;
		//decrements itemcount if an item is removed
	}

	return;
}

template <typename T>
void DynamicArrayList<T>::clear()
{
	itemCount = 0;
}

template <typename T>
T DynamicArrayList<T>::getEntry(std::size_t position)
{
	if (itemCount == 0 || position >= itemCount)
		throw std::range_error("Entry reference greater than list length.");
	else
		return items[position];
	//returns the vaalue at position
}

template <typename T>
void DynamicArrayList<T>::setEntry(std::size_t position, const T& newValue)
{
	if (itemCount == 0 || position > itemCount - 1)
		throw std::range_error("Entry reference greater than list length.");
	else items[position] = newValue;
	//sets the value stored at position to the newValue
	return;
}
