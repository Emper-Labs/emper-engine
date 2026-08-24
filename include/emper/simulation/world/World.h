#pragma once

#include <cstddef>
#include <memory>
#include <typeindex>
#include <unordered_map>

#include <emper/Types.h>
#include <emper/simulation/storage/Field.h>
#include <emper/simulation/storage/Handle.h>
#include <emper/simulation/storage/Storage.h>
#include <emper/simulation/storage/StorageView.h>
#include <emper/simulation/storage/View.h>
#include <emper/simulation/world/WorldStatistics.h>

namespace emper::simulation::world
{

class World
{
public:
    template<typename T>
    storage::FieldBuilder<T> registerType()
    {
        return storage::FieldBuilder<T>(
            [this](std::unique_ptr<storage::TypeStorage<T>> typedStorage)
            {
                commitStorage<T>(std::move(typedStorage));
            }
        );
    }

    template<typename T>
    void reserve(std::size_t count)
    {
        auto* storage = getStorage<T>();

        if (storage)
            storage->reserve(count);
    }

    template<typename T>
    storage::Handle<T> create()
    {
        auto* storage = getStorage<T>();

        if (!storage)
            return {};

        const auto slot = storage->create();

        ++statistics_.objectCount;

        return storage::Handle<T>(storage, slot);
    }

    template<typename T>
    void destroy(storage::Handle<T> handle)
    {
        auto* storage = getStorage<T>();

        if (!storage || !handle.valid())
            return;

        storage->destroy(handle.slot());

        --statistics_.objectCount;
    }

    template<typename T>
    void clear()
    {
        auto* storage = getStorage<T>();

        if (!storage)
            return;

        const auto count = storage->size();

        storage->clear();

        statistics_.objectCount -= count;
    }

    template<typename T>
    storage::View<T> view()
    {
        return storage::View<T>(getStorage<T>());
    }

    template<typename T>
    storage::StorageView<T> storage()
    {
        return storage::StorageView<T>(getStorage<T>());
    }

    std::size_t objectCount() const;

    const WorldStatistics& statistics() const;

private:
    template<typename T>
    friend class storage::FieldBuilder;

    template<typename T>
    void commitStorage(
        std::unique_ptr<storage::TypeStorage<T>> typedStorage)
    {
        const auto key = std::type_index(typeid(T));

        storages_.emplace(
            key,
            std::move(typedStorage)
        );
    }

    template<typename T>
    storage::TypeStorage<T>* getStorage()
    {
        const auto key = std::type_index(typeid(T));

        const auto it = storages_.find(key);

        if (it == storages_.end())
            return nullptr;

        return static_cast<storage::TypeStorage<T>*>(
            it->second.get()
        );
    }

private:
    std::unordered_map<
        std::type_index,
        std::unique_ptr<storage::TypeStorageBase>
    > storages_;

    WorldStatistics statistics_;
};

}