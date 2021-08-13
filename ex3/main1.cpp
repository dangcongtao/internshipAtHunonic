#include<iostream>
#include"house.h"
#include"person.h"
#include"string.h"
#include<fstream>
#include<stdio_ext.h>

using namespace std;

void input (Person **person, FILE *file_input, int n , int m) {
    int int_temp = 0;
    char char_temp[30];
    file_input = fopen("input.txt", "r");
    /*input */    
    for (int i = 0 ; i <n ; i ++) {
        
        /* discard \0 in the file 
        fgets(char_temp,255,file_input);*/

        for (int j = 0 ;j<m ; j ++) {

            memset(char_temp,0,sizeof(char_temp));
            fgets(char_temp,255,file_input);
            (person[i][j]).set_person_id(char_temp);

            memset(char_temp,0,sizeof(char_temp));
            fgets(char_temp,255,file_input);  
            person[i][j].set_person_name(char_temp);   
        }
    }
    fclose(file_input);
}

void print_all_infor (Person ** person, int n, int m, const char * string_push_in) {
    cout << "***"<< string_push_in <<"***\n";
    /* out put */
    for (int i = 0 ; i <n ; i ++) {
        
        cout<<endl;
        for (int j = 0 ;j<m ; j ++) {
            person[i][j].print_all_person_infor();
        }
        cout<< endl;
        cout << endl;
    }
    cout << "--- end " << string_push_in << "---\n\n";
}


void sort_by_person_id (Person **person, int n, int m) {
    /* sort sort by person */
    for (int i = 0 ; i < n ; i ++) {
        for (int j = 0 ;j < m-1 ; j ++) {
            for (int k = j+1 ; k < m ; k++) {
                if (strcmp(person[i][j].get_person_id(), person[i][k].get_person_id()) > 0){
                    /* swap */
                    Person temp;
                    temp.set_person_id(person[i][j].get_person_id());
                    temp.set_person_name(person[i][j].get_person_name());

                    person[i][j].set_person_id(person[i][k].get_person_id());
                    person[i][j].set_person_name(person[i][k].get_person_name());

                    person[i][k].set_person_id(temp.get_person_id());
                    person[i][k].set_person_name(temp.get_person_name());
                }
            }
        }
    }
}

void sort_by_person_name (Person **person, int n, int m){
    /* sort sort by person */
    for (int i = 0 ; i < n ; i ++) {
        for (int j = 0 ;j < m-1 ; j ++) {
            for (int k = j+1 ; k < m ; k++) {
                if (strcmp(person[i][j].get_person_name(), person[i][k].get_person_name()) > 0){
                    /* swap */
                    Person temp;
                    temp.set_person_id(person[i][j].get_person_id());
                    temp.set_person_name(person[i][j].get_person_name());

                    person[i][j].set_person_id(person[i][k].get_person_id());
                    person[i][j].set_person_name(person[i][k].get_person_name());

                    person[i][k].set_person_id(temp.get_person_id());
                    person[i][k].set_person_name(temp.get_person_name());
                }
            }
        }
    }
}



void sort_by_house (Person **person, int n , int m) {
    for (int i = 0 ; i <n-1 ; i ++) {
        for (int j = i+1 ;j<n ; j ++) {
            if (strcmp(person[i][0].get_person_id(), person[j][0].get_person_id()) > 0) {                
                
                /* swap house */
                Person *temp_per;
                temp_per = *&person[i];
                person[i] = *&person[j];
                person[j] = *(&temp_per);

                /* pointer pointer to no where - to be safe */
                temp_per = nullptr;
            }
        }
    }
}

int main () {
    int n = 3;
    int m = 3;

    Person **list_person;
    
    FILE *file;
    
    
    /* allocate */
    list_person = new Person*[m];
    for (int i = 0 ; i < n ; i ++) {
        (list_person[i]) = new Person[m];
    }
    
    input(list_person, file, n, m);
    print_all_infor(list_person, n, m, "print all infor ");
        
    // sort_by_person_id(list_person, n, m);
    // print_all_infor(list_person, n, m, " sort by person's id");

    sort_by_person_name(list_person, n,m);
    print_all_infor(list_person, n , m, " sort by person's name ");

    sort_by_house(list_person, n,m);
    print_all_infor(list_person, n , m, " sort by house ");



    /* anti leak */
    for (int i = 0 ; i < n ; i ++) {
        delete[] list_person[i];
        list_person[i] = nullptr;
    }
    delete[] list_person;
    list_person = nullptr;
    
    cout << "end..";
}