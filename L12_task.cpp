//
//  main.cpp
//  prak_L12_t
//
//  Created by Анна on 28/11/2019.
//  Copyright © 2019 Анна. All rights reserved.
//

#include <iostream>
#include <exception>
#include <optional>
#include <iterator>
#include <memory>
#include <unordered_set>
#include "gmock/gmock.h"
#include "gtest/gtest.h"

class TRange : std::enable_shared_from_this<TRange>{
private:
    int64_t N;
    int64_t M;
    int64_t s;
    int64_t size;
    
public:

    class const_iterator: public std::iterator<std::forward_iterator_tag, int64_t> {
    public:
        const_iterator(int64_t ii, const TRange& r) : i(ii) {
            c_ptr = std::make_shared<TRange>(r);
            if (i == c_ptr->size) ptr = nullptr;
            if (c_ptr->size == 0) ptr = nullptr;
            else {
                ptr = std::make_shared<int64_t>(r.N+r.s*ii);
            }
        }
        const_iterator(const const_iterator &it) : ptr(it.ptr), c_ptr(it.c_ptr), i(it.i) {}

        bool operator!=(const_iterator const& it) const {
            if ((ptr==nullptr) && (it.ptr==nullptr))
                return false;
            else {
                if ((ptr==nullptr)&&(it.ptr!=nullptr)) return false;
                if ((it.ptr==nullptr)&&(ptr!=nullptr)) return false;
                return *ptr != *(it.ptr);
            }
        }
        typename const_iterator::reference operator*() const {
            if (((i < c_ptr->size) && (i>0)) || ((i==0) && (c_ptr->size!=0)))
                return *ptr;
            else throw std::out_of_range("index out of range");
            
        }
        const_iterator& operator++() {
            i++;
            if ((((i<c_ptr->size) && (i>0)) && (i*c_ptr->s <= (c_ptr->M - c_ptr->N))) || ((i==0) && (c_ptr->size!=0)) || (i==c_ptr->size)) {
                if (i==c_ptr->size) ptr = nullptr;
                else *ptr = *((*c_ptr)[i]);
                return *this;
            }
            else throw std::out_of_range("index out of range");
        }
        const_iterator operator++(int) {
            const_iterator ret = *this;
            this->operator++();
            return ret;
        }
        
    private:
        std::shared_ptr<int64_t> ptr;
        std::shared_ptr<TRange> c_ptr;
        int64_t i;
    };
    
    TRange(int64_t nn, int64_t mm, int64_t ss) {
        if (ss == 0) {
            throw std::invalid_argument("s can not equal zero");
        }
        else {
            N = nn;
            M = mm;
            s = ss;
            size = (((M - N)/s + 1) > 0) ? (M - N)/s + 1 : 0;
        }
    }
    TRange(const TRange& elem) : N(elem.N), M(elem.M), s(elem.s), size(elem.size) {}
    
    const_iterator begin() const {
        return const_iterator (0, *this);
        
    }
    const_iterator end() const {
        return const_iterator (size, *this);
    }
    
    std::optional<int64_t> operator[](int64_t i) const {
        if (((i>0) && (i*s <= (M - N))) || ((i==0) && (size!=0))) return N + s*i;
        else return std::nullopt;
    }
    int64_t GetSize() const {
        return size;
    }
};

struct THashRange {
    void hashCombine(size_t& seed, const int64_t v) const {
        seed ^= std::hash<int64_t>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    size_t operator() (TRange const& p) const {
        size_t hash = 0;
        for (auto it : p) {
            hashCombine(hash, it);
        }
        return hash;
    }
};

struct TCompRange {
  bool operator() (const TRange& p1, const TRange& p2) const {
      if (p1.GetSize() != p2.GetSize()) return false;
      else {
          auto it_p2 = p2.begin();
          for (auto it_p1 : p1) {
              if (it_p1 != *it_p2) return false;
              it_p2++;
          }
          return true;
      }
  }
};

TEST(MyTest, TestInitConstructor) {
    EXPECT_NO_THROW(TRange(4,12,-1));
    EXPECT_THROW(TRange(4,12,0), std::invalid_argument);
}

TEST(MyTest, TestIndexOperator) {
    TRange c1(4,12,4); // trois elems: 4,8,12
    EXPECT_EQ(std::nullopt, (c1[-1]));
    EXPECT_EQ(8, *(c1[1]));
    EXPECT_EQ(std::nullopt, (c1[3]));
        
    TRange c2(4,12,-1);
    EXPECT_EQ(std::nullopt, c2[0]);
}

TEST(MyTest, TestGetSize) {
    TRange c1(4,12,4);
    EXPECT_EQ(c1.GetSize(), 3);
    TRange c2(4,12,3);
    EXPECT_EQ(c2.GetSize(), 3);
    TRange c3(4,12,-1);
    EXPECT_EQ(c3.GetSize(), 0);
}

TEST(MyTest, TestIterator) {
    TRange c1(4,12,4);
    auto it = c1.begin();
    EXPECT_EQ(*(it), 4);
    it++;
    EXPECT_EQ(*(it), 8);
    it++;
    EXPECT_EQ(*(it), 12);
    it++;
    EXPECT_THROW(*(it), std::out_of_range);
    EXPECT_FALSE(it!=c1.end());
    EXPECT_THROW(it++, std::out_of_range);
    it = c1.begin();
    static_assert(std::is_same<decltype(it), TRange::const_iterator>::value, "");
    it = c1.end();
    static_assert(std::is_same<decltype(it), TRange::const_iterator>::value, "");
}

TEST(MyTest, TestMap) {
    TRange c1(4,12,4); // trois elems: 4,8,12
    TRange c2(4,12,3); // trois elems: 4,7,10
    TRange c3(4,12,4); // trois elems: 4,8,12
    std::unordered_set<TRange, THashRange, TCompRange> set;
    set.insert(c1);
    EXPECT_EQ(set.size(), 1);
    set.insert(c2);
    EXPECT_EQ(set.size(), 2);
    set.insert(c3);
    EXPECT_EQ(set.size(), 2);
    EXPECT_TRUE(set.find(c1)!=set.end());
    EXPECT_TRUE(set.find(c2)!=set.end());
    EXPECT_TRUE(set.find(c3)!=set.end());
}

int main(int argc, char * argv[]) {
    try {
        TRange el(4,12,4); // trois elems: 4,8,12
        TRange el2(4,12,3); // trois elems: 4,7,10
        TRange el3(12,4,4); // zero elems
        
        std::cout << "\n...ITERATION THROUGH THE CONTAINER...\n";
        std::cout << "container(4,12,4).size = " << el.GetSize() << "\n    elems with iter: ";
        for (auto it = el.begin(); it!=el.end(); it++) {
            std::cout << *it << ", ";
        }
        std::cout << "\n    elems with [i]: ";;
        for (int i = 0; i < el.GetSize(); i++) {
            std::cout << *(el[i]) << ", ";
        }
        std::cout << std::endl;
        std::cout << "container(4,12,3).size = " << el2.GetSize() << "\n    elems with iter: ";
        for (auto it : el2) {
            std::cout << it << ", ";
        }
        std::cout << "\n    elems with [i]: ";;
        for (int i = 0; i < el2.GetSize(); i++) {
            std::cout << *(el2[i]) << ", ";
        }
        std::cout << std::endl;
        std::cout << "container(12,4,4).size = " << el3.GetSize() << "\n    elems with iter: ";
        for (auto it : el3) {
            std::cout << it << ", ";
        }
        std::cout << "\n    elems with [i]: ";;
        for (int i = 0; i < el3.GetSize(); i++) {
            std::cout << *(el3[i]) << ", ";
        }
        std::cout << std::endl;
    }
    catch (std::invalid_argument& er) {std::cout << er.what() << std::endl;}
    catch (std::out_of_range& er) {std::cout << er.what() << std::endl;}

    std::cout << "\n...TESTS...\n";
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
