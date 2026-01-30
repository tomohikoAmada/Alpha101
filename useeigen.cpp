#include <Eigen/Dense>
#include <iostream>

int main() {
    // 定义一个 2x2 的矩阵
    Eigen::Matrix2d matrix;
    matrix << 1, 2,
              3, 4;

    // 定义一个 2x1 的向量
    Eigen::Vector2d vector(5, 6);

    // 矩阵乘法
    auto result = matrix * vector;

    std::cout << "Matrix:\n" << matrix << std::endl;
    std::cout << "Result of Multiplication:\n" << result << std::endl;

    return 0;
}