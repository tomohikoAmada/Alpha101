#ifndef ALPHA101_H
#define ALPHA101_H

#include <iostream>
#include <vector>
#include <cmath>
#include <span>
#include <set>
#include <algorithm>  // 提供 sort, upper_bound 等算法
#include <ranges>     // 提供 sliding_window (C++23)

using namespace std;

// 辅助函数：打印结果
void print_result(const vector<float> &result);

// 滚动求和
vector<float> rolling_ts_sum(vector<float> DataFrame, int window);

// 滚动简单移动平均
vector<float> rolling_sma(vector<float> DataFrame, int window);

// 滚动标准差
vector<float> rolling_stddev(vector<float> DataFrame, int window);

// 单个窗口的相关系数
float correlation(vector<float> a, vector<float> b, int window);

// 滚动相关系数
vector<float> rolling_correlation(vector<float> a, vector<float> b, int window);

// 单个窗口的协方差
float covariance(vector<float> a, vector<float> b, int window);

// 滚动协方差
vector<float> rolling_covariance(vector<float> a, vector<float> b, int window);

// ====== 实现部分 ======

void print_result(const vector<float> &result) {
    cout << "[";
    for (size_t i = 0; i < result.size(); i++) {
        if (isnan(result[i])) {
            cout << "NaN";
        } else {
            cout << result[i];
        }
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

vector<float> rolling_ts_sum(vector<float> DataFrame, int window) {
    vector<float> result;
    for (size_t i = 0; i < DataFrame.size(); i++) {
        if (i + 1 < window) {
            result.push_back(NAN);
        } else {
            float sum = 0;
            for (int j = 0; j < window; j++) {
                sum += DataFrame[i - j];
            }
            result.push_back(sum);
        }
    }
    return result;
}

vector<float> rolling_sma(vector<float> DataFrame, int window) {
    vector<float> result;
    for (int i = 0; i < DataFrame.size(); ++i) {
        if (i + 1 < window) {
            result.push_back(NAN);
        } else {
            float sum = 0;
            for (int j = 0; j < window; ++j) {
                sum += DataFrame[i - j];
            }
            float avg = sum / window;
            result.push_back(avg);
        }
    }
    return result;
}

vector<float> rolling_stddev(vector<float> DataFrame, int window) {
    vector<float> result;
    for (int i = 0; i < DataFrame.size(); i++) {
        if (i + 1 < window) {
            result.push_back(NAN);
        } else {
            float sum = 0;
            for (int j = 0; j < window; j++) {
                sum += DataFrame[i - j];
            }
            float avg = sum / window;
            sum = 0;
            vector<float> tmp_window;
            for (int j = 0; j < window; j++) {
                tmp_window.push_back(pow((DataFrame[i - j] - avg), 2));
            }
            for (int j = 0; j < tmp_window.size(); j++) {
                sum += tmp_window[j];
            }
            float res = sqrt(sum / (window - 1));
            result.push_back(res);
        }
    }
    return result;
}

float correlation(vector<float> a, vector<float> b, int window) {
    float result = 0;
    float avg_a = rolling_sma(a, a.size()).back();
    float avg_b = rolling_sma(b, b.size()).back();
    vector<float> deviation_a, deviation_b;
    for (int i = 0; i < a.size(); ++i) {
        deviation_a.push_back(a[i] - avg_a);
    }
    for (int i = 0; i < b.size(); ++i) {
        deviation_b.push_back(b[i] - avg_b);
    }
    float SPD = 0;
    for (int i = 0; i < a.size(); ++i) {
        SPD += deviation_a[i] * deviation_b[i];
    }
    float ss_a(0), ss_b(0);
    for (int i = 0; i < deviation_a.size(); ++i) {
        ss_a += deviation_a[i] * deviation_a[i];
    }
    for (int i = 0; i < deviation_b.size(); ++i) {
        ss_b += deviation_b[i] * deviation_b[i];
    }

    result = SPD / sqrt(ss_a * ss_b);

    return result;
}

vector<float> rolling_correlation(vector<float> a, vector<float> b, int window) {
    vector<float> result;

    for (int i = 0; i < a.size(); ++i) {
        if (i + 1 < window) {
            result.push_back(NAN);
        } else {
            vector<float> window_a, window_b;
            for (int j = 0; j < window; ++j) {
                window_a.push_back(a[i - j]);
                window_b.push_back(b[i - j]);
            }

            float corr = correlation(window_a, window_b, window_a.size());
            result.push_back(corr);
        }
    }

    return result;
}

float covariance(vector<float> a, vector<float> b, int window) {
    float avg_a = rolling_sma(a, a.size()).back();
    float avg_b = rolling_sma(b, b.size()).back();

    vector<float> deviation_a, deviation_b;
    for (int i = 0; i < a.size(); ++i) {
        deviation_a.push_back(a[i] - avg_a);
    }
    for (int i = 0; i < b.size(); ++i) {
        deviation_b.push_back(b[i] - avg_b);
    }

    float SPD = 0;
    for (int i = 0; i < a.size(); ++i) {
        SPD += deviation_a[i] * deviation_b[i];
    }

    return SPD / (a.size() - 1);
}

vector<float> rolling_covariance(vector<float> a, vector<float> b, int window) {
    vector<float> result;
    for (int i = 0; i < a.size(); ++i) {
        if (i + 1 < window) {
            result.push_back(NAN);
        } else {
            vector<float> window_a, window_b;
            for (int j = 0; j < window; ++j) {
                window_a.push_back(a[i - j]);
                window_b.push_back(b[i - j]);
            }
            float cov = covariance(window_a, window_b, window_a.size());
            result.push_back(cov);
        }
    }

    return result;
}

float rolling_rank(vector<float> a) {
    if (a.empty()) return 0.0f;

    float last_value = a.back(); // 获取最后一个值

    // 排序以找到排名（传值，不影响原数组）
    sort(a.begin(), a.end());

    // 找到所有等于 last_value 的值的范围
    // lower_bound: 第一个不小于 last_value 的位置
    // upper_bound: 第一个大于 last_value 的位置
    auto lower = lower_bound(a.begin(), a.end(), last_value);
    auto upper = upper_bound(a.begin(), a.end(), last_value);

    // 计算平均排名
    // 例如：[1, 2, 3, 3, 3]，三个3占据位置3,4,5（索引2,3,4）
    // lower索引=2, upper索引=5
    // 排名范围：3到5，平均排名=(3+4+5)/3=4.0
    size_t first_rank = distance(a.begin(), lower) + 1; // 第一个相同值的排名
    size_t last_rank = distance(a.begin(), upper); // 最后一个相同值的排名
    float avg_rank = (first_rank + last_rank) / 2.0f; // 平均排名

    return avg_rank;
}

// rolling_rank 的优化版本：使用 span 避免在调用点创建临时 vector，span 是 C++20 特性，只是数据的"视图"，不拥有数据，不拷贝
float rolling_rank(span<const float> data) {
    if (data.empty()) return 0.0f;

    float last_value = data.back();

    // 在这里创建临时 vector 用于排序（无法避免，因为需要排序）
    vector<float> sorted(data.begin(), data.end());
    sort(sorted.begin(), sorted.end());

    auto lower = lower_bound(sorted.begin(), sorted.end(), last_value);
    auto upper = upper_bound(sorted.begin(), sorted.end(), last_value);

    size_t first_rank = distance(sorted.begin(), lower) + 1;
    size_t last_rank = distance(sorted.begin(), upper);
    float avg_rank = (first_rank + last_rank) / 2.0f;

    return avg_rank;
}

vector<float> ts_rank(vector<float> a, int window) {
    vector<float> result;

    for (int i = 0; i < a.size(); ++i) {
        if (i + 1 < window) {
            // 前 window-1 个位置返回 NaN
            result.push_back(NAN);
        } else {
            // 提取窗口 [i-window+1, i]，包含 window 个元素
            // C++ 范围构造函数是 [first, last)，所以结束位置是 i+1
            vector<float> tmp(&a[i - window + 1], &a[i + 1]);
            result.push_back(rolling_rank(tmp));

            // 可以写成简化的
            // result.push_back(rolling_rank(vector<float>(&a[i - window + 1], &a[i + 1])));
        }
    }

    return result;
}

// 使用 span 优化的版本：避免创建临时 vector
vector<float> ts_rank_optimized(const vector<float> &a, int window) {
    size_t n = a.size();
    vector<float> result(n);
    for (size_t i = 0; i < n; ++i)
        result[i] = i + 1 < window
                        ? NAN
                        : rolling_rank(span<const float>(&a[i - window + 1], window));
    return result;
}

// 超级优化版本：使用滑动窗口 + multiset，复杂度：O(n × log window) vs 原来的 O(n × window × log window)
vector<float> ts_rank_ultra(const vector<float> &a, int window) {
    size_t n = a.size();
    vector<float> result(n);

    multiset<float> ordered_window; // 自动保持有序

    for (size_t i = 0; i < n; ++i) {
        // 添加新元素到窗口
        ordered_window.insert(a[i]);

        // 如果窗口满了，移除最旧的元素
        if (i >= window) {
            // find() 返回第一个匹配的元素，然后删除
            ordered_window.erase(ordered_window.find(a[i - window]));
        }

        // 计算排名
        if (i + 1 < window) {
            result[i] = NAN;
        } else {
            float last_value = a[i];

            // lower_bound: 第一个不小于 last_value 的位置
            // upper_bound: 第一个大于 last_value 的位置
            auto lower = ordered_window.lower_bound(last_value);
            auto upper = ordered_window.upper_bound(last_value);

            // 计算平均排名
            size_t rank_start = distance(ordered_window.begin(), lower) + 1;
            size_t rank_end = distance(ordered_window.begin(), upper);

            result[i] = (rank_start + rank_end) / 2.0f;
        }
    }

    return result;
}

float rolling_prod(vector<float> a) {
    float result = 1;

    for (int i = 0; i < a.size(); ++i) {
        result *= a[i];
    }

    return result;
}

vector<float> product(vector<float> a, int window) {
    vector<float> result;

    for (int i = 0; i < a.size(); ++i) {
        if (i + 1 < window) {
            result.push_back(NAN);
        } else {
            result.push_back(rolling_prod(vector<float>(&a[i - window + 1], &a[i + 1])));
        }
    }

    return result;
}

vector<float> ts_min(vector<float> a, int window) {
    vector<float> result;

    auto getminval = [](vector<float> aa) {
        sort(aa.begin(), aa.end());
        return aa.front();
    };

    // 不想使用auto的话，这是另一种写法，使用函数指针指向匿名函数 并传参
    // float (*getminval_without_auto)(vector<float>) = [](vector<float> aa) {
    //     sort(aa.begin(), aa.end());
    //     return aa.front();
    // };

    for (int i = 0; i < a.size(); ++i) {
        if (i + 1 < window) {
            result.push_back(NAN);
        } else {
            result.push_back(getminval(vector<float>(&a[i - window + 1], &a[i + 1])));
        }
    }

    return result;
}

vector<float> ts_max(vector<float> a, int window) {
    vector<float> result;

    auto getmaxval = [](vector<float> aa) {
        sort(aa.begin(), aa.end());
        return aa.back();
    };

    for (int i = 0; i < a.size(); ++i) {
        if (i + 1 < window) {
            result.push_back(NAN);
        } else {
            result.push_back(getmaxval(vector<float>(&a[i - window + 1], &a[i + 1])));
        }
    }

    return result;
}

#endif // ALPHA101_H
