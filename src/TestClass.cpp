//
// Created by jonas on 9/24/19.
//

#include "TestClass.hpp"

TestClass::TestClass(int age) : age(age) {}

int TestClass::getAge() const {
    return age;
}

void TestClass::setAge(int age) {
    TestClass::age = age;
}
