#include "../exercise.h"
#include <string>
#include <type_traits> // for std::is_same_v

// READ: 字符串 <https://zh.cppreference.com/w/cpp/string/basic_string>

int main(int argc, char **argv) {
    // 使用字符串字面量操作符 "s" 创建 std::string 类型的字符串
    using namespace std::string_literals;
    auto hello = "Hello"s;
    auto world = "world";
    
    // 使用 decltype 和 std::is_same_v 来检查变量的类型
    ASSERT((std::is_same_v<decltype(hello), std::string>), "Fill in the missing type.");
    ASSERT((std::is_same_v<decltype(world), const char*>), "Fill in the missing type.");
    
    // 构建完整的问候语句并检查它是否等于预期的字符串
    ASSERT(hello + ", " + world + '!' == "Hello, world!", "Fill in the missing string.");
    
    return 0;
}