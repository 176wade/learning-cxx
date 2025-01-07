#include "../exercise.h"
#include <cstring>
#include <stdexcept>

template<class T>
struct Tensor4D {
    unsigned int shape[4];
    T *data;

    // 构造函数
    Tensor4D(unsigned int const shape_[4], T const *data_) {
        for (int i = 0; i < 4; ++i) {
            shape[i] = shape_[i];
        }
        unsigned int size = shape[0] * shape[1] * shape[2] * shape[3];
        data = new T[size];
        std::memcpy(data, data_, size * sizeof(T));
    }

    // 析构函数
    ~Tensor4D() {
        delete[] data;
    }

    // 禁止复制和移动
    Tensor4D(Tensor4D const &) = delete;
    Tensor4D(Tensor4D &&) noexcept = delete;

    Tensor4D &operator+=(Tensor4D const &others) {
        // 检查形状兼容性并进行广播加法
        for (int dim = 0; dim < 4; ++dim) {
            if (shape[dim] != others.shape[dim] && others.shape[dim] != 1) {
                throw std::runtime_error("Incompatible shapes for broadcasting addition.");
            }
        }

        // 遍历所有元素，使用辅助函数获取正确索引
        for (unsigned int i = 0; i < shape[0]; ++i) {
            for (unsigned int j = 0; j < shape[1]; ++j) {
                for (unsigned int k = 0; k < shape[2]; ++k) {
                    for (unsigned int l = 0, idxThis = getIndex(i, j, k, l); l < shape[3]; ++l, ++idxThis) {
                        unsigned int idxOthers = getBroadcastIndex(i, j, k, l, others);
                        data[idxThis] += others.data[idxOthers];
                    }
                }
            }
        }
        return *this;
    }

private:
    unsigned int getIndex(unsigned int i, unsigned int j, unsigned int k, unsigned int l) const {
        return ((i * shape[1] + j) * shape[2] + k) * shape[3] + l;
    }

    unsigned int getBroadcastIndex(unsigned int i, unsigned int j, unsigned int k, unsigned int l, Tensor4D const &others) const {
        unsigned int idx = 0;
        unsigned int dims[] = {i, j, k, l};
        for (int dim = 0; dim < 4; ++dim) {
            idx = idx * others.shape[dim] + (others.shape[dim] == 1 ? 0 : dims[dim]);
        }
        return idx;
    }
};


// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    {
        unsigned int shape[]{1, 2, 3, 4};
        // clang-format off
        int data[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,

            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        // clang-format on
        auto t0 = Tensor4D<int>(shape, data);
        auto t1 = Tensor4D<int>(shape, data);
        t0 += t1;
        for (auto i = 0u; i < sizeof(data) / sizeof(*data); ++i) {
            ASSERT(t0.data[i] == data[i] * 2, "Tensor doubled by plus its self.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        // clang-format off
        float d0[]{
            1, 1, 1, 1,
            2, 2, 2, 2,
            3, 3, 3, 3,

            4, 4, 4, 4,
            5, 5, 5, 5,
            6, 6, 6, 6};
        // clang-format on
        unsigned int s1[]{1, 2, 3, 1};
        // clang-format off
        float d1[]{
            6,
            5,
            4,

            3,
            2,
            1};
        // clang-format on

        auto t0 = Tensor4D<float>(s0, d0);
        auto t1 = Tensor4D<float>(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            ASSERT(t0.data[i] == 7.f, "Every element of t0 should be 7 after adding t1 to it.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        // clang-format off
        double d0[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,

            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        // clang-format on
        unsigned int s1[]{1, 1, 1, 1};
        double d1[]{1};

        auto t0 = Tensor4D<double>(s0, d0);
        auto t1 = Tensor4D<double>(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            ASSERT(t0.data[i] == d0[i] + 1, "Every element of t0 should be incremented by 1 after adding t1 to it.");
        }
    }
}