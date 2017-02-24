#ifndef LINKEDLIST_h
#define LINKEDLIST_h

#include "Iterator.h"

template <class T>
class Node
{
public:
	T* value = nullptr;

	Node* previous = nullptr;
	Node* next = nullptr;
};

template <class T>
class LinkedListIterator : public Iterator<T>
{
private:

	Node<T>** _head;
	Node<T>* _ptr = nullptr;

public:

	LinkedListIterator<T>(Node<T>** head)
	{
		_head = head;
	}

	T* current() override
	{
		if (nullptr == _ptr)
		{
			return nullptr;
		}

		return _ptr->value;
	}

	void reset() override
	{
		_ptr = nullptr;
	}

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

template <class T>
class LinkedList
{
private:
	Node<T>* _head = nullptr;
	Node<T>* _tail = nullptr;

public:

	~LinkedList()
	{
		clear();
	}

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

	Iterator<T>* it()
	{
		return new LinkedListIterator<T>(&_head);
	}

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