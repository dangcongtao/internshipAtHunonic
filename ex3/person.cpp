#include<iostream>
#include"person.h"
#include<string.h>
#include<stdio_ext.h>
using namespace std;

Person::Person(){
    memset(this->person_name,0,sizeof(this->person_name));
    memset(this->person_id,0, sizeof(this->person_id));
}
Person::~Person(){
    /* no pointer */
}


void Person::type_person_infor (){
    char person_id_temp[30];
    char person_name_temp[30];
    
    cout <<"type person id: ";
    cin>>person_id_temp;
    __fpurge(stdin);

    cout <<"type person name: ";
    scanf("%[a-zA-Z0-9 ]",person_name_temp);
    __fpurge(stdin);

    this->set_person_id(person_id_temp);
    this->set_person_name(person_name_temp);
};

void Person::print_all_person_infor(){
    cout << "\tperson id: " << this->get_person_id() << endl;
    cout << "\tperson name: "<< this->get_person_name() << endl;
};

void Person::set_person_id (char *_person_id){
    memset(this->person_id, 0 , sizeof(person_id));
    strcpy(person_id,_person_id);
};
void Person::set_person_name (char *_person_name){
    memset(this->person_name, 0 , sizeof(person_name));
    strcpy(person_name, _person_name);
};

char* Person::get_person_id (){
    return this->person_id;
};
char* Person::get_person_name (){
    return this->person_name;
};

