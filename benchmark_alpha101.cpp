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

// ========== Delta (差分) Benchmarks ==========

static void BM_Delta_Small(benchmark::State& state) {
    vector<float> data = generate_random_data(100);
    int period = 1;

    for (auto _ : state) {
        auto result = delta(data, period);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Delta_Small);

static void BM_Delta_Medium(benchmark::State& state) {
    vector<float> data = generate_random_data(1000);
    int period = 1;

    for (auto _ : state) {
        auto result = delta(data, period);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Delta_Medium);

static void BM_Delta_Large(benchmark::State& state) {
    vector<float> data = generate_random_data(10000);
    int period = 1;

    for (auto _ : state) {
        auto result = delta(data, period);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Delta_Large);

static void BM_Delta_VeryLarge(benchmark::State& state) {
    vector<float> data = generate_random_data(100000);
    int period = 1;

    for (auto _ : state) {
        auto result = delta(data, period);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Delta_VeryLarge);

static void BM_Delta_VaryingPeriod(benchmark::State& state) {
    int period = state.range(0);
    vector<float> data = generate_random_data(10000);

    for (auto _ : state) {
        auto result = delta(data, period);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Delta_VaryingPeriod)->Arg(1)->Arg(5)->Arg(10)->Arg(20)->Arg(50)->Arg(100);

// ========== Delay (滞后) Benchmarks ==========

static void BM_Delay_Small(benchmark::State& state) {
    vector<float> data = generate_random_data(100);
    int period = 1;

    for (auto _ : state) {
        auto result = delay(data, period);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Delay_Small);

static void BM_Delay_Medium(benchmark::State& state) {
    vector<float> data = generate_random_data(1000);
    int period = 1;

    for (auto _ : state) {
        auto result = delay(data, period);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Delay_Medium);

static void BM_Delay_Large(benchmark::State& state) {
    vector<float> data = generate_random_data(10000);
    int period = 1;

    for (auto _ : state) {
        auto result = delay(data, period);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Delay_Large);

static void BM_Delay_VeryLarge(benchmark::State& state) {
    vector<float> data = generate_random_data(100000);
    int period = 1;

    for (auto _ : state) {
        auto result = delay(data, period);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Delay_VeryLarge);

static void BM_Delay_VaryingPeriod(benchmark::State& state) {
    int period = state.range(0);
    vector<float> data = generate_random_data(10000);

    for (auto _ : state) {
        auto result = delay(data, period);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Delay_VaryingPeriod)->Arg(1)->Arg(5)->Arg(10)->Arg(20)->Arg(50)->Arg(100);

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

// ========== Rank (横截面排名) Benchmarks ==========

static void BM_Rank_Small(benchmark::State& state) {
    // 小数据量：100个元素
    vector<float> data = generate_random_data(100, 42);

    for (auto _ : state) {
        auto result = alpha_rank(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Rank_Small);

static void BM_Rank_Medium(benchmark::State& state) {
    // 中等数据量：1000个元素
    vector<float> data = generate_random_data(1000, 42);

    for (auto _ : state) {
        auto result = alpha_rank(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Rank_Medium);

static void BM_Rank_Large(benchmark::State& state) {
    // 大数据量：10000个元素
    vector<float> data = generate_random_data(10000, 42);

    for (auto _ : state) {
        auto result = alpha_rank(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Rank_Large);

static void BM_Rank_VeryLarge(benchmark::State& state) {
    // 超大数据量：100000个元素（模拟真实股票数量）
    vector<float> data = generate_random_data(100000, 42);

    for (auto _ : state) {
        auto result = alpha_rank(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Rank_VeryLarge);

// ========== 不同数据规模的性能对比 ==========

static void BM_Rank_VaryingSize(benchmark::State& state) {
    size_t size = state.range(0);
    vector<float> data = generate_random_data(size, 42);

    for (auto _ : state) {
        auto result = alpha_rank(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * size);
}
BENCHMARK(BM_Rank_VaryingSize)
    ->Arg(10)
    ->Arg(100)
    ->Arg(1000)
    ->Arg(5000)
    ->Arg(10000)
    ->Arg(50000)
    ->Arg(100000);

// ========== 不同重复值比例的性能测试 ==========

// 辅助函数：生成具有特定重复比例的数据
vector<float> generate_data_with_duplicates(size_t size, float duplicate_ratio, int seed = 42) {
    vector<float> data;
    data.reserve(size);

    std::mt19937 gen(seed);
    // 根据重复比例决定唯一值的数量
    size_t unique_count = static_cast<size_t>(size * (1.0f - duplicate_ratio));
    unique_count = std::max(unique_count, size_t(1));  // 至少1个唯一值

    std::uniform_int_distribution<size_t> dis(0, unique_count - 1);

    // 生成唯一值池
    vector<float> unique_values;
    for (size_t i = 0; i < unique_count; ++i) {
        unique_values.push_back(static_cast<float>(i));
    }

    // 从唯一值池中随机选择
    for (size_t i = 0; i < size; ++i) {
        size_t idx = dis(gen);
        data.push_back(unique_values[idx]);
    }

    return data;
}

static void BM_Rank_NoDuplicates(benchmark::State& state) {
    // 完全没有重复值（最优情况）
    vector<float> data = generate_data_with_duplicates(10000, 0.0f, 42);

    for (auto _ : state) {
        auto result = alpha_rank(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Rank_NoDuplicates);

static void BM_Rank_FewDuplicates(benchmark::State& state) {
    // 10%重复值
    vector<float> data = generate_data_with_duplicates(10000, 0.1f, 42);

    for (auto _ : state) {
        auto result = alpha_rank(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Rank_FewDuplicates);

static void BM_Rank_ManyDuplicates(benchmark::State& state) {
    // 50%重复值
    vector<float> data = generate_data_with_duplicates(10000, 0.5f, 42);

    for (auto _ : state) {
        auto result = alpha_rank(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Rank_ManyDuplicates);

static void BM_Rank_MostlyDuplicates(benchmark::State& state) {
    // 90%重复值
    vector<float> data = generate_data_with_duplicates(10000, 0.9f, 42);

    for (auto _ : state) {
        auto result = alpha_rank(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Rank_MostlyDuplicates);

static void BM_Rank_AllSame(benchmark::State& state) {
    // 所有值相同（最坏情况）
    vector<float> data(10000, 42.0f);

    for (auto _ : state) {
        auto result = alpha_rank(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Rank_AllSame);

// ========== 不同数据分布的性能测试 ==========

static void BM_Rank_MonotonicIncreasing(benchmark::State& state) {
    // 单调递增序列（最优排序情况）
    vector<float> data;
    data.reserve(10000);
    for (int i = 0; i < 10000; ++i) {
        data.push_back(static_cast<float>(i));
    }

    for (auto _ : state) {
        auto result = alpha_rank(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Rank_MonotonicIncreasing);

static void BM_Rank_MonotonicDecreasing(benchmark::State& state) {
    // 单调递减序列（需要反转）
    vector<float> data;
    data.reserve(10000);
    for (int i = 10000; i > 0; --i) {
        data.push_back(static_cast<float>(i));
    }

    for (auto _ : state) {
        auto result = alpha_rank(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Rank_MonotonicDecreasing);

static void BM_Rank_RandomData(benchmark::State& state) {
    // 随机分布数据（典型情况）
    vector<float> data = generate_random_data(10000, 42);

    for (auto _ : state) {
        auto result = alpha_rank(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Rank_RandomData);

// ========== 现实场景模拟 ==========

static void BM_Rank_StockReturns(benchmark::State& state) {
    // 模拟股票收益率排名（正态分布，少量重复）
    vector<float> data;
    data.reserve(5000);  // 模拟5000只股票

    std::mt19937 gen(42);
    std::normal_distribution<float> dis(0.0f, 0.02f);  // 均值0%，标准差2%

    for (int i = 0; i < 5000; ++i) {
        data.push_back(dis(gen));
    }

    for (auto _ : state) {
        auto result = alpha_rank(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
    state.SetLabel("模拟5000只股票的收益率排名");
}
BENCHMARK(BM_Rank_StockReturns);

static void BM_Rank_LimitUpStocks(benchmark::State& state) {
    // 模拟涨跌停场景（大量重复值）
    vector<float> data;
    data.reserve(5000);

    std::mt19937 gen(42);
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    for (int i = 0; i < 5000; ++i) {
        float r = dis(gen);
        if (r < 0.05) {
            data.push_back(0.10f);   // 5%涨停
        } else if (r < 0.10) {
            data.push_back(-0.10f);  // 5%跌停
        } else {
            // 90%正常波动
            std::normal_distribution<float> normal_dis(0.0f, 0.02f);
            data.push_back(normal_dis(gen));
        }
    }

    for (auto _ : state) {
        auto result = alpha_rank(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
    state.SetLabel("模拟涨跌停场景（10%涨跌停股票）");
}
BENCHMARK(BM_Rank_LimitUpStocks);

// ========== 内存访问模式分析 ==========

static void BM_Rank_MemoryPattern(benchmark::State& state) {
    size_t size = state.range(0);
    vector<float> data = generate_random_data(size, 42);

    size_t total_bytes = 0;
    for (auto _ : state) {
        auto result = alpha_rank(data);
        benchmark::DoNotOptimize(result);
        // 估算内存访问：输入数组 + 索引数组 + 结果数组
        total_bytes += size * sizeof(float) * 3;
    }
    state.SetBytesProcessed(total_bytes);
    state.SetItemsProcessed(state.iterations() * size);
}
BENCHMARK(BM_Rank_MemoryPattern)
    ->Arg(100)
    ->Arg(1000)
    ->Arg(10000)
    ->Arg(100000)
    ->ArgName("size");

BENCHMARK_MAIN();