#include <iostream>
#include <string>
#include <json/json.h>

struct Student
{
    std::string name;
    int age;
};

template<class T>
struct reflect_trait{};

template<>
struct reflect_trait<Student>
{
    template<class Func>
    static void for_each_members(Student& stu, Func&& func)
    {
        func("name", stu.name);
        func("age", stu.age);
    }
};

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
    };
    std::string bin = serialize(stu);
    std::cout << bin << '\n';
    return 0;
}
