#include "../exercise.h"
#include <cstring>
#include <vector>

// READ: std::vector <https://zh.cppreference.com/w/cpp/container/vector>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    {
        std::vector<int> vec{1, 2, 3, 4, 5};
        ASSERT(vec.size() == 5, "Vector size should be 5.");
        // `std::vector` 的大小是指它当前存储的元素数量。
        // 它与实际分配的内存容量不同，后者可能更大以允许快速添加新元素。
        ASSERT(sizeof(vec) != 5 * sizeof(int), "Sizeof vector is not directly related to the number of elements it holds.");
        int ans[]{1, 2, 3, 4, 5};
        ASSERT(std::memcmp(vec.data(), ans, sizeof(ans)) == 0, "The contents of vec and ans should match.");
    }
    {
        std::vector<double> vec{1, 2, 3, 4, 5};
        {
            ASSERT(vec.size() == 5, "Vector size should be 5.");
            ASSERT(sizeof(vec) != 5 * sizeof(double), "Sizeof vector is not directly related to the number of elements it holds.");
            double ans[]{1, 2, 3, 4, 5};
            ASSERT(std::memcmp(vec.data(), ans, sizeof(ans)) == 0, "The contents of vec and ans should match.");
        }
        {
            vec.push_back(6);
            ASSERT(vec.size() == 6, "After pushing back, vector size should be 6.");
            ASSERT(sizeof(vec) != 6 * sizeof(double), "Sizeof vector is not directly related to the number of elements it holds.");
            vec.pop_back();
            ASSERT(vec.size() == 5, "After popping back, vector size should return to 5.");
            ASSERT(sizeof(vec) != 5 * sizeof(double), "Sizeof vector is not directly related to the number of elements it holds.");
        }
        {
            vec[4] = 6;
            ASSERT(vec[0] == 1, "Element at index 0 should be 1.");
            ASSERT(vec[1] == 2, "Element at index 1 should be 2.");
            ASSERT(vec[2] == 3, "Element at index 2 should be 3.");
            ASSERT(vec[3] == 4, "Element at index 3 should be 4.");
            ASSERT(vec[4] == 6, "Element at index 4 should be updated to 6.");
        }
        {
            // `std::vector` 插入删除的时间复杂度通常是 O(n)，因为可能需要移动元素。
            vec.insert(vec.begin() + 1, 1.5);
            ASSERT((vec == std::vector<double>{1, 1.5, 2, 3, 4, 6}), "Make this assertion pass.");
            vec.erase(vec.begin() + 1);
            ASSERT((vec == std::vector<double>{1, 2, 3, 4, 6}), "Make this assertion pass.");
        }
        {
            vec.shrink_to_fit();
            ASSERT(vec.capacity() >= vec.size(), "Capacity should be at least as large as size after shrink_to_fit.");
            vec.clear();
            ASSERT(vec.empty(), "`vec` is empty now.");
            ASSERT(vec.size() == 0, "After clearing, vector size should be 0.");
            // After clear(), capacity may remain unchanged or reduced depending on implementation.
            // We cannot make a definite statement about capacity here.
        }
    }
    {
        std::vector<char> vec(48, 'z'); // 调用带有大小和初始值的构造函数
        ASSERT(vec[0] == 'z', "Make this assertion pass.");
        ASSERT(vec[47] == 'z', "Make this assertion pass.");
        ASSERT(vec.size() == 48, "Make this assertion pass.");
        ASSERT(sizeof(vec) != 48 * sizeof(char), "Sizeof vector is not directly related to the number of elements it holds.");
        {
            auto capacity = vec.capacity();
            vec.resize(16);
            ASSERT(vec.size() == 16, "After resizing, vector size should be 16.");
            ASSERT(vec.capacity() == capacity, "Capacity remains unchanged after resize unless shrink_to_fit is called.");
        }
        {
            vec.reserve(256);
            ASSERT(vec.size() == 16, "Reserve does not change size.");
            ASSERT(vec.capacity() == 256, "After reserving, capacity should be at least 256.");
        }
        {
            vec.push_back('a');
            vec.push_back('b');
            vec.push_back('c');
            vec.push_back('d');
            ASSERT(vec.size() == 20, "After pushing four elements, vector size should be 20.");
            ASSERT(vec.capacity() == 256, "Capacity should remain 256 as we reserved that much space.");
            ASSERT(vec[15] == 'z', "Element at index 15 should still be 'z'.");
            ASSERT(vec[16] == 'a', "Element at index 16 should be 'a'.");
            ASSERT(vec[17] == 'b', "Element at index 17 should be 'b'.");
            ASSERT(vec[18] == 'c', "Element at index 18 should be 'c'.");
            ASSERT(vec[19] == 'd', "Element at index 19 should be 'd'.");
        }
    }

    return 0;
}