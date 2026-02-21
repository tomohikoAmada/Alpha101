#include <gtest/gtest.h>

#include <cmath>

#include "Alpha101Utils.h"

// Hilfsfunktion: Zwei Vektoren auf Gleichheit prüfen (NaN berücksichtigt)
bool vectors_equal(const vector<float>& a, const vector<float>& b, float tolerance = 1e-5) {
    if (a.size() != b.size()) return false;

    for (size_t i = 0; i < a.size(); i++) {
        bool a_is_nan = isnan(a[i]);
        bool b_is_nan = isnan(b[i]);

        if (a_is_nan && b_is_nan) continue;
        if (a_is_nan != b_is_nan) return false;
        if (fabs(a[i] - b[i]) > tolerance) return false;
    }

    return true;
}

// ========== Rolling TS Sum Tests ==========

TEST(RollingTsSumTest, BasicTest) {
    vector<float> input = {1, 2, 3, 4, 5};
    vector<float> result = rolling_ts_sum(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 6);
    EXPECT_FLOAT_EQ(result[3], 9);
    EXPECT_FLOAT_EQ(result[4], 12);
}

TEST(RollingTsSumTest, LongerSequence) {
    vector<float> input = {1, 2, 3, 4, 5, 6, 7, 8};
    vector<float> result = rolling_ts_sum(input, 5);

    ASSERT_EQ(result.size(), 8);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_TRUE(isnan(result[2]));
    EXPECT_TRUE(isnan(result[3]));
    EXPECT_FLOAT_EQ(result[4], 15);
    EXPECT_FLOAT_EQ(result[5], 20);
    EXPECT_FLOAT_EQ(result[6], 25);
    EXPECT_FLOAT_EQ(result[7], 30);
}

TEST(RollingTsSumTest, WindowOne) {
    vector<float> input = {10, 20, 30};
    vector<float> result = rolling_ts_sum(input, 1);

    ASSERT_EQ(result.size(), 3);
    EXPECT_FLOAT_EQ(result[0], 10);
    EXPECT_FLOAT_EQ(result[1], 20);
    EXPECT_FLOAT_EQ(result[2], 30);
}

// ========== Rolling Prod Tests ==========

TEST(RollingProdTest, BasicTest) {
    // Grundlegendes Produkt testen: [2, 3, 4]
    // 2 × 3 × 4 = 24
    vector<float> input = {2, 3, 4};
    float result = rolling_prod(input);

    EXPECT_FLOAT_EQ(result, 24.0);
}

TEST(RollingProdTest, WithOne) {
    // Produkt mit 1: [5, 1, 4]
    // 5 × 1 × 4 = 20
    vector<float> input = {5, 1, 4};
    float result = rolling_prod(input);

    EXPECT_FLOAT_EQ(result, 20.0);
}

TEST(RollingProdTest, WithZero) {
    // Produkt mit 0: [2, 0, 5]
    // 2 × 0 × 5 = 0
    vector<float> input = {2, 0, 5};
    float result = rolling_prod(input);

    EXPECT_FLOAT_EQ(result, 0.0);
}

TEST(RollingProdTest, NegativeNumbers) {
    // Mit negativen Zahlen: [2, -3, 4]
    // 2 × (-3) × 4 = -24
    vector<float> input = {2, -3, 4};
    float result = rolling_prod(input);

    EXPECT_FLOAT_EQ(result, -24.0);
}

TEST(RollingProdTest, TwoNegatives) {
    // Zwei negative Zahlen: [-2, -3, 4]
    // (-2) × (-3) × 4 = 24
    vector<float> input = {-2, -3, 4};
    float result = rolling_prod(input);

    EXPECT_FLOAT_EQ(result, 24.0);
}

TEST(RollingProdTest, SingleElement) {
    // Einzelnes Element: [5]
    // Ergebnis ist 5
    vector<float> input = {5};
    float result = rolling_prod(input);

    EXPECT_FLOAT_EQ(result, 5.0);
}

TEST(RollingProdTest, AllOnes) {
    // Alles Einsen: [1, 1, 1, 1]
    // 1 × 1 × 1 × 1 = 1
    vector<float> input = {1, 1, 1, 1};
    float result = rolling_prod(input);

    EXPECT_FLOAT_EQ(result, 1.0);
}

TEST(RollingProdTest, DecimalNumbers) {
    // Dezimalzahlen: [0.5, 2.0, 4.0]
    // 0.5 × 2.0 × 4.0 = 4.0
    vector<float> input = {0.5, 2.0, 4.0};
    float result = rolling_prod(input);

    EXPECT_FLOAT_EQ(result, 4.0);
}

TEST(RollingProdTest, LargerSequence) {
    // Längere Folge: [1, 2, 3, 4, 5]
    // 1 × 2 × 3 × 4 × 5 = 120
    vector<float> input = {1, 2, 3, 4, 5};
    float result = rolling_prod(input);

    EXPECT_FLOAT_EQ(result, 120.0);
}

// ========== Product (rollendes Produkt) Tests ==========

TEST(ProductTest, BasicTest) {
    // Eingabedaten: [1, 2, 3, 4, 5]
    // Ausgabe bei window=3: [NaN, NaN, 6, 24, 60]
    // Erklärung: 6=1×2×3, 24=2×3×4, 60=3×4×5
    vector<float> input = {1, 2, 3, 4, 5};
    vector<float> result = product(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 6.0);   // 1×2×3
    EXPECT_FLOAT_EQ(result[3], 24.0);  // 2×3×4
    EXPECT_FLOAT_EQ(result[4], 60.0);  // 3×4×5
}

TEST(ProductTest, WindowTwo) {
    // [2, 3, 4, 5], window=2
    // Ausgabe: [NaN, 6, 12, 20]
    vector<float> input = {2, 3, 4, 5};
    vector<float> result = product(input, 2);

    ASSERT_EQ(result.size(), 4);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_FLOAT_EQ(result[1], 6.0);   // 2×3
    EXPECT_FLOAT_EQ(result[2], 12.0);  // 3×4
    EXPECT_FLOAT_EQ(result[3], 20.0);  // 4×5
}

TEST(ProductTest, WithZero) {
    // Produkt mit 0: [1, 2, 0, 3, 4], window=3
    // [NaN, NaN, 0, 0, 0]
    vector<float> input = {1, 2, 0, 3, 4};
    vector<float> result = product(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 0.0);  // 1×2×0
    EXPECT_FLOAT_EQ(result[3], 0.0);  // 2×0×3
    EXPECT_FLOAT_EQ(result[4], 0.0);  // 0×3×4
}

TEST(ProductTest, WithNegatives) {
    // Mit negativen Zahlen: [2, -3, 4, -1], window=2
    // [NaN, -6, -12, -4]
    vector<float> input = {2, -3, 4, -1};
    vector<float> result = product(input, 2);

    ASSERT_EQ(result.size(), 4);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_FLOAT_EQ(result[1], -6.0);   // 2×(-3)
    EXPECT_FLOAT_EQ(result[2], -12.0);  // (-3)×4
    EXPECT_FLOAT_EQ(result[3], -4.0);   // 4×(-1)
}

TEST(ProductTest, WindowOne) {
    // Bei window=1 soll die Ausgabe gleich der Eingabe sein
    vector<float> input = {5, 10, 15, 20};
    vector<float> result = product(input, 1);

    ASSERT_EQ(result.size(), 4);
    EXPECT_FLOAT_EQ(result[0], 5.0);
    EXPECT_FLOAT_EQ(result[1], 10.0);
    EXPECT_FLOAT_EQ(result[2], 15.0);
    EXPECT_FLOAT_EQ(result[3], 20.0);
}

TEST(ProductTest, LargerWindow) {
    // [1, 2, 3, 4, 5, 6], window=4
    // [NaN, NaN, NaN, 24, 120, 360]
    // 24=1×2×3×4, 120=2×3×4×5, 360=3×4×5×6
    vector<float> input = {1, 2, 3, 4, 5, 6};
    vector<float> result = product(input, 4);

    ASSERT_EQ(result.size(), 6);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_TRUE(isnan(result[2]));
    EXPECT_FLOAT_EQ(result[3], 24.0);   // 1×2×3×4
    EXPECT_FLOAT_EQ(result[4], 120.0);  // 2×3×4×5
    EXPECT_FLOAT_EQ(result[5], 360.0);  // 3×4×5×6
}

TEST(ProductTest, AllOnes) {
    // Alles Einsen: [1, 1, 1, 1, 1], window=3
    // [NaN, NaN, 1, 1, 1]
    vector<float> input = {1, 1, 1, 1, 1};
    vector<float> result = product(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 1.0);
    EXPECT_FLOAT_EQ(result[3], 1.0);
    EXPECT_FLOAT_EQ(result[4], 1.0);
}

TEST(ProductTest, DecimalNumbers) {
    // Dezimalzahlen: [0.5, 2.0, 4.0, 0.5], window=2
    // [NaN, 1.0, 8.0, 2.0]
    vector<float> input = {0.5, 2.0, 4.0, 0.5};
    vector<float> result = product(input, 2);

    ASSERT_EQ(result.size(), 4);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_FLOAT_EQ(result[1], 1.0);  // 0.5×2.0
    EXPECT_FLOAT_EQ(result[2], 8.0);  // 2.0×4.0
    EXPECT_FLOAT_EQ(result[3], 2.0);  // 4.0×0.5
}

// ========== TS Min (rollendes Minimum) Tests ==========

TEST(TsMinTest, BasicTest) {
    // Eingabedaten: [5, 3, 8, 2, 6]
    // Ausgabe bei window=3: [NaN, NaN, 3, 2, 2]
    // Erklärung: min([5,3,8])=3, min([3,8,2])=2, min([8,2,6])=2
    vector<float> input = {5, 3, 8, 2, 6};
    vector<float> result = ts_min(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 3.0);  // min([5,3,8])
    EXPECT_FLOAT_EQ(result[3], 2.0);  // min([3,8,2])
    EXPECT_FLOAT_EQ(result[4], 2.0);  // min([8,2,6])
}

TEST(TsMinTest, MonotonicIncreasing) {
    // Monoton steigende Folge: [1, 2, 3, 4, 5], window=3
    // Das Minimum jedes Fensters ist das erste Element
    // [NaN, NaN, 1, 2, 3]
    vector<float> input = {1, 2, 3, 4, 5};
    vector<float> result = ts_min(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 1.0);  // min([1,2,3])
    EXPECT_FLOAT_EQ(result[3], 2.0);  // min([2,3,4])
    EXPECT_FLOAT_EQ(result[4], 3.0);  // min([3,4,5])
}

TEST(TsMinTest, MonotonicDecreasing) {
    // Monoton fallende Folge: [10, 8, 6, 4, 2], window=3
    // Das Minimum jedes Fensters ist das letzte Element
    // [NaN, NaN, 6, 4, 2]
    vector<float> input = {10, 8, 6, 4, 2};
    vector<float> result = ts_min(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 6.0);  // min([10,8,6])
    EXPECT_FLOAT_EQ(result[3], 4.0);  // min([8,6,4])
    EXPECT_FLOAT_EQ(result[4], 2.0);  // min([6,4,2])
}

TEST(TsMinTest, WithNegatives) {
    // Mit negativen Zahlen: [3, -1, 5, -2, 4], window=3
    // [NaN, NaN, -1, -2, -2]
    vector<float> input = {3, -1, 5, -2, 4};
    vector<float> result = ts_min(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], -1.0);  // min([3,-1,5])
    EXPECT_FLOAT_EQ(result[3], -2.0);  // min([-1,5,-2])
    EXPECT_FLOAT_EQ(result[4], -2.0);  // min([5,-2,4])
}

TEST(TsMinTest, WindowOne) {
    // Bei window=1 soll die Ausgabe gleich der Eingabe sein
    vector<float> input = {5, 10, 3, 8};
    vector<float> result = ts_min(input, 1);

    ASSERT_EQ(result.size(), 4);
    EXPECT_FLOAT_EQ(result[0], 5.0);
    EXPECT_FLOAT_EQ(result[1], 10.0);
    EXPECT_FLOAT_EQ(result[2], 3.0);
    EXPECT_FLOAT_EQ(result[3], 8.0);
}

TEST(TsMinTest, WindowTwo) {
    // [7, 2, 9, 3, 5], window=2
    // [NaN, 2, 2, 3, 3]
    vector<float> input = {7, 2, 9, 3, 5};
    vector<float> result = ts_min(input, 2);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_FLOAT_EQ(result[1], 2.0);  // min([7,2])
    EXPECT_FLOAT_EQ(result[2], 2.0);  // min([2,9])
    EXPECT_FLOAT_EQ(result[3], 3.0);  // min([9,3])
    EXPECT_FLOAT_EQ(result[4], 3.0);  // min([3,5])
}

TEST(TsMinTest, AllSameValues) {
    // Alle Werte gleich: [5, 5, 5, 5], window=3
    // [NaN, NaN, 5, 5]
    vector<float> input = {5, 5, 5, 5};
    vector<float> result = ts_min(input, 3);

    ASSERT_EQ(result.size(), 4);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 5.0);
    EXPECT_FLOAT_EQ(result[3], 5.0);
}

TEST(TsMinTest, LargerWindow) {
    // [8, 3, 9, 1, 6, 4], window=4
    // [NaN, NaN, NaN, 1, 1, 1]
    vector<float> input = {8, 3, 9, 1, 6, 4};
    vector<float> result = ts_min(input, 4);

    ASSERT_EQ(result.size(), 6);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_TRUE(isnan(result[2]));
    EXPECT_FLOAT_EQ(result[3], 1.0);  // min([8,3,9,1])
    EXPECT_FLOAT_EQ(result[4], 1.0);  // min([3,9,1,6])
    EXPECT_FLOAT_EQ(result[5], 1.0);  // min([9,1,6,4])
}

TEST(TsMinTest, DecimalNumbers) {
    // Dezimalzahlen: [2.5, 1.2, 3.7, 0.9], window=3
    // [NaN, NaN, 1.2, 0.9]
    vector<float> input = {2.5, 1.2, 3.7, 0.9};
    vector<float> result = ts_min(input, 3);

    ASSERT_EQ(result.size(), 4);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_NEAR(result[2], 1.2, 1e-5);  // min([2.5,1.2,3.7])
    EXPECT_NEAR(result[3], 0.9, 1e-5);  // min([1.2,3.7,0.9])
}

// ========== TS Max (rollendes Maximum) Tests ==========

TEST(TsMaxTest, BasicTest) {
    // Eingabedaten: [5, 3, 8, 2, 6]
    // Ausgabe bei window=3: [NaN, NaN, 8, 8, 8]
    // Erklärung: max([5,3,8])=8, max([3,8,2])=8, max([8,2,6])=8
    vector<float> input = {5, 3, 8, 2, 6};
    vector<float> result = ts_max(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 8.0);  // max([5,3,8])
    EXPECT_FLOAT_EQ(result[3], 8.0);  // max([3,8,2])
    EXPECT_FLOAT_EQ(result[4], 8.0);  // max([8,2,6])
}

TEST(TsMaxTest, MonotonicIncreasing) {
    // Monoton steigende Folge: [1, 2, 3, 4, 5], window=3
    // Das Maximum jedes Fensters ist das letzte Element
    // [NaN, NaN, 3, 4, 5]
    vector<float> input = {1, 2, 3, 4, 5};
    vector<float> result = ts_max(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 3.0);  // max([1,2,3])
    EXPECT_FLOAT_EQ(result[3], 4.0);  // max([2,3,4])
    EXPECT_FLOAT_EQ(result[4], 5.0);  // max([3,4,5])
}

TEST(TsMaxTest, MonotonicDecreasing) {
    // Monoton fallende Folge: [10, 8, 6, 4, 2], window=3
    // Das Maximum jedes Fensters ist das erste Element
    // [NaN, NaN, 10, 8, 6]
    vector<float> input = {10, 8, 6, 4, 2};
    vector<float> result = ts_max(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 10.0);  // max([10,8,6])
    EXPECT_FLOAT_EQ(result[3], 8.0);   // max([8,6,4])
    EXPECT_FLOAT_EQ(result[4], 6.0);   // max([6,4,2])
}

TEST(TsMaxTest, WithNegatives) {
    // Mit negativen Zahlen: [3, -1, 5, -2, 4], window=3
    // [NaN, NaN, 5, 5, 5]
    vector<float> input = {3, -1, 5, -2, 4};
    vector<float> result = ts_max(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 5.0);  // max([3,-1,5])
    EXPECT_FLOAT_EQ(result[3], 5.0);  // max([-1,5,-2])
    EXPECT_FLOAT_EQ(result[4], 5.0);  // max([5,-2,4])
}

TEST(TsMaxTest, WindowOne) {
    // Bei window=1 soll die Ausgabe gleich der Eingabe sein
    vector<float> input = {5, 10, 3, 8};
    vector<float> result = ts_max(input, 1);

    ASSERT_EQ(result.size(), 4);
    EXPECT_FLOAT_EQ(result[0], 5.0);
    EXPECT_FLOAT_EQ(result[1], 10.0);
    EXPECT_FLOAT_EQ(result[2], 3.0);
    EXPECT_FLOAT_EQ(result[3], 8.0);
}

TEST(TsMaxTest, WindowTwo) {
    // [7, 2, 9, 3, 5], window=2
    // [NaN, 7, 9, 9, 5]
    vector<float> input = {7, 2, 9, 3, 5};
    vector<float> result = ts_max(input, 2);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_FLOAT_EQ(result[1], 7.0);  // max([7,2])
    EXPECT_FLOAT_EQ(result[2], 9.0);  // max([2,9])
    EXPECT_FLOAT_EQ(result[3], 9.0);  // max([9,3])
    EXPECT_FLOAT_EQ(result[4], 5.0);  // max([3,5])
}

TEST(TsMaxTest, AllSameValues) {
    // Alle Werte gleich: [5, 5, 5, 5], window=3
    // [NaN, NaN, 5, 5]
    vector<float> input = {5, 5, 5, 5};
    vector<float> result = ts_max(input, 3);

    ASSERT_EQ(result.size(), 4);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 5.0);
    EXPECT_FLOAT_EQ(result[3], 5.0);
}

TEST(TsMaxTest, LargerWindow) {
    // [8, 3, 9, 1, 6, 4], window=4
    // [NaN, NaN, NaN, 9, 9, 9]
    vector<float> input = {8, 3, 9, 1, 6, 4};
    vector<float> result = ts_max(input, 4);

    ASSERT_EQ(result.size(), 6);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_TRUE(isnan(result[2]));
    EXPECT_FLOAT_EQ(result[3], 9.0);  // max([8,3,9,1])
    EXPECT_FLOAT_EQ(result[4], 9.0);  // max([3,9,1,6])
    EXPECT_FLOAT_EQ(result[5], 9.0);  // max([9,1,6,4])
}

TEST(TsMaxTest, DecimalNumbers) {
    // Dezimalzahlen: [2.5, 1.2, 3.7, 0.9], window=3
    // [NaN, NaN, 3.7, 3.7]
    vector<float> input = {2.5, 1.2, 3.7, 0.9};
    vector<float> result = ts_max(input, 3);

    ASSERT_EQ(result.size(), 4);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_NEAR(result[2], 3.7, 1e-5);  // max([2.5,1.2,3.7])
    EXPECT_NEAR(result[3], 3.7, 1e-5);  // max([1.2,3.7,0.9])
}

TEST(TsMaxTest, ZigzagPattern) {
    // Zickzack-Muster: [1, 5, 2, 6, 3], window=3
    // [NaN, NaN, 5, 6, 6]
    vector<float> input = {1, 5, 2, 6, 3};
    vector<float> result = ts_max(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 5.0);  // max([1,5,2])
    EXPECT_FLOAT_EQ(result[3], 6.0);  // max([5,2,6])
    EXPECT_FLOAT_EQ(result[4], 6.0);  // max([2,6,3])
}

// ========== Delta (Differenz) Tests ==========

TEST(DeltaTest, BasicTest) {
    // Eingabedaten: [10, 12, 15, 13, 18]
    // Ausgabe bei period=1: [NaN, 2, 3, -2, 5]
    // Erklärung: 12-10=2, 15-12=3, 13-15=-2, 18-13=5
    vector<float> input = {10, 12, 15, 13, 18};
    vector<float> result = delta(input, 1);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_FLOAT_EQ(result[1], 2.0);   // 12-10
    EXPECT_FLOAT_EQ(result[2], 3.0);   // 15-12
    EXPECT_FLOAT_EQ(result[3], -2.0);  // 13-15
    EXPECT_FLOAT_EQ(result[4], 5.0);   // 18-13
}

TEST(DeltaTest, PeriodTwo) {
    // Eingabedaten: [10, 12, 15, 13, 18, 20]
    // Ausgabe bei period=2: [NaN, NaN, 5, 1, 3, 7]
    // Erklärung: 15-10=5, 13-12=1, 18-15=3, 20-13=7
    vector<float> input = {10, 12, 15, 13, 18, 20};
    vector<float> result = delta(input, 2);

    ASSERT_EQ(result.size(), 6);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 5.0);  // 15-10
    EXPECT_FLOAT_EQ(result[3], 1.0);  // 13-12
    EXPECT_FLOAT_EQ(result[4], 3.0);  // 18-15
    EXPECT_FLOAT_EQ(result[5], 7.0);  // 20-13
}

TEST(DeltaTest, LargerPeriod) {
    // period=3: [NaN, NaN, NaN, 3, 6, 8]
    vector<float> input = {10, 12, 15, 13, 18, 23};
    vector<float> result = delta(input, 3);

    ASSERT_EQ(result.size(), 6);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_TRUE(isnan(result[2]));
    EXPECT_FLOAT_EQ(result[3], 3.0);  // 13-10
    EXPECT_FLOAT_EQ(result[4], 6.0);  // 18-12
    EXPECT_FLOAT_EQ(result[5], 8.0);  // 23-15
}

TEST(DeltaTest, WithNegatives) {
    // Mit negativen Zahlen: [5, 2, -3, 1, -2]
    // period=1: [NaN, -3, -5, 4, -3]
    vector<float> input = {5, 2, -3, 1, -2};
    vector<float> result = delta(input, 1);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_FLOAT_EQ(result[1], -3.0);  // 2-5
    EXPECT_FLOAT_EQ(result[2], -5.0);  // -3-2
    EXPECT_FLOAT_EQ(result[3], 4.0);   // 1-(-3)
    EXPECT_FLOAT_EQ(result[4], -3.0);  // -2-1
}

TEST(DeltaTest, MonotonicIncreasing) {
    // Monoton steigend: [1, 2, 3, 4, 5]
    // period=1: [NaN, 1, 1, 1, 1]
    vector<float> input = {1, 2, 3, 4, 5};
    vector<float> result = delta(input, 1);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_FLOAT_EQ(result[1], 1.0);
    EXPECT_FLOAT_EQ(result[2], 1.0);
    EXPECT_FLOAT_EQ(result[3], 1.0);
    EXPECT_FLOAT_EQ(result[4], 1.0);
}

TEST(DeltaTest, MonotonicDecreasing) {
    // Monoton fallend: [10, 8, 6, 4, 2]
    // period=1: [NaN, -2, -2, -2, -2]
    vector<float> input = {10, 8, 6, 4, 2};
    vector<float> result = delta(input, 1);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_FLOAT_EQ(result[1], -2.0);
    EXPECT_FLOAT_EQ(result[2], -2.0);
    EXPECT_FLOAT_EQ(result[3], -2.0);
    EXPECT_FLOAT_EQ(result[4], -2.0);
}

TEST(DeltaTest, AllSameValues) {
    // Alle Werte gleich: [5, 5, 5, 5]
    // period=1: [NaN, 0, 0, 0]
    vector<float> input = {5, 5, 5, 5};
    vector<float> result = delta(input, 1);

    ASSERT_EQ(result.size(), 4);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_FLOAT_EQ(result[1], 0.0);
    EXPECT_FLOAT_EQ(result[2], 0.0);
    EXPECT_FLOAT_EQ(result[3], 0.0);
}

TEST(DeltaTest, DecimalNumbers) {
    // Dezimalzahlen: [10.5, 12.3, 15.7, 13.2]
    // period=1: [NaN, 1.8, 3.4, -2.5]
    vector<float> input = {10.5, 12.3, 15.7, 13.2};
    vector<float> result = delta(input, 1);

    ASSERT_EQ(result.size(), 4);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_NEAR(result[1], 1.8, 1e-5);   // 12.3-10.5
    EXPECT_NEAR(result[2], 3.4, 1e-5);   // 15.7-12.3
    EXPECT_NEAR(result[3], -2.5, 1e-5);  // 13.2-15.7
}

TEST(DeltaTest, ZeroChange) {
    // Mit gleichen aufeinanderfolgenden Werten: [10, 10, 15, 15, 20]
    // period=1: [NaN, 0, 5, 0, 5]
    vector<float> input = {10, 10, 15, 15, 20};
    vector<float> result = delta(input, 1);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_FLOAT_EQ(result[1], 0.0);  // 10-10
    EXPECT_FLOAT_EQ(result[2], 5.0);  // 15-10
    EXPECT_FLOAT_EQ(result[3], 0.0);  // 15-15
    EXPECT_FLOAT_EQ(result[4], 5.0);  // 20-15
}

// ========== Delay (Verzögerung) Tests ==========

TEST(DelayTest, BasicTest) {
    // Eingabedaten: [10, 12, 15, 13, 18]
    // Ausgabe bei period=1: [NaN, 10, 12, 15, 13]
    // Erklärung: Jeder Wert ist der Wert des Vortages
    vector<float> input = {10, 12, 15, 13, 18};
    vector<float> result = delay(input, 1);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_FLOAT_EQ(result[1], 10.0);  // delay 1: input[0]
    EXPECT_FLOAT_EQ(result[2], 12.0);  // delay 1: input[1]
    EXPECT_FLOAT_EQ(result[3], 15.0);  // delay 1: input[2]
    EXPECT_FLOAT_EQ(result[4], 13.0);  // delay 1: input[3]
}

TEST(DelayTest, PeriodTwo) {
    // Eingabedaten: [10, 12, 15, 13, 18, 20]
    // Ausgabe bei period=2: [NaN, NaN, 10, 12, 15, 13]
    // Erklärung: Jeder Wert ist der Wert vor zwei Tagen
    vector<float> input = {10, 12, 15, 13, 18, 20};
    vector<float> result = delay(input, 2);

    ASSERT_EQ(result.size(), 6);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 10.0);  // delay 2: input[0]
    EXPECT_FLOAT_EQ(result[3], 12.0);  // delay 2: input[1]
    EXPECT_FLOAT_EQ(result[4], 15.0);  // delay 2: input[2]
    EXPECT_FLOAT_EQ(result[5], 13.0);  // delay 2: input[3]
}

TEST(DelayTest, LargerPeriod) {
    // period=3: [NaN, NaN, NaN, 10, 12, 15]
    vector<float> input = {10, 12, 15, 13, 18, 23};
    vector<float> result = delay(input, 3);

    ASSERT_EQ(result.size(), 6);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_TRUE(isnan(result[2]));
    EXPECT_FLOAT_EQ(result[3], 10.0);  // delay 3: input[0]
    EXPECT_FLOAT_EQ(result[4], 12.0);  // delay 3: input[1]
    EXPECT_FLOAT_EQ(result[5], 15.0);  // delay 3: input[2]
}

TEST(DelayTest, WithNegatives) {
    // Mit negativen Zahlen: [5, -2, 8, -3, 10]
    // period=1: [NaN, 5, -2, 8, -3]
    vector<float> input = {5, -2, 8, -3, 10};
    vector<float> result = delay(input, 1);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_FLOAT_EQ(result[1], 5.0);
    EXPECT_FLOAT_EQ(result[2], -2.0);
    EXPECT_FLOAT_EQ(result[3], 8.0);
    EXPECT_FLOAT_EQ(result[4], -3.0);
}

TEST(DelayTest, MonotonicIncreasing) {
    // Monoton steigend: [1, 2, 3, 4, 5]
    // period=1: [NaN, 1, 2, 3, 4]
    vector<float> input = {1, 2, 3, 4, 5};
    vector<float> result = delay(input, 1);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_FLOAT_EQ(result[1], 1.0);
    EXPECT_FLOAT_EQ(result[2], 2.0);
    EXPECT_FLOAT_EQ(result[3], 3.0);
    EXPECT_FLOAT_EQ(result[4], 4.0);
}

TEST(DelayTest, AllSameValues) {
    // Alle Werte gleich: [5, 5, 5, 5]
    // period=1: [NaN, 5, 5, 5]
    vector<float> input = {5, 5, 5, 5};
    vector<float> result = delay(input, 1);

    ASSERT_EQ(result.size(), 4);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_FLOAT_EQ(result[1], 5.0);
    EXPECT_FLOAT_EQ(result[2], 5.0);
    EXPECT_FLOAT_EQ(result[3], 5.0);
}

TEST(DelayTest, DecimalNumbers) {
    // Dezimalzahlen: [10.5, 12.3, 15.7, 13.2]
    // period=1: [NaN, 10.5, 12.3, 15.7]
    vector<float> input = {10.5, 12.3, 15.7, 13.2};
    vector<float> result = delay(input, 1);

    ASSERT_EQ(result.size(), 4);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_NEAR(result[1], 10.5, 1e-5);
    EXPECT_NEAR(result[2], 12.3, 1e-5);
    EXPECT_NEAR(result[3], 15.7, 1e-5);
}

TEST(DelayTest, ZeroValues) {
    // Mit 0-Werten: [10, 0, 15, 0, 20]
    // period=1: [NaN, 10, 0, 15, 0]
    vector<float> input = {10, 0, 15, 0, 20};
    vector<float> result = delay(input, 1);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_FLOAT_EQ(result[1], 10.0);
    EXPECT_FLOAT_EQ(result[2], 0.0);
    EXPECT_FLOAT_EQ(result[3], 15.0);
    EXPECT_FLOAT_EQ(result[4], 0.0);
}

TEST(DelayTest, LargePeriod) {
    // Bei period=5 sind die ersten 5 Elemente NaN
    vector<float> input = {1, 2, 3, 4, 5, 6, 7, 8};
    vector<float> result = delay(input, 5);

    ASSERT_EQ(result.size(), 8);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_TRUE(isnan(result[2]));
    EXPECT_TRUE(isnan(result[3]));
    EXPECT_TRUE(isnan(result[4]));
    EXPECT_FLOAT_EQ(result[5], 1.0);  // input[0]
    EXPECT_FLOAT_EQ(result[6], 2.0);  // input[1]
    EXPECT_FLOAT_EQ(result[7], 3.0);  // input[2]
}

// ========== Rolling SMA Tests ==========

TEST(RollingSmaTest, BasicTest) {
    vector<float> input = {2, 4, 6, 8, 10};
    vector<float> result = rolling_sma(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 4);
    EXPECT_FLOAT_EQ(result[3], 6);
    EXPECT_FLOAT_EQ(result[4], 8);
}

TEST(RollingSmaTest, WindowTwo) {
    vector<float> input = {10, 20, 30, 40, 50};
    vector<float> result = rolling_sma(input, 2);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_FLOAT_EQ(result[1], 15);
    EXPECT_FLOAT_EQ(result[2], 25);
    EXPECT_FLOAT_EQ(result[3], 35);
    EXPECT_FLOAT_EQ(result[4], 45);
}

// ========== Rolling Stddev Tests ==========

TEST(RollingStddevTest, BasicTest) {
    vector<float> input = {1, 2, 3, 4, 5};
    vector<float> result = rolling_stddev(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_NEAR(result[2], 1.0, 1e-5);
    EXPECT_NEAR(result[3], 1.0, 1e-5);
    EXPECT_NEAR(result[4], 1.0, 1e-5);
}

// ========== Rolling Correlation Tests ==========

TEST(RollingCorrelationTest, PositiveCorrelation) {
    // y = 2x, vollständige positive Korrelation
    vector<float> x = {1, 2, 3, 4, 5};
    vector<float> y = {2, 4, 6, 8, 10};
    vector<float> result = rolling_correlation(x, y, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_NEAR(result[2], 1.0, 1e-5);
    EXPECT_NEAR(result[3], 1.0, 1e-5);
    EXPECT_NEAR(result[4], 1.0, 1e-5);
}

TEST(RollingCorrelationTest, NegativeCorrelation) {
    // Negative Korrelation
    vector<float> x = {1, 2, 3, 4, 5};
    vector<float> y = {10, 8, 6, 4, 2};
    vector<float> result = rolling_correlation(x, y, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_NEAR(result[2], -1.0, 1e-5);
    EXPECT_NEAR(result[3], -1.0, 1e-5);
    EXPECT_NEAR(result[4], -1.0, 1e-5);
}

TEST(RollingCorrelationTest, ManualVerification) {
    // Manuelle Verifikation: Mittelwert x̄=2, ȳ=4
    // Abweichung x: [-1, 0, 1], Abweichung y: [-2, 0, 2]
    // Korrelationskoeffizient: 4 / √(2×8) = 1.0
    vector<float> x = {1, 2, 3};
    vector<float> y = {2, 4, 6};
    vector<float> result = rolling_correlation(x, y, 3);

    ASSERT_EQ(result.size(), 3);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_NEAR(result[2], 1.0, 1e-5);
}

// ========== Rolling Covariance Tests ==========

TEST(RollingCovarianceTest, BasicTest) {
    vector<float> x = {1, 2, 3, 4, 5};
    vector<float> y = {2, 4, 6, 8, 10};
    vector<float> result = rolling_covariance(x, y, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_NEAR(result[2], 2.0, 1e-5);
    EXPECT_NEAR(result[3], 2.0, 1e-5);
    EXPECT_NEAR(result[4], 2.0, 1e-5);
}

TEST(RollingCovarianceTest, ManualVerification) {
    // Mittelwert: x̄=2, ȳ=4
    // Abweichung: x=[-1,0,1], y=[-2,0,2]
    // Abweichungsprodukt: [2,0,2]
    // Kovarianz: (2+0+2)/(3-1) = 2.0
    vector<float> x = {1, 2, 3};
    vector<float> y = {2, 4, 6};
    vector<float> result = rolling_covariance(x, y, 3);

    ASSERT_EQ(result.size(), 3);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_NEAR(result[2], 2.0, 1e-5);
}

TEST(RollingCovarianceTest, NegativeCovariance) {
    vector<float> x = {1, 2, 3, 4, 5};
    vector<float> y = {10, 8, 6, 4, 2};
    vector<float> result = rolling_covariance(x, y, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_NEAR(result[2], -2.0, 1e-5);
    EXPECT_NEAR(result[3], -2.0, 1e-5);
    EXPECT_NEAR(result[4], -2.0, 1e-5);
}

// ========== Rolling Rank Tests ==========

TEST(RollingRankTest, BasicTest) {
    // Eingabe-Array: [3, 1, 4, 2, 5]
    // Nach Sortierung: [1, 2, 3, 4, 5]
    // Letzter Wert 5 an Position 4, Rang=5
    vector<float> input = {3, 1, 4, 2, 5};
    float result = rolling_rank(input);

    EXPECT_FLOAT_EQ(result, 5.0);
}

TEST(RollingRankTest, LowestValue) {
    // Fenster [100, 102, 98]: 98 ist der kleinste Wert, Rang 1
    vector<float> input = {100, 102, 98};
    float result = rolling_rank(input);

    EXPECT_FLOAT_EQ(result, 1.0);
}

TEST(RollingRankTest, HighestValue) {
    // Fenster [102, 98, 105]: 105 ist der größte Wert, Rang 3
    vector<float> input = {102, 98, 105};
    float result = rolling_rank(input);

    EXPECT_FLOAT_EQ(result, 3.0);
}

TEST(RollingRankTest, MiddleValue) {
    // [5, 1, 3, 2, 4], letzter Wert 4, nach Sortierung [1,2,3,4,5], 4 belegt Rang 4
    vector<float> input = {5, 1, 3, 2, 4};
    float result = rolling_rank(input);

    EXPECT_FLOAT_EQ(result, 4.0);
}

TEST(RollingRankTest, SingleElement) {
    // Einzelnes Element, Rang = 1
    vector<float> input = {42};
    float result = rolling_rank(input);

    EXPECT_FLOAT_EQ(result, 1.0);
}

TEST(RollingRankTest, DuplicateValues) {
    // [1, 2, 2, 3], letzter Wert 3, nach Sortierung [1,2,2,3], 3 belegt Rang 4
    vector<float> input = {1, 2, 2, 3};
    float result = rolling_rank(input);

    EXPECT_FLOAT_EQ(result, 4.0);
}

TEST(RollingRankTest, DuplicateLastValue) {
    // [1, 3, 2, 3, 3], letzter Wert 3
    // Nach Sortierung: [1, 2, 3, 3, 3]
    // Drei 3er belegen Plätze 3,4,5, Durchschnittsrang=(3+4+5)/3=4.0
    vector<float> input = {1, 3, 2, 3, 3};
    float result = rolling_rank(input);

    EXPECT_FLOAT_EQ(result, 4.0);
}

TEST(RollingRankTest, AllSameValues) {
    // [5, 5, 5, 5], alle Werte gleich
    // belegen Plätze 1,2,3,4, Durchschnittsrang=(1+2+3+4)/4=2.5
    vector<float> input = {5, 5, 5, 5};
    float result = rolling_rank(input);

    EXPECT_FLOAT_EQ(result, 2.5);
}

TEST(RollingRankTest, TwoDuplicates) {
    // [1, 2, 3, 2], letzter Wert 2
    // Nach Sortierung: [1, 2, 2, 3]
    // Zwei 2er belegen Plätze 2,3, Durchschnittsrang=(2+3)/2=2.5
    vector<float> input = {1, 2, 3, 2};
    float result = rolling_rank(input);

    EXPECT_FLOAT_EQ(result, 2.5);
}

// ========== TS Rank Tests ==========

TEST(TsRankTest, BasicTest) {
    // Eingabedaten: [1, 5, 3, 7, 2]
    // Ausgabe bei window=3: [NaN, NaN, 2.0, 3.0, 1.0]
    // Erklärung: In [1,5,3] belegt 3 Rang 2, in [5,3,7] belegt 7 Rang 3, in [3,7,2] belegt 2 Rang 1
    vector<float> input = {1, 5, 3, 7, 2};
    vector<float> result = ts_rank(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 2.0);  // [1,5,3]: 3 belegt Rang 2
    EXPECT_FLOAT_EQ(result[3], 3.0);  // [5,3,7]: 7 belegt Rang 3 (Maximum)
    EXPECT_FLOAT_EQ(result[4], 1.0);  // [3,7,2]: 2 belegt Rang 1 (Minimum)
}

TEST(TsRankTest, MonotonicIncreasing) {
    // Monoton steigende Folge
    // [1, 2, 3, 4, 5], window=3
    // Der letzte Wert jedes Fensters ist der größte, Rang ist immer 3
    vector<float> input = {1, 2, 3, 4, 5};
    vector<float> result = ts_rank(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 3.0);  // [1,2,3]: 3 belegt Rang 3
    EXPECT_FLOAT_EQ(result[3], 3.0);  // [2,3,4]: 4 belegt Rang 3
    EXPECT_FLOAT_EQ(result[4], 3.0);  // [3,4,5]: 5 belegt Rang 3
}

TEST(TsRankTest, MonotonicDecreasing) {
    // Monoton fallende Folge
    // [5, 4, 3, 2, 1], window=3
    // Der letzte Wert jedes Fensters ist der kleinste, Rang ist immer 1
    vector<float> input = {5, 4, 3, 2, 1};
    vector<float> result = ts_rank(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 1.0);  // [5,4,3]: 3 belegt Rang 1
    EXPECT_FLOAT_EQ(result[3], 1.0);  // [4,3,2]: 2 belegt Rang 1
    EXPECT_FLOAT_EQ(result[4], 1.0);  // [3,2,1]: 1 belegt Rang 1
}

TEST(TsRankTest, PriceSequenceExample) {
    // Kursfolge: [100, 102, 98, 105, 103]
    // window=3
    vector<float> input = {100, 102, 98, 105, 103};
    vector<float> result = ts_rank(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 1.0);  // [100,102,98]: 98 belegt Rang 1 (überverkauft)
    EXPECT_FLOAT_EQ(result[3], 3.0);  // [102,98,105]: 105 belegt Rang 3 (überkauft)
    EXPECT_FLOAT_EQ(result[4], 2.0);  // [98,105,103]: 103 belegt Rang 2 (mittel)
}

TEST(TsRankTest, WithDuplicates) {
    // Mit Duplikaten
    // [1, 3, 2, 3, 3], window=3
    vector<float> input = {1, 3, 2, 3, 3};
    vector<float> result = ts_rank(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 2.0);  // [1,3,2]: 2 belegt Rang 2
    EXPECT_FLOAT_EQ(result[3], 2.5);  // [3,2,3]: nach Sortierung [2,3,3], Durchschnittsrang von 3=(2+3)/2=2.5
    EXPECT_FLOAT_EQ(result[4], 2.5);  // [2,3,3]: nach Sortierung [2,3,3], Durchschnittsrang von 3=(2+3)/2=2.5
}

// ========== TS Rank Optimized Tests ==========

TEST(TsRankOptimizedTest, BasicTest) {
    // Überprüfen, ob optimierte und Originalversion gleiche Ergebnisse liefern
    vector<float> input = {1, 5, 3, 7, 2};
    vector<float> result_original = ts_rank(input, 3);
    vector<float> result_optimized = ts_rank_optimized(input, 3);

    ASSERT_EQ(result_original.size(), result_optimized.size());
    for (size_t i = 0; i < result_original.size(); ++i) {
        if (isnan(result_original[i])) {
            EXPECT_TRUE(isnan(result_optimized[i]));
        } else {
            EXPECT_FLOAT_EQ(result_original[i], result_optimized[i]);
        }
    }
}

TEST(TsRankOptimizedTest, LargeDataset) {
    // Größeren Datensatz testen
    vector<float> input;
    for (int i = 0; i < 1000; ++i) {
        input.push_back(i % 100);
    }

    vector<float> result_original = ts_rank(input, 20);
    vector<float> result_optimized = ts_rank_optimized(input, 20);

    ASSERT_EQ(result_original.size(), result_optimized.size());
    for (size_t i = 0; i < result_original.size(); ++i) {
        if (isnan(result_original[i])) {
            EXPECT_TRUE(isnan(result_optimized[i]));
        } else {
            EXPECT_FLOAT_EQ(result_original[i], result_optimized[i]);
        }
    }
}

TEST(TsRankOptimizedTest, WithDuplicates) {
    // Konsistenz der Duplikatbehandlung prüfen
    vector<float> input = {1, 3, 2, 3, 3};
    vector<float> result_original = ts_rank(input, 3);
    vector<float> result_optimized = ts_rank_optimized(input, 3);

    ASSERT_EQ(result_original.size(), result_optimized.size());
    for (size_t i = 0; i < result_original.size(); ++i) {
        if (isnan(result_original[i])) {
            EXPECT_TRUE(isnan(result_optimized[i]));
        } else {
            EXPECT_FLOAT_EQ(result_original[i], result_optimized[i]);
        }
    }
}

// ========== Rank (Querschnittsrang) Tests ==========

TEST(RankTest, BasicExample) {
    // Python-Docstring-Beispiel: [10, 50, 30, 20, 40]
    // Sortierung: 10 < 20 < 30 < 40 < 50
    // Regulärer Rang: [1, 5, 3, 2, 4]
    // Prozentrang: [0.2, 1.0, 0.6, 0.4, 0.8]
    vector<float> input = {10, 50, 30, 20, 40};
    vector<float> result = alpha_rank(input);

    ASSERT_EQ(result.size(), 5);
    EXPECT_FLOAT_EQ(result[0], 0.2);  // 10 kleinster -> 1/5
    EXPECT_FLOAT_EQ(result[1], 1.0);  // 50 größter -> 5/5
    EXPECT_FLOAT_EQ(result[2], 0.6);  // 30 mittel -> 3/5
    EXPECT_FLOAT_EQ(result[3], 0.4);  // 20 zweitkleinster -> 2/5
    EXPECT_FLOAT_EQ(result[4], 0.8);  // 40 zweitgrößter -> 4/5
}

TEST(RankTest, TwoDuplicates) {
    // Python-Docstring-Beispiel 1: [10, 30, 30, 20, 40]
    // Sortierung: 10(1) < 20(2) < 30(3,4) < 40(5)
    // Zwei 30er belegen Plätze 3 und 4, Durchschnittsrang = (3+4)/2 = 3.5
    // Prozentrang: [0.2, 0.7, 0.7, 0.4, 1.0]
    vector<float> input = {10, 30, 30, 20, 40};
    vector<float> result = alpha_rank(input);

    ASSERT_EQ(result.size(), 5);
    EXPECT_FLOAT_EQ(result[0], 0.2);  // 10 -> 1/5
    EXPECT_FLOAT_EQ(result[1], 0.7);  // 30 -> 3.5/5
    EXPECT_FLOAT_EQ(result[2], 0.7);  // 30 -> 3.5/5
    EXPECT_FLOAT_EQ(result[3], 0.4);  // 20 -> 2/5
    EXPECT_FLOAT_EQ(result[4], 1.0);  // 40 -> 5/5
}

TEST(RankTest, ThreeDuplicates) {
    // Python-Docstring-Beispiel 2: [10, 30, 30, 30, 40]
    // Sortierung: 10(1) < 30(2,3,4) < 40(5)
    // Drei 30er belegen Plätze 2,3,4, Durchschnittsrang = (2+3+4)/3 = 3.0
    // Prozentrang: [0.2, 0.6, 0.6, 0.6, 1.0]
    vector<float> input = {10, 30, 30, 30, 40};
    vector<float> result = alpha_rank(input);

    ASSERT_EQ(result.size(), 5);
    EXPECT_FLOAT_EQ(result[0], 0.2);  // 10 -> 1/5
    EXPECT_FLOAT_EQ(result[1], 0.6);  // 30 -> 3.0/5
    EXPECT_FLOAT_EQ(result[2], 0.6);  // 30 -> 3.0/5
    EXPECT_FLOAT_EQ(result[3], 0.6);  // 30 -> 3.0/5
    EXPECT_FLOAT_EQ(result[4], 1.0);  // 40 -> 5/5
}

TEST(RankTest, FourDuplicates) {
    // Python-Docstring-Beispiel 3: [50, 30, 30, 30, 30]
    // Sortierung: 30(1,2,3,4) < 50(5)
    // Vier 30er belegen Plätze 1,2,3,4, Durchschnittsrang = (1+2+3+4)/4 = 2.5
    // Prozentrang: [1.0, 0.5, 0.5, 0.5, 0.5]
    vector<float> input = {50, 30, 30, 30, 30};
    vector<float> result = alpha_rank(input);

    ASSERT_EQ(result.size(), 5);
    EXPECT_FLOAT_EQ(result[0], 1.0);  // 50 -> 5/5
    EXPECT_FLOAT_EQ(result[1], 0.5);  // 30 -> 2.5/5
    EXPECT_FLOAT_EQ(result[2], 0.5);  // 30 -> 2.5/5
    EXPECT_FLOAT_EQ(result[3], 0.5);  // 30 -> 2.5/5
    EXPECT_FLOAT_EQ(result[4], 0.5);  // 30 -> 2.5/5
}

TEST(RankTest, AllSameValues) {
    // Alle Werte gleich: [5, 5, 5, 5, 5]
    // belegen Plätze 1,2,3,4,5, Durchschnittsrang = (1+2+3+4+5)/5 = 3.0
    // Prozentrang: [0.6, 0.6, 0.6, 0.6, 0.6]
    vector<float> input = {5, 5, 5, 5, 5};
    vector<float> result = alpha_rank(input);

    ASSERT_EQ(result.size(), 5);
    EXPECT_FLOAT_EQ(result[0], 0.6);
    EXPECT_FLOAT_EQ(result[1], 0.6);
    EXPECT_FLOAT_EQ(result[2], 0.6);
    EXPECT_FLOAT_EQ(result[3], 0.6);
    EXPECT_FLOAT_EQ(result[4], 0.6);
}

TEST(RankTest, SingleElement) {
    // Einzelnes Element: [42]
    // Rang 1, Prozentanteil = 1/1 = 1.0
    vector<float> input = {42};
    vector<float> result = alpha_rank(input);

    ASSERT_EQ(result.size(), 1);
    EXPECT_FLOAT_EQ(result[0], 1.0);
}

TEST(RankTest, EmptyArray) {
    // Leeres Array
    vector<float> input = {};
    vector<float> result = alpha_rank(input);

    ASSERT_EQ(result.size(), 0);
}

TEST(RankTest, TwoElements) {
    // Zwei verschiedene Elemente: [10, 20]
    // Prozentrang: [0.5, 1.0]
    vector<float> input = {10, 20};
    vector<float> result = alpha_rank(input);

    ASSERT_EQ(result.size(), 2);
    EXPECT_FLOAT_EQ(result[0], 0.5);  // 10 -> 1/2
    EXPECT_FLOAT_EQ(result[1], 1.0);  // 20 -> 2/2
}

TEST(RankTest, TwoElementsSame) {
    // Zwei gleiche Elemente: [10, 10]
    // Durchschnittsrang = (1+2)/2 = 1.5
    // Prozentrang: [0.75, 0.75]
    vector<float> input = {10, 10};
    vector<float> result = alpha_rank(input);

    ASSERT_EQ(result.size(), 2);
    EXPECT_FLOAT_EQ(result[0], 0.75);  // 1.5/2
    EXPECT_FLOAT_EQ(result[1], 0.75);  // 1.5/2
}

TEST(RankTest, NegativeNumbers) {
    // Mit negativen Zahlen: [-10, 20, -5, 15, 0]
    // Sortierung: -10 < -5 < 0 < 15 < 20
    // Rang: [1, 5, 2, 4, 3]
    // Prozentanteil: [0.2, 1.0, 0.4, 0.8, 0.6]
    vector<float> input = {-10, 20, -5, 15, 0};
    vector<float> result = alpha_rank(input);

    ASSERT_EQ(result.size(), 5);
    EXPECT_FLOAT_EQ(result[0], 0.2);  // -10 -> 1/5
    EXPECT_FLOAT_EQ(result[1], 1.0);  // 20 -> 5/5
    EXPECT_FLOAT_EQ(result[2], 0.4);  // -5 -> 2/5
    EXPECT_FLOAT_EQ(result[3], 0.8);  // 15 -> 4/5
    EXPECT_FLOAT_EQ(result[4], 0.6);  // 0 -> 3/5
}

TEST(RankTest, DecimalNumbers) {
    // Dezimalzahlen: [1.5, 2.5, 1.5, 3.5, 2.5]
    // Sortierung: 1.5(1,2) < 2.5(3,4) < 3.5(5)
    // 1.5 Durchschnittsrang=(1+2)/2=1.5, 2.5 Durchschnittsrang=(3+4)/2=3.5
    // Prozentanteil: [0.3, 0.7, 0.3, 1.0, 0.7]
    vector<float> input = {1.5, 2.5, 1.5, 3.5, 2.5};
    vector<float> result = alpha_rank(input);

    ASSERT_EQ(result.size(), 5);
    EXPECT_FLOAT_EQ(result[0], 0.3);  // 1.5 -> 1.5/5
    EXPECT_FLOAT_EQ(result[1], 0.7);  // 2.5 -> 3.5/5
    EXPECT_FLOAT_EQ(result[2], 0.3);  // 1.5 -> 1.5/5
    EXPECT_FLOAT_EQ(result[3], 1.0);  // 3.5 -> 5/5
    EXPECT_FLOAT_EQ(result[4], 0.7);  // 2.5 -> 3.5/5
}

TEST(RankTest, MonotonicIncreasing) {
    // Monoton steigend: [1, 2, 3, 4, 5]
    // Prozentrang: [0.2, 0.4, 0.6, 0.8, 1.0]
    vector<float> input = {1, 2, 3, 4, 5};
    vector<float> result = alpha_rank(input);

    ASSERT_EQ(result.size(), 5);
    EXPECT_FLOAT_EQ(result[0], 0.2);
    EXPECT_FLOAT_EQ(result[1], 0.4);
    EXPECT_FLOAT_EQ(result[2], 0.6);
    EXPECT_FLOAT_EQ(result[3], 0.8);
    EXPECT_FLOAT_EQ(result[4], 1.0);
}

TEST(RankTest, MonotonicDecreasing) {
    // Monoton fallend: [5, 4, 3, 2, 1]
    // Prozentrang: [1.0, 0.8, 0.6, 0.4, 0.2]
    vector<float> input = {5, 4, 3, 2, 1};
    vector<float> result = alpha_rank(input);

    ASSERT_EQ(result.size(), 5);
    EXPECT_FLOAT_EQ(result[0], 1.0);
    EXPECT_FLOAT_EQ(result[1], 0.8);
    EXPECT_FLOAT_EQ(result[2], 0.6);
    EXPECT_FLOAT_EQ(result[3], 0.4);
    EXPECT_FLOAT_EQ(result[4], 0.2);
}

TEST(RankTest, StockReturnExample) {
    // Anwendungsfall aus Python-Docstring: Aktienrendite-Ranking
    // Renditen: [0.02, 0.05, 0.01, -0.01, 0.03]
    // Sortierung: -0.01 < 0.01 < 0.02 < 0.03 < 0.05
    // Prozentrang: [0.6, 1.0, 0.4, 0.2, 0.8]
    vector<float> returns = {0.02, 0.05, 0.01, -0.01, 0.03};
    vector<float> result = alpha_rank(returns);

    ASSERT_EQ(result.size(), 5);
    EXPECT_FLOAT_EQ(result[0], 0.6);  // 0.02 -> mittel
    EXPECT_FLOAT_EQ(result[1], 1.0);  // 0.05 -> starke Aktie
    EXPECT_FLOAT_EQ(result[2], 0.4);  // 0.01 -> leicht schwach
    EXPECT_FLOAT_EQ(result[3], 0.2);  // -0.01 -> schwache Aktie
    EXPECT_FLOAT_EQ(result[4], 0.8);  // 0.03 -> leicht stark
}

TEST(RankTest, LimitUpStocksExample) {
    // Praxisszenario: Aktien mit Kursanstieg-Limit
    // Drei Aktien mit Kursanstieg-Limit (10%), eine Normalaktie (5%), eine schwache Aktie (2%)
    // Renditen: [0.10, 0.10, 0.10, 0.05, 0.02]
    // Sortierung: 0.02(1) < 0.05(2) < 0.10(3,4,5)
    // Drei 0.10er Durchschnittsrang=(3+4+5)/3=4.0
    // Prozentrang: [0.8, 0.8, 0.8, 0.4, 0.2]
    vector<float> returns = {0.10, 0.10, 0.10, 0.05, 0.02};
    vector<float> result = alpha_rank(returns);

    ASSERT_EQ(result.size(), 5);
    EXPECT_FLOAT_EQ(result[0], 0.8);  // Aktie mit Kursanstieg-Limit
    EXPECT_FLOAT_EQ(result[1], 0.8);  // Aktie mit Kursanstieg-Limit
    EXPECT_FLOAT_EQ(result[2], 0.8);  // Aktie mit Kursanstieg-Limit
    EXPECT_FLOAT_EQ(result[3], 0.4);  // Normalaktie
    EXPECT_FLOAT_EQ(result[4], 0.2);  // schwache Aktie
}

TEST(RankTest, LargerDataset) {
    // Größeren Datensatz testen: 10 Elemente
    vector<float> input = {15, 25, 10, 30, 20, 25, 5, 35, 20, 10};
    vector<float> result = alpha_rank(input);

    ASSERT_EQ(result.size(), 10);

    // Sortierung: 5(1) < 10(2,3) < 15(4) < 20(5,6) < 25(7,8) < 30(9) < 35(10)
    // 5 -> 1/10 = 0.1
    // 10 Durchschnittsrang=(2+3)/2=2.5 -> 2.5/10 = 0.25
    // 15 -> 4/10 = 0.4
    // 20 Durchschnittsrang=(5+6)/2=5.5 -> 5.5/10 = 0.55
    // 25 Durchschnittsrang=(7+8)/2=7.5 -> 7.5/10 = 0.75
    // 30 -> 9/10 = 0.9
    // 35 -> 10/10 = 1.0

    EXPECT_FLOAT_EQ(result[0], 0.4);   // 15
    EXPECT_FLOAT_EQ(result[1], 0.75);  // 25
    EXPECT_FLOAT_EQ(result[2], 0.25);  // 10
    EXPECT_FLOAT_EQ(result[3], 0.9);   // 30
    EXPECT_FLOAT_EQ(result[4], 0.55);  // 20
    EXPECT_FLOAT_EQ(result[5], 0.75);  // 25
    EXPECT_FLOAT_EQ(result[6], 0.1);   // 5
    EXPECT_FLOAT_EQ(result[7], 1.0);   // 35
    EXPECT_FLOAT_EQ(result[8], 0.55);  // 20
    EXPECT_FLOAT_EQ(result[9], 0.25);  // 10
}

// ========== TS Rank Ultra Tests ==========

TEST(TsRankUltraTest, BasicTest) {
    // Überprüfen, ob Ultra-Version und Originalversion gleiche Ergebnisse liefern
    vector<float> input = {1, 5, 3, 7, 2};
    vector<float> result_original = ts_rank(input, 3);
    vector<float> result_ultra = ts_rank_ultra(input, 3);

    ASSERT_EQ(result_original.size(), result_ultra.size());
    for (size_t i = 0; i < result_original.size(); ++i) {
        if (isnan(result_original[i])) {
            EXPECT_TRUE(isnan(result_ultra[i]));
        } else {
            EXPECT_FLOAT_EQ(result_original[i], result_ultra[i]);
        }
    }
}

TEST(TsRankUltraTest, LargeDataset) {
    // Großen Datensatz testen (das ist der Vorteil der Ultra-Version)
    vector<float> input;
    for (int i = 0; i < 10000; ++i) {
        input.push_back(i % 100);
    }

    vector<float> result_original = ts_rank(input, 50);
    vector<float> result_ultra = ts_rank_ultra(input, 50);

    ASSERT_EQ(result_original.size(), result_ultra.size());
    for (size_t i = 0; i < result_original.size(); ++i) {
        if (isnan(result_original[i])) {
            EXPECT_TRUE(isnan(result_ultra[i]));
        } else {
            EXPECT_FLOAT_EQ(result_original[i], result_ultra[i]);
        }
    }
}

TEST(TsRankUltraTest, WithDuplicates) {
    // Konsistenz der Duplikatbehandlung prüfen
    vector<float> input = {1, 3, 2, 3, 3, 2, 1, 4};
    vector<float> result_original = ts_rank(input, 4);
    vector<float> result_ultra = ts_rank_ultra(input, 4);

    ASSERT_EQ(result_original.size(), result_ultra.size());
    for (size_t i = 0; i < result_original.size(); ++i) {
        if (isnan(result_original[i])) {
            EXPECT_TRUE(isnan(result_ultra[i]));
        } else {
            EXPECT_FLOAT_EQ(result_original[i], result_ultra[i]);
        }
    }
}

// ========== Scale (Skalierung) Tests ==========

TEST(ScaleTest, BasicExample) {
    // Python-Docstring-Beispiel: [1, 2, 3, 4], k=1
    // sum(abs) = 1+2+3+4 = 10
    // Ausgabe: [0.1, 0.2, 0.3, 0.4]
    vector<float> input = {1, 2, 3, 4};
    vector<float> result = scale(input);

    ASSERT_EQ(result.size(), 4);
    EXPECT_NEAR(result[0], 0.1f, 1e-6);
    EXPECT_NEAR(result[1], 0.2f, 1e-6);
    EXPECT_NEAR(result[2], 0.3f, 1e-6);
    EXPECT_NEAR(result[3], 0.4f, 1e-6);
}

TEST(ScaleTest, SumAbsEqualsK) {
    // Kerneigenschaft prüfen: sum(abs(result)) == k
    vector<float> input = {1, 2, 3, 4};
    vector<float> result = scale(input);

    float sum_abs = 0;
    for (float v : result) sum_abs += std::abs(v);
    EXPECT_NEAR(sum_abs, 1.0f, 1e-5);
}

TEST(ScaleTest, WithKParameter) {
    // Bei k=2: sum(abs(result)) == 2
    vector<float> input = {1, 2, 3, 4};
    vector<float> result = scale(input, 2.0f);

    ASSERT_EQ(result.size(), 4);
    EXPECT_NEAR(result[0], 0.2f, 1e-6);
    EXPECT_NEAR(result[1], 0.4f, 1e-6);
    EXPECT_NEAR(result[2], 0.6f, 1e-6);
    EXPECT_NEAR(result[3], 0.8f, 1e-6);

    float sum_abs = 0;
    for (float v : result) sum_abs += std::abs(v);
    EXPECT_NEAR(sum_abs, 2.0f, 1e-5);
}

TEST(ScaleTest, WithNegativeNumbers) {
    // Mit negativen Zahlen: [-1, 2, 3, 4]
    // sum(abs) = 1+2+3+4 = 10
    // Ausgabe: [-0.1, 0.2, 0.3, 0.4]
    // Bei negativen Zahlen wird abs für die Summe verwendet (wie in Python)
    vector<float> input = {-1, 2, 3, 4};
    vector<float> result = scale(input);

    ASSERT_EQ(result.size(), 4);
    EXPECT_NEAR(result[0], -0.1f, 1e-6);
    EXPECT_NEAR(result[1], 0.2f, 1e-6);
    EXPECT_NEAR(result[2], 0.3f, 1e-6);
    EXPECT_NEAR(result[3], 0.4f, 1e-6);

    float sum_abs = 0;
    for (float v : result) sum_abs += std::abs(v);
    EXPECT_NEAR(sum_abs, 1.0f, 1e-5);
}

TEST(ScaleTest, AllNegativeNumbers) {
    // Alle negative Zahlen: [-2, -3, -5]
    // sum(abs) = 2+3+5 = 10
    // Ausgabe: [-0.2, -0.3, -0.5]
    vector<float> input = {-2, -3, -5};
    vector<float> result = scale(input);

    ASSERT_EQ(result.size(), 3);
    EXPECT_NEAR(result[0], -0.2f, 1e-6);
    EXPECT_NEAR(result[1], -0.3f, 1e-6);
    EXPECT_NEAR(result[2], -0.5f, 1e-6);

    float sum_abs = 0;
    for (float v : result) sum_abs += std::abs(v);
    EXPECT_NEAR(sum_abs, 1.0f, 1e-5);
}

TEST(ScaleTest, SingleElement) {
    // Einzelnes Element: [5], k=1
    // sum(abs) = 5, Ausgabe: [1.0]
    vector<float> input = {5};
    vector<float> result = scale(input);

    ASSERT_EQ(result.size(), 1);
    EXPECT_NEAR(result[0], 1.0f, 1e-6);
}

TEST(ScaleTest, SingleElementWithK) {
    // Einzelnes Element: [5], k=3
    // sum(abs) = 5, Ausgabe: [3.0]
    vector<float> input = {5};
    vector<float> result = scale(input, 3.0f);

    ASSERT_EQ(result.size(), 1);
    EXPECT_NEAR(result[0], 3.0f, 1e-6);
}

TEST(ScaleTest, AllSameValues) {
    // Alle Werte gleich: [2, 2, 2, 2], k=1
    // sum(abs) = 8, Ausgabe: [0.25, 0.25, 0.25, 0.25]
    vector<float> input = {2, 2, 2, 2};
    vector<float> result = scale(input);

    ASSERT_EQ(result.size(), 4);
    for (float v : result) {
        EXPECT_NEAR(v, 0.25f, 1e-6);
    }
}

TEST(ScaleTest, MixedSignSymmetric) {
    // Positiv-negativ-symmetrisch: [-1, 1], sum(abs)=2
    // Ausgabe: [-0.5, 0.5]
    vector<float> input = {-1, 1};
    vector<float> result = scale(input);

    ASSERT_EQ(result.size(), 2);
    EXPECT_NEAR(result[0], -0.5f, 1e-6);
    EXPECT_NEAR(result[1], 0.5f, 1e-6);
}

TEST(ScaleTest, DecimalInput) {
    // Dezimale Eingabe: [0.5, 1.5, 3.0]
    // sum(abs) = 5.0
    // Ausgabe: [0.1, 0.3, 0.6]
    vector<float> input = {0.5f, 1.5f, 3.0f};
    vector<float> result = scale(input);

    ASSERT_EQ(result.size(), 3);
    EXPECT_NEAR(result[0], 0.1f, 1e-5);
    EXPECT_NEAR(result[1], 0.3f, 1e-5);
    EXPECT_NEAR(result[2], 0.6f, 1e-5);
}

TEST(ScaleTest, StockReturnsExample) {
    // Praxisszenario: Skalierung von Aktien-Überrenditen
    // Renditen: [0.02, -0.01, 0.03, -0.04]
    // sum(abs) = 0.02+0.01+0.03+0.04 = 0.10
    // Ausgabe: [0.2, -0.1, 0.3, -0.4], sum(abs) = 1.0
    vector<float> returns = {0.02f, -0.01f, 0.03f, -0.04f};
    vector<float> result = scale(returns);

    ASSERT_EQ(result.size(), 4);
    EXPECT_NEAR(result[0], 0.2f, 1e-5);
    EXPECT_NEAR(result[1], -0.1f, 1e-5);
    EXPECT_NEAR(result[2], 0.3f, 1e-5);
    EXPECT_NEAR(result[3], -0.4f, 1e-5);

    float sum_abs = 0;
    for (float v : result) sum_abs += std::abs(v);
    EXPECT_NEAR(sum_abs, 1.0f, 1e-5);
}

// ========== TS Argmax Tests ==========

TEST(TsArgmaxTest, BasicTest) {
    // [3,1,5]: argmax=2 (0-indexed) -> +1 = 3
    // [1,5,2]: argmax=1 (0-indexed) -> +1 = 2
    // [5,2,4]: argmax=0 (0-indexed) -> +1 = 1
    vector<float> input = {3, 1, 5, 2, 4};
    vector<float> result = ts_argmax(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));  // Warm-up: NaN
    EXPECT_TRUE(isnan(result[1]));  // Warm-up: NaN
    EXPECT_FLOAT_EQ(result[2], 3.0f);  // [3,1,5]: max=5 an Position 3
    EXPECT_FLOAT_EQ(result[3], 2.0f);  // [1,5,2]: max=5 an Position 2
    EXPECT_FLOAT_EQ(result[4], 1.0f);  // [5,2,4]: max=5 an Position 1
}

TEST(TsArgmaxTest, MaxAtFirstPosition) {
    // Maximum immer am Anfang des Fensters
    vector<float> input = {9, 1, 2, 1, 2};
    vector<float> result = ts_argmax(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_FLOAT_EQ(result[2], 1.0f);  // [9,1,2]: max=9 an Position 1
    EXPECT_FLOAT_EQ(result[3], 2.0f);  // [1,2,1]: max=2 an Position 2
    EXPECT_FLOAT_EQ(result[4], 1.0f);  // [2,1,2]: max=2 an Position 1 (erster Treffer)
}

TEST(TsArgmaxTest, MaxAtLastPosition) {
    // Maximum immer am Ende des Fensters (monoton steigend)
    vector<float> input = {1, 2, 3, 4, 5};
    vector<float> result = ts_argmax(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_FLOAT_EQ(result[2], 3.0f);  // [1,2,3]: max=3 an Position 3
    EXPECT_FLOAT_EQ(result[3], 3.0f);  // [2,3,4]: max=4 an Position 3
    EXPECT_FLOAT_EQ(result[4], 3.0f);  // [3,4,5]: max=5 an Position 3
}

TEST(TsArgmaxTest, Window2) {
    // window=2: argmax 1-indexed
    // [3,1]: max=3 an Position 1
    // [1,4]: max=4 an Position 2
    // [4,1]: max=4 an Position 1
    // [1,5]: max=5 an Position 2
    vector<float> input = {3, 1, 4, 1, 5};
    vector<float> result = ts_argmax(input, 2);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));      // Warm-up: NaN
    EXPECT_FLOAT_EQ(result[1], 1.0f);  // [3,1]: max=3 an Position 1
    EXPECT_FLOAT_EQ(result[2], 2.0f);  // [1,4]: max=4 an Position 2
    EXPECT_FLOAT_EQ(result[3], 1.0f);  // [4,1]: max=4 an Position 1
    EXPECT_FLOAT_EQ(result[4], 2.0f);  // [1,5]: max=5 an Position 2
}

TEST(TsArgmaxTest, ResultSize) {
    vector<float> input = {1, 2, 3, 4, 5};
    EXPECT_EQ(ts_argmax(input, 3).size(), input.size());
}

TEST(TsArgmaxTest, DefaultWindow) {
    // Standardfenstergröße = 10
    vector<float> input(15, 1.0f);
    input[5] = 99.0f;  // Maximum an Position 5
    vector<float> result = ts_argmax(input, 10);

    ASSERT_EQ(result.size(), 15);
    // Für i=9: Fenster=[1,1,1,1,1,99,1,1,1,1] (Index 0-9), max=99 an Index 5 -> +1=6
    EXPECT_FLOAT_EQ(result[9], 6.0f);
}

// ========== TS Argmin Tests ==========

TEST(TsArgminTest, BasicTest) {
    // [3,1,5]: argmin=1 (0-indexed) -> +1 = 2
    // [1,5,2]: argmin=0 (0-indexed) -> +1 = 1
    // [5,2,4]: argmin=1 (0-indexed) -> +1 = 2
    vector<float> input = {3, 1, 5, 2, 4};
    vector<float> result = ts_argmin(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));      // Warm-up: NaN
    EXPECT_TRUE(isnan(result[1]));      // Warm-up: NaN
    EXPECT_FLOAT_EQ(result[2], 2.0f);  // [3,1,5]: min=1 an Position 2
    EXPECT_FLOAT_EQ(result[3], 1.0f);  // [1,5,2]: min=1 an Position 1
    EXPECT_FLOAT_EQ(result[4], 2.0f);  // [5,2,4]: min=2 an Position 2
}

TEST(TsArgminTest, MinAtFirstPosition) {
    // Minimum immer am Anfang des Fensters (monoton fallend)
    vector<float> input = {5, 4, 3, 2, 1};
    vector<float> result = ts_argmin(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_FLOAT_EQ(result[2], 3.0f);  // [5,4,3]: min=3 an Position 3
    EXPECT_FLOAT_EQ(result[3], 3.0f);  // [4,3,2]: min=2 an Position 3
    EXPECT_FLOAT_EQ(result[4], 3.0f);  // [3,2,1]: min=1 an Position 3
}

TEST(TsArgminTest, MinAtLastPosition) {
    // Minimum immer am Ende des Fensters (monoton steigend)
    vector<float> input = {1, 2, 3, 4, 5};
    vector<float> result = ts_argmin(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_FLOAT_EQ(result[2], 1.0f);  // [1,2,3]: min=1 an Position 1
    EXPECT_FLOAT_EQ(result[3], 1.0f);  // [2,3,4]: min=2 an Position 1
    EXPECT_FLOAT_EQ(result[4], 1.0f);  // [3,4,5]: min=3 an Position 1
}

TEST(TsArgminTest, Window2) {
    // window=2: argmin 1-indexed
    // [3,1]: min=1 an Position 2
    // [1,4]: min=1 an Position 1
    // [4,1]: min=1 an Position 2
    // [1,5]: min=1 an Position 1
    vector<float> input = {3, 1, 4, 1, 5};
    vector<float> result = ts_argmin(input, 2);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));      // Warm-up: NaN
    EXPECT_FLOAT_EQ(result[1], 2.0f);  // [3,1]: min=1 an Position 2
    EXPECT_FLOAT_EQ(result[2], 1.0f);  // [1,4]: min=1 an Position 1
    EXPECT_FLOAT_EQ(result[3], 2.0f);  // [4,1]: min=1 an Position 2
    EXPECT_FLOAT_EQ(result[4], 1.0f);  // [1,5]: min=1 an Position 1
}

TEST(TsArgminTest, ResultSize) {
    vector<float> input = {1, 2, 3, 4, 5};
    EXPECT_EQ(ts_argmin(input, 3).size(), input.size());
}

TEST(TsArgminTest, DefaultWindow) {
    // Standardfenstergröße = 10
    vector<float> input(15, 99.0f);
    input[5] = 1.0f;  // Minimum an Position 5
    vector<float> result = ts_argmin(input, 10);

    ASSERT_EQ(result.size(), 15);
    // Für i=9: Fenster=[99,99,99,99,99,1,99,99,99,99] (Index 0-9), min=1 an Index 5 -> +1=6
    EXPECT_FLOAT_EQ(result[9], 6.0f);
}

// ========== Decay Linear Tests ==========

TEST(DecayLinearTest, BasicTest) {
    // period=3, divisor=6, Gewichte=[1/6, 2/6, 3/6]
    // result[2] = 1*(1/6) + 2*(2/6) + 3*(3/6) = 14/6 ≈ 2.3333
    // result[3] = 2*(1/6) + 3*(2/6) + 4*(3/6) = 20/6 ≈ 3.3333
    // result[4] = 3*(1/6) + 4*(2/6) + 5*(3/6) = 26/6 ≈ 4.3333
    vector<float> input = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    vector<float> result = decay_linear(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_NEAR(result[2], 14.0f / 6.0f, 1e-5f);
    EXPECT_NEAR(result[3], 20.0f / 6.0f, 1e-5f);
    EXPECT_NEAR(result[4], 26.0f / 6.0f, 1e-5f);
}

TEST(DecayLinearTest, WindowOne) {
    // period=1: Gewicht=1, Ergebnis entspricht der Eingabe
    vector<float> input = {3.0f, 7.0f, 2.0f, 9.0f};
    vector<float> result = decay_linear(input, 1);

    ASSERT_EQ(result.size(), 4);
    EXPECT_FLOAT_EQ(result[0], 3.0f);
    EXPECT_FLOAT_EQ(result[1], 7.0f);
    EXPECT_FLOAT_EQ(result[2], 2.0f);
    EXPECT_FLOAT_EQ(result[3], 9.0f);
}

TEST(DecayLinearTest, WindowTwo) {
    // period=2, divisor=3, Gewichte=[1/3, 2/3]
    // result[1] = 1*(1/3) + 2*(2/3) = 5/3
    // result[2] = 2*(1/3) + 3*(2/3) = 8/3
    // result[3] = 3*(1/3) + 4*(2/3) = 11/3
    vector<float> input = {1.0f, 2.0f, 3.0f, 4.0f};
    vector<float> result = decay_linear(input, 2);

    ASSERT_EQ(result.size(), 4);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_NEAR(result[1], 5.0f / 3.0f, 1e-5f);
    EXPECT_NEAR(result[2], 8.0f / 3.0f, 1e-5f);
    EXPECT_NEAR(result[3], 11.0f / 3.0f, 1e-5f);
}

TEST(DecayLinearTest, NanPrefixLength) {
    // Die ersten (period-1) Elemente müssen NaN sein
    int period = 5;
    vector<float> input(10, 1.0f);
    vector<float> result = decay_linear(input, period);

    ASSERT_EQ(result.size(), 10);
    for (int i = 0; i < period - 1; ++i) {
        EXPECT_TRUE(isnan(result[i])) << "Index " << i << " sollte NaN sein";
    }
    for (size_t i = period - 1; i < result.size(); ++i) {
        EXPECT_FALSE(isnan(result[i])) << "Index " << i << " sollte kein NaN sein";
    }
}

TEST(DecayLinearTest, AllSameValues) {
    // Konstanter Eingabevektor: gewichteter Mittelwert = Konstante selbst
    float c = 5.0f;
    vector<float> input(8, c);
    vector<float> result = decay_linear(input, 4);

    ASSERT_EQ(result.size(), 8);
    for (size_t i = 3; i < result.size(); ++i) {
        EXPECT_NEAR(result[i], c, 1e-5f) << "Index " << i;
    }
}

TEST(DecayLinearTest, RecentValuesWeightedHigher) {
    // Spätere Elemente haben höhere Gewichte → Ergebnis näher am letzten Wert
    // Fenster [0, 0, 10], period=3: result = 0*(1/6) + 0*(2/6) + 10*(3/6) = 5.0
    vector<float> input = {0.0f, 0.0f, 10.0f};
    vector<float> result = decay_linear(input, 3);

    ASSERT_EQ(result.size(), 3);
    EXPECT_NEAR(result[2], 5.0f, 1e-5f);

    // Umgekehrt: [10, 0, 0] → 10*(1/6) + 0 + 0 ≈ 1.6667
    vector<float> input2 = {10.0f, 0.0f, 0.0f};
    vector<float> result2 = decay_linear(input2, 3);
    EXPECT_NEAR(result2[2], 10.0f / 6.0f, 1e-5f);

    // Neuerer Wert wird stärker gewichtet
    EXPECT_GT(result[2], result2[2]);
}

TEST(DecayLinearTest, ResultSize) {
    vector<float> input = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    EXPECT_EQ(decay_linear(input, 3).size(), input.size());
}

// main-Funktion wird von GTest::gtest_main bereitgestellt, kein manuelles Schreiben nötig