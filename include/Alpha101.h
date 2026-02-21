#ifndef ALPHA101_H
#define ALPHA101_H

#include "Alpha101Utils.h"

// ====== Alpha-Faktor-Implementierungen ======

/**
 * @brief Alpha#1，截面rank版（符合论文原意）
 *
 * 公式: rank(Ts_ArgMax(SignedPower(((returns < 0) ? stddev(returns, 20) : close), 2.), 5)) - 0.5
 * 来源: Kakushadze, "101 Formulaic Alphas", 2016
 *
 * @param close_mat   收盘价矩阵，close_mat[s][t]，s = 股票索引，t = 时间索引
 * @param returns_mat 收益率矩阵，returns_mat[s][t]，维度与 close_mat 相同
 * @return            因子矩阵 result[s][t]，值域 (-0.5, 0.5]；
 *                    前23个时间点（热身期）输出 NaN
 */
inline vector<vector<float>> alpha001(const vector<vector<float>>& close_mat,
                                      const vector<vector<float>>& returns_mat) {
    size_t S = close_mat.size();
    if (S == 0) return {};
    size_t T = close_mat[0].size();

    // Step 1: 每只股票独立计算 ts_argmax(inner_sq, 5)
    // 结果直接写入列主序平坦缓冲区 argmax_flat[t*S + s]，
    // 使 Step 2 的截面读取成为连续内存访问
    vector<float> argmax_flat(T * S, NAN);
    for (size_t s = 0; s < S; ++s) {
        vector<float> std_ret = rolling_stddev(returns_mat[s], 20);

        vector<float> inner_sq(T, NAN);
        for (size_t t = 0; t < T; ++t) {
            if (isnan(std_ret[t])) continue;
            float val = (returns_mat[s][t] < 0.0f) ? std_ret[t] : close_mat[s][t];
            inner_sq[t] = val * val;
        }
        vector<float> argmax_s = ts_argmax(inner_sq, 5);
        for (size_t t = 0; t < T; ++t)
            argmax_flat[t * S + s] = argmax_s[t];
    }

    // Step 2: 对每个时间截面，跨股票做截面排名
    // argmax_flat[t*S .. t*S+S) 为连续内存，直接以 span 传入，无需额外拷贝
    // ranked/idx_buf 在循环外预分配，T 次迭代全程复用，零内部堆分配
    vector<vector<float>> result(S, vector<float>(T, NAN));
    vector<float> ranked(S);
    vector<size_t> idx_buf;
    idx_buf.reserve(S);
    for (size_t t = 0; t < T; ++t) {
        alpha_rank(span<const float>(&argmax_flat[t * S], S), span<float>(ranked), idx_buf);
        for (size_t s = 0; s < S; ++s)
            if (!isnan(ranked[s])) result[s][t] = ranked[s] - 0.5f;
    }

    return result;
}

#endif  // ALPHA101_H
