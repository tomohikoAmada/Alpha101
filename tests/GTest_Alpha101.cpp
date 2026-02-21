#include <gtest/gtest.h>

#include <cmath>

#include "Alpha101.h"

// ========== Alpha001 截面版测试 ==========
// alpha001(vector<vector<float>>, vector<vector<float>>)
// 数据布局: [股票][时间]，输出同样为 [股票][时间]

class Alpha001CrossTest : public ::testing::Test {
   protected:
    // 生成常量矩阵：S只股票，T个时间点，全部等于value
    static vector<vector<float>> const_mat(size_t S, size_t T, float value) {
        return vector<vector<float>>(S, vector<float>(T, value));
    }

    // 生成线性递增矩阵：每只股票的close从start开始以step递增
    static vector<vector<float>> linspace_mat(size_t S, size_t T, float start, float step) {
        vector<vector<float>> mat(S, vector<float>(T));
        for (size_t s = 0; s < S; ++s)
            for (size_t t = 0; t < T; ++t)
                mat[s][t] = start + t * step + s * 10.0f;  // 不同股票价格错开
        return mat;
    }
};

// ---------- 输出形状 ----------

TEST_F(Alpha001CrossTest, OutputShape) {
    size_t S = 5, T = 50;
    auto close   = const_mat(S, T, 100.0f);
    auto returns = const_mat(S, T, 0.01f);
    auto result  = alpha001(close, returns);

    ASSERT_EQ(result.size(), S);
    for (size_t s = 0; s < S; ++s)
        EXPECT_EQ(result[s].size(), T);
}

// ---------- 热身期 ----------

TEST_F(Alpha001CrossTest, WarmupPeriod) {
    // 前23个时间点（0..22）应全为NaN，23起应有有效值
    size_t S = 3, T = 50;
    auto close   = linspace_mat(S, T, 100.0f, 0.5f);
    auto returns = const_mat(S, T, 0.01f);
    auto result  = alpha001(close, returns);

    for (size_t s = 0; s < S; ++s) {
        for (size_t t = 0; t < 23; ++t)
            EXPECT_TRUE(isnan(result[s][t])) << "s=" << s << " t=" << t << " 应为NaN";
        for (size_t t = 23; t < T; ++t)
            EXPECT_FALSE(isnan(result[s][t])) << "s=" << s << " t=" << t << " 不应为NaN";
    }
}

// ---------- 输出范围 ----------

TEST_F(Alpha001CrossTest, OutputRange) {
    size_t S = 5, T = 60;
    auto close   = linspace_mat(S, T, 50.0f, 1.0f);
    auto returns = const_mat(S, T, 0.01f);
    auto result  = alpha001(close, returns);

    for (size_t s = 0; s < S; ++s)
        for (size_t t = 23; t < T; ++t) {
            EXPECT_GE(result[s][t], -0.5f) << "s=" << s << " t=" << t;
            EXPECT_LE(result[s][t], 0.5f)  << "s=" << s << " t=" << t;
        }
}

// ---------- 截面性质：相同股票得到相同排名（Tie） ----------

TEST_F(Alpha001CrossTest, IdenticalStocksGetSameRank) {
    // 所有股票数据相同 → argmax相同 → 截面排名全部并列
    size_t S = 4, T = 40;
    auto close   = const_mat(S, T, 100.0f);
    auto returns = const_mat(S, T, 0.01f);
    auto result  = alpha001(close, returns);

    for (size_t t = 23; t < T; ++t) {
        float v0 = result[0][t];
        for (size_t s = 1; s < S; ++s)
            EXPECT_NEAR(result[s][t], v0, 1e-5f) << "t=" << t << " s=" << s;
    }
}

// ---------- 截面性质：不同股票排名之和固定 ----------

TEST_F(Alpha001CrossTest, CrossSectionalRankSumIsFixed) {
    // S只股票的截面百分位排名均值 = (1+S)/(2*S)，减去0.5后均值 = (1-S)/(2*S)
    // 等价地，所有股票排名之和 = S * (1+S)/(2*S) - S*0.5 = (S+1)/2 - S/2 = 0.5
    size_t S = 5, T = 50;
    auto close   = linspace_mat(S, T, 100.0f, 1.0f);
    auto returns = const_mat(S, T, 0.01f);
    auto result  = alpha001(close, returns);

    for (size_t t = 23; t < T; ++t) {
        float sum = 0.0f;
        for (size_t s = 0; s < S; ++s)
            sum += result[s][t];
        EXPECT_NEAR(sum, 0.5f, 1e-4f) << "t=" << t;
    }
}

// main-Funktion wird von GTest::gtest_main bereitgestellt, kein manuelles Schreiben nötig
