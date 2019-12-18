//
//  main.cpp
//  L14_task1
//
//  Created by Анна on 18.12.2019.
//  Copyright © 2019 Анна. All rights reserved.
//

#include <iostream>

template <char ...c> struct TString {
    static constexpr char value[sizeof...(c)+1] = {c...,'\0'};
    static constexpr int size = sizeof...(c);
    template<char ...t, char ...d>
    constexpr bool friend operator==(const TString<t...>& left, const TString<d...>& right);
};

template<char ...c, char ...d>
static constexpr TString<c..., d...> operator+(const TString<c...>& left, const TString<d...>& right) {
    return TString<c..., d...>();
}

template<char ...c, char ...d>
static constexpr bool operator==(const TString<c...>& left, const TString<d...>& right){
    if (left.size != right.size) return false;
    else
        for (auto i = 0; i < left.size; i++) {
            if (left.value[i] != right.value[i]) return false;
        }
    return true;
}

template <typename c, c ... str>
constexpr TString<str...> operator "" _s() {
    return TString<str...>();
}


int main(int argc, const char * argv[]) {
    constexpr auto hello = "hello"_s + " world"_s;
    static_assert(hello == "hello world"_s);
    return 0;
}
