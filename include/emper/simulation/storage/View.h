#pragma once

#include <cstddef>

#include <emper/simulation/storage/Handle.h>
#include <emper/simulation/storage/Storage.h>

namespace emper::storage
{

template<typename T>
class View
{
public:
    class Iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Handle<T>;
        using difference_type = std::ptrdiff_t;
        using pointer = Handle<T>*;
        using reference = Handle<T>&;

        Iterator() = default;

        Iterator(TypeStorage<T>* storage, std::size_t index)
            : storage_(storage)
            , index_(index)
        {
        }

        Handle<T> operator*() const
        {
            return Handle<T>(storage_, index_);
        }

        Iterator& operator++()
        {
            ++index_;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator copy = *this;
            ++index_;
            return copy;
        }

        bool operator==(const Iterator& other) const
        {
            return index_ == other.index_;
        }

        bool operator!=(const Iterator& other) const
        {
            return index_ != other.index_;
        }

    private:
        TypeStorage<T>* storage_ = nullptr;
        std::size_t index_ = 0;
    };

    View() = default;

    explicit View(TypeStorage<T>* storage)
        : storage_(storage)
    {
    }

    Iterator begin()
    {
        return Iterator(storage_, 0);
    }

    Iterator end()
    {
        return Iterator(storage_, storage_ ? storage_->size() : 0);
    }

    std::size_t size() const
    {
        return storage_ ? storage_->size() : 0;
    }

private:
    TypeStorage<T>* storage_ = nullptr;
};

} // namespace emper::storage