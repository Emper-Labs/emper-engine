#pragma once

#include <cstddef>
#include <span>

#include <emper/Types.h>
#include <emper/simulation/storage/Storage.h>

namespace emper::storage
{

// Storage API: direct access to the contiguous SoA columns.
//
// The metadata lookup happens once when column() is called; the returned
// std::span is then iterated with zero overhead (ideal for SIMD/GPU loops).
template<typename T>
class StorageView
{
public:
    explicit StorageView(TypeStorage<T>* storage)
        : storage_(storage)
    {
    }

    std::size_t size() const
    {
        return storage_ ? storage_->size() : 0;
    }

    // Returns a contiguous std::span over one field. Access by data-member pointer:
    //     storage.column<&Particle::position>()[i].x
    template<auto Member>
    std::span<MemberType<Member>> column()
    {
        if (storage_)
        {
            return storage_->template column<Member>();
        }
        return std::span<MemberType<Member>>{};
    }

private:
    TypeStorage<T>* storage_ = nullptr;
};

} // namespace emper::storage