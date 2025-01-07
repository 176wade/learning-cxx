#include "../exercise.h"
#include <iostream>
#include <cassert>

struct Fibonacci {
    unsigned long long cache[128];
    int cached;

    // 构造函数初始化缓存和计数器
    Fibonacci() : cached(2) {
        cache[0] = 0; // F(0)
        cache[1] = 1; // F(1)
    }

    // 实现正确的缓存优化斐波那契计算
    unsigned long long get(int i) {
        // 如果索引大于或等于数组长度，直接返回0以避免越界访问
        if (i >= 128) return 0;

        // 如果索引小于等于1或已经在缓存中，则直接返回
        if (i <= 1 || i < cached) {
            return cache[i];
        }

        // 填充缓存直到第i个斐波那契数
        for (; cached <= i && cached < 128; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        
        // 返回计算结果或已缓存的结果
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // 初始化缓存结构体，使计算正确
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