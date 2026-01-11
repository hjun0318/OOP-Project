#include "People.h"

void People::setName(string name) {this->name = name;}
void People::setAge(int age) {this->age = age;}
void People::setPassword(string password) {this->password = password;}  

string People::getName() {return name;}
int People::getAge() {return age;}
string People::getPassword() {return password;}