//
//  main.cpp
//  prak_L11_t1
//
//  Created by Анна on 28/11/2019.
//  Copyright © 2019 Анна. All rights reserved.
//

#include <iostream>
#include <tuple>

template <class ...>
struct are_same_base {};

template <class ...>
struct are_same {};

template<class First, class Second>
struct are_same_base <First,Second> : public std::false_type {
};

template<class First>
struct are_same_base <First, First> : public std::true_type {
};

template<class First, class Second, class ...Args>
struct are_same_base <First, Second, Args...> : public std::false_type{};

template<class First, class ...Args>
struct are_same_base <First, First, Args...> : public are_same<First, Args...> {};

template<class First, class Second, class ...Args>
struct are_same <First, Second, Args...> : public are_same_base <std::decay_t<First>, std::decay_t<Second>, Args...> {};

template<class ...Args >
constexpr bool are_same_v = are_same<Args...>::value;


int main(int argc, const char * argv[]) {
    static_assert(are_same_v<int, int32_t, signed int>,  "compile assert");
    return 0;
}
