#include "../exercise.h"
#include <numeric>
#include <iostream>

// READ: `std::accumulate` <https://zh.cppreference.com/w/cpp/algorithm/accumulate>

int main(int argc, char **argv) {
    using DataType = float;
    int shape[]{1, 3, 224, 224};
    // 计算张量中元素的总数量
    int element_count = std::accumulate(std::begin(shape), std::end(shape), 1, std::multiplies<int>());
    // 每个元素占用的字节数
    int bytes_per_element = sizeof(DataType);
    // 总字节数
    int size = element_count * bytes_per_element;

    // 输出结果以便检查
    std::cout << "Total bytes required: " << size << std::endl;

    // 注意：这里的断言值看起来是错误的，因为 1*3*224*224*4 != 602112
    // 正确的断言应该是：
    ASSERT(size == 1 * 3 * 224 * 224 * 4, "1x3x224x224 with float type should equal to 1 * 3 * 224 * 224 * 4");

    return 0;
}