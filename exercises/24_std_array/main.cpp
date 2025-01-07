#include "../exercise.h"
#include <array>
#include <cstring>

// READ: std::array <https://zh.cppreference.com/w/cpp/container/array>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    {
        std::array<int, 5> arr{{1, 2, 3, 4, 5}};
        ASSERT(arr.size() == 5, "Array size should be 5.");
        ASSERT(sizeof(arr) == sizeof(int) * 5, "Sizeof array should be the number of elements times the size of each element.");
        int ans[]{1, 2, 3, 4, 5};
        ASSERT(std::memcmp(arr.data(), ans, sizeof(ans)) == 0, "The contents of arr and ans should match.");
    }
    {
        std::array<double, 8> arr;
        ASSERT(arr.size() == 8, "Array size should be 8.");
        ASSERT(sizeof(arr) == sizeof(double) * 8, "Sizeof array should be the number of elements times the size of each element.");
    }
    {
        std::array<char, 21> arr{"Hello, InfiniTensor!"};
        ASSERT(arr.size() == 21, "Array size should be 21.");
        ASSERT(sizeof(arr) == sizeof(char) * 21, "Sizeof array should be the number of elements times the size of each element.");
        // 注意：arr.data() 指向数组的第一个元素，用于与 C 字符串比较
        ASSERT(std::strcmp(arr.data(), "Hello, InfiniTensor!") == 0, "String contents should match.");
    }
    return 0;
}