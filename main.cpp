#include <iostream>
#include <string>
#include <json/json.h>

#define REFLECT_PP_FOREACH_2(f, x, y) f(x) f(y)
#define REFLECT_PP_FOREACH_3(f, x, y, z) f(x) f(y) f(z)

struct Student
{
    std::string name;
    int age;
};

template<class T>
struct reflect_trait{};

#define REFLECT_BEGIN(Type) \
template<> \
struct reflect_trait<Student> \
{ \
    template<class Func> \
    static void for_each_members(Student& stu, Func&& func) \
    { \

#define REFLECT_PER_MEMBER(x) \
    func(#x, stu.x);

#define REFLECT_END() \
    } \
};


#define REFLECT(Type, ...) \
REFLECT_BEGIN(Student) \
REFLECT_PP_FOREACH_2(REFLECT_PER_MEMBER, __VA_ARGS__); \
REFLECT_END()

REFLECT(Student, name, age);

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
