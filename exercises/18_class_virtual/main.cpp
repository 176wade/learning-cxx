#include "../exercise.h"

// READ: 虚函数 <https://zh.cppreference.com/w/cpp/language/virtual>

struct A {
    virtual char virtual_name() const {
        return 'A';
    }
    char direct_name() const {
        return 'A';
    }
};
struct B : public A {
    char virtual_name() const override {
        return 'B';
    }
    char direct_name() const {
        return 'B';
    }
};
struct C : public B {
    char virtual_name() const final {
        return 'C';
    }
    char direct_name() const {
        return 'C';
    }
};
struct D : public C {
    char direct_name() const {
        return 'D';
    }
};

int main(int argc, char **argv) {
    constexpr auto MSG = "Replace '?' with its correct name.";

    A a;
    B b;
    C c;
    D d;

    // 直接调用对象的成员函数
    ASSERT(a.virtual_name() == 'A', MSG); // 虚函数调用，返回 'A'
    ASSERT(b.virtual_name() == 'B', MSG); // 虚函数调用，返回 'B'
    ASSERT(c.virtual_name() == 'C', MSG); // 虚函数调用，返回 'C'
    ASSERT(d.virtual_name() == 'C', MSG); // 虚函数调用，返回 'C' (因为 C::virtual_name 是 final)
    ASSERT(a.direct_name() == 'A', MSG);  // 非虚函数调用，返回 'A'
    ASSERT(b.direct_name() == 'B', MSG);  // 非虚函数调用，返回 'B'
    ASSERT(c.direct_name() == 'C', MSG);  // 非虚函数调用，返回 'C'
    ASSERT(d.direct_name() == 'D', MSG);  // 非虚函数调用，返回 'D'

    // 通过基类引用调用成员函数
    A &rab = b;
    B &rbc = c;
    C &rcd = d;

    ASSERT(rab.virtual_name() == 'B', MSG); // 虚函数调用，返回 'B'
    ASSERT(rbc.virtual_name() == 'C', MSG); // 虚函数调用，返回 'C'
    ASSERT(rcd.virtual_name() == 'C', MSG); // 虚函数调用，返回 'C'
    ASSERT(rab.direct_name() == 'A', MSG);  // 非虚函数调用，返回 'A'
    ASSERT(rbc.direct_name() == 'B', MSG);  // 非虚函数调用，返回 'B'
    ASSERT(rcd.direct_name() == 'C', MSG);  // 非虚函数调用，返回 'C'

    // 通过更高级别的基类引用调用成员函数
    A &rac = c;
    B &rbd = d;

    ASSERT(rac.virtual_name() == 'C', MSG); // 虚函数调用，返回 'C'
    ASSERT(rbd.virtual_name() == 'C', MSG); // 虚函数调用，返回 'C'
    ASSERT(rac.direct_name() == 'A', MSG);  // 非虚函数调用，返回 'A'
    ASSERT(rbd.direct_name() == 'B', MSG);  // 非虚函数调用，返回 'B'

    // 通过最高级别的基类引用调用成员函数
    A &rad = d;

    ASSERT(rad.virtual_name() == 'C', MSG); // 虚函数调用，返回 'C'
    ASSERT(rad.direct_name() == 'A', MSG);  // 非虚函数调用，返回 'A'

    return 0;
}

// READ: 扩展阅读-纯虚、抽象 <https://zh.cppreference.com/w/cpp/language/abstract_class>
// READ: 扩展阅读-虚继承 <https://zh.cppreference.com/w/cpp/language/derived_class>