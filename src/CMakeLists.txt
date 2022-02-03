cmake_minimum_required(VERSION 3.21)
project(rl_da_zero)
add_subdirectory(entity)
add_subdirectory(systems)
add_subdirectory(states)
add_subdirectory(commands)
add_subdirectory(utils)
add_subdirectory(lib)
add_subdirectory(world)
add_subdirectory(items)
add_subdirectory(ui)
add_subdirectory(scenes)
add_subdirectory(events)


target_include_directories(rl_da_zero PRIVATE .)



FILE(GLOB SRCS *.cpp)

target_sources( rl_da_zero PRIVATE ${SRCS})

