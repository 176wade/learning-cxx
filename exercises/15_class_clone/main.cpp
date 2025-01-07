#include "../exercise.h"
#include <iostream>
#include <cassert>

class DynFibonacci {
    size_t *cache;
    int capacity; // 缓存容量
    int cached;   // 已缓存的数量

public:
    // 实现动态设置容量的构造器
    DynFibonacci(int cap) : capacity(cap), cached(2), cache(new size_t[capacity]) {
        if (capacity >= 2) { // 确保数组可以至少容纳两个元素
            cache[0] = 0; // F(0)
            cache[1] = 1; // F(1)
        }
    }

    // 显式弃置复制构造器和赋值操作符
    DynFibonacci(DynFibonacci const &) = delete;
    DynFibonacci& operator=(DynFibonacci const &) = delete;

    // 实现析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache;
    }

    // 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        // 如果索引大于或等于数组长度，直接返回0以避免越界访问
        if (i >= capacity) return 0;

        // 如果索引小于等于1或已经在缓存中，则直接返回
        if (i <= 1 || i < cached) {
            return cache[i];
        }

        // 填充缓存直到第i个斐波那契数
        for (; cached <= i && cached < capacity; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }

        // 返回计算结果或已缓存的结果
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    // const 修饰的 get 方法
    size_t get(int i) const {
        if (i >= capacity || i >= cached) {
            ASSERT(false, "i out of range");
        }
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // 使用指定的缓存容量创建 DynFibonacci 实例
    DynFibonacci fib(12);

    // 测试非 const 版本的 get 方法
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");

    // 创建常量引用而不是复制对象
    DynFibonacci const &fib_ = fib;
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");

    // 打印更多的测试结果以确认缓存工作正常
    for (int i = 0; i <= 10; ++i) {
        std::cout << "fibonacci(" << i << ") = " << fib.get(i) << std::endl;
    }

    return 0;
}