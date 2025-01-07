#include "../exercise.h"
#include <vector>
#include <iostream>

int main(int argc, char **argv) {
    // 构造函数调用：创建一个包含100个元素的向量，默认初始化为true。
    std::vector<bool> vec(100, true);
    ASSERT(vec[0], "Make this assertion pass.");
    ASSERT(vec[99], "Make this assertion pass.");
    ASSERT(vec.size() == 100, "Make this assertion pass.");

    std::cout << "sizeof(std::vector<bool>) = " << sizeof(std::vector<bool>) << std::endl;
    // 注意：这里的大小是平台相关的，并且依赖于实现细节，因此不能简单地断言它的具体值。
    
    // 测试 vec[20] 设置为 false
    {
        vec[20] = false;
        ASSERT(!vec[20], "vec[20] should be false.");
    }

    // 测试 push_back(false)
    {
        vec.push_back(false);
        ASSERT(vec.size() == 101, "After pushing back, size should be 101.");
        ASSERT(!vec[100], "The new element at index 100 should be false.");
    }

    // 测试获取副本并修改副本
    {
        bool ref = vec[30]; // 获取第30个元素的副本
        ASSERT(ref, "vec[30] should still be true.");
        ref = false; // 修改副本
        ASSERT(!ref, "The local copy ref should now be false.");
        // 确认原始 vec[30] 没有改变
        ASSERT(vec[30], "vec[30] should remain true after modifying the local copy.");
    }

    // 再次确认 vec[30] 的值没有被之前的测试块改变
    ASSERT(vec[30], "vec[30] should still be true after all previous tests.");

    return 0;
}