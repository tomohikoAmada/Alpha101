#include <benchmark/benchmark.h>

#include <random>

#include "Alpha101.h"

// Hilfsfunktion zur Erzeugung von Zufallsdaten
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

// ========== Product (rollendes Produkt) Benchmarks ==========

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

// ========== TS Min (rollendes Minimum) Benchmarks ==========

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

// ========== TS Max (rollendes Maximum) Benchmarks ==========

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

// ========== Delta (Differenz) Benchmarks ==========

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

// ========== Delay (Verzögerung) Benchmarks ==========

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

// ========== Leistungsvergleich bei unterschiedlichen Fenstergrößen ==========

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

// ========== Leistungsvergleich bei unterschiedlichen Datenmengen ==========

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
BENCHMARK(BM_RollingCorrelation_VaryingDataSize)->Arg(100)->Arg(500)->Arg(1000)->Arg(5000)->Arg(10000);

// ========== TS Rank Leistungsvergleich ==========

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

// ========== Direktvergleich (automatische relative Leistungsberechnung) ==========

static void BM_TsRank_Compare(benchmark::State& state) {
    size_t data_size = state.range(0);
    int window = state.range(1);
    vector<float> data = generate_random_data(data_size, 42);

    // state.name() enthält "Original" oder "Optimized"
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

// Vergleich bei unterschiedlichen Datenmengen und Fenstergrößen
BENCHMARK(BM_TsRank_Compare)
    ->Args({100, 10, 0})    // 100 Datenpunkte, Fenster 10, Original
    ->Args({100, 10, 1})    // 100 Datenpunkte, Fenster 10, Optimiert
    ->Args({1000, 20, 0})   // 1000 Datenpunkte, Fenster 20, Original
    ->Args({1000, 20, 1})   // 1000 Datenpunkte, Fenster 20, Optimiert
    ->Args({10000, 50, 0})  // 10000 Datenpunkte, Fenster 50, Original
    ->Args({10000, 50, 1})  // 10000 Datenpunkte, Fenster 50, Optimiert
    ->ArgNames({"data_size", "window", "optimized"});

// ========== TS Rank Ultra (gleitendes Fenster optimiert) Leistungsvergleich ==========

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

// Direktvergleich der drei Versionen
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

// Vergleich der drei Versionen: Original, span-optimiert, gleitendes-Fenster-optimiert
BENCHMARK(BM_TsRank_ThreeWay_Compare)
    ->Args({10000, 50, 0})  // 10000 Datenpunkte, Fenster 50, Originalversion
    ->Args({10000, 50, 1})  // 10000 Datenpunkte, Fenster 50, span-optimiert
    ->Args({10000, 50, 2})  // 10000 Datenpunkte, Fenster 50, ultra-optimiert
    ->ArgNames({"data_size", "window", "version"});

// ========== Rank (Querschnittsrang) Benchmarks ==========

static void BM_Rank_Small(benchmark::State& state) {
    // Kleine Datenmenge: 100 Elemente
    vector<float> data = generate_random_data(100, 42);

    for (auto _ : state) {
        auto result = alpha_rank(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Rank_Small);

static void BM_Rank_Medium(benchmark::State& state) {
    // Mittlere Datenmenge: 1000 Elemente
    vector<float> data = generate_random_data(1000, 42);

    for (auto _ : state) {
        auto result = alpha_rank(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Rank_Medium);

static void BM_Rank_Large(benchmark::State& state) {
    // Große Datenmenge: 10000 Elemente
    vector<float> data = generate_random_data(10000, 42);

    for (auto _ : state) {
        auto result = alpha_rank(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Rank_Large);

static void BM_Rank_VeryLarge(benchmark::State& state) {
    // Sehr große Datenmenge: 100000 Elemente (simuliert reale Aktienanzahl)
    vector<float> data = generate_random_data(100000, 42);

    for (auto _ : state) {
        auto result = alpha_rank(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Rank_VeryLarge);

// ========== Leistungsvergleich bei verschiedenen Datengrößen ==========

static void BM_Rank_VaryingSize(benchmark::State& state) {
    size_t size = state.range(0);
    vector<float> data = generate_random_data(size, 42);

    for (auto _ : state) {
        auto result = alpha_rank(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * size);
}
BENCHMARK(BM_Rank_VaryingSize)->Arg(10)->Arg(100)->Arg(1000)->Arg(5000)->Arg(10000)->Arg(50000)->Arg(100000);

// ========== Leistungstest bei verschiedenen Duplikatanteilen ==========

// Hilfsfunktion: Daten mit bestimmtem Duplikatanteil erzeugen
vector<float> generate_data_with_duplicates(size_t size, float duplicate_ratio, int seed = 42) {
    vector<float> data;
    data.reserve(size);

    std::mt19937 gen(seed);
    // Anzahl eindeutiger Werte anhand des Duplikatanteils bestimmen
    size_t unique_count = static_cast<size_t>(size * (1.0f - duplicate_ratio));
    unique_count = std::max(unique_count, size_t(1));  // Mindestens 1 eindeutiger Wert

    std::uniform_int_distribution<size_t> dis(0, unique_count - 1);

    // Eindeutige Wertemenge erzeugen
    vector<float> unique_values;
    for (size_t i = 0; i < unique_count; ++i) {
        unique_values.push_back(static_cast<float>(i));
    }

    // Zufällig aus der Wertemenge auswählen
    for (size_t i = 0; i < size; ++i) {
        size_t idx = dis(gen);
        data.push_back(unique_values[idx]);
    }

    return data;
}

static void BM_Rank_NoDuplicates(benchmark::State& state) {
    // Keine Duplikate (bester Fall)
    vector<float> data = generate_data_with_duplicates(10000, 0.0f, 42);

    for (auto _ : state) {
        auto result = alpha_rank(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Rank_NoDuplicates);

static void BM_Rank_FewDuplicates(benchmark::State& state) {
    // 10% Duplikate
    vector<float> data = generate_data_with_duplicates(10000, 0.1f, 42);

    for (auto _ : state) {
        auto result = alpha_rank(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Rank_FewDuplicates);

static void BM_Rank_ManyDuplicates(benchmark::State& state) {
    // 50% Duplikate
    vector<float> data = generate_data_with_duplicates(10000, 0.5f, 42);

    for (auto _ : state) {
        auto result = alpha_rank(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Rank_ManyDuplicates);

static void BM_Rank_MostlyDuplicates(benchmark::State& state) {
    // 90% Duplikate
    vector<float> data = generate_data_with_duplicates(10000, 0.9f, 42);

    for (auto _ : state) {
        auto result = alpha_rank(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Rank_MostlyDuplicates);

static void BM_Rank_AllSame(benchmark::State& state) {
    // Alle Werte gleich (schlechtester Fall)
    vector<float> data(10000, 42.0f);

    for (auto _ : state) {
        auto result = alpha_rank(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Rank_AllSame);

// ========== Leistungstest bei verschiedenen Datenverteilungen ==========

static void BM_Rank_MonotonicIncreasing(benchmark::State& state) {
    // Monoton steigende Folge (bester Sortierfall)
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
    // Monoton fallende Folge (Umkehrung erforderlich)
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
    // Zufällig verteilte Daten (typischer Fall)
    vector<float> data = generate_random_data(10000, 42);

    for (auto _ : state) {
        auto result = alpha_rank(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Rank_RandomData);

// ========== Simulation realer Szenarien ==========

static void BM_Rank_StockReturns(benchmark::State& state) {
    // Simulation von Aktienrendite-Ranking (Normalverteilung, wenige Duplikate)
    vector<float> data;
    data.reserve(5000);  // 5000 Aktien simulieren

    std::mt19937 gen(42);
    std::normal_distribution<float> dis(0.0f, 0.02f);  // Mittelwert 0%, Standardabweichung 2%

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
    // Simulation von Kursgrenzszenarien (viele Duplikate)
    vector<float> data;
    data.reserve(5000);

    std::mt19937 gen(42);
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    for (int i = 0; i < 5000; ++i) {
        float r = dis(gen);
        if (r < 0.05) {
            data.push_back(0.10f);  // 5% Kursanstieg-Limit
        } else if (r < 0.10) {
            data.push_back(-0.10f);  // 5% Kursabfall-Limit
        } else {
            // 90% normale Schwankung
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

// ========== Analyse der Speicherzugriffsmuster ==========

static void BM_Rank_MemoryPattern(benchmark::State& state) {
    size_t size = state.range(0);
    vector<float> data = generate_random_data(size, 42);

    size_t total_bytes = 0;
    for (auto _ : state) {
        auto result = alpha_rank(data);
        benchmark::DoNotOptimize(result);
        // Geschätzte Speicherzugriffe: Eingabearray + Indexarray + Ergebnisarray
        total_bytes += size * sizeof(float) * 3;
    }
    state.SetBytesProcessed(total_bytes);
    state.SetItemsProcessed(state.iterations() * size);
}
BENCHMARK(BM_Rank_MemoryPattern)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->ArgName("size");

// ========== Scale (Skalierung) Benchmarks ==========

static void BM_Scale_Small(benchmark::State& state) {
    vector<float> data = generate_random_data(100);

    for (auto _ : state) {
        auto result = scale(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Scale_Small);

static void BM_Scale_Medium(benchmark::State& state) {
    vector<float> data = generate_random_data(1000);

    for (auto _ : state) {
        auto result = scale(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Scale_Medium);

static void BM_Scale_Large(benchmark::State& state) {
    vector<float> data = generate_random_data(10000);

    for (auto _ : state) {
        auto result = scale(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Scale_Large);

static void BM_Scale_VeryLarge(benchmark::State& state) {
    vector<float> data = generate_random_data(100000);

    for (auto _ : state) {
        auto result = scale(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Scale_VeryLarge);

// Skalierungsleistung mit negativen Zahlen (Einfluss von abs auf Performance)
static void BM_Scale_WithNegatives(benchmark::State& state) {
    // Daten mit negativen Werten erzeugen [-50, 50)
    vector<float> data;
    data.reserve(10000);
    std::mt19937 gen(42);
    std::uniform_real_distribution<float> dis(-50.0f, 50.0f);
    for (size_t i = 0; i < 10000; i++) {
        data.push_back(dis(gen));
    }

    for (auto _ : state) {
        auto result = scale(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Scale_WithNegatives);

// Leistungsvergleich bei verschiedenen k-Werten
static void BM_Scale_VaryingK(benchmark::State& state) {
    float k = static_cast<float>(state.range(0));
    vector<float> data = generate_random_data(10000);

    for (auto _ : state) {
        auto result = scale(data, k);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_Scale_VaryingK)->Arg(1)->Arg(2)->Arg(10)->Arg(100);

// Leistungsvergleich bei verschiedenen Datengrößen
static void BM_Scale_VaryingSize(benchmark::State& state) {
    size_t size = state.range(0);
    vector<float> data = generate_random_data(size);

    for (auto _ : state) {
        auto result = scale(data);
        benchmark::DoNotOptimize(result);
    }
    state.SetBytesProcessed(state.iterations() * size * sizeof(float));
    state.SetItemsProcessed(state.iterations() * size);
}
BENCHMARK(BM_Scale_VaryingSize)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000)->ArgName("size");

// ========== TS Argmax Benchmarks ==========

static void BM_TsArgmax_Small(benchmark::State& state) {
    vector<float> data = generate_random_data(100);
    int window = 10;

    for (auto _ : state) {
        auto result = ts_argmax(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_TsArgmax_Small);

static void BM_TsArgmax_Medium(benchmark::State& state) {
    vector<float> data = generate_random_data(1000);
    int window = 20;

    for (auto _ : state) {
        auto result = ts_argmax(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_TsArgmax_Medium);

static void BM_TsArgmax_Large(benchmark::State& state) {
    vector<float> data = generate_random_data(10000);
    int window = 50;

    for (auto _ : state) {
        auto result = ts_argmax(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_TsArgmax_Large);

static void BM_TsArgmax_VaryingWindow(benchmark::State& state) {
    int window = state.range(0);
    vector<float> data = generate_random_data(10000);

    for (auto _ : state) {
        auto result = ts_argmax(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_TsArgmax_VaryingWindow)->Arg(5)->Arg(10)->Arg(20)->Arg(50)->Arg(100);

// Vergleich ts_argmax vs ts_max (strukturell ähnlich, unterschiedliche Rückgabetypen)
static void BM_TsArgmax_vs_TsMax(benchmark::State& state) {
    int version = state.range(0);  // 0=ts_argmax, 1=ts_max
    vector<float> data = generate_random_data(10000);
    int window = 50;

    for (auto _ : state) {
        if (version == 0) {
            auto result = ts_argmax(data, window);
            benchmark::DoNotOptimize(result);
        } else {
            auto result = ts_max(data, window);
            benchmark::DoNotOptimize(result);
        }
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_TsArgmax_vs_TsMax)->Arg(0)->Arg(1)->ArgNames({"version"});

// ========== TS Argmin Benchmarks ==========

static void BM_TsArgmin_Small(benchmark::State& state) {
    vector<float> data = generate_random_data(100);
    int window = 10;

    for (auto _ : state) {
        auto result = ts_argmin(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_TsArgmin_Small);

static void BM_TsArgmin_Medium(benchmark::State& state) {
    vector<float> data = generate_random_data(1000);
    int window = 20;

    for (auto _ : state) {
        auto result = ts_argmin(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_TsArgmin_Medium);

static void BM_TsArgmin_Large(benchmark::State& state) {
    vector<float> data = generate_random_data(10000);
    int window = 50;

    for (auto _ : state) {
        auto result = ts_argmin(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_TsArgmin_Large);

static void BM_TsArgmin_VaryingWindow(benchmark::State& state) {
    int window = state.range(0);
    vector<float> data = generate_random_data(10000);

    for (auto _ : state) {
        auto result = ts_argmin(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_TsArgmin_VaryingWindow)->Arg(5)->Arg(10)->Arg(20)->Arg(50)->Arg(100);

// Vergleich ts_argmin vs ts_min (strukturell ähnlich, unterschiedliche Rückgabetypen)
static void BM_TsArgmin_vs_TsMin(benchmark::State& state) {
    int version = state.range(0);  // 0=ts_argmin, 1=ts_min
    vector<float> data = generate_random_data(10000);
    int window = 50;

    for (auto _ : state) {
        if (version == 0) {
            auto result = ts_argmin(data, window);
            benchmark::DoNotOptimize(result);
        } else {
            auto result = ts_min(data, window);
            benchmark::DoNotOptimize(result);
        }
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_TsArgmin_vs_TsMin)->Arg(0)->Arg(1)->ArgNames({"version"});

// ========== Decay Linear Benchmarks ==========

static void BM_DecayLinear_Small(benchmark::State& state) {
    vector<float> data = generate_random_data(100);
    int window = 5;

    for (auto _ : state) {
        auto result = decay_linear(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_DecayLinear_Small);

static void BM_DecayLinear_Medium(benchmark::State& state) {
    vector<float> data = generate_random_data(1000);
    int window = 20;

    for (auto _ : state) {
        auto result = decay_linear(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_DecayLinear_Medium);

static void BM_DecayLinear_Large(benchmark::State& state) {
    vector<float> data = generate_random_data(10000);
    int window = 50;

    for (auto _ : state) {
        auto result = decay_linear(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_DecayLinear_Large);

// Fenstergröße als Parameter variieren
static void BM_DecayLinear_VaryWindow(benchmark::State& state) {
    vector<float> data = generate_random_data(5000);
    int window = static_cast<int>(state.range(0));

    for (auto _ : state) {
        auto result = decay_linear(data, window);
        benchmark::DoNotOptimize(result);
    }
    state.SetItemsProcessed(state.iterations() * data.size());
}
BENCHMARK(BM_DecayLinear_VaryWindow)->Arg(5)->Arg(20)->Arg(50)->Arg(100)->ArgNames({"window"});

BENCHMARK_MAIN();
