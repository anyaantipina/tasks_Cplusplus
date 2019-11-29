//
//  main.cpp
//  prak_L11_t1
//
//  Created by Анна on 28/11/2019.
//  Copyright © 2019 Анна. All rights reserved.
//

#include <iostream>

class BaseObj {
public:
    virtual ~BaseObj() = default;
    virtual const std::type_info& type_info() const = 0;
};

template <typename T>
class ObjHolder : public BaseObj {
public:
    std::decay_t<T> value;
    ObjHolder(T v) : value(std::move(v)) {}
    const std::type_info& type_info() const{
        return typeid(value);
    }
};


class Any {
    std::shared_ptr<BaseObj> ObjPtr;
public:
    template <typename T>
    Any (const T& v) : ObjPtr(new ObjHolder<T>(v)) {}
    template<typename U>
        U get() const {
            U res;
            try {
                res = this->getHelp<U>();
            }
            catch (std::bad_typeid &t) {std::cout << "error in get()" << std::endl;}
            return res;
        }
        template<typename U>
        U getHelp() const {
            if(typeid(U) != ObjPtr->type_info()) {
                throw std::bad_typeid();
            }
            return static_cast<ObjHolder<U>* >(ObjPtr.get())->value;
        }
    };


    int main(int argc, const char * argv[]) {
        Any a(5);
        a.get<int>();
        a.get<std::string>(); // error
        return 0;
    }
