cmake_minimum_required(VERSION 3.21)
project(rl_da_zero)

set(CMAKE_CXX_STANDARD 20)

#include(FetchContent)
#FetchContent_Declare(_project_options URL https://github.com/cpp-best-practices/project_options/archive/refs/tags/v0.12.3.zip)
#FetchContent_MakeAvailable(_project_options)
#include(${_project_options_SOURCE_DIR}/Index.cmake)
set(_CRT_SECURE_NO_WARNINGS)
# raylib
find_package(raylib QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git
            GIT_TAG 0851960397f02a477d80eda2239f90fae14dec64
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
        set(BUILD_TESTING  OFF CACHE BOOL "" FORCE)
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

# raylib-cpp
find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib_cpp
            URL https://github.com/RobLoach/raylib-cpp/archive/master.tar.gz
    )
    FetchContent_GetProperties(raylib_cpp)
    if (NOT raylib_cpp_POPULATED) # Have we downloaded raylib-cpp yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib_cpp)
        set(BUILD_RAYLIB_CPP_EXAMPLES OFF CACHE BOOL "" FORCE)
        set(BUILD_TESTING             OFF CACHE BOOL "" FORCE)
        add_subdirectory(${raylib_cpp_SOURCE_DIR} ${raylib_cpp_BINARY_DIR})
    endif()
endif()





#foreach(CONFIG_FILE ${CONFIG_FILES})
#    message(STATUS "Found config file: ${CONFIG_FILE}")
#    file(COPY ${CONFIG_FILE} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
#endforeach()

#file(GLOB TERRAIN_GENERATOR_ASSETS
#  "${CMAKE_CURRENT_SOURCE_DIR}/assets/*.ttf"
#)
#
#project_options(
#        #ENABLE_CACHE
#        # WARNINGS_AS_ERRORS
#        ENABLE_CPPCHECK
#        #ENABLE_CLANG_TIDY
#        # ENABLE_CONAN
#        #ENABLE_COVERAGE
#        # ENABLE_IPO
#        # ENABLE_INCLUDE_WHAT_YOU_USE
#        # ENABLE_PCH
#        # PCH_HEADERS
#        # ENABLE_DOXYGEN
#        # ENABLE_USER_LINKER
#        # ENABLE_BUILD_WITH_TIME_TRACE
#        # ENABLE_UNITY
#        # ENABLE_SANITIZER_ADDRESS
#        # ENABLE_SANITIZER_LEAK
#        # ENABLE_SANITIZER_UNDEFINED_BEHAVIOR
#        # ENABLE_SANITIZER_THREAD
#        # ENABLE_SANITIZER_MEMORY
#        # CONAN_OPTIONS
#)
#target_compile_features(project_options INTERFACE cxx_std_20)



add_subdirectory(vendor/fmt)
add_subdirectory(vendor/json)


#find_package(nlohmann_json 3.10.5 REQUIRED)

add_executable(rl_da_zero main.cpp)

add_subdirectory(src)


target_link_libraries(rl_da_zero PRIVATE fmt::fmt-header-only)
#set(raylib_VERBOSE 1)
target_link_libraries(rl_da_zero PUBLIC raylib raylib_cpp)
target_link_libraries(rl_da_zero PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(rl_da_zero PRIVATE spdlog::spdlog_header_only)
find_package(spdlog CONFIG REQUIRED)
target_link_libraries(rl_da_zero PRIVATE spdlog::spdlog spdlog::spdlog_header_only)
#target_link_libraries(rl_da_zero PRIVATE  project_warnings) # connect project_options to myprogram


#file(GLOB_RECURSE CONFIG_FILES  config/* )
#file(GLOB_RECURSE CONFIG_ASSETS  ${CMAKE_CURRENT_SOURCE_DIR}/config/*.png )
#
#foreach(CONFIG_FILE ${CONFIG_FILES})
#    message("-- Add config file: ${CONFIG_FILE}")
#    add_custom_command(TARGET rl_da_zero POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy_if_different
#            ${CONFIG_FILE}
#            $<TARGET_FILE_DIR:rl_da_zero>/config/
#            )
#endforeach()
#
#foreach(CONFIG_ASSET ${CONFIG_ASSETS})
#    message("-- Add asset file: ${CONFIG_ASSET}")
#    add_custom_command(TARGET rl_da_zero POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy_if_different
#            ${CONFIG_ASSET}
#            $<TARGET_FILE_DIR:rl_da_zero>/config/prefabs/
#            )
#endforeach()

