#ifndef EMPER_SIMULATION_WORLD_WORLD_H
#define EMPER_SIMULATION_WORLD_WORLD_H

#pragma once

#include <cstddef>
#include <functional>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>
#include <iostream>


#include <emper/Types.h>
#include <emper/interfaces/backend/IRenderer.h>
#include <emper/simulation/storage/Field.h>
#include <emper/simulation/storage/Handle.h>
#include <emper/simulation/storage/Storage.h>
#include <emper/simulation/storage/StorageView.h>
#include <emper/simulation/storage/View.h>
#include <emper/simulation/world/WorldStatistics.h>
#include <emper/interfaces/module/ISystem.h>

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
                this->commitStorage<T>(std::move(typedStorage));
            },
            [this](std::function<void(storage::StorageView<T>&,
                                      float,
                                      interfaces::backend::IRenderer*)> fn)
            {
                this->setOnTick<T>(std::move(fn));
            }
        );
    }

    template<typename T>
    void reserve(std::size_t count)
    {
        auto* storage = getStorage<T>();
        if (storage)
        {
            storage->reserve(count);
        }
    }

    template<typename T>
    storage::Handle<T> create()
    {
        auto* storage = getStorage<T>();

        //std::cout << "storage = " << storage << '\n';

        if (!storage)
        {
            return {};
        }

        const auto slot = storage->create();
        /*
            std::cout << "storage after create = " << storage
                << ", slot = " << slot << '\n';

        */
        
        const auto handle = storage::Handle<T>(storage, slot);

        ++object_count_;
        ++statistics_.objectCount;

        return handle;
    }

    template<typename T>
    void destroy(storage::Handle<T> handle)
    {
        auto* storage = getStorage<T>();
        if (!storage || !handle.valid())
        {
            return;
        }
        storage->destroy(handle.slot());
        --object_count_;
        --statistics_.objectCount;
    }

    template<typename T>
    void clear()
    {
        auto* storage = getStorage<T>();
        if (!storage)
        {
            return;
        }

        std::size_t count = storage->size();

        storage->clear();

        object_count_ -= count;

        statistics_.objectCount = object_count_;
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

    void setRenderer(interfaces::backend::IRenderer* renderer);
    void addSystem(interfaces::module::ISystem* system);

    void tick(f32 dt);
    void render(interfaces::backend::IRenderer& renderer);

    std::size_t objectCount() const;
    const WorldStatistics& statistics() const;

private:
    template<typename T>
    friend class storage::FieldBuilder;

    template<typename T>
    void commitStorage(std::unique_ptr<storage::TypeStorage<T>> typedStorage)
    {
        const auto key = std::type_index(typeid(T));
        storages_.emplace(key, std::move(typedStorage));
    }

    template<typename T>
    storage::TypeStorage<T>* getStorage()
    {
        const auto key = std::type_index(typeid(T));
        const auto it = storages_.find(key);
        if (it == storages_.end())
        {
            return nullptr;
        }
        return static_cast<storage::TypeStorage<T>*>(it->second.get());
    }

    struct ITypeTick
    {
        virtual ~ITypeTick() = default;
        virtual void invoke(storage::TypeStorageBase* storage,
                            f32 dt,
                            interfaces::backend::IRenderer* renderer) = 0;
    };

    template<typename T>
    struct TypeTick final : ITypeTick
    {
        std::function<void(storage::StorageView<T>&,
                           f32,
                           interfaces::backend::IRenderer*)> fn;

        void invoke(storage::TypeStorageBase* storage,
                    f32 dt,
                    interfaces::backend::IRenderer* renderer) override
        {
            auto* typed = static_cast<storage::TypeStorage<T>*>(storage);
            storage::StorageView<T> view(typed);
            if (fn)
            {
                fn(view, dt, renderer);
            }
        }
    };

    template<typename T>
    void setOnTick(std::function<void(storage::StorageView<T>&,
                                    f32,
                                    interfaces::backend::IRenderer*)> fn)
    {
        auto tick = std::make_unique<TypeTick<T>>();
        tick->fn = std::move(fn);
        onTicks_[std::type_index(typeid(T))] = std::move(tick);
    }

    std::unordered_map<std::type_index, std::unique_ptr<storage::TypeStorageBase>> storages_;
    std::unordered_map<std::type_index, std::unique_ptr<ITypeTick>> onTicks_;
    std::vector<emper::interfaces::module::ISystem*> systems_;
    interfaces::backend::IRenderer* renderer_ = nullptr;
    std::size_t object_count_ = 0;
    WorldStatistics statistics_;
};

} // namespace emper

#endif // EMPER_SIMULATION_WORLD_WORLD_H
