//
//  main.cpp
//  L14_task2
//
//  Created by Анна on 18.12.2019.
//  Copyright © 2019 Анна. All rights reserved.
//

#include <iostream>
#include <map>
#include <exception>
#include <iterator>
#include <ctime>
#define N 800000
#define N2 N*2
#define N3 N*3


int main(int argc, const char * argv[]) {
    std::map<int,int> myMap1, myMap2, myMap3, myMap4;
    for (auto i = 0; i < N; i++) {
        myMap1.insert(std::make_pair(i,i));
        myMap2.insert(std::make_pair(i,i));
        myMap3.insert(std::make_pair(i,i));
        myMap4.insert(std::make_pair(i,i));
    }
    for (auto i = N2; i < N3; i++) {
        myMap1.insert(std::make_pair(i,i));
        myMap2.insert(std::make_pair(i,i));
    }
    
    std::cout << "First example: insert in the middle of a sorted map\n";
    std::clock_t t1 = std::clock();
    for (auto i = N; i < N2; i++) {
        myMap1.insert(std::make_pair(i,i));
    }
    std::clock_t t2 = std::clock();
    std::cout << float((t2 - t1)) / CLOCKS_PER_SEC<< std::endl;
    auto hint = myMap2.find(N2);
    t1 = std::clock();
    for (auto i = N; i < N2; i++) {
        myMap1.insert(hint, std::make_pair(i,i));
    }
    t2 = std::clock();
    std::cout << float((t2 - t1)) / CLOCKS_PER_SEC << std::endl;
    

    std::cout << "Second example: insert in the end of a sorted map\n";
    t1 = std::clock();
    for (auto i = N; i < N2; i++) {
        myMap3.insert(std::make_pair(i,i));
    }
    t2 = std::clock();
    std::cout << float((t2 - t1)) / CLOCKS_PER_SEC<< std::endl;
    t1 = std::clock();
    for (auto i = N; i < N2; i++) {
        myMap4.insert(myMap4.end(), std::make_pair(i,i));
    }
    t2 = std::clock();
    std::cout << float((t2 - t1)) / CLOCKS_PER_SEC << std::endl;
    
    std::cout << "Third example: filling the map from the end\n";
    std::map<int,int> myMap5, myMap6;
    t1 = std::clock();
    for (auto i = N2-1; i >= 0; i--) {
        myMap5.insert(std::make_pair(i, i));
    }
    t2 = std::clock();
    std::cout << float((t2 - t1)) / CLOCKS_PER_SEC<< std::endl;
    auto it = myMap6.end();
    t1 = std::clock();
    for (auto i = N2-1; i >= 0; i--) {
        it = myMap6.insert(it,std::make_pair(i, i));
    }
    t2 = std::clock();
    std::cout << float((t2 - t1)) / CLOCKS_PER_SEC<< std::endl;
    return 0;
}
