# Emper Engine

The core runtime and data-oriented foundation of the Emper simulation ecosystem.

Emper Engine provides the infrastructure required to build simulations while keeping domain-specific algorithms and applications outside of the core.

The engine is designed to remain small, reusable, and independent of any particular simulation domain.

---

## What is Emper Engine?

Emper Engine provides the fundamental building blocks for simulation software:

* Simulation lifecycle
* World and object management
* Data-oriented storage
* Systems and execution
* Backend interfaces
* Reusable runtime infrastructure

The engine does **not** implement domain-specific simulations.

Algorithms such as flocking, physics, cellular automata, chemistry, or biology belong in modules or applications built on top of the engine.

---

## Architecture

Emper follows a simple separation of responsibilities:

```text
Application / Simulation
        │
        ▼
     Modules
        │
        ▼
  Emper Engine
        │
        ▼
   Backends
```

The engine provides infrastructure.

Modules provide reusable algorithms.

Applications combine them to build specific simulations.

Backends provide platform- or implementation-specific functionality behind engine interfaces.

This separation allows the core to evolve independently from individual simulation domains.

---

## Data-Oriented Storage

Simulation data is stored independently from the algorithms operating on it.

The storage layer is designed around data-oriented access patterns such as Structure of Arrays (SoA), allowing simulation state to be organized for efficient iteration and processing.

For example, conceptual simulation data:

```cpp
struct Particle
{
    Vec2 position;
    Vec2 velocity;
};
```

can be represented internally as separate data streams:

```text
position.x[]
position.y[]
velocity.x[]
velocity.y[]
```

This allows systems to process only the data they require and provides a foundation for vectorized and parallel workloads.

The storage system is intentionally independent from simulation algorithms.

---

## Systems

Simulation behavior is implemented through systems rather than being embedded into the data itself.

A system operates on simulation state and defines what happens during a simulation step.

This keeps:

```text
Data
```

separate from:

```text
Behavior
```

and allows the same storage infrastructure to support different simulation models.

---

## Backends

Platform-specific implementations are exposed through interfaces.

The engine does not require a particular rendering or compute implementation.

This allows applications and modules to use different backends without coupling the simulation core to a specific graphics or compute API.

Backend implementations can evolve independently from the engine's simulation model.

---

## Modules

Domain-specific functionality belongs outside the core engine.

Examples include:

* Spatial partitioning
* Flocking
* Physics
* Cellular automata
* Chemistry
* Biology
* Fluid simulation
* Artificial intelligence

A module should depend on the engine rather than requiring the engine to know about the module.

This keeps the dependency direction simple:

```text
Application
    │
    ├── Module
    │     │
    │     └── Engine
    │
    └── Engine
```

The engine should remain unaware of higher-level domain algorithms.

---

## Design Principles

### Small Core

The engine should provide infrastructure rather than attempting to implement every simulation algorithm.

### Data Is Not Policy

The engine describes simulation state.

Systems and modules define how that state changes.

### Algorithms Drive Abstractions

New abstractions should emerge from real requirements rather than speculative architecture.

### Modular by Default

Functionality that does not belong to the fundamental runtime should remain independently reusable.

### Performance With Measurement

Performance matters for large simulations, but optimization should be guided by measurement rather than assumptions.

### Backend Independence

Simulation code should not depend directly on a particular rendering or compute implementation.

---

## Building

Emper Engine uses CMake for configuration and supports standard C++ build workflows.

A typical build looks like:

```bash
cmake -S . -B build
cmake --build build
```

The exact toolchain and build configuration may vary by platform.

---

## Using the Engine

The engine is intended to be embedded into applications and higher-level simulation modules.

A typical application follows this structure:

```text
Application
    │
    ├── Create simulation world
    │
    ├── Register simulation data
    │
    ├── Attach systems
    │
    ├── Run simulation
    │
    └── Use appropriate backends
```

The engine does not prescribe how a particular simulation should be implemented.

---

## Project Status

Emper Engine is under active development.

Public APIs and internal architecture may evolve as they are validated through real simulation workloads.

The project intentionally avoids freezing abstractions before they have been exercised by multiple use cases.

For this reason, applications should expect the API to evolve during the early development of Emper.

---

## Relationship to Emper Labs

Emper Engine is the core foundation of the Emper ecosystem.

Higher-level functionality is developed independently and can be composed with the engine without requiring domain-specific logic to become part of the core.

See the Emper Labs organization for the current ecosystem and related projects.

---

## License

Apache License 2.0
