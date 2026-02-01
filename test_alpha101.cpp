#include <gtest/gtest.h>
#include "alpha101.h"
#include <cmath>

// 辅助函数：比较两个 vector 是否相等（考虑 NaN）
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

// ========== Rolling TS Sum 测试 ==========

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

// ========== Rolling Prod 测试 ==========

TEST(RollingProdTest, BasicTest) {
    // 测试基本乘积: [2, 3, 4]
    // 2 × 3 × 4 = 24
    vector<float> input = {2, 3, 4};
    float result = rolling_prod(input);

    EXPECT_FLOAT_EQ(result, 24.0);
}

TEST(RollingProdTest, WithOne) {
    // 包含1的乘积: [5, 1, 4]
    // 5 × 1 × 4 = 20
    vector<float> input = {5, 1, 4};
    float result = rolling_prod(input);

    EXPECT_FLOAT_EQ(result, 20.0);
}

TEST(RollingProdTest, WithZero) {
    // 包含0的乘积: [2, 0, 5]
    // 2 × 0 × 5 = 0
    vector<float> input = {2, 0, 5};
    float result = rolling_prod(input);

    EXPECT_FLOAT_EQ(result, 0.0);
}

TEST(RollingProdTest, NegativeNumbers) {
    // 负数乘积: [2, -3, 4]
    // 2 × (-3) × 4 = -24
    vector<float> input = {2, -3, 4};
    float result = rolling_prod(input);

    EXPECT_FLOAT_EQ(result, -24.0);
}

TEST(RollingProdTest, TwoNegatives) {
    // 两个负数: [-2, -3, 4]
    // (-2) × (-3) × 4 = 24
    vector<float> input = {-2, -3, 4};
    float result = rolling_prod(input);

    EXPECT_FLOAT_EQ(result, 24.0);
}

TEST(RollingProdTest, SingleElement) {
    // 单个元素: [5]
    // 结果为 5
    vector<float> input = {5};
    float result = rolling_prod(input);

    EXPECT_FLOAT_EQ(result, 5.0);
}

TEST(RollingProdTest, AllOnes) {
    // 全是1: [1, 1, 1, 1]
    // 1 × 1 × 1 × 1 = 1
    vector<float> input = {1, 1, 1, 1};
    float result = rolling_prod(input);

    EXPECT_FLOAT_EQ(result, 1.0);
}

TEST(RollingProdTest, DecimalNumbers) {
    // 小数: [0.5, 2.0, 4.0]
    // 0.5 × 2.0 × 4.0 = 4.0
    vector<float> input = {0.5, 2.0, 4.0};
    float result = rolling_prod(input);

    EXPECT_FLOAT_EQ(result, 4.0);
}

TEST(RollingProdTest, LargerSequence) {
    // 较长序列: [1, 2, 3, 4, 5]
    // 1 × 2 × 3 × 4 × 5 = 120
    vector<float> input = {1, 2, 3, 4, 5};
    float result = rolling_prod(input);

    EXPECT_FLOAT_EQ(result, 120.0);
}

// ========== Product (滚动乘积) 测试 ==========

TEST(ProductTest, BasicTest) {
    // 输入数据: [1, 2, 3, 4, 5]
    // window=3时的输出: [NaN, NaN, 6, 24, 60]
    // 解释: 6=1×2×3, 24=2×3×4, 60=3×4×5
    vector<float> input = {1, 2, 3, 4, 5};
    vector<float> result = product(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 6.0);    // 1×2×3
    EXPECT_FLOAT_EQ(result[3], 24.0);   // 2×3×4
    EXPECT_FLOAT_EQ(result[4], 60.0);   // 3×4×5
}

TEST(ProductTest, WindowTwo) {
    // [2, 3, 4, 5], window=2
    // 输出: [NaN, 6, 12, 20]
    vector<float> input = {2, 3, 4, 5};
    vector<float> result = product(input, 2);

    ASSERT_EQ(result.size(), 4);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_FLOAT_EQ(result[1], 6.0);    // 2×3
    EXPECT_FLOAT_EQ(result[2], 12.0);   // 3×4
    EXPECT_FLOAT_EQ(result[3], 20.0);   // 4×5
}

TEST(ProductTest, WithZero) {
    // 包含0的情况: [1, 2, 0, 3, 4], window=3
    // [NaN, NaN, 0, 0, 0]
    vector<float> input = {1, 2, 0, 3, 4};
    vector<float> result = product(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 0.0);    // 1×2×0
    EXPECT_FLOAT_EQ(result[3], 0.0);    // 2×0×3
    EXPECT_FLOAT_EQ(result[4], 0.0);    // 0×3×4
}

TEST(ProductTest, WithNegatives) {
    // 包含负数: [2, -3, 4, -1], window=2
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
    // window=1 时，输出应该与输入相同
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
    // 全是1: [1, 1, 1, 1, 1], window=3
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
    // 小数: [0.5, 2.0, 4.0, 0.5], window=2
    // [NaN, 1.0, 8.0, 2.0]
    vector<float> input = {0.5, 2.0, 4.0, 0.5};
    vector<float> result = product(input, 2);

    ASSERT_EQ(result.size(), 4);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_FLOAT_EQ(result[1], 1.0);    // 0.5×2.0
    EXPECT_FLOAT_EQ(result[2], 8.0);    // 2.0×4.0
    EXPECT_FLOAT_EQ(result[3], 2.0);    // 4.0×0.5
}

// ========== TS Min (滚动最小值) 测试 ==========

TEST(TsMinTest, BasicTest) {
    // 输入数据: [5, 3, 8, 2, 6]
    // window=3时的输出: [NaN, NaN, 3, 2, 2]
    // 解释: min([5,3,8])=3, min([3,8,2])=2, min([8,2,6])=2
    vector<float> input = {5, 3, 8, 2, 6};
    vector<float> result = ts_min(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 3.0);    // min([5,3,8])
    EXPECT_FLOAT_EQ(result[3], 2.0);    // min([3,8,2])
    EXPECT_FLOAT_EQ(result[4], 2.0);    // min([8,2,6])
}

TEST(TsMinTest, MonotonicIncreasing) {
    // 单调递增序列: [1, 2, 3, 4, 5], window=3
    // 每个窗口的最小值是第一个元素
    // [NaN, NaN, 1, 2, 3]
    vector<float> input = {1, 2, 3, 4, 5};
    vector<float> result = ts_min(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 1.0);    // min([1,2,3])
    EXPECT_FLOAT_EQ(result[3], 2.0);    // min([2,3,4])
    EXPECT_FLOAT_EQ(result[4], 3.0);    // min([3,4,5])
}

TEST(TsMinTest, MonotonicDecreasing) {
    // 单调递减序列: [10, 8, 6, 4, 2], window=3
    // 每个窗口的最小值是最后一个元素
    // [NaN, NaN, 6, 4, 2]
    vector<float> input = {10, 8, 6, 4, 2};
    vector<float> result = ts_min(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 6.0);    // min([10,8,6])
    EXPECT_FLOAT_EQ(result[3], 4.0);    // min([8,6,4])
    EXPECT_FLOAT_EQ(result[4], 2.0);    // min([6,4,2])
}

TEST(TsMinTest, WithNegatives) {
    // 包含负数: [3, -1, 5, -2, 4], window=3
    // [NaN, NaN, -1, -2, -2]
    vector<float> input = {3, -1, 5, -2, 4};
    vector<float> result = ts_min(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], -1.0);   // min([3,-1,5])
    EXPECT_FLOAT_EQ(result[3], -2.0);   // min([-1,5,-2])
    EXPECT_FLOAT_EQ(result[4], -2.0);   // min([5,-2,4])
}

TEST(TsMinTest, WindowOne) {
    // window=1 时，输出应该与输入相同
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
    EXPECT_FLOAT_EQ(result[1], 2.0);    // min([7,2])
    EXPECT_FLOAT_EQ(result[2], 2.0);    // min([2,9])
    EXPECT_FLOAT_EQ(result[3], 3.0);    // min([9,3])
    EXPECT_FLOAT_EQ(result[4], 3.0);    // min([3,5])
}

TEST(TsMinTest, AllSameValues) {
    // 所有值相同: [5, 5, 5, 5], window=3
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
    EXPECT_FLOAT_EQ(result[3], 1.0);    // min([8,3,9,1])
    EXPECT_FLOAT_EQ(result[4], 1.0);    // min([3,9,1,6])
    EXPECT_FLOAT_EQ(result[5], 1.0);    // min([9,1,6,4])
}

TEST(TsMinTest, DecimalNumbers) {
    // 小数: [2.5, 1.2, 3.7, 0.9], window=3
    // [NaN, NaN, 1.2, 0.9]
    vector<float> input = {2.5, 1.2, 3.7, 0.9};
    vector<float> result = ts_min(input, 3);

    ASSERT_EQ(result.size(), 4);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_NEAR(result[2], 1.2, 1e-5);  // min([2.5,1.2,3.7])
    EXPECT_NEAR(result[3], 0.9, 1e-5);  // min([1.2,3.7,0.9])
}

// ========== TS Max (滚动最大值) 测试 ==========

TEST(TsMaxTest, BasicTest) {
    // 输入数据: [5, 3, 8, 2, 6]
    // window=3时的输出: [NaN, NaN, 8, 8, 8]
    // 解释: max([5,3,8])=8, max([3,8,2])=8, max([8,2,6])=8
    vector<float> input = {5, 3, 8, 2, 6};
    vector<float> result = ts_max(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 8.0);    // max([5,3,8])
    EXPECT_FLOAT_EQ(result[3], 8.0);    // max([3,8,2])
    EXPECT_FLOAT_EQ(result[4], 8.0);    // max([8,2,6])
}

TEST(TsMaxTest, MonotonicIncreasing) {
    // 单调递增序列: [1, 2, 3, 4, 5], window=3
    // 每个窗口的最大值是最后一个元素
    // [NaN, NaN, 3, 4, 5]
    vector<float> input = {1, 2, 3, 4, 5};
    vector<float> result = ts_max(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 3.0);    // max([1,2,3])
    EXPECT_FLOAT_EQ(result[3], 4.0);    // max([2,3,4])
    EXPECT_FLOAT_EQ(result[4], 5.0);    // max([3,4,5])
}

TEST(TsMaxTest, MonotonicDecreasing) {
    // 单调递减序列: [10, 8, 6, 4, 2], window=3
    // 每个窗口的最大值是第一个元素
    // [NaN, NaN, 10, 8, 6]
    vector<float> input = {10, 8, 6, 4, 2};
    vector<float> result = ts_max(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 10.0);   // max([10,8,6])
    EXPECT_FLOAT_EQ(result[3], 8.0);    // max([8,6,4])
    EXPECT_FLOAT_EQ(result[4], 6.0);    // max([6,4,2])
}

TEST(TsMaxTest, WithNegatives) {
    // 包含负数: [3, -1, 5, -2, 4], window=3
    // [NaN, NaN, 5, 5, 5]
    vector<float> input = {3, -1, 5, -2, 4};
    vector<float> result = ts_max(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 5.0);    // max([3,-1,5])
    EXPECT_FLOAT_EQ(result[3], 5.0);    // max([-1,5,-2])
    EXPECT_FLOAT_EQ(result[4], 5.0);    // max([5,-2,4])
}

TEST(TsMaxTest, WindowOne) {
    // window=1 时，输出应该与输入相同
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
    EXPECT_FLOAT_EQ(result[1], 7.0);    // max([7,2])
    EXPECT_FLOAT_EQ(result[2], 9.0);    // max([2,9])
    EXPECT_FLOAT_EQ(result[3], 9.0);    // max([9,3])
    EXPECT_FLOAT_EQ(result[4], 5.0);    // max([3,5])
}

TEST(TsMaxTest, AllSameValues) {
    // 所有值相同: [5, 5, 5, 5], window=3
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
    EXPECT_FLOAT_EQ(result[3], 9.0);    // max([8,3,9,1])
    EXPECT_FLOAT_EQ(result[4], 9.0);    // max([3,9,1,6])
    EXPECT_FLOAT_EQ(result[5], 9.0);    // max([9,1,6,4])
}

TEST(TsMaxTest, DecimalNumbers) {
    // 小数: [2.5, 1.2, 3.7, 0.9], window=3
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
    // 锯齿形: [1, 5, 2, 6, 3], window=3
    // [NaN, NaN, 5, 6, 6]
    vector<float> input = {1, 5, 2, 6, 3};
    vector<float> result = ts_max(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 5.0);    // max([1,5,2])
    EXPECT_FLOAT_EQ(result[3], 6.0);    // max([5,2,6])
    EXPECT_FLOAT_EQ(result[4], 6.0);    // max([2,6,3])
}

// ========== Delta (差分) 测试 ==========

TEST(DeltaTest, BasicTest) {
    // 输入数据: [10, 12, 15, 13, 18]
    // period=1时的输出: [NaN, 2, 3, -2, 5]
    // 解释: 12-10=2, 15-12=3, 13-15=-2, 18-13=5
    vector<float> input = {10, 12, 15, 13, 18};
    vector<float> result = delta(input, 1);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_FLOAT_EQ(result[1], 2.0);    // 12-10
    EXPECT_FLOAT_EQ(result[2], 3.0);    // 15-12
    EXPECT_FLOAT_EQ(result[3], -2.0);   // 13-15
    EXPECT_FLOAT_EQ(result[4], 5.0);    // 18-13
}

TEST(DeltaTest, PeriodTwo) {
    // 输入数据: [10, 12, 15, 13, 18, 20]
    // period=2时的输出: [NaN, NaN, 5, 1, 3, 7]
    // 解释: 15-10=5, 13-12=1, 18-15=3, 20-13=7
    vector<float> input = {10, 12, 15, 13, 18, 20};
    vector<float> result = delta(input, 2);

    ASSERT_EQ(result.size(), 6);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 5.0);    // 15-10
    EXPECT_FLOAT_EQ(result[3], 1.0);    // 13-12
    EXPECT_FLOAT_EQ(result[4], 3.0);    // 18-15
    EXPECT_FLOAT_EQ(result[5], 7.0);    // 20-13
}

TEST(DeltaTest, LargerPeriod) {
    // period=3: [NaN, NaN, NaN, 3, 6, 8]
    vector<float> input = {10, 12, 15, 13, 18, 23};
    vector<float> result = delta(input, 3);

    ASSERT_EQ(result.size(), 6);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_TRUE(isnan(result[2]));
    EXPECT_FLOAT_EQ(result[3], 3.0);    // 13-10
    EXPECT_FLOAT_EQ(result[4], 6.0);    // 18-12
    EXPECT_FLOAT_EQ(result[5], 8.0);    // 23-15
}

TEST(DeltaTest, WithNegatives) {
    // 包含负数: [5, 2, -3, 1, -2]
    // period=1: [NaN, -3, -5, 4, -3]
    vector<float> input = {5, 2, -3, 1, -2};
    vector<float> result = delta(input, 1);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_FLOAT_EQ(result[1], -3.0);   // 2-5
    EXPECT_FLOAT_EQ(result[2], -5.0);   // -3-2
    EXPECT_FLOAT_EQ(result[3], 4.0);    // 1-(-3)
    EXPECT_FLOAT_EQ(result[4], -3.0);   // -2-1
}

TEST(DeltaTest, MonotonicIncreasing) {
    // 单调递增: [1, 2, 3, 4, 5]
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
    // 单调递减: [10, 8, 6, 4, 2]
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
    // 所有值相同: [5, 5, 5, 5]
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
    // 小数: [10.5, 12.3, 15.7, 13.2]
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
    // 包含相同连续值: [10, 10, 15, 15, 20]
    // period=1: [NaN, 0, 5, 0, 5]
    vector<float> input = {10, 10, 15, 15, 20};
    vector<float> result = delta(input, 1);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_FLOAT_EQ(result[1], 0.0);    // 10-10
    EXPECT_FLOAT_EQ(result[2], 5.0);    // 15-10
    EXPECT_FLOAT_EQ(result[3], 0.0);    // 15-15
    EXPECT_FLOAT_EQ(result[4], 5.0);    // 20-15
}

// ========== Delay (滞后) 测试 ==========

TEST(DelayTest, BasicTest) {
    // 输入数据: [10, 12, 15, 13, 18]
    // period=1时的输出: [NaN, 10, 12, 15, 13]
    // 解释: 每个值都是前一天的值
    vector<float> input = {10, 12, 15, 13, 18};
    vector<float> result = delay(input, 1);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_FLOAT_EQ(result[1], 10.0);   // delay 1: input[0]
    EXPECT_FLOAT_EQ(result[2], 12.0);   // delay 1: input[1]
    EXPECT_FLOAT_EQ(result[3], 15.0);   // delay 1: input[2]
    EXPECT_FLOAT_EQ(result[4], 13.0);   // delay 1: input[3]
}

TEST(DelayTest, PeriodTwo) {
    // 输入数据: [10, 12, 15, 13, 18, 20]
    // period=2时的输出: [NaN, NaN, 10, 12, 15, 13]
    // 解释: 每个值都是前两天的值
    vector<float> input = {10, 12, 15, 13, 18, 20};
    vector<float> result = delay(input, 2);

    ASSERT_EQ(result.size(), 6);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 10.0);   // delay 2: input[0]
    EXPECT_FLOAT_EQ(result[3], 12.0);   // delay 2: input[1]
    EXPECT_FLOAT_EQ(result[4], 15.0);   // delay 2: input[2]
    EXPECT_FLOAT_EQ(result[5], 13.0);   // delay 2: input[3]
}

TEST(DelayTest, LargerPeriod) {
    // period=3: [NaN, NaN, NaN, 10, 12, 15]
    vector<float> input = {10, 12, 15, 13, 18, 23};
    vector<float> result = delay(input, 3);

    ASSERT_EQ(result.size(), 6);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_TRUE(isnan(result[2]));
    EXPECT_FLOAT_EQ(result[3], 10.0);   // delay 3: input[0]
    EXPECT_FLOAT_EQ(result[4], 12.0);   // delay 3: input[1]
    EXPECT_FLOAT_EQ(result[5], 15.0);   // delay 3: input[2]
}

TEST(DelayTest, WithNegatives) {
    // 包含负数: [5, -2, 8, -3, 10]
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
    // 单调递增: [1, 2, 3, 4, 5]
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
    // 所有值相同: [5, 5, 5, 5]
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
    // 小数: [10.5, 12.3, 15.7, 13.2]
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
    // 包含0: [10, 0, 15, 0, 20]
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
    // period=5 时，前5个元素都是NaN
    vector<float> input = {1, 2, 3, 4, 5, 6, 7, 8};
    vector<float> result = delay(input, 5);

    ASSERT_EQ(result.size(), 8);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_TRUE(isnan(result[2]));
    EXPECT_TRUE(isnan(result[3]));
    EXPECT_TRUE(isnan(result[4]));
    EXPECT_FLOAT_EQ(result[5], 1.0);    // input[0]
    EXPECT_FLOAT_EQ(result[6], 2.0);    // input[1]
    EXPECT_FLOAT_EQ(result[7], 3.0);    // input[2]
}

// ========== Rolling SMA 测试 ==========

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

// ========== Rolling Stddev 测试 ==========

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

// ========== Rolling Correlation 测试 ==========

TEST(RollingCorrelationTest, PositiveCorrelation) {
    // y = 2x, 完全正相关
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
    // 负相关
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
    // 手动验证：平均值x̄=2, ȳ=4
    // 偏差x: [-1, 0, 1], 偏差y: [-2, 0, 2]
    // 相关系数: 4 / √(2×8) = 1.0
    vector<float> x = {1, 2, 3};
    vector<float> y = {2, 4, 6};
    vector<float> result = rolling_correlation(x, y, 3);

    ASSERT_EQ(result.size(), 3);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_NEAR(result[2], 1.0, 1e-5);
}

// ========== Rolling Covariance 测试 ==========

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
    // 平均值: x̄=2, ȳ=4
    // 偏差: x=[-1,0,1], y=[-2,0,2]
    // 偏差乘积: [2,0,2]
    // 协方差: (2+0+2)/(3-1) = 2.0
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

// ========== Rolling Rank 测试 ==========

TEST(RollingRankTest, BasicTest) {
    // 输入数组: [3, 1, 4, 2, 5]
    // 排序后: [1, 2, 3, 4, 5]
    // 最后值5在位置4，排名=5
    vector<float> input = {3, 1, 4, 2, 5};
    float result = rolling_rank(input);

    EXPECT_FLOAT_EQ(result, 5.0);
}

TEST(RollingRankTest, LowestValue) {
    // 窗口[100, 102, 98]: 98是最小值，排名1
    vector<float> input = {100, 102, 98};
    float result = rolling_rank(input);

    EXPECT_FLOAT_EQ(result, 1.0);
}

TEST(RollingRankTest, HighestValue) {
    // 窗口[102, 98, 105]: 105是最大值，排名3
    vector<float> input = {102, 98, 105};
    float result = rolling_rank(input);

    EXPECT_FLOAT_EQ(result, 3.0);
}

TEST(RollingRankTest, MiddleValue) {
    // [5, 1, 3, 2, 4]，最后值4，排序后[1,2,3,4,5]，4排名第4
    vector<float> input = {5, 1, 3, 2, 4};
    float result = rolling_rank(input);

    EXPECT_FLOAT_EQ(result, 4.0);
}

TEST(RollingRankTest, SingleElement) {
    // 单个元素，排名为1
    vector<float> input = {42};
    float result = rolling_rank(input);

    EXPECT_FLOAT_EQ(result, 1.0);
}

TEST(RollingRankTest, DuplicateValues) {
    // [1, 2, 2, 3]，最后值3，排序后[1,2,2,3]，3排名第4
    vector<float> input = {1, 2, 2, 3};
    float result = rolling_rank(input);

    EXPECT_FLOAT_EQ(result, 4.0);
}

TEST(RollingRankTest, DuplicateLastValue) {
    // [1, 3, 2, 3, 3]，最后值3
    // 排序后: [1, 2, 3, 3, 3]
    // 三个3占据位置3,4,5，平均排名=(3+4+5)/3=4.0
    vector<float> input = {1, 3, 2, 3, 3};
    float result = rolling_rank(input);

    EXPECT_FLOAT_EQ(result, 4.0);
}

TEST(RollingRankTest, AllSameValues) {
    // [5, 5, 5, 5]，所有值相同
    // 占据位置1,2,3,4，平均排名=(1+2+3+4)/4=2.5
    vector<float> input = {5, 5, 5, 5};
    float result = rolling_rank(input);

    EXPECT_FLOAT_EQ(result, 2.5);
}

TEST(RollingRankTest, TwoDuplicates) {
    // [1, 2, 3, 2]，最后值2
    // 排序后: [1, 2, 2, 3]
    // 两个2占据位置2,3，平均排名=(2+3)/2=2.5
    vector<float> input = {1, 2, 3, 2};
    float result = rolling_rank(input);

    EXPECT_FLOAT_EQ(result, 2.5);
}

// ========== TS Rank 测试 ==========

TEST(TsRankTest, BasicTest) {
    // 输入数据: [1, 5, 3, 7, 2]
    // window=3时的输出: [NaN, NaN, 2.0, 3.0, 1.0]
    // 解释: 在[1,5,3]中3排第2, 在[5,3,7]中7排第3, 在[3,7,2]中2排第1
    vector<float> input = {1, 5, 3, 7, 2};
    vector<float> result = ts_rank(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 2.0);  // [1,5,3]: 3排第2
    EXPECT_FLOAT_EQ(result[3], 3.0);  // [5,3,7]: 7排第3（最大）
    EXPECT_FLOAT_EQ(result[4], 1.0);  // [3,7,2]: 2排第1（最小）
}

TEST(TsRankTest, MonotonicIncreasing) {
    // 单调递增序列
    // [1, 2, 3, 4, 5], window=3
    // 每个窗口的最后值都是最大的，排名都是3
    vector<float> input = {1, 2, 3, 4, 5};
    vector<float> result = ts_rank(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 3.0);  // [1,2,3]: 3排第3
    EXPECT_FLOAT_EQ(result[3], 3.0);  // [2,3,4]: 4排第3
    EXPECT_FLOAT_EQ(result[4], 3.0);  // [3,4,5]: 5排第3
}

TEST(TsRankTest, MonotonicDecreasing) {
    // 单调递减序列
    // [5, 4, 3, 2, 1], window=3
    // 每个窗口的最后值都是最小的，排名都是1
    vector<float> input = {5, 4, 3, 2, 1};
    vector<float> result = ts_rank(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 1.0);  // [5,4,3]: 3排第1
    EXPECT_FLOAT_EQ(result[3], 1.0);  // [4,3,2]: 2排第1
    EXPECT_FLOAT_EQ(result[4], 1.0);  // [3,2,1]: 1排第1
}

TEST(TsRankTest, PriceSequenceExample) {
    // 价格序列: [100, 102, 98, 105, 103]
    // window=3
    vector<float> input = {100, 102, 98, 105, 103};
    vector<float> result = ts_rank(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 1.0);  // [100,102,98]: 98排第1（超跌）
    EXPECT_FLOAT_EQ(result[3], 3.0);  // [102,98,105]: 105排第3（超买）
    EXPECT_FLOAT_EQ(result[4], 2.0);  // [98,105,103]: 103排第2（中等）
}

TEST(TsRankTest, WithDuplicates) {
    // 包含重复值
    // [1, 3, 2, 3, 3], window=3
    vector<float> input = {1, 3, 2, 3, 3};
    vector<float> result = ts_rank(input, 3);

    ASSERT_EQ(result.size(), 5);
    EXPECT_TRUE(isnan(result[0]));
    EXPECT_TRUE(isnan(result[1]));
    EXPECT_FLOAT_EQ(result[2], 2.0);   // [1,3,2]: 2排第2
    EXPECT_FLOAT_EQ(result[3], 2.5);   // [3,2,3]: 排序后[2,3,3]，3的平均排名=(2+3)/2=2.5
    EXPECT_FLOAT_EQ(result[4], 2.5);   // [2,3,3]: 排序后[2,3,3]，3的平均排名=(2+3)/2=2.5
}

// ========== TS Rank Optimized 测试 ==========

TEST(TsRankOptimizedTest, BasicTest) {
    // 验证优化版本与原版本结果一致
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
    // 测试较大数据集
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
    // 验证重复值处理一致
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

// ========== Rank (横截面排名) 测试 ==========

TEST(RankTest, BasicExample) {
    // Python docstring 示例: [10, 50, 30, 20, 40]
    // 排序: 10 < 20 < 30 < 40 < 50
    // 常规排名: [1, 5, 3, 2, 4]
    // 百分比排名: [0.2, 1.0, 0.6, 0.4, 0.8]
    vector<float> input = {10, 50, 30, 20, 40};
    vector<float> result = alpha_rank(input);

    ASSERT_EQ(result.size(), 5);
    EXPECT_FLOAT_EQ(result[0], 0.2);   // 10最小 -> 1/5
    EXPECT_FLOAT_EQ(result[1], 1.0);   // 50最大 -> 5/5
    EXPECT_FLOAT_EQ(result[2], 0.6);   // 30中等 -> 3/5
    EXPECT_FLOAT_EQ(result[3], 0.4);   // 20第二小 -> 2/5
    EXPECT_FLOAT_EQ(result[4], 0.8);   // 40第二大 -> 4/5
}

TEST(RankTest, TwoDuplicates) {
    // Python docstring 示例1: [10, 30, 30, 20, 40]
    // 排序: 10(1) < 20(2) < 30(3,4) < 40(5)
    // 两个30占据位置3和4，平均排名 = (3+4)/2 = 3.5
    // 百分比排名: [0.2, 0.7, 0.7, 0.4, 1.0]
    vector<float> input = {10, 30, 30, 20, 40};
    vector<float> result = alpha_rank(input);

    ASSERT_EQ(result.size(), 5);
    EXPECT_FLOAT_EQ(result[0], 0.2);   // 10 -> 1/5
    EXPECT_FLOAT_EQ(result[1], 0.7);   // 30 -> 3.5/5
    EXPECT_FLOAT_EQ(result[2], 0.7);   // 30 -> 3.5/5
    EXPECT_FLOAT_EQ(result[3], 0.4);   // 20 -> 2/5
    EXPECT_FLOAT_EQ(result[4], 1.0);   // 40 -> 5/5
}

TEST(RankTest, ThreeDuplicates) {
    // Python docstring 示例2: [10, 30, 30, 30, 40]
    // 排序: 10(1) < 30(2,3,4) < 40(5)
    // 三个30占据位置2,3,4，平均排名 = (2+3+4)/3 = 3.0
    // 百分比排名: [0.2, 0.6, 0.6, 0.6, 1.0]
    vector<float> input = {10, 30, 30, 30, 40};
    vector<float> result = alpha_rank(input);

    ASSERT_EQ(result.size(), 5);
    EXPECT_FLOAT_EQ(result[0], 0.2);   // 10 -> 1/5
    EXPECT_FLOAT_EQ(result[1], 0.6);   // 30 -> 3.0/5
    EXPECT_FLOAT_EQ(result[2], 0.6);   // 30 -> 3.0/5
    EXPECT_FLOAT_EQ(result[3], 0.6);   // 30 -> 3.0/5
    EXPECT_FLOAT_EQ(result[4], 1.0);   // 40 -> 5/5
}

TEST(RankTest, FourDuplicates) {
    // Python docstring 示例3: [50, 30, 30, 30, 30]
    // 排序: 30(1,2,3,4) < 50(5)
    // 四个30占据位置1,2,3,4，平均排名 = (1+2+3+4)/4 = 2.5
    // 百分比排名: [1.0, 0.5, 0.5, 0.5, 0.5]
    vector<float> input = {50, 30, 30, 30, 30};
    vector<float> result = alpha_rank(input);

    ASSERT_EQ(result.size(), 5);
    EXPECT_FLOAT_EQ(result[0], 1.0);   // 50 -> 5/5
    EXPECT_FLOAT_EQ(result[1], 0.5);   // 30 -> 2.5/5
    EXPECT_FLOAT_EQ(result[2], 0.5);   // 30 -> 2.5/5
    EXPECT_FLOAT_EQ(result[3], 0.5);   // 30 -> 2.5/5
    EXPECT_FLOAT_EQ(result[4], 0.5);   // 30 -> 2.5/5
}

TEST(RankTest, AllSameValues) {
    // 所有值相同: [5, 5, 5, 5, 5]
    // 占据位置1,2,3,4,5，平均排名 = (1+2+3+4+5)/5 = 3.0
    // 百分比排名: [0.6, 0.6, 0.6, 0.6, 0.6]
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
    // 单个元素: [42]
    // 排名1，百分比 = 1/1 = 1.0
    vector<float> input = {42};
    vector<float> result = alpha_rank(input);

    ASSERT_EQ(result.size(), 1);
    EXPECT_FLOAT_EQ(result[0], 1.0);
}

TEST(RankTest, EmptyArray) {
    // 空数组
    vector<float> input = {};
    vector<float> result = alpha_rank(input);

    ASSERT_EQ(result.size(), 0);
}

TEST(RankTest, TwoElements) {
    // 两个不同的元素: [10, 20]
    // 百分比排名: [0.5, 1.0]
    vector<float> input = {10, 20};
    vector<float> result = alpha_rank(input);

    ASSERT_EQ(result.size(), 2);
    EXPECT_FLOAT_EQ(result[0], 0.5);   // 10 -> 1/2
    EXPECT_FLOAT_EQ(result[1], 1.0);   // 20 -> 2/2
}

TEST(RankTest, TwoElementsSame) {
    // 两个相同元素: [10, 10]
    // 平均排名 = (1+2)/2 = 1.5
    // 百分比排名: [0.75, 0.75]
    vector<float> input = {10, 10};
    vector<float> result = alpha_rank(input);

    ASSERT_EQ(result.size(), 2);
    EXPECT_FLOAT_EQ(result[0], 0.75);  // 1.5/2
    EXPECT_FLOAT_EQ(result[1], 0.75);  // 1.5/2
}

TEST(RankTest, NegativeNumbers) {
    // 包含负数: [-10, 20, -5, 15, 0]
    // 排序: -10 < -5 < 0 < 15 < 20
    // 排名: [1, 5, 2, 4, 3]
    // 百分比: [0.2, 1.0, 0.4, 0.8, 0.6]
    vector<float> input = {-10, 20, -5, 15, 0};
    vector<float> result = alpha_rank(input);

    ASSERT_EQ(result.size(), 5);
    EXPECT_FLOAT_EQ(result[0], 0.2);   // -10 -> 1/5
    EXPECT_FLOAT_EQ(result[1], 1.0);   // 20 -> 5/5
    EXPECT_FLOAT_EQ(result[2], 0.4);   // -5 -> 2/5
    EXPECT_FLOAT_EQ(result[3], 0.8);   // 15 -> 4/5
    EXPECT_FLOAT_EQ(result[4], 0.6);   // 0 -> 3/5
}

TEST(RankTest, DecimalNumbers) {
    // 小数: [1.5, 2.5, 1.5, 3.5, 2.5]
    // 排序: 1.5(1,2) < 2.5(3,4) < 3.5(5)
    // 1.5平均排名=(1+2)/2=1.5, 2.5平均排名=(3+4)/2=3.5
    // 百分比: [0.3, 0.7, 0.3, 1.0, 0.7]
    vector<float> input = {1.5, 2.5, 1.5, 3.5, 2.5};
    vector<float> result = alpha_rank(input);

    ASSERT_EQ(result.size(), 5);
    EXPECT_FLOAT_EQ(result[0], 0.3);   // 1.5 -> 1.5/5
    EXPECT_FLOAT_EQ(result[1], 0.7);   // 2.5 -> 3.5/5
    EXPECT_FLOAT_EQ(result[2], 0.3);   // 1.5 -> 1.5/5
    EXPECT_FLOAT_EQ(result[3], 1.0);   // 3.5 -> 5/5
    EXPECT_FLOAT_EQ(result[4], 0.7);   // 2.5 -> 3.5/5
}

TEST(RankTest, MonotonicIncreasing) {
    // 单调递增: [1, 2, 3, 4, 5]
    // 百分比排名: [0.2, 0.4, 0.6, 0.8, 1.0]
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
    // 单调递减: [5, 4, 3, 2, 1]
    // 百分比排名: [1.0, 0.8, 0.6, 0.4, 0.2]
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
    // Python docstring 应用场景: 股票收益率排名
    // 收益率: [0.02, 0.05, 0.01, -0.01, 0.03]
    // 排序: -0.01 < 0.01 < 0.02 < 0.03 < 0.05
    // 百分比排名: [0.6, 1.0, 0.4, 0.2, 0.8]
    vector<float> returns = {0.02, 0.05, 0.01, -0.01, 0.03};
    vector<float> result = alpha_rank(returns);

    ASSERT_EQ(result.size(), 5);
    EXPECT_FLOAT_EQ(result[0], 0.6);   // 0.02 -> 中等
    EXPECT_FLOAT_EQ(result[1], 1.0);   // 0.05 -> 强势股
    EXPECT_FLOAT_EQ(result[2], 0.4);   // 0.01 -> 偏弱
    EXPECT_FLOAT_EQ(result[3], 0.2);   // -0.01 -> 弱势股
    EXPECT_FLOAT_EQ(result[4], 0.8);   // 0.03 -> 偏强
}

TEST(RankTest, LimitUpStocksExample) {
    // Python docstring 实际案例: 涨停股处理
    // 三只涨停股(10%)，一只普通股(5%)，一只弱势股(2%)
    // 收益率: [0.10, 0.10, 0.10, 0.05, 0.02]
    // 排序: 0.02(1) < 0.05(2) < 0.10(3,4,5)
    // 三个0.10平均排名=(3+4+5)/3=4.0
    // 百分比排名: [0.8, 0.8, 0.8, 0.4, 0.2]
    vector<float> returns = {0.10, 0.10, 0.10, 0.05, 0.02};
    vector<float> result = alpha_rank(returns);

    ASSERT_EQ(result.size(), 5);
    EXPECT_FLOAT_EQ(result[0], 0.8);   // 涨停股
    EXPECT_FLOAT_EQ(result[1], 0.8);   // 涨停股
    EXPECT_FLOAT_EQ(result[2], 0.8);   // 涨停股
    EXPECT_FLOAT_EQ(result[3], 0.4);   // 普通股
    EXPECT_FLOAT_EQ(result[4], 0.2);   // 弱势股
}

TEST(RankTest, LargerDataset) {
    // 测试较大数据集: 10个元素
    vector<float> input = {15, 25, 10, 30, 20, 25, 5, 35, 20, 10};
    vector<float> result = alpha_rank(input);

    ASSERT_EQ(result.size(), 10);

    // 排序: 5(1) < 10(2,3) < 15(4) < 20(5,6) < 25(7,8) < 30(9) < 35(10)
    // 5 -> 1/10 = 0.1
    // 10平均排名=(2+3)/2=2.5 -> 2.5/10 = 0.25
    // 15 -> 4/10 = 0.4
    // 20平均排名=(5+6)/2=5.5 -> 5.5/10 = 0.55
    // 25平均排名=(7+8)/2=7.5 -> 7.5/10 = 0.75
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

// ========== TS Rank Ultra 测试 ==========

TEST(TsRankUltraTest, BasicTest) {
    // 验证 ultra 版本与原版结果一致
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
    // 测试大数据集（这是 ultra 版本的优势）
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
    // 验证重复值处理一致
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

// main 函数由 GTest::gtest_main 提供，不需要手动编写