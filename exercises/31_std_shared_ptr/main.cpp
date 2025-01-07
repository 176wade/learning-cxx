#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10);
    std::shared_ptr<int> ptrs[]{shared, shared, shared};

    std::weak_ptr<int> observer = shared;
    ASSERT(observer.use_count() == 4, "Initial use count should be 4");

    ptrs[0].reset();
    ASSERT(observer.use_count() == 3, "After reset ptrs[0], use count should be 3");

    ptrs[1] = nullptr;
    ASSERT(observer.use_count() == 2, "After setting ptrs[1] to nullptr, use count should be 2");

    // Correct the assignment so that ptrs[2] still points to the original object
    ptrs[2] = shared;
    ASSERT(observer.use_count() == 3, "After reassigning ptrs[2] to shared, use count should be 3");

    ptrs[0] = shared;
    ptrs[1] = shared;
    ptrs[2] = std::move(shared);
    ASSERT(observer.use_count() == 4, "After restoring ptrs, use count should be 4");

    std::ignore = std::move(ptrs[0]);
    ptrs[1] = std::move(ptrs[1]);
    ptrs[1] = std::move(ptrs[2]);
    ASSERT(observer.use_count() == 1, "After moving and releasing ptrs, use count should be 1");

    shared = observer.lock();
    ASSERT(observer.use_count() == 2, "After locking weak_ptr, use count should be 2");

    shared = nullptr;
    for (auto &ptr : ptrs) ptr = nullptr;
    ASSERT(observer.use_count() == 0, "After destroying all shared_ptrs, use count should be 0");

    shared = observer.lock();
    ASSERT(observer.use_count() == 0, "After trying to lock again, use count should still be 0");

    return 0;
}