#include "../exercise.h"

// READ: 有 cv 限定符的成员函数 <https://zh.cppreference.com/w/cpp/language/member_functions>

struct Fibonacci {
    int numbers[11];
    // TODO: 修改方法签名和实现，使测试通过
    // 将 get 方法声明为 constexpr 以支持编译期求值
    constexpr int get(int i) const {
        // 检查索引是否在合法范围内
        if (i >= 0 && i < 11) {
            return numbers[i];
        } else {
            // 如果索引超出范围，可以抛出异常或返回一个特定值（这里简单地返回0）
            // 在 constexpr 上下文中不能抛出异常，所以选择返回0
            return 0;
        }
    }
};

int main(int argc, char **argv) {
    Fibonacci constexpr FIB{{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55}};
    ASSERT(FIB.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << FIB.get(10) << std::endl;
    return 0;
}
