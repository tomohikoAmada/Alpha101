#include <benchmark/benchmark.h>

#include <random>

#include "Alpha101.h"

// Hilfsfunktionen zur Datenerzeugung

static vector<float> gen_close(size_t n, int seed = 42) {
    vector<float> data(n);
    std::mt19937 gen(seed);
    std::uniform_real_distribution<float> dis(10.0f, 200.0f);
    for (auto& v : data) v = dis(gen);
    return data;
}

static vector<float> gen_returns(size_t n, float mean = 0.0f, int seed = 99) {
    vector<float> data(n);
    std::mt19937 gen(seed);
    std::normal_distribution<float> dis(mean, 0.02f);
    for (auto& v : data) v = dis(gen);
    return data;
}

// ========== Alpha001 Benchmarks ==========

static void BM_Alpha001_Small(benchmark::State& state) {
    auto close   = gen_close(100);
    auto returns = gen_returns(100);

    for (auto _ : state) {
        auto result = alpha001(close, returns);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * close.size());
}
BENCHMARK(BM_Alpha001_Small);

static void BM_Alpha001_Medium(benchmark::State& state) {
    auto close   = gen_close(1000);
    auto returns = gen_returns(1000);

    for (auto _ : state) {
        auto result = alpha001(close, returns);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * close.size());
}
BENCHMARK(BM_Alpha001_Medium);

static void BM_Alpha001_Large(benchmark::State& state) {
    auto close   = gen_close(10000);
    auto returns = gen_returns(10000);

    for (auto _ : state) {
        auto result = alpha001(close, returns);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * close.size());
}
BENCHMARK(BM_Alpha001_Large);

static void BM_Alpha001_AllNegativeReturns(benchmark::State& state) {
    // returns < 0: innerer Ausdruck verwendet stddev statt close
    auto close   = gen_close(1000);
    auto returns = gen_returns(1000, -0.05f);  // negativer Mittelwert

    for (auto _ : state) {
        auto result = alpha001(close, returns);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * close.size());
}
BENCHMARK(BM_Alpha001_AllNegativeReturns);

static void BM_Alpha001_AllPositiveReturns(benchmark::State& state) {
    // returns >= 0: innerer Ausdruck verwendet close
    auto close   = gen_close(1000);
    auto returns = gen_returns(1000, 0.05f);  // positiver Mittelwert

    for (auto _ : state) {
        auto result = alpha001(close, returns);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * close.size());
}
BENCHMARK(BM_Alpha001_AllPositiveReturns);

static void BM_Alpha001_VaryingSize(benchmark::State& state) {
    size_t n = static_cast<size_t>(state.range(0));
    auto close   = gen_close(n);
    auto returns = gen_returns(n);

    for (auto _ : state) {
        auto result = alpha001(close, returns);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * n);
}
BENCHMARK(BM_Alpha001_VaryingSize)->Arg(100)->Arg(500)->Arg(1000)->Arg(5000)->Arg(10000);

BENCHMARK_MAIN();
