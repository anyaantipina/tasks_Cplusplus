//
//  main.cpp
//  prak_L11_t3
//
//  Created by Анна on 28/11/2019.
//  Copyright © 2019 Анна. All rights reserved.
//

#include <iostream>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <exception>

class TMyException: public std::exception {
private:
    const char* message;
     
public:
    TMyException(std::string m): message(m.c_str()) {}
    const char* what() const noexcept {
        return message;
    }
    friend std::ostream& operator<< (std::ostream &out, const TMyException &exep);
};

std::ostream& operator<< (std::ostream &out, const TMyException &exep) {
    out << exep.message;
    return out;
}

class FirstExcept : public TMyException {
public:
    FirstExcept(std::string m): TMyException(m) {}
    const char* what() const noexcept {
        return this->what();
    }
};

class SecondExcept : public TMyException {
public:
    SecondExcept(std::string m): TMyException(m) {}
    const char* what() const noexcept {
        return this->what();
    }
};


void CheckBase () {
    throw TMyException("The TMyException");
}
void CheckFirst () {
    throw FirstExcept("The FirstExcept");
}
void CheckSecond () {
    throw SecondExcept("The SecondExcept");
}


TEST(MyTest, CheckExceptions) {
    EXPECT_THROW(CheckBase(), TMyException);
    EXPECT_THROW(CheckFirst(), FirstExcept);
    EXPECT_THROW(CheckSecond(), SecondExcept);
}


int main(int argc, char * argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    return 0;
}
