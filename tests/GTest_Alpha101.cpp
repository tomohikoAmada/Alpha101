#include <gtest/gtest.h>

#include <cmath>

#include "Alpha101.h"

// ========== Alpha001 Tests ==========
// Alpha#1: rank(Ts_ArgMax(SignedPower(((returns < 0) ? stddev(returns, 20) : close), 2.), 5)) - 0.5
//
// Warm-up: rolling_stddev benötigt window=20 → erste 19 Indizes NaN
//          ts_argmax benötigt window=5  → weitere 4 Indizes NaN
//          Erster gültiger Index: 23 (0-indexed)

class Alpha001Test : public ::testing::Test {
   protected:
    // Erzeugt einen Vektor mit n Elementen, alle gleich value
    static vector<float> const_vec(size_t n, float value) { return vector<float>(n, value); }

    // Erzeugt einen Vektor mit steigenden Werten: start, start+step, ...
    static vector<float> linspace(size_t n, float start, float step) {
        vector<float> v(n);
        for (size_t i = 0; i < n; ++i) v[i] = start + i * step;
        return v;
    }
};

// ---------- Grundlegende Struktur ----------

TEST_F(Alpha001Test, OutputSize) {
    // Ausgabegröße muss der Eingabegröße entsprechen
    size_t n = 50;
    auto close = const_vec(n, 10.0f);
    auto returns = const_vec(n, 0.01f);
    auto result = alpha001(close, returns);
    EXPECT_EQ(result.size(), n);
}

TEST_F(Alpha001Test, WarmupPeriod) {
    // Indizes 0..22 (erste 23 Elemente) müssen NaN sein
    size_t n = 50;
    auto close = linspace(n, 10.0f, 0.5f);
    auto returns = const_vec(n, 0.01f);
    auto result = alpha001(close, returns);

    for (size_t i = 0; i < 23; ++i) {
        EXPECT_TRUE(isnan(result[i])) << "Index " << i << " sollte NaN sein";
    }
    // Ab Index 23 darf kein NaN mehr sein (sofern genug Eingabedaten)
    for (size_t i = 23; i < n; ++i) {
        EXPECT_FALSE(isnan(result[i])) << "Index " << i << " sollte kein NaN sein";
    }
}

TEST_F(Alpha001Test, AllNanForShortInput) {
    // Bei weniger als 24 Elementen ist die gesamte Ausgabe NaN
    for (size_t n : {1u, 10u, 22u, 23u}) {
        auto close = linspace(n, 10.0f, 1.0f);
        auto returns = const_vec(n, 0.01f);
        auto result = alpha001(close, returns);
        for (size_t i = 0; i < n; ++i) {
            EXPECT_TRUE(isnan(result[i])) << "n=" << n << ", Index " << i << " sollte NaN sein";
        }
    }
}

// ---------- Ausgabebereich ----------

TEST_F(Alpha001Test, OutputRangeValid) {
    // Gültige Ausgabewerte liegen in (-0.5, 0.5]
    size_t n = 60;
    auto close = linspace(n, 100.0f, 1.0f);
    auto returns = const_vec(n, 0.01f);
    auto result = alpha001(close, returns);

    for (size_t i = 23; i < n; ++i) {
        EXPECT_GE(result[i], -0.5f) << "Index " << i;
        EXPECT_LE(result[i], 0.5f) << "Index " << i;
    }
}

// ---------- Einzelner gültiger Ausgabewert = -0.5 ----------

TEST_F(Alpha001Test, SingleValidOutputEquals_Minus05) {
    // Genau 24 Elemente → nur result[23] ist gültig
    // alpha_rank eines einzelnen Elements = 1.0 → 1.0 - 0.5 = 0.5
    size_t n = 24;
    auto close = linspace(n, 10.0f, 1.0f);
    auto returns = const_vec(n, 0.01f);
    auto result = alpha001(close, returns);

    EXPECT_FALSE(isnan(result[23]));
    EXPECT_FLOAT_EQ(result[23], 0.5f);
}

// ---------- Bekannte Werte ----------

TEST_F(Alpha001Test, KnownValues) {
    size_t n = 25;
    vector<float> close(n, 100.0f);
    close[19] = 10.0f;
    close[20] = 5.0f;
    close[21] = 15.0f;
    close[22] = 20.0f;
    close[23] = 12.0f;
    close[24] = 25.0f;
    auto returns = const_vec(n, 0.01f);

    auto result = alpha001(close, returns);

    EXPECT_FALSE(isnan(result[23]));
    EXPECT_FALSE(isnan(result[24]));
    EXPECT_FLOAT_EQ(result[23], 0.0f);
    EXPECT_FLOAT_EQ(result[24], 0.5f);
}

// ---------- Gleichstand (Ties) ----------

TEST_F(Alpha001Test, TieHandling) {
    size_t n = 30;
    auto close = const_vec(n, 50.0f);
    auto returns = const_vec(n, 0.01f);
    auto result = alpha001(close, returns);

    size_t m = n - 23;  // Anzahl gültiger Ausgabewerte
    float expected = 1.0f / (2.0f * static_cast<float>(m));

    for (size_t i = 23; i < n; ++i) {
        EXPECT_FALSE(isnan(result[i])) << "Index " << i;
        EXPECT_NEAR(result[i], expected, 1e-5f) << "Index " << i;
    }
}

// ---------- Negative Renditen verwenden stddev ----------

TEST_F(Alpha001Test, NegativeReturnUsesStddev) {
    // Wenn returns < 0, wird stddev(returns, 20) statt close verwendet
    // Bei konstanten Renditen ist stddev=0 → inner_sq=0
    // ts_argmax([0,0,...,0]) → Position 1 (erster Treffer überall)
    size_t n = 40;
    auto close = linspace(n, 10.0f, 1.0f);
    auto returns = const_vec(n, -0.01f);  // alle negativ
    auto result = alpha001(close, returns);

    // Ergebnis muss für alle gültigen Indizes definiert und im Bereich sein
    for (size_t i = 23; i < n; ++i) {
        EXPECT_FALSE(isnan(result[i])) << "Index " << i;
        EXPECT_GE(result[i], -0.5f);
        EXPECT_LE(result[i], 0.5f);
    }
}

// ---------- Gemischte Renditen ----------

TEST_F(Alpha001Test, MixedReturns) {
    // Abwechselnd positive und negative Renditen
    size_t n = 40;
    auto close = linspace(n, 50.0f, 0.5f);
    vector<float> returns(n);
    for (size_t i = 0; i < n; ++i) returns[i] = (i % 2 == 0) ? 0.02f : -0.02f;
    auto result = alpha001(close, returns);

    for (size_t i = 23; i < n; ++i) {
        EXPECT_FALSE(isnan(result[i])) << "Index " << i;
        EXPECT_GE(result[i], -0.5f);
        EXPECT_LE(result[i], 0.5f);
    }
}

// main-Funktion wird von GTest::gtest_main bereitgestellt, kein manuelles Schreiben nötig
