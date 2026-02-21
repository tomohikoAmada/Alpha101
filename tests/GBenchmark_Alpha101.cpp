#include <benchmark/benchmark.h>

#include <random>

#include "Alpha101.h"

// ========== Alpha001 截面版 Benchmarks ==========
// 参数：S=股票数，T=时间长度

static vector<vector<float>> gen_close_mat(size_t S, size_t T, int seed = 42) {
    std::mt19937 gen(seed);
    std::uniform_real_distribution<float> dis(10.0f, 200.0f);
    vector<vector<float>> mat(S, vector<float>(T));
    for (auto& row : mat)
        for (auto& v : row) v = dis(gen);
    return mat;
}

static vector<vector<float>> gen_returns_mat(size_t S, size_t T, float mean = 0.0f, int seed = 99) {
    std::mt19937 gen(seed);
    std::normal_distribution<float> dis(mean, 0.02f);
    vector<vector<float>> mat(S, vector<float>(T));
    for (auto& row : mat)
        for (auto& v : row) v = dis(gen);
    return mat;
}

// 固定股票数(500只)，改变时间长度
static void BM_Alpha001Cross_VaryingT(benchmark::State& state) {
    size_t T = static_cast<size_t>(state.range(0));
    size_t S = 500;
    auto close   = gen_close_mat(S, T);
    auto returns = gen_returns_mat(S, T);

    for (auto _ : state) {
        auto result = alpha001(close, returns);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * S * T);
}
BENCHMARK(BM_Alpha001Cross_VaryingT)->Arg(100)->Arg(250)->Arg(500)->Arg(1000)->Arg(2000);

// 固定时间长度(250天)，改变股票数
static void BM_Alpha001Cross_VaryingS(benchmark::State& state) {
    size_t S = static_cast<size_t>(state.range(0));
    size_t T = 250;
    auto close   = gen_close_mat(S, T);
    auto returns = gen_returns_mat(S, T);

    for (auto _ : state) {
        auto result = alpha001(close, returns);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * S * T);
}
BENCHMARK(BM_Alpha001Cross_VaryingS)->Arg(50)->Arg(100)->Arg(300)->Arg(500)->Arg(1000);

BENCHMARK_MAIN();
