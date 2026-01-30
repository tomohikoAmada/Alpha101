cmake_minimum_required(VERSION 3.14)
project(Alpha101)

set(CMAKE_CXX_STANDARD 20)

find_package(Eigen3 REQUIRED)

# 自动下载并集成 GoogleTest 和 Google Benchmark
include(FetchContent)

# GoogleTest
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Google Benchmark
FetchContent_Declare(
        googlebenchmark
        URL https://github.com/google/benchmark/archive/refs/heads/main.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googlebenchmark)

# 每个 .cpp 文件编译成独立的可执行程序
add_executable(eztest eztest.cpp)
add_executable(useeigen useeigen.cpp)

target_link_libraries(useeigen Eigen3::Eigen)

# 测试可执行文件
add_executable(run_tests test_alpha101.cpp)
target_link_libraries(run_tests GTest::gtest_main)

# 性能测试可执行文件
add_executable(run_benchmarks benchmark_alpha101.cpp)
target_link_libraries(run_benchmarks benchmark::benchmark)
