// 根据 Article/101 Formulaic Alphas.pdf 和 WorldQuant_alpha101_code 中的 py 代码，
// 用简单 C++ 实现的 Alpha101

#include "alpha101.h"

// 所有函数实现已经在 alpha101.h 中，这里只保留 main() 函数

int main() {
    // 测试用例1: 与Python示例相同
    // 输入: [1, 2, 3, 4, 5], window=3
    // 期望输出: [NaN, NaN, 6, 9, 12]
    vector<float> test1 = {1, 2, 3, 4, 5};
    vector<float> result1 = rolling_ts_sum(test1, 3);

    cout << "测试1 (window=3):" << endl;
    cout << "输入: [1, 2, 3, 4, 5]" << endl;
    cout << "输出: ";
    print_result(result1);
    cout << "期望: [NaN, NaN, 6, 9, 12]" << endl;
    cout << endl;

    // 测试用例2: 更长的序列
    vector<float> test2 = {1, 2, 3, 4, 5, 6, 7, 8};
    vector<float> result2 = rolling_ts_sum(test2, 5);

    cout << "测试2 (window=5):" << endl;
    cout << "输入: [1, 2, 3, 4, 5, 6, 7, 8]" << endl;
    cout << "输出: ";
    print_result(result2);
    cout << endl;

    // 测试用例3: window=1 (应该返回原数组)
    vector<float> test3 = {10, 20, 30};
    vector<float> result3 = rolling_ts_sum(test3, 1);

    cout << "测试3 (window=1):" << endl;
    cout << "输入: [10, 20, 30]" << endl;
    cout << "输出: ";
    print_result(result3);
    cout << "期望: [10, 20, 30]" << endl;
    cout << endl;

    // SMA 测试用例1: 与Python示例相同
    // 输入: [2, 4, 6, 8, 10], window=3
    // 期望输出: [NaN, NaN, 4.0, 6.0, 8.0]
    vector<float> sma_test1 = {2, 4, 6, 8, 10};
    vector<float> sma_result1 = rolling_sma(sma_test1, 3);

    cout << "SMA测试1 (window=3):" << endl;
    cout << "输入: [2, 4, 6, 8, 10]" << endl;
    cout << "输出: ";
    print_result(sma_result1);
    cout << "期望: [NaN, NaN, 4, 6, 8]" << endl;
    cout << endl;

    // SMA 测试用例2
    vector<float> sma_test2 = {10, 20, 30, 40, 50};
    vector<float> sma_result2 = rolling_sma(sma_test2, 2);

    cout << "SMA测试2 (window=2):" << endl;
    cout << "输入: [10, 20, 30, 40, 50]" << endl;
    cout << "输出: ";
    print_result(sma_result2);
    cout << "期望: [NaN, 15, 25, 35, 45]" << endl;
    cout << endl;

    // Rolling Correlation 测试用例1: 与Python示例相同 - 完全正相关
    // x=[1, 2, 3, 4, 5], y=[2, 4, 6, 8, 10] (y=2x)
    // window=3时的期望输出: [NaN, NaN, 1.0, 1.0, 1.0]
    vector<float> corr_x1 = {1, 2, 3, 4, 5};
    vector<float> corr_y1 = {2, 4, 6, 8, 10};
    vector<float> corr_result1 = rolling_correlation(corr_x1, corr_y1, 3);

    cout << "Rolling Correlation 测试1 (window=3, 完全正相关):" << endl;
    cout << "输入x: [1, 2, 3, 4, 5]" << endl;
    cout << "输入y: [2, 4, 6, 8, 10] (y=2x)" << endl;
    cout << "输出: ";
    print_result(corr_result1);
    cout << "期望: [NaN, NaN, 1, 1, 1]" << endl;
    cout << endl;

    // Rolling Correlation 测试用例2: 完全负相关
    // x=[1, 2, 3, 4, 5], y=[10, 8, 6, 4, 2] (y=-2x+12)
    // 期望输出: [NaN, NaN, -1.0, -1.0, -1.0]
    vector<float> corr_x2 = {1, 2, 3, 4, 5};
    vector<float> corr_y2 = {10, 8, 6, 4, 2};
    vector<float> corr_result2 = rolling_correlation(corr_x2, corr_y2, 3);

    cout << "Rolling Correlation 测试2 (window=3, 完全负相关):" << endl;
    cout << "输入x: [1, 2, 3, 4, 5]" << endl;
    cout << "输入y: [10, 8, 6, 4, 2]" << endl;
    cout << "输出: ";
    print_result(corr_result2);
    cout << "期望: [NaN, NaN, -1, -1, -1]" << endl;
    cout << endl;

    // Rolling Correlation 测试用例3: 手动验证计算
    // x=[1, 2, 3], y=[2, 4, 6], window=3
    // 应该计算整个窗口: 平均值x̄=2, ȳ=4
    // 偏差x: [-1, 0, 1], 偏差y: [-2, 0, 2]
    // 相关系数: 4 / √(2×8) = 1.0
    vector<float> corr_x3 = {1, 2, 3};
    vector<float> corr_y3 = {2, 4, 6};
    vector<float> corr_result3 = rolling_correlation(corr_x3, corr_y3, 3);

    cout << "Rolling Correlation 测试3 (window=3, 手动验证):" << endl;
    cout << "输入x: [1, 2, 3]" << endl;
    cout << "输入y: [2, 4, 6]" << endl;
    cout << "输出: ";
    print_result(corr_result3);
    cout << "期望: [NaN, NaN, 1]" << endl;
    cout << endl;

    // Rolling Covariance 测试用例1: 与Python示例相同
    // x=[1, 2, 3, 4, 5], y=[2, 4, 6, 8, 10] (y=2x)
    // window=3时的期望输出: [NaN, NaN, 2.0, 2.0, 2.0]
    vector<float> cov_x1 = {1, 2, 3, 4, 5};
    vector<float> cov_y1 = {2, 4, 6, 8, 10};
    vector<float> cov_result1 = rolling_covariance(cov_x1, cov_y1, 3);

    cout << "Rolling Covariance 测试1 (window=3):" << endl;
    cout << "输入x: [1, 2, 3, 4, 5]" << endl;
    cout << "输入y: [2, 4, 6, 8, 10]" << endl;
    cout << "输出: ";
    print_result(cov_result1);
    cout << "期望: [NaN, NaN, 2, 2, 2]" << endl;
    cout << endl;

    // Rolling Covariance 测试用例2: 手动验证计算
    // x=[1, 2, 3], y=[2, 4, 6], window=3
    // 平均值: x̄=2, ȳ=4
    // 偏差: x=[-1,0,1], y=[-2,0,2]
    // 偏差乘积: [2,0,2]
    // 协方差: (2+0+2)/(3-1) = 2.0
    vector<float> cov_x2 = {1, 2, 3};
    vector<float> cov_y2 = {2, 4, 6};
    vector<float> cov_result2 = rolling_covariance(cov_x2, cov_y2, 3);

    cout << "Rolling Covariance 测试2 (window=3, 手动验证):" << endl;
    cout << "输入x: [1, 2, 3]" << endl;
    cout << "输入y: [2, 4, 6]" << endl;
    cout << "输出: ";
    print_result(cov_result2);
    cout << "期望: [NaN, NaN, 2]" << endl;
    cout << endl;

    // Rolling Covariance 测试用例3: 负协方差
    // x=[1, 2, 3, 4, 5], y=[10, 8, 6, 4, 2] (负相关)
    vector<float> cov_x3 = {1, 2, 3, 4, 5};
    vector<float> cov_y3 = {10, 8, 6, 4, 2};
    vector<float> cov_result3 = rolling_covariance(cov_x3, cov_y3, 3);

    cout << "Rolling Covariance 测试3 (window=3, 负协方差):" << endl;
    cout << "输入x: [1, 2, 3, 4, 5]" << endl;
    cout << "输入y: [10, 8, 6, 4, 2]" << endl;
    cout << "输出: ";
    print_result(cov_result3);
    cout << "期望: [NaN, NaN, -2, -2, -2]" << endl;

    return 0;
}
