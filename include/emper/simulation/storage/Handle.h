#pragma once

#include <cstddef>

#include <emper/simulation/storage/Storage.h>

namespace emper::storage
{

template<typename T>
class Handle
{
public:
    Handle() = default;

    Handle(TypeStorage<T>* storage, std::size_t slot)
        : storage_(storage)
        , slot_(slot)
    {
    }

    template<auto Member>
    MemberType<Member>& get()
    {
        return storage_->template get<Member>(slot_);
    }

    template<auto Member>
    const MemberType<Member>& get() const
    {
        return storage_->template get<Member>(slot_);
    }

    template<auto Member>
    void set(const MemberType<Member>& value)
    {
        storage_->template get<Member>(slot_) = value;
    }

    std::size_t slot() const
    {
        return slot_;
    }

    bool valid() const
    {
        return storage_ != nullptr;
    }

    explicit operator bool() const
    {
        return valid();
    }

private:
    TypeStorage<T>* storage_ = nullptr;
    std::size_t slot_ = 0;
};

} // namespace emper::storage