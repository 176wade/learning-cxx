#include "../exercise.h"
#include <iostream>
#include <cassert>

class Fibonacci {
    size_t cache[16];
    int cached;

public:
    // 实现构造器，初始化缓存和计数器
    Fibonacci() : cached(2) {
        if (16 >= 2) { // Ensure the array can at least hold two elements
            cache[0] = 0; // F(0)
            cache[1] = 1; // F(1)
        }
    }

    // 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        // 如果索引大于或等于数组长度，直接返回0以避免越界访问
        if (i >= 16) return 0;

        // 如果索引小于等于1或已经在缓存中，则直接返回
        if (i <= 1 || i < cached) {
            return cache[i];
        }

        // 填充缓存直到第i个斐波那契数
        for (; cached <= i && cached < 16; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }

        // 返回计算结果或已缓存的结果
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // 现在类型拥有无参构造器，声明时会直接调用。
    // 这个写法不再是未定义行为了。
    Fibonacci fib;

    // 测试
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;

    // 打印更多的测试结果以确认缓存工作正常
    for (int i = 0; i <= 10; ++i) {
        std::cout << "fibonacci(" << i << ") = " << fib.get(i) << std::endl;
    }

    return 0;
}