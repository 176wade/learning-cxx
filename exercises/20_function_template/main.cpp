#include "../exercise.h"
#include <cmath> // 用于 std::abs

// 将这个函数模板化
template <typename T>
T plus(T a, T b) {
    return a + b;
}

// 定义一个辅助函数来比较浮点数
template <typename T>
bool nearly_equal(T a, T b, T epsilon = T(1e-5)) {
    return std::abs(a - b) <= epsilon;
}

int main(int argc, char **argv) {
    // 测试整数加法
    ASSERT(plus(1, 2) == 3, "Plus two int");
    ASSERT(plus(1u, 2u) == 3u, "Plus two unsigned int");

    // 测试浮点数加法，并使用 nearly_equal 来比较结果
    ASSERT(nearly_equal(plus(1.25f, 2.5f), 3.75f), "Plus two float");
    ASSERT(nearly_equal(plus(1.25, 2.5), 3.75), "Plus two double");

    // 修改判断条件使测试通过，特别是对于0.1 + 0.2的情况
    ASSERT(nearly_equal(plus(0.1, 0.2), 0.3), "How to make this pass?");

    return 0;
}