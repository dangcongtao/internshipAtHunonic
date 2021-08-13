#include<iostream>
#include"class_a.h"
using namespace std;

A::A(){

};
A::~A(){

};
void A::set_private_var_a(int _number ){
    private_variable_a = _number;
}
int A::get_private_var_a () {
    cout << "get in class a" << endl;
    return private_variable_a;
}




B::B(){

};
B::~B(){

};
int B::get_private_variable_b() {
    return private_variable_b;
}

int B::get_private_variable_a_from_b(){
    return this->get_private_var_a();
}

