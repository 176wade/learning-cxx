#include "../exercise.h"

// READ: 左值右值（概念）<https://learn.microsoft.com/zh-cn/cpp/c-language/l-value-and-r-value-expressions?view=msvc-170>
// READ: 左值右值（细节）<https://zh.cppreference.com/w/cpp/language/value_category>
// READ: 关于移动语义 <https://learn.microsoft.com/zh-cn/cpp/cpp/rvalue-reference-declarator-amp-amp?view=msvc-170#move-semantics>
// READ: 如果实现移动构造 <https://learn.microsoft.com/zh-cn/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170>

// READ: 移动构造函数 <https://zh.cppreference.com/w/cpp/language/move_constructor>
// READ: 移动赋值 <https://zh.cppreference.com/w/cpp/language/move_assignment>
// READ: 运算符重载 <https://zh.cppreference.com/w/cpp/language/operators>

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

    // 实现移动构造器
    DynFibonacci(DynFibonacci &&other) noexcept 
        : cache(other.cache), capacity(other.capacity), cached(other.cached) {
        other.cache = nullptr; // 防止析构时释放原对象的资源
        other.capacity = 0;
        other.cached = 0;
    }

    // 实现移动赋值操作符
    DynFibonacci &operator=(DynFibonacci &&other) noexcept {
        if (this != &other) { // 检查是否是自我赋值
            delete[] cache; // 释放当前资源
            cache = other.cache;
            capacity = other.capacity;
            cached = other.cached;

            other.cache = nullptr; // 防止析构时释放原对象的资源
            other.capacity = 0;
            other.cached = 0;
        }
        return *this;
    }

    // 实现析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache;
    }

    // 实现正确的缓存优化斐波那契计算
    size_t operator[](int i) {
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
    size_t operator[](int i) const {
        ASSERT(i <= cached, "i out of range");
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    bool is_alive() const {
        return cache != nullptr;
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    // 使用 std::move 创建常量引用
    DynFibonacci const fib_ = std::move(fib);
    ASSERT(!fib.is_alive(), "Object moved");
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    fib0 = std::move(fib1);
    fib0 = std::move(fib0); // 自我赋值测试
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}
