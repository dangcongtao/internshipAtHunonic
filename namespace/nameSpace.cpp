#include<iostream>
#include<stdlib.h>

namespace nameSpaceTest {
class Student
{
private:
    /* data */
    int age;
    char *name = (char*)malloc(sizeof(char)*30);

public:
    Student(/* args */);
    ~Student();


};

Student::Student(/* args */)
{
}

Student::~Student()
{
}


}
using namespace std;
using namespace nameSpaceTest;

int main () {
}