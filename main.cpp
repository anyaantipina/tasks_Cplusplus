//
//  main.cpp
//  tasks
//
//  Created by Анна on 26/09/2019.
//  Copyright © 2019 Анна. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <vector>
#include <assert.h>

struct TItem {
    int value;
    time_t timestamp;
    TItem(int v)
            : value(v)
            , timestamp(std::time(0)) {}
    bool operator== (int v) const {
        return value == v;
    }
};

using Items = std::vector<TItem>;

template <int... Args>
Items MakeItemsSimple () {
    Items tmp = {Args ...};
    return tmp;
}

auto MakePredicate(Items values) {
    auto search = [values] (int value) {
        if (values.size() != 0) {
            auto find = std::find(values.begin(), values.end(), value);
            return find != values.end();
        }
        else
            return false;
    };
    return search;
}


int main(int argc, const char * argv[]) {
    Items items = MakeItemsSimple<0, 1, 4, 5, 6>();

    Items newItems = MakeItemsSimple<7, 15, 1>();
    auto isFound = MakePredicate(items);
    auto isFoundNew = MakePredicate(newItems);
    assert(isFound(0) == true);
    assert(isFound(7) == false);
    assert(isFoundNew(7) == true);
    assert(isFoundNew(6) == false);
    return 0;
}
