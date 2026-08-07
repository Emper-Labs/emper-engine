add_library(emper-engine
    src/emper/simulation/Simulation.cpp
)

target_include_directories(emper-engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)