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
    
    template<class A>
    struct custom_allocator {
        typedef A value_type;
        custom_allocator() noexcept {}
        template <class U> custom_allocator (const custom_allocator<U>&) noexcept {}
        A* allocate (size_t size) {
            return static_cast<A*>( operator new(size*sizeof(A)));
        }
        void deallocate (A* p, size_t size) {
            operator delete(p, size);
        }
    };
    
    static void * operator new(size_t size) {
        std::cout << "operator new!" << std::endl;
        return ::operator new(size);
    }
    static void operator delete(void *p, size_t size) {
        std::cout << "operator delete!" << std::endl;
        return ::operator delete(p);
    }
};


int main() {
    //auto sp = std::make_shared<A>();
    A::custom_allocator<A> allocator;
    auto sp = std::allocate_shared<A>(allocator);
}

