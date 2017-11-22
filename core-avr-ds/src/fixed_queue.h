#ifndef CIRCLEQUEUE_H
#define CIRCLEQUEUE_H

#include <inttypes.h>

/**
 * Queue with a fixed size in memory.
 */
template<class T>
class FixedQueue
{
private:

    /**
     * Dynamically allocated array of pointers.
     */
    T** buffer_;

    /**
     * Total capacity of the queue.
     */
    int32_t capacity_;

    /**
     * Start index of the queue.
     */
    int32_t start_;

    /**
     * End index of the queue.
     */
    int32_t end_;

    /**
     * Advances the start index.
     */
    void AdvanceStart()
    {
        if (start_ == end_)
        {
            start_ = end_ = -1;
        }
        else
        {
            start_ = (start_ + 1) % capacity_;
        }
    }

    /**
     * Advances the end index.
     */
    bool AdvanceEnd()
    {
        if (this->get_size() == this->get_capacity())
        {
            return false;
        }

        end_ = (end_ + 1) % capacity_;

        return true;
    }

public:

    /**
     * Creates a fixed size queue.
     */
    FixedQueue(int32_t capacity) : capacity_(capacity), start_(-1), end_(-1)
    {
        buffer_ = new T*[capacity];
    }

    /**
     * Destroys a fixed size queue.
     */
    ~FixedQueue()
    {
        delete[] buffer_;
    }

    /**
     * Retrieve the capacity of the queue.
     */
    int32_t get_capacity()
    {
        return capacity_;
    }

    /**
     * Retrieves the size, i.e. how many elements are currently in the queue.
     */
    int32_t get_size()
    {
        if (start_ == -1)
        {
            return 0;
        }

        if (start_ > end_)
        {
            return capacity_ - start_ + end_ + 1;
        }

        return end_ - start_ + 1;
    }

    /**
     * Adds an element to the queue.
     */
    bool Add(T* element) 
    {
        if (!AdvanceEnd())
        {
            return false;
        }

        if (start_ == -1)
        {
            start_ = 0;
        }

        buffer_[end_] = element;

        return true;
    }

    /**
     * Retrieves the first element in the queue without removing it.
     */
    T* Peek()
    {
        if (start_ == -1)
        {
            return nullptr;
        }

        return buffer_[start_];
    }

    /**
     * Removes the first element in the queue.
     */
    T* Remove()
    {
        if (start_ == -1)
        {
            return nullptr;
        }

        auto current = buffer_[start_];

        AdvanceStart();

        return current;
    }
};

#endif