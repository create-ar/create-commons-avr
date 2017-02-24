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
public:
	/**
	 * @brief      Destructor.
	 */
	virtual ~Iterator()
	{
		//
	}

	/**
	 * @brief      Element currently pointed to.
	 *
	 * @return     A pointer to the current element.
	 */
	virtual T* current() = 0;

	/**
	 * @brief      Resets the iterator to the beginning.
	 */
	virtual void reset() = 0;

	/**
	 * @brief      Moves the iterator to the next value.
	 *
	 * @return     True if there is another value, false otherwise.
	 */
	virtual bool moveNext() = 0;
};

#endif