cmake_minimum_required (VERSION 3.16)

project ("ArkMat")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable (ArkMat "benchmark.cpp")

target_include_directories(ArkMat PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../src)



