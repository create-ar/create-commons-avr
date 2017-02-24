#ifndef ITERATOR_H
#define ITERATOR_H

/**
 * @brief      Defines an interface for an iterator.
 *
 * @tparam     T     Type parameter.
 */
template<class T>
class Iterator
{
	/**
	 * @brief      Element iterator is currently pointing at.
	 *
	 * @return     { description_of_the_return_value }
	 */
	T* current() = 0;
	void reset() = 0;
	bool moveNext() = 0;
}

#endif