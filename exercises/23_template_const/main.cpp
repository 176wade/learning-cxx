#include "../exercise.h"
#include <cstring>
#include <stdexcept>

template<unsigned int N, class T>
struct Tensor {
    unsigned int shape[N];
    T *data;

    // 构造函数：初始化 shape 和 data
    Tensor(unsigned int const shape_[N]) {
        for (unsigned int i = 0; i < N; ++i) {
            shape[i] = shape_[i];
        }
        unsigned int size = 1;
        for (unsigned int i = 0; i < N; ++i) {
            size *= shape[i]; // 计算总的元素数量
        }
        data = new T[size];
        std::memset(data, 0, size * sizeof(T)); // 初始化数据为0
    }

    // 析构函数：释放分配的内存
    ~Tensor() {
        delete[] data;
    }

    // 禁止复制和移动
    Tensor(Tensor const &) = delete;
    Tensor(Tensor &&) noexcept = delete;

    // 下标运算符重载
    T &operator[](unsigned int const indices[N]) {
        return data[data_index(indices)];
    }
    T const &operator[](unsigned int const indices[N]) const {
        return data[data_index(indices)];
    }

private:
    // 将多维索引转换为一维索引
    unsigned int data_index(unsigned int const indices[N]) const {
        unsigned int index = 0;
        unsigned int stride = 1;
        for (int i = N - 1; i >= 0; --i) { // 从最后一个维度开始计算
            ASSERT(indices[i] < shape[i], "Invalid index");
            index += indices[i] * stride;
            stride *= shape[i];
        }
        return index;
    }
};

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    {
        unsigned int shape[]{2, 3, 4, 5};
        auto tensor = Tensor<4, int>(shape);

        unsigned int i0[]{0, 0, 0, 0};
        tensor[i0] = 1;
        ASSERT(tensor[i0] == 1, "tensor[i0] should be 1");
        ASSERT(tensor.data[0] == 1, "tensor[i0] should be 1");

        unsigned int i1[]{1, 2, 3, 4};
        tensor[i1] = 2;
        ASSERT(tensor[i1] == 2, "tensor[i1] should be 2");
        ASSERT(tensor.data[119] == 2, "tensor[i1] should be 2");
    }
    {
        unsigned int shape[]{7, 8, 128};
        auto tensor = Tensor<3, float>(shape);

        unsigned int i0[]{0, 0, 0};
        tensor[i0] = 1.f;
        ASSERT(tensor[i0] == 1.f, "tensor[i0] should be 1");
        ASSERT(tensor.data[0] == 1.f, "tensor[i0] should be 1");

        unsigned int i1[]{3, 4, 99};
        tensor[i1] = 2.f;
        ASSERT(tensor[i1] == 2.f, "tensor[i1] should be 2");
        ASSERT(tensor.data[3683] == 2.f, "tensor[i1] should be 2");
    }
    return 0;
}
