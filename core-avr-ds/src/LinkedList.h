#ifndef LINKEDLIST_h
#define LINKEDLIST_h

#include "Iterator.h"

/**
 * @brief      Node class used internally to LinkedList.
 *
 * @tparam     T     Type of value this node can hold.
 */
template <class T>
class Node
{
public:
	/**
	 * Value this node holds.
	 */
	T* value = nullptr;

	/**
	 * The previous node in the list.
	 */
	Node* previous = nullptr;

	/**
	 * The next node in the list.
	 */
	Node* next = nullptr;
};

/**
 * @brief      Iterator implementation for linked lists.
 *
 * @tparam     T     Type parameter.
 */
template <class T>
class LinkedListIterator : public Iterator<T>
{
private:

	/**
	 * Pointer to the head pointer.
	 */
	Node<T>** _head;

	/**
	 * Current pointer.
	 */
	Node<T>* _ptr = nullptr;

public:

	/**
	 * @brief      Constructor.
	 *
	 * @param      head  The pointer to the head pointer.
	 */
	LinkedListIterator<T>(Node<T>** head)
	{
		_head = head;
	}

	/**
	 * @brief      Retrieves the current value.
	 *
	 * @return     Pointer to current value.
	 */
	T* current() override
	{
		if (nullptr == _ptr)
		{
			return nullptr;
		}

		return _ptr->value;
	}

	/**
	 * @brief      Resets iterator.
	 */
	void reset() override
	{
		_ptr = nullptr;
	}

	/**
	 * @brief      Moves to the next element.
	 *
	 * @return     True if there is a next element, false if not.
	 */
	bool moveNext() override
	{
		if (nullptr == _ptr)
		{
			if (nullptr == *_head)
			{
				return false;
			}

			_ptr = *_head;

			return true;
		}

		if (nullptr == _ptr->next)
		{
			return false;
		}

		_ptr = _ptr->next;

		return true;
	}
};

/**
 * @brief      Basic doubly linked list implementation.
 *
 * @tparam     T     Type parameter.
 */
template <class T>
class LinkedList
{
private:
	/**
	 * Pointer to the head node.
	 */
	Node<T>* _head = nullptr;

	/**
	 * Pointer to the tail node.
	 */
	Node<T>* _tail = nullptr;

public:

	/**
	 * @brief      Destructor.
	 */
	~LinkedList()
	{
		clear();
	}

	/**
	 * @brief      Clears all nodes.
	 */
	void clear()
	{
		Node<T>* ptr = _head;
		while (nullptr != ptr)
		{
			Node<T>* next = ptr->next;

			delete ptr;

			ptr = next;
		}

		_head = _tail = nullptr;
	}

	/**
	 * @brief      Retrieves an iterator.
	 *
	 * @return     The iterator with which to iterate.
	 */
	Iterator<T>* it()
	{
		return new LinkedListIterator<T>(&_head);
	}

	/**
	 * @brief      The total number of elements.
	 *
	 * @return     The total number of elements.
	 */
	int count()
	{
		int count = 0;

		Node<T>* ptr = _head;
		while (nullptr != ptr)
		{
			count++;

			ptr = ptr->next;
		}

		return count;
	}
	
	/**
	 * @brief      Adds an element to the list. Heap allocates a new node with
	 * which to store the element.
	 *
	 * @param      element  The element to add.
	 */
	void add(T* element)
	{
		Node<T>* node = new Node<T>();
		node->value = element;

		if (nullptr == _head)
		{
			_head = _tail = node;
		}
		else
		{
			node->previous = _tail;
			_tail->next = node;

			_tail = node;
		}
	}

	/**
	 * @brief      Removes the element and deletes the node the element was
	 * stored within.
	 *
	 * @param      element  The element to remove.
	 *
	 * @return     True if successfully removed.
	 */
	bool remove(T* element)
	{
		Node<T>* ptr = _head;
		while (nullptr != ptr)
		{
			if (ptr->value != element)
			{
				ptr = ptr->next;

				continue;
			}

			// head
			if (nullptr == ptr->previous)
			{
				// head and tail
				if (nullptr == ptr->next)
				{
					_head = _tail = nullptr;
				}
				else
				{
					_head = ptr->next;
					_head->previous = nullptr;
				}
			}
			// tail
			else if (nullptr == ptr->next)
			{
				ptr->previous->next = nullptr;
				_tail = ptr->previous;
			}
			// somewhere in the middle
			else
			{
				ptr->next->previous = ptr->previous;
				ptr->previous->next = ptr->next;
			}

			// delete the node
			delete ptr;

			return true;
		}

		return false;
	}

	/**
	 * @brief      Determines if the element is contained within the list.
	 *
	 * @param      element  The element to query for.
	 *
	 * @return     True if the element is contained within the list.
	 */
	bool contains(T* element)
	{
		Node<T>* ptr = _head;
		while (nullptr != ptr)
		{
			if (ptr->value == element)
			{
				return true;
			}

			ptr = ptr->next;
		}

		return false;
	}
};

#endif