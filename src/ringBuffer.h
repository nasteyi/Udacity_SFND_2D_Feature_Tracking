#ifndef rignBuffer_h
#define rignBuffer_h

#include <vector>


template <typename T>
class RingBufferConstIterator;

template <typename T>
class RingBufferIterator;

template <typename T>
class RingBuffer final
{
public:
    using value_type = T;

    explicit RingBuffer(std::size_t size)
    : capacity(size)
    {
        innerArray.resize(size);
    }

    T& at(std::size_t idx)
    {
        return innerArray.at((readIdx + idx) % innerArray.size());
    }

    T& back()
    {
        return at(size() - 1);
    }

    T& shift_back()
    {
        if (curSize < innerArray.size())
        {
            curSize++;
        }
        else
        {
            readIdx = (readIdx + 1) % innerArray.size();
        }

        return back();
    }

    void push_back(const T& item)
    {
        shift_back() = item;

        assert(innerArray.size() <= capacity &&  "array exceeds max capacity");
    }

    bool empty() const
    {
        return 0 == curSize;
    }

    std::size_t size() const
    {
        return curSize;
    }

    void clear()
    {
        curSize = 0;
        readIdx = 0;
    }

    RingBufferIterator<T> end()
    {
        return RingBufferIterator<T>(*this, size());
    }

    RingBufferIterator<T> begin()
    {
        return RingBufferIterator<T>(*this, 0);
    }

private:
    const std::size_t capacity;

    std::vector<T> innerArray;

    std::size_t curSize{};
    std::size_t readIdx{};
};


template <typename T>
RingBufferIterator<T> operator-(
    const RingBufferIterator<T>& a,
    std::ptrdiff_t offset)
{
    RingBufferIterator<T> result = a;
    result += -offset;
    return result;
}


template <typename T>
class RingBufferConstIterator : public std::iterator<
    std::random_access_iterator_tag,
    T,
    std::ptrdiff_t,
    const T*,
    const T&>
{
public:
    friend class RingBuffer<T>;

    RingBufferConstIterator() = default;

    explicit RingBufferConstIterator(
        const RingBuffer<T>& container,
        const std::size_t idx)
        : pContainer(&container)
        , containerIdx(idx)
    {}

protected:
    const RingBuffer<T>* pContainer{};
    std::size_t containerIdx{};
};


template <typename T>
class RingBufferIterator : public RingBufferConstIterator<T>
{
public:
    friend class RingBuffer<T>;

    RingBufferIterator() = default;

    explicit RingBufferIterator(
        RingBuffer<T>& container,
        const std::size_t idx)
        : RingBufferConstIterator<T>(container, idx)
    {}

    T& operator*() const
    {
        return (*const_cast<RingBuffer<T>*>(
            RingBufferIterator<T>::pContainer)).at(
                RingBufferIterator<T>::containerIdx);
    }

    T* operator->() const
    {
        return &(operator*());
    }

    RingBufferIterator<T>& operator++()
    {
        ++RingBufferIterator<T>::containerIdx;
        return *this;
    }

    RingBufferIterator<T>& operator--()
    {
        --RingBufferConstIterator<T>::containerIdx;
        return *this;
    }

    RingBufferIterator<T>& operator+=(std::ptrdiff_t offset)
    {
        RingBufferConstIterator<T>::containerIdx += offset;
        return *this;
    }
};

#endif // rignBuffer_h