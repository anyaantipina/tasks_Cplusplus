//
//  main.cpp
//  plus_prak
//
//  Created by Анна on 21/10/2019.
//  Copyright © 2019 Анна. All rights reserved.
//

#include <iostream>
class A {
public:
    
    static void * operator new(size_t size) {
        std::cout << "operator new!" << std::endl;
        return ::operator new(size);
    }
    static void operator delete(void *p, size_t size) {
        std::cout << "operator delete!" << std::endl;
        return ::operator delete(p);
    }
};

template<class T, class TT>
struct custom_allocator {
    typedef T value_type;
    custom_allocator() noexcept {}
    template <class U> custom_allocator (const custom_allocator<U,U>&) noexcept {}
    T* allocate (size_t size) {
        return static_cast<T*>(TT::operator new(size*sizeof(T)));
    }
    void deallocate (T* p, size_t size) {
        TT::operator delete(p, size);
    }
};

int main() {
    //auto sp = std::make_shared<A>();
    custom_allocator<A,A> allocator;
    auto sp = std::allocate_shared<A>(allocator);
}
