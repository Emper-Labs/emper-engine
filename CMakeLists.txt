add_library(emper-engine
    src/emper/simulation/Simulation.cpp
    src/emper/simulation/world/World.cpp
    src/emper/interfaces/backend/IRenderer.cpp
    src/emper/interfaces/module/ISystem.cpp
    src/emper/simulation/system/SystemManager.cpp
)

target_include_directories(emper-engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
