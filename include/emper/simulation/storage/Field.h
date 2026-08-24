#pragma once

#include <cstddef>
#include <functional>
#include <memory>
#include <type_traits>
#include <utility>

#include <emper/simulation/storage/Storage.h>
#include <emper/simulation/storage/StorageView.h>

namespace emper::interfaces::backend { class IRenderer; }

namespace emper::storage
{

template<typename T>
class FieldBuilder
{
public:
    using CommitFn =
        std::function<void(std::unique_ptr<TypeStorage<T>>)>;

    explicit FieldBuilder(CommitFn fn)
        : commitFn_(std::move(fn))
        , storage_(std::make_unique<TypeStorage<T>>())
    {
    }

    FieldBuilder(const FieldBuilder&) = delete;
    FieldBuilder& operator=(const FieldBuilder&) = delete;

    FieldBuilder(FieldBuilder&& other) noexcept
        : commitFn_(std::move(other.commitFn_))
        , storage_(std::move(other.storage_))
        , committed_(other.committed_)
    {
        other.committed_ = true;
    }

    FieldBuilder& operator=(FieldBuilder&& other) noexcept
    {
        if (this != &other)
        {
            commitFn_ = std::move(other.commitFn_);
            storage_ = std::move(other.storage_);
            committed_ = other.committed_;

            other.committed_ = true;
        }

        return *this;
    }

    ~FieldBuilder()
    {
        commit();
    }

    template<auto Member>
    FieldBuilder& field()
    {
        storage_->template addField<Member>();
        return *this;
    }

private:
    void commit()
    {
        if (!committed_ && commitFn_ && storage_)
        {
            commitFn_(std::move(storage_));
            committed_ = true;
        }
    }

    CommitFn commitFn_;
    std::unique_ptr<TypeStorage<T>> storage_;
    bool committed_ = false;
};
} // namespace emper::storage