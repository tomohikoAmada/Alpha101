cmake_minimum_required(VERSION 3.14)
project(Alpha101)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

# Alpha101-Header-Verzeichnis
include_directories(include)

# Hilfsprogramme (Wurzelverzeichnis)
add_executable(eztest eztest.cpp)
add_executable(useeigen useeigen.cpp)

target_link_libraries(useeigen Eigen3::Eigen)

# GTest (tests/)
add_executable(GTest_Alpha101Utils tests/GTest_Alpha101Utils.cpp)
target_link_libraries(GTest_Alpha101Utils GTest::gtest_main)

add_executable(GTest_Alpha101 tests/GTest_Alpha101.cpp)
target_link_libraries(GTest_Alpha101 GTest::gtest_main)

# CTest-Integration: Testfälle für VSCode und ctest sichtbar machen
enable_testing()
include(GoogleTest)
gtest_discover_tests(GTest_Alpha101Utils)
gtest_discover_tests(GTest_Alpha101)

# GBenchmark (tests/)
add_executable(GBenchmark_Alpha101Utils tests/GBenchmark_Alpha101Utils.cpp)
target_link_libraries(GBenchmark_Alpha101Utils benchmark::benchmark)

add_executable(GBenchmark_Alpha101 tests/GBenchmark_Alpha101.cpp)
target_link_libraries(GBenchmark_Alpha101 benchmark::benchmark)

# Benchmark-Ergebnisse persistieren (JSON nach results/benchmark/)
set(BENCH_RESULTS_DIR ${CMAKE_SOURCE_DIR}/tests/benchmark)

add_custom_target(bench_alpha101utils
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BENCH_RESULTS_DIR}
    COMMAND $<TARGET_FILE:GBenchmark_Alpha101Utils>
            --benchmark_out=${BENCH_RESULTS_DIR}/alpha101utils.json
            --benchmark_out_format=json
    DEPENDS GBenchmark_Alpha101Utils
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "GBenchmark_Alpha101Utils ausfuehren und Ergebnisse speichern..."
)

add_custom_target(bench_alpha101
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BENCH_RESULTS_DIR}
    COMMAND $<TARGET_FILE:GBenchmark_Alpha101>
            --benchmark_out=${BENCH_RESULTS_DIR}/alpha101.json
            --benchmark_out_format=json
    DEPENDS GBenchmark_Alpha101
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "GBenchmark_Alpha101 ausfuehren und Ergebnisse speichern..."
)
