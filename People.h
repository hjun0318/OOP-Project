#ifndef PEOPLE_H
#define PEOPLE_H
#include <string>
#include <iostream>
using namespace std;

class People
{
protected:
    string name;
    int age;
    string password;

public:
    void setName(string name);
    void setAge(int age);
    void setPassword(string password); 

    string getName();
    int getAge();
    string getPassword();
};

#endif