#include <iostream>
using namespace std;

class Student {
    public:
        Student();
        Student();
        string getName();
        void setName();
        int getAge();
        void setAge();
        void output();

    private:
        string name;
        int age;
};

int main()
{
    Student s1, s2("Michael");

    return 0;
}