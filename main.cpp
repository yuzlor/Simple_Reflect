#include <iostream>
#include <string>
#include <json/json.h>
#include "reflect.hpp"

struct Student
{
    std::string name;
    int age;
    int sex;
};

struct Baby
{
    std::string name;
    int age;
};


REFLECT(Student, name, age, sex);
REFLECT(Baby, name, age);

template<class T>
std::string serialize(T& object)
{
    Json::Value root;
    // root["name"] = stu.name;
    // root["age"] = stu.age;
    reflect_trait<T>::for_each_members(object, [&](const char* key, auto& value){ 
        root[key] = value;
    });

    return root.toStyledString();
}

int main()
{
    Student stu = {
        .name = "Jack",
        .age = 23,
        .sex = 1,
    };
    Baby baby = {
        .name = "Tom",
        .age = 2,
    };
    std::string bin = serialize(stu);
    std::cout << bin << '\n';
    std::string bin1 = serialize(baby);
    std::cout << bin1 << '\n';
    return 0;
}
