#include "../exercise.h"
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>

// READ: `std::transform` <https://zh.cppreference.com/w/cpp/algorithm/transform>
// READ: `std::vector::begin` <https://zh.cppreference.com/w/cpp/container/vector/begin>

int main(int argc, char **argv) {
    std::vector<int> val{8, 13, 21, 34, 55};
    // 定义一个空的字符串向量用于存放转换结果
    std::vector<std::string> ans;

    // 预先分配空间以提高性能
    ans.reserve(val.size());

    // 使用 `std::transform` 对 `val` 中的每个元素乘以2，并转换为字符串存入 `ans`
    std::transform(val.begin(), val.end(), std::back_inserter(ans), [](int num) {
        std::ostringstream oss;
        oss << num * 2;
        return oss.str();
    });

    // 或者使用 to_string 直接转换
    // std::transform(val.begin(), val.end(), std::back_inserter(ans), 
    //                [](int num) { return std::to_string(num * 2); });

    // 断言检查
    ASSERT(ans.size() == val.size(), "ans size should be equal to val size");
    ASSERT(ans[0] == "16", "ans[0] should be 16");
    ASSERT(ans[1] == "26", "ans[1] should be 26");
    ASSERT(ans[2] == "42", "ans[2] should be 42");
    ASSERT(ans[3] == "68", "ans[3] should be 68");
    ASSERT(ans[4] == "110", "ans[4] should be 110");

    return 0;
}