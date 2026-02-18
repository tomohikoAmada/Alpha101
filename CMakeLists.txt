cmake_minimum_required(VERSION 3.14)
project(Alpha101)

set(CMAKE_CXX_STANDARD 20)

# 告诉 MSVC 用 UTF-8 编码读取源文件（防止中文字符串编译出错）
if(MSVC)
    add_compile_options(/utf-8)
endif()

include(FetchContent)

# Eigen3：优先使用系统已安装版本，否则自动下载
find_package(Eigen3 QUIET)
if(NOT Eigen3_FOUND)
    FetchContent_Declare(
            eigen3
            URL https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.zip
            DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    set(EIGEN_BUILD_TESTING OFF CACHE BOOL "" FORCE)
    set(EIGEN_BUILD_DOC OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(eigen3)
endif()

# GoogleTest：优先使用系统已安装版本，否则自动下载
find_package(GTest QUIET)
if(NOT GTest_FOUND)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/refs/heads/main.zip
            DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

# Google Benchmark：优先使用系统已安装版本，否则自动下载
find_package(benchmark QUIET)
if(NOT benchmark_FOUND)
    FetchContent_Declare(
            googlebenchmark
            URL https://github.com/google/benchmark/archive/refs/heads/main.zip
            DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googlebenchmark)
endif()

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
