#include <benchmark/benchmark.h>
#include "alpha101.h"
#include <random>

// 生成随机数据的辅助函数
vector<float> generate_random_data(size_t size, int seed = 42) {
    vector<float> data;
    data.reserve(size);

    std::mt19937 gen(seed);
    std::uniform_real_distribution<float> dis(1.0f, 100.0f);

    for (size_t i = 0; i < size; i++) {
        data.push_back(dis(gen));
    }

    return data;
}

// ========== Rolling TS Sum Benchmarks ==========

static void BM_RollingTsSum_Small(benchmark::State& state) {
    vector<float> data = generate_random_data(100);
    int window = 10;

    for (auto _ : state) {
        auto result = rolling_ts_sum(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_RollingTsSum_Small);

static void BM_RollingTsSum_Medium(benchmark::State& state) {
    vector<float> data = generate_random_data(1000);
    int window = 20;

    for (auto _ : state) {
        auto result = rolling_ts_sum(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_RollingTsSum_Medium);

static void BM_RollingTsSum_Large(benchmark::State& state) {
    vector<float> data = generate_random_data(10000);
    int window = 50;

    for (auto _ : state) {
        auto result = rolling_ts_sum(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_RollingTsSum_Large);

// ========== Product (滚动乘积) Benchmarks ==========

static void BM_Product_Small(benchmark::State& state) {
    vector<float> data = generate_random_data(100);
    int window = 10;

    for (auto _ : state) {
        auto result = product(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Product_Small);

static void BM_Product_Medium(benchmark::State& state) {
    vector<float> data = generate_random_data(1000);
    int window = 20;

    for (auto _ : state) {
        auto result = product(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Product_Medium);

static void BM_Product_Large(benchmark::State& state) {
    vector<float> data = generate_random_data(10000);
    int window = 50;

    for (auto _ : state) {
        auto result = product(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Product_Large);

static void BM_Product_VaryingWindow(benchmark::State& state) {
    int window = state.range(0);
    vector<float> data = generate_random_data(1000);

    for (auto _ : state) {
        auto result = product(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Product_VaryingWindow)->Arg(5)->Arg(10)->Arg(20)->Arg(50)->Arg(100);

// ========== TS Min (滚动最小值) Benchmarks ==========

static void BM_TsMin_Small(benchmark::State& state) {
    vector<float> data = generate_random_data(100);
    int window = 10;

    for (auto _ : state) {
        auto result = ts_min(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_TsMin_Small);

static void BM_TsMin_Medium(benchmark::State& state) {
    vector<float> data = generate_random_data(1000);
    int window = 20;

    for (auto _ : state) {
        auto result = ts_min(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_TsMin_Medium);

static void BM_TsMin_Large(benchmark::State& state) {
    vector<float> data = generate_random_data(10000);
    int window = 50;

    for (auto _ : state) {
        auto result = ts_min(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_TsMin_Large);

static void BM_TsMin_VaryingWindow(benchmark::State& state) {
    int window = state.range(0);
    vector<float> data = generate_random_data(1000);

    for (auto _ : state) {
        auto result = ts_min(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_TsMin_VaryingWindow)->Arg(5)->Arg(10)->Arg(20)->Arg(50)->Arg(100);

// ========== TS Max (滚动最大值) Benchmarks ==========

static void BM_TsMax_Small(benchmark::State& state) {
    vector<float> data = generate_random_data(100);
    int window = 10;

    for (auto _ : state) {
        auto result = ts_max(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_TsMax_Small);

static void BM_TsMax_Medium(benchmark::State& state) {
    vector<float> data = generate_random_data(1000);
    int window = 20;

    for (auto _ : state) {
        auto result = ts_max(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_TsMax_Medium);

static void BM_TsMax_Large(benchmark::State& state) {
    vector<float> data = generate_random_data(10000);
    int window = 50;

    for (auto _ : state) {
        auto result = ts_max(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_TsMax_Large);

static void BM_TsMax_VaryingWindow(benchmark::State& state) {
    int window = state.range(0);
    vector<float> data = generate_random_data(1000);

    for (auto _ : state) {
        auto result = ts_max(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_TsMax_VaryingWindow)->Arg(5)->Arg(10)->Arg(20)->Arg(50)->Arg(100);

// ========== Rolling SMA Benchmarks ==========

static void BM_RollingSma_Small(benchmark::State& state) {
    vector<float> data = generate_random_data(100);
    int window = 10;

    for (auto _ : state) {
        auto result = rolling_sma(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_RollingSma_Small);

static void BM_RollingSma_Large(benchmark::State& state) {
    vector<float> data = generate_random_data(10000);
    int window = 50;

    for (auto _ : state) {
        auto result = rolling_sma(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_RollingSma_Large);

// ========== Rolling Stddev Benchmarks ==========

static void BM_RollingStddev_Small(benchmark::State& state) {
    vector<float> data = generate_random_data(100);
    int window = 10;

    for (auto _ : state) {
        auto result = rolling_stddev(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_RollingStddev_Small);

static void BM_RollingStddev_Large(benchmark::State& state) {
    vector<float> data = generate_random_data(10000);
    int window = 50;

    for (auto _ : state) {
        auto result = rolling_stddev(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_RollingStddev_Large);

// ========== Rolling Correlation Benchmarks ==========

static void BM_RollingCorrelation_Small(benchmark::State& state) {
    vector<float> x = generate_random_data(100, 42);
    vector<float> y = generate_random_data(100, 43);
    int window = 10;

    for (auto _ : state) {
        auto result = rolling_correlation(x, y, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * x.size());
}
BENCHMARK(BM_RollingCorrelation_Small);

static void BM_RollingCorrelation_Medium(benchmark::State& state) {
    vector<float> x = generate_random_data(1000, 42);
    vector<float> y = generate_random_data(1000, 43);
    int window = 20;

    for (auto _ : state) {
        auto result = rolling_correlation(x, y, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * x.size());
}
BENCHMARK(BM_RollingCorrelation_Medium);

static void BM_RollingCorrelation_Large(benchmark::State& state) {
    vector<float> x = generate_random_data(10000, 42);
    vector<float> y = generate_random_data(10000, 43);
    int window = 50;

    for (auto _ : state) {
        auto result = rolling_correlation(x, y, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * x.size());
}
BENCHMARK(BM_RollingCorrelation_Large);

// ========== Rolling Covariance Benchmarks ==========

static void BM_RollingCovariance_Small(benchmark::State& state) {
    vector<float> x = generate_random_data(100, 42);
    vector<float> y = generate_random_data(100, 43);
    int window = 10;

    for (auto _ : state) {
        auto result = rolling_covariance(x, y, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * x.size());
}
BENCHMARK(BM_RollingCovariance_Small);

static void BM_RollingCovariance_Large(benchmark::State& state) {
    vector<float> x = generate_random_data(10000, 42);
    vector<float> y = generate_random_data(10000, 43);
    int window = 50;

    for (auto _ : state) {
        auto result = rolling_covariance(x, y, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * x.size());
}
BENCHMARK(BM_RollingCovariance_Large);

// ========== 不同窗口大小的性能对比 ==========

static void BM_RollingSma_VaryingWindow(benchmark::State& state) {
    int window = state.range(0);
    vector<float> data = generate_random_data(1000);

    for (auto _ : state) {
        auto result = rolling_sma(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_RollingSma_VaryingWindow)->Arg(5)->Arg(10)->Arg(20)->Arg(50)->Arg(100);

// ========== 不同数据大小的性能对比 ==========

static void BM_RollingCorrelation_VaryingDataSize(benchmark::State& state) {
    size_t size = state.range(0);
    vector<float> x = generate_random_data(size, 42);
    vector<float> y = generate_random_data(size, 43);
    int window = 20;

    for (auto _ : state) {
        auto result = rolling_correlation(x, y, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * size);
}
BENCHMARK(BM_RollingCorrelation_VaryingDataSize)
    ->Arg(100)
    ->Arg(500)
    ->Arg(1000)
    ->Arg(5000)
    ->Arg(10000);

// ========== TS Rank 性能对比 ==========

static void BM_TsRank_Original_Small(benchmark::State& state) {
    vector<float> data = generate_random_data(100, 42);
    int window = 10;

    for (auto _ : state) {
        auto result = ts_rank(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_TsRank_Original_Small);

static void BM_TsRank_Optimized_Small(benchmark::State& state) {
    vector<float> data = generate_random_data(100, 42);
    int window = 10;

    for (auto _ : state) {
        auto result = ts_rank_optimized(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_TsRank_Optimized_Small);

static void BM_TsRank_Original_Medium(benchmark::State& state) {
    vector<float> data = generate_random_data(1000, 42);
    int window = 20;

    for (auto _ : state) {
        auto result = ts_rank(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_TsRank_Original_Medium);

static void BM_TsRank_Optimized_Medium(benchmark::State& state) {
    vector<float> data = generate_random_data(1000, 42);
    int window = 20;

    for (auto _ : state) {
        auto result = ts_rank_optimized(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_TsRank_Optimized_Medium);

static void BM_TsRank_Original_Large(benchmark::State& state) {
    vector<float> data = generate_random_data(10000, 42);
    int window = 50;

    for (auto _ : state) {
        auto result = ts_rank(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_TsRank_Original_Large);

static void BM_TsRank_Optimized_Large(benchmark::State& state) {
    vector<float> data = generate_random_data(10000, 42);
    int window = 50;

    for (auto _ : state) {
        auto result = ts_rank_optimized(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_TsRank_Optimized_Large);

// ========== 直接对比（自动计算相对性能）==========

static void BM_TsRank_Compare(benchmark::State& state) {
    size_t data_size = state.range(0);
    int window = state.range(1);
    vector<float> data = generate_random_data(data_size, 42);

    // state.name() 包含 "Original" 或 "Optimized"
    bool use_optimized = state.range(2);

    for (auto _ : state) {
        if (use_optimized) {
            auto result = ts_rank_optimized(data, window);
            benchmark::DoNotOptimize(result);
        } else {
            auto result = ts_rank(data, window);
            benchmark::DoNotOptimize(result);
        }
    }
    state.SetItemsProcessed(state.iterations() * data_size);
}

// 对比不同数据量和窗口大小
BENCHMARK(BM_TsRank_Compare)
    ->Args({100, 10, 0})   // 100 个数据，窗口 10，原版
    ->Args({100, 10, 1})   // 100 个数据，窗口 10，优化版
    ->Args({1000, 20, 0})  // 1000 个数据，窗口 20，原版
    ->Args({1000, 20, 1})  // 1000 个数据，窗口 20，优化版
    ->Args({10000, 50, 0}) // 10000 个数据，窗口 50，原版
    ->Args({10000, 50, 1}) // 10000 个数据，窗口 50，优化版
    ->ArgNames({"data_size", "window", "optimized"});

// ========== TS Rank Ultra (滑动窗口优化) 性能对比 ==========

static void BM_TsRank_Ultra_Small(benchmark::State& state) {
    vector<float> data = generate_random_data(100, 42);
    int window = 10;

    for (auto _ : state) {
        auto result = ts_rank_ultra(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_TsRank_Ultra_Small);

static void BM_TsRank_Ultra_Medium(benchmark::State& state) {
    vector<float> data = generate_random_data(1000, 42);
    int window = 20;

    for (auto _ : state) {
        auto result = ts_rank_ultra(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_TsRank_Ultra_Medium);

static void BM_TsRank_Ultra_Large(benchmark::State& state) {
    vector<float> data = generate_random_data(10000, 42);
    int window = 50;

    for (auto _ : state) {
        auto result = ts_rank_ultra(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_TsRank_Ultra_Large);

// 三个版本的直接对比
static void BM_TsRank_ThreeWay_Compare(benchmark::State& state) {
    size_t data_size = state.range(0);
    int window = state.range(1);
    int version = state.range(2);  // 0=Original, 1=Optimized, 2=Ultra

    vector<float> data = generate_random_data(data_size, 42);

    for (auto _ : state) {
        if (version == 0) {
            auto result = ts_rank(data, window);
            benchmark::DoNotOptimize(result);
        } else if (version == 1) {
            auto result = ts_rank_optimized(data, window);
            benchmark::DoNotOptimize(result);
        } else {
            auto result = ts_rank_ultra(data, window);
            benchmark::DoNotOptimize(result);
        }
    }
    state.SetItemsProcessed(state.iterations() * data_size);
}

// 对比三个版本：原始、span优化、滑动窗口优化
BENCHMARK(BM_TsRank_ThreeWay_Compare)
    ->Args({10000, 50, 0})  // 10000 个数据，窗口 50，原始版本
    ->Args({10000, 50, 1})  // 10000 个数据，窗口 50，span 优化
    ->Args({10000, 50, 2})  // 10000 个数据，窗口 50，ultra 优化
    ->ArgNames({"data_size", "window", "version"});

BENCHMARK_MAIN();