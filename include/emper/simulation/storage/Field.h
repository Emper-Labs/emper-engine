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

// Fluent builder returned by World::registerType<T>().
//
// Each .field<&T::member>() call adds a SoA column to a temporary
// TypeStorage owned by this builder. When the builder is destroyed
// (normally at the end of the registration expression) the storage is
// committed to the World.
template<typename T>
class FieldBuilder
{
public:
    using CommitFn = std::function<void(std::unique_ptr<TypeStorage<T>>)>;
    using OnTickFn = std::function<void(storage::StorageView<T>&,
                                        float,
                                        interfaces::backend::IRenderer*)>;
    using RegisterOnTickFn = std::function<void(OnTickFn)>;

    explicit FieldBuilder(CommitFn fn, RegisterOnTickFn onTickFn = {})
        : commitFn_(std::move(fn))
        , onTickRegisterFn_(std::move(onTickFn))
        , storage_(std::make_unique<TypeStorage<T>>())
    {
    }

    FieldBuilder(const FieldBuilder&) = delete;
    FieldBuilder& operator=(const FieldBuilder&) = delete;

    FieldBuilder(FieldBuilder&& other) noexcept
        : commitFn_(std::move(other.commitFn_))
        , onTickRegisterFn_(std::move(other.onTickRegisterFn_))
        , onTickFn_(std::move(other.onTickFn_))
        , storage_(std::move(other.storage_))
        , committed_(other.committed_)
        , tickSet_(other.tickSet_)
    {
        other.committed_ = true;
        other.tickSet_ = true;
    }

    FieldBuilder& operator=(FieldBuilder&& other) noexcept
    {
        if (this != &other)
        {
            commitFn_ = std::move(other.commitFn_);
            onTickRegisterFn_ = std::move(other.onTickRegisterFn_);
            onTickFn_ = std::move(other.onTickFn_);
            storage_ = std::move(other.storage_);
            committed_ = other.committed_;
            tickSet_ = other.tickSet_;
            other.committed_ = true;
            other.tickSet_ = true;
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

    // Register a per-type update/render callback.
    //
    // The callback is invoked twice per frame by the World:
    //   * during the update phase: dt > 0, renderer == nullptr   -> simulation
    //   * during the render phase: dt == 0, renderer != nullptr  -> drawing
    template<typename Fn>
    FieldBuilder& onTick(Fn&& fn)
    {
        onTickFn_ = OnTickFn(std::forward<Fn>(fn));
        return *this;
    }

    void commit()
    {
        if (!committed_ && commitFn_ && storage_)
        {
            commitFn_(std::move(storage_));
            committed_ = true;
        }
        if (!tickSet_ && onTickRegisterFn_ && onTickFn_)
        {
            onTickRegisterFn_(std::move(onTickFn_));
            tickSet_ = true;
        }
    }

private:
    CommitFn commitFn_;
    RegisterOnTickFn onTickRegisterFn_;
    OnTickFn onTickFn_;
    std::unique_ptr<TypeStorage<T>> storage_;
    bool committed_ = false;
    bool tickSet_ = false;
};

} // namespace emper::storage