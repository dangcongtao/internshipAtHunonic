#include<iostream>
#include"house.h"
#include"person.h"
#include"string.h"
#include<fstream>
#include<stdio_ext.h>

using namespace std;

int main () {
    int n = 2;
    int m = 3;

    Person **list_person;
    House *list_house;
    
    FILE *file = fopen("input.txt", "r");
    int int_temp = 0;
    char char_temp[30];
    
    /* allocate */
    list_person = new Person*[m];
    for (int i = 0 ; i < n ; i ++) {
        (list_person[i]) = new Person[m];
    }
    list_house = new House[n];

    /*input */    
    for (int i = 0 ; i <n ; i ++) {

        memset(char_temp,0,sizeof(char_temp));
        fgets(char_temp,255,file);
        list_house[i].set_house_id(char_temp);

        int_temp = 0;
        fscanf(file, "%d",&int_temp);
        list_house[i].set_house_age(int_temp);
        
        /* discard \0 in the file */
        fgets(char_temp,255,file);

        for (int j = 0 ;j<m ; j ++) {

            memset(char_temp,0,sizeof(char_temp));
            fgets(char_temp,255,file);
            list_person[i][j].set_person_id(char_temp);

            memset(char_temp,0,sizeof(char_temp));
            fgets(char_temp,255,file);  
            list_person[i][j].set_person_name(char_temp);   
        }
    }        
    
    fclose(file);

    cout << "***in tt***\n";
    /* out put */
    for (int i = 0 ; i <n ; i ++) {
        list_house[i].print_all_house_infor();
        cout<<endl;
        for (int j = 0 ;j<m ; j ++) {
            list_person[i][j].print_all_person_infor();
        }
        cout<< endl;
        cout << endl;
    }
    cout << "--- end in tt ---\n\n";


    /* sort sort by person */
    for (int i = 0 ; i < n ; i ++) {
        for (int j = 0 ;j < m-1 ; j ++) {
            for (int k = j+1 ; k < m ; k++) {
                if (strcmp(list_person[i][j].get_person_id(), list_person[i][k].get_person_id()) > 0){
                    /* swap */
                    Person temp;
                    temp.set_person_id(list_person[i][j].get_person_id());
                    temp.set_person_name(list_person[i][j].get_person_name());

                    list_person[i][j].set_person_id(list_person[i][k].get_person_id());
                    list_person[i][j].set_person_name(list_person[i][k].get_person_name());

                    list_person[i][k].set_person_id(temp.get_person_id());
                    list_person[i][k].set_person_name(temp.get_person_name());
                }
            }
        }
    }

    cout << "--- sort by person ---\n";
    /* out put */
    for (int i = 0 ; i <n ; i ++) {
        list_house[i].print_all_house_infor();
        cout<<endl;
        for (int j = 0 ;j<m ; j ++) {
            list_person[i][j].print_all_person_infor();
        }
        cout<< endl;
        cout << endl;
    }
    cout << "--- end sort by person ---\n" << endl;

    /* sort by house  */
    for (int i = 0 ; i <n-1 ; i ++) {
        for (int j = i+1 ;j<n ; j ++) {
            if (strcmp(list_house[i].get_house_id(), list_house[j].get_house_id()) > 0) {
                /* swap house */
                House temp;
                temp.set_house_id(list_house[i].get_house_id());
                temp.set_house_age(list_house[i].get_house_age());

                list_house[i].set_house_id(list_house[j].get_house_id());
                list_house[i].set_house_age(list_house[j].get_house_age());

                list_house[j].set_house_id(temp.get_house_id());
                list_house[j].set_house_age(temp.get_house_age());

                /* swap person */
                Person *temp_per;
                temp_per = *&list_person[i];
                list_person[i] = *&list_person[j];
                (list_person[j]) = *(&temp_per);
                temp_per = nullptr;
            }
        }
    }


    cout << "---- sort by house --- \n";
    /* out put */
    for (int i = 0 ; i <n ; i ++) {
        list_house[i].print_all_house_infor();
        cout<<endl;
        for (int j = 0 ;j<m ; j ++) {
            list_person[i][j].print_all_person_infor();
        }
        cout<< endl;
        cout << endl;
    }
}