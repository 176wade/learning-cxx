#include "../exercise.h"
#include <vector>

using udim = unsigned int;

/// @brief 计算连续存储张量的步长
/// @param shape 张量的形状
/// @return 张量每维度的访问步长
std::vector<udim> strides(std::vector<udim> const &shape) {
    if (shape.empty()) return {};

    std::vector<udim> strides(shape.size());
    // 初始化最后一个维度的步长为 1
    strides.back() = 1;
    
    // 使用逆向遍历计算步长
    udim stride = 1;
    for (size_t i = shape.size(); i > 0; --i) {
        strides[i - 1] = stride;
        stride *= shape[i - 1];
    }

    return strides;
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    ASSERT((strides({2, 3, 4}) == std::vector<udim>{12, 4, 1}), "Make this assertion pass.");
    ASSERT((strides({3, 4, 5}) == std::vector<udim>{20, 5, 1}), "Make this assertion pass.");
    ASSERT((strides({1, 3, 224, 224}) == std::vector<udim>{150528, 50176, 224, 1}), "Make this assertion pass.");
    ASSERT((strides({7, 1, 1, 1, 5}) == std::vector<udim>{5, 5, 5, 5, 1}), "Make this assertion pass.");
    return 0;
}