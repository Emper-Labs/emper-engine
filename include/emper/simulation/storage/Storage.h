#pragma once

#include <cstddef>
#include <cstring>
#include <memory>
#include <span>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#include <emper/Types.h>

namespace emper::storage
{

template<auto Member>
std::size_t memberKey()
{
    auto ptr = Member;
    std::size_t key;
    static_assert(sizeof(ptr) <= sizeof(key));
    std::memcpy(&key, &ptr, sizeof(ptr));
    return key;
}

template<typename T>
struct MemberTypeHelper;

template<typename Class, typename FieldType>
struct MemberTypeHelper<FieldType Class::*>
{
    using type = FieldType;
};

template<auto Member>
using MemberType = typename MemberTypeHelper<decltype(Member)>::type;

struct TypeStorageBase
{
    virtual ~TypeStorageBase() = default;
    virtual std::size_t size() const = 0;
};

template<typename T>
class TypeStorage : public TypeStorageBase
{
    struct ColumnBase
    {
        virtual ~ColumnBase() = default;
        virtual std::size_t size() const = 0;
        virtual void pushBack() = 0;
        virtual void destroy(std::size_t index) = 0;
        virtual void reserve(std::size_t capacity) = 0;
        virtual void clear() = 0;
    };

    template<typename FieldType>
    struct Column : ColumnBase
    {
        std::vector<FieldType> data;

        std::size_t size() const override
        {
            return data.size();
        }

        void pushBack() override
        {
            data.emplace_back();
        }

        void destroy(std::size_t index) override
        {
            if (index + 1 < data.size())
            {
                data[index] = std::move(data.back());
            }
            data.pop_back();
        }

        void reserve(std::size_t capacity) override
        {
            data.reserve(capacity);
        }

        void clear() override
        {
            data.clear();
        }

        FieldType& at(std::size_t index)
        {
            return data[index];
        }

        const FieldType& at(std::size_t index) const
        {
            return data[index];
        }

        FieldType* dataPtr()
        {
            return data.data();
        }
    };

    std::unordered_map<std::size_t, std::unique_ptr<ColumnBase>> columns_;
    std::size_t size_ = 0;

public:
    std::size_t size() const override
    {
        return size_;
    }

    template<auto Member>
    void addField()
    {
        using FieldType = MemberType<Member>;
        const auto key = memberKey<Member>();
        columns_.emplace(key, std::make_unique<Column<FieldType>>());
    }

    template<auto Member>
    MemberType<Member>& get(std::size_t slot)
    {
        const auto key = memberKey<Member>();
        auto it = columns_.find(key);
        return static_cast<Column<MemberType<Member>>&>(*it->second).at(slot);
    }

    template<auto Member>
    const MemberType<Member>& get(std::size_t slot) const
    {
        const auto key = memberKey<Member>();
        auto it = columns_.find(key);
        return static_cast<const Column<MemberType<Member>>&>(*it->second).at(slot);
    }

    template<auto Member>
    std::span<MemberType<Member>> column()
    {
        const auto key = memberKey<Member>();
        auto it = columns_.find(key);
        if (it == columns_.end())
        {
            return std::span<MemberType<Member>>{};
        }
        auto* col = static_cast<Column<MemberType<Member>>*>(it->second.get());
        return std::span<MemberType<Member>>(col->dataPtr(), col->size());
    }

    void reserve(std::size_t capacity)
    {
        for (auto& pair : columns_)
        {
            pair.second->reserve(capacity);
        }
    }

    void clear()
    {
        for (auto& pair : columns_)
        {
            pair.second->clear();
        }
        size_ = 0;
    }

    std::size_t create()
    {
        for (auto& pair : columns_)
        {
            pair.second->pushBack();
        }
        return size_++;
    }

    void destroy(std::size_t slot)
    {
        for (auto& pair : columns_)
        {
            pair.second->destroy(slot);
        }
        --size_;
    }
};

} // namespace emper::storage