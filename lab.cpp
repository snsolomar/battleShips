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

void Student::output()
{
    cout << "Student name is " << name << " age is " << age << "!" << endl; 
}

int main()
{
    Student s1, s2("Michael");

    s1.setName("Natalie");

    return 0;
}