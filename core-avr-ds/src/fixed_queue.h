#ifndef CIRCLEQUEUE_H
#define CIRCLEQUEUE_H

#include <inttypes.h>

template<class T>
class FixedQueue
{
private:

    T** buffer_;

    int32_t capacity_;
    int32_t startIndex_;
    int32_t endIndex_;

    void AdvanceQueue()
    {
        startIndex_ = (startIndex_ + 1) % capacity_;

        if (startIndex_ == endIndex_)
        {
            startIndex_ = endIndex_ = -1;
        }
    }

public:

    FixedQueue(int32_t capacity) : capacity_(capacity), startIndex_(-1), endIndex_(-1)
    {
        buffer_ = new T*[capacity];
    }

    ~FixedQueue()
    {
        delete[] buffer_;
    }

    int32_t get_capacity()
    {
        return capacity_;
    }

    int32_t get_size()
    {
        return endIndex_ - startIndex_;
    }

    bool Add(T* element) 
    {
        // find an index
        auto index = -1;
        if (-1 == startIndex_)
        {
            index = 0;

            startIndex_ = 0;
            endIndex_ = 1;

            buffer_[index] = element;

            return true;
        }

        return false;
    }

    T* Peek()
    {
        if (startIndex_ > -1)
        {
            return buffer_[startIndex_];
        }

        return nullptr;
    }

    T* Poll()
    {
        if (startIndex_ > -1)
        {
            auto current = buffer_[startIndex_];

            this->AdvanceQueue();

            return current;
        }

        return nullptr;
    }
};

#endif