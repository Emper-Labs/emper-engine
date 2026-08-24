# Emper Engine

Engine provides interfaces and data storage for simulation.

Emper Engine contains the core runtime and storage primitives used to build simulation workloads. It provides a place to keep simulation state, register data fields, access stored data, and run systems that operate on that state.

The engine does not define a specific simulation domain or require a specific way to consume simulation data.

## Core Concepts

### Simulation

`Simulation` coordinates the simulation lifecycle.

It owns the `World`, manages registered systems through `SystemManager`, and can optionally use a renderer. Systems and rendering are kept outside the `World` itself.

### World

`World` owns the simulation state.

It provides APIs for:

* Registering typed storage
* Reserving storage
* Creating and destroying objects
* Clearing storage
* Accessing data through views
* Accessing typed storage
* Querying world statistics

`World` does not execute systems or manage rendering.

### Storage

Simulation data is stored through typed field storage.

A type can register individual members as fields:

```cpp
struct Particle
{
    Vec2 position;
    Vec2 velocity;
};

world.registerType<Particle>()
    .field<&Particle::position>()
    .field<&Particle::velocity>();
```

The current implementation stores registered fields as separate columns backed by contiguous `std::vector` storage.

### Systems

Simulation behavior is implemented through systems.

`SystemManager` registers systems and calls their `tick()` function during simulation updates.

```cpp
class MySystem : public ISystem
{
public:
    void tick(f32 dt) override;
};
```

Systems are non-owning objects registered with the simulation.

## Architecture

The current runtime is organized around simulation state and systems:

```text
                    Simulation
                        │
          ┌─────────────┼─────────────┐
          ▼             ▼             ▼
        World     SystemManager    Renderer*
          │             │             │
          │             ▼             │
          │          Systems          │
          │                           │
          └────── Simulation Data ────┘
```

The renderer is optional. Simulation data does not have to be rendered.

## Data-Oriented Storage

Emper Engine uses a field-based, column-oriented storage model.

Conceptually:

```text
Particle

position[]
velocity[]
```

Each registered field is stored in its own column. The current implementation uses contiguous vectors for those columns and exposes column data through `std::span`.

The storage layer also provides:

* `FieldBuilder`
* `TypeStorage`
* `Handle`
* `View`
* `StorageView`

For example:

```cpp
auto particles = world.storage<Particle>();

for (auto& position : particles.column<&Particle::position>())
{
    // process position
}
```

The storage design is intended to keep simulation data separate from the systems that process it.

## Systems

`ISystem` is the basic interface for simulation behavior.

```cpp
class ISystem
{
public:
    virtual ~ISystem() = default;

    virtual void tick(f32 dt) = 0;
};
```

Systems are managed by `SystemManager`:

```cpp
simulation.addSystem(system);
simulation.removeSystem(system);
```

`SystemManager` is responsible for registering systems and executing them.

A system can also provide an optional rendering capability through `IRenderable`. Systems that do not provide that capability do not need to implement rendering.

## Consumers

Simulation data is not tied to a single output path.

The same simulation state can be:

* Processed by systems
* Rendered
* Analyzed
* Exported
* Serialized
* Used by other computations
* Passed to another application layer

Rendering is therefore one possible consumer of simulation data, not a requirement of the simulation itself.

## Building

Emper Engine uses CMake.

```bash
cmake -S . -B build
cmake --build build
```

The current library target is:

```text
emper-engine
```

The target is built from the simulation, world, system manager, and interface implementations in this repository.

## Current Status

Emper Engine is in early development.

Currently implemented:

* Simulation lifecycle
* World and object management
* Typed field registration
* Column-based storage
* Handles and views
* System management
* Optional renderer integration

The current API is still evolving.

The engine does not currently provide:

* A general-purpose ECS
* A general-purpose task scheduler
* A complete physics framework
* A complete scientific simulation framework

These are outside the current scope of the core engine.

## Design Direction

### Data Is the Simulation State

The engine provides infrastructure for representing and accessing simulation state without defining a particular scientific model.

### Data Is Separate From Behavior

Storage contains simulation data while systems define operations performed on that data.

### Rendering Is Optional

A simulation does not require a renderer.

Rendering is only one possible way to consume simulation state.

### Domain Logic Stays Outside the Core

Domain-specific algorithms belong in higher-level modules and applications rather than in the engine core.

### Abstractions Follow Real Requirements

The engine favors small abstractions that are validated through real simulation workloads.

## Contributing

Contributions are welcome.

Before contributing, read the project's contribution guidelines.

When changing the engine, prefer changes that:

* Solve a concrete problem
* Keep the core focused
* Avoid unnecessary dependencies
* Preserve separation between data and processing
* Include tests or benchmarks where appropriate

## License

Apache License 2.0