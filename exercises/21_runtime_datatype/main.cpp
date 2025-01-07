#include "../exercise.h"
#include <cmath>

enum class DataType {
    Float,
    Double,
};

/// @brief Tagged union 即标签化联合体，是联合体的一种常见应用。
///        Rust enum 在实现上就是标签化联合体。
struct TaggedUnion {
    DataType type;
    // NOTICE: struct/union 可以相互任意嵌套。
    union {
        float f;
        double d;
    };
};

// 模板化的 sigmoid 函数
template <typename T>
T sigmoid(T x) {
    return static_cast<T>(1) / (static_cast<T>(1) + std::exp(-x));
}

TaggedUnion sigmoid_dyn(TaggedUnion x) {
    TaggedUnion ans{x.type};
    switch (x.type) {
        case DataType::Float:
            ans.f = sigmoid(x.f);
            break;
        case DataType::Double:
            ans.d = sigmoid(x.d);
            break;
    }
    return ans;
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    TaggedUnion xf{DataType::Float};
    xf.f = 5.f;
    auto yf = sigmoid_dyn(xf);
    ASSERT(yf.type == DataType::Float, "type mismatch");
    ASSERT(std::abs(yf.f - (1 / (1 + std::exp(-5.f)))) < 1e-6, "sigmoid float");

    TaggedUnion xd{DataType::Double};
    xd.d = 5.0;
    auto yd = sigmoid_dyn(xd);
    ASSERT(yd.type == DataType::Double, "type mismatch");
    ASSERT(std::abs(yd.d - (1 / (1 + std::exp(-5.0)))) < 1e-10, "sigmoid double");
    return 0;
}