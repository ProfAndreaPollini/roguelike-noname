cmake_minimum_required(VERSION 3.21)
project(rl_da_zero)
target_include_directories(rl_da_zero PRIVATE .)

FILE(GLOB SRCS *.cpp)

target_sources( rl_da_zero PRIVATE ${SRCS})