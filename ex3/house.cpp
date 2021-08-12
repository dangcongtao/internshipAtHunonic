#include<iostream>
#include<string.h>
#include"house.h"
#include<stdio_ext.h>

using namespace std;


House::House(){
    memset(this->house_id, 0, sizeof(house_id));
    this->house_age = 0;
};
House::~House(){

};


void House::type_house_infor (){
    int _house_age;
    char _house_id[30];

    cout << "type house id: ";
    cin>> _house_id;
    __fpurge(stdin);

    cout << "type house age(int): ";
    cin>>_house_age;
    __fpurge(stdin);

    this->set_house_age(_house_age);
    this->set_house_id(_house_id);
};
void House::print_all_house_infor (){
    cout << "house id: " << this->get_house_id();
    cout << "house age: " << this->get_house_age();
};
void House::set_house_id (char *_house_id){
    memset(this->house_id, 0 , sizeof(house_id));
    strcpy(this->house_id,_house_id);
};
void House::set_house_age (int _house_age){
    this->house_age = _house_age;
};

char* House::get_house_id (){
    return this->house_id;
};
int House::get_house_age (){
    return this->house_age;
};