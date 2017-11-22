#ifndef CIRCLEQUEUE_H
#define CIRCLEQUEUE_H

#include <inttypes.h>

template<class T>
class FixedQueue
{
private:

    T** buffer_;

    int32_t capacity_;
    int32_t start_;
    int32_t end_;

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

    FixedQueue(int32_t capacity) : capacity_(capacity), start_(-1), end_(-1)
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

    T* Peek()
    {
        if (start_ == -1)
        {
            return nullptr;
        }

        return buffer_[start_];
    }

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