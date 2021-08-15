#include <iostream>
#include <string.h>
#include "team.h"

Team::Team(){

};

Team::~Team() {

}


void Team::get_infor_a_team_with_buff_effect(FILE *file){
    
    char temp[250];
    int a;
    char type[10];
    char *char_ptr;
    char _m_code[10];
    float _m_attack;
    float _m_defend;
    bool _m_equip;
    char yes_or_no[10];
    int _m_strength;
    float _m_experience;
    float buff =1;
    
    fscanf(file, "%[a-zA-Z ]",temp);
    /* normalize */

    fscanf(file, "%d", &a);
    this->set_number_man(a);
    fgets(temp,250,file);

    team = new Man*[a];
    for ( int i = 0 ; i <a; i ++) {        

        memset(temp, 0 , sizeof(temp));
        fgets(temp, 250, file);
        
        /* delete charecter \n at the end of string temp */
        char_ptr = strtok(temp,"\n");
        strcpy(temp, char_ptr);

        /* get type */
        memset(type, 0 , sizeof(type));
        char_ptr = strtok(temp," ");
        strcpy(type, char_ptr);


        /* get m-code */
        memset(_m_code, 0 , sizeof(_m_code));
        char_ptr = strtok(NULL, " ");
        strcpy(_m_code, char_ptr);

        /* get m_atk */        
        char_ptr = strtok(NULL, " ");
        _m_attack = atof(char_ptr);

        /* get m_def */
        char_ptr = strtok(NULL, " ");
        _m_defend = atof(char_ptr);

        /* get equip*/
        char_ptr = strtok(NULL, " ");
        if (strcmp(char_ptr,"YES") == 0)
            _m_equip =true;
        else _m_equip = false;

        /* get strength */
        char_ptr = strtok(NULL, " ");
        _m_strength = atoi(char_ptr);

        /* get experince */
        if (i == 0 ){
            char_ptr = strtok(NULL, " ");
            _m_experience = atof(char_ptr);
        }    

       
        /* allocate */
        if (strcmp(type,"AG") == 0){
            if ( _m_experience == 0 )
                buff =0.5f;
            if (_m_experience > 0 && _m_experience <= 2)
                buff = 0.8f;
            if (_m_experience >2 && _m_experience <= 5)
                buff = 1.5;
            if (_m_experience > 5 )
                buff = 2;
            *(team+i) = new Army_General(_m_code, _m_attack*buff, _m_defend*buff, _m_equip, _m_strength, _m_experience);
        }
        if (strcmp(type,"A") == 0){
            *(team+i) = new Archer(_m_code,_m_attack*buff, _m_defend*buff, _m_equip, _m_strength);
        }
        if (strcmp(type,"V") == 0){
            *(team+i) = new Valiant(_m_code, _m_attack*buff, _m_defend*buff, _m_equip, _m_strength);
        }
        if (strcmp(type,"K") == 0){
            *(team+i) = new Knight(_m_code, _m_attack*buff, _m_defend*buff, _m_equip, _m_strength);
        } 
        char_ptr =nullptr;
    }   
    
}



void Team::get_infor_a_team_without_buff_effect (FILE *file){

    char temp[250];
    int a;
    char type[10];
    char *char_ptr;
    char _m_code[10];
    float _m_attack;
    float _m_defend;
    bool _m_equip;
    char yes_or_no[10];
    int _m_strength;
    float _m_experience;
    
    fscanf(file, "%[a-zA-Z ]",temp);
    /* normalize */

    fscanf(file, "%d", &a);
    this->set_number_man(a);
    fgets(temp,250,file);

    team = new Man*[a];
    for ( int i = 0 ; i <a; i ++) {        

        memset(temp, 0 , sizeof(temp));
        fgets(temp, 250, file);
        
        /* delete charecter \n at the end of string temp */
        char_ptr = strtok(temp,"\n");
        strcpy(temp, char_ptr);

        /* get type */
        memset(type, 0 , sizeof(type));
        char_ptr = strtok(temp," ");
        strcpy(type, char_ptr);


        /* get m-code */
        memset(_m_code, 0 , sizeof(_m_code));
        char_ptr = strtok(NULL, " ");
        strcpy(_m_code, char_ptr);

        /* get m_atk */        
        char_ptr = strtok(NULL, " ");
        _m_attack = atof(char_ptr);

        /* get m_def */
        char_ptr = strtok(NULL, " ");
        _m_defend = atof(char_ptr);

        /* get equip*/
        char_ptr = strtok(NULL, " ");
        if (strcmp(char_ptr,"YES") == 0)
            _m_equip =true;
        else _m_equip = false;

        /* get strength */
        char_ptr = strtok(NULL, " ");
        _m_strength = atoi(char_ptr);

        /* get experince */
        if (i == 0 ){
            char_ptr = strtok(NULL, " ");
            _m_experience = atof(char_ptr);
        }    

       
        /* allocate */
        if (strcmp(type,"AG") == 0){
            
            *(team+i) = new Army_General(_m_code, _m_attack, _m_defend, _m_equip, _m_strength, _m_experience);
            this->ex = _m_experience;
        }
        if (strcmp(type,"A") == 0){
            *(team+i) = new Archer(_m_code,_m_attack, _m_defend, _m_equip, _m_strength);
        }
        if (strcmp(type,"V") == 0){
            *(team+i) = new Valiant(_m_code, _m_attack, _m_defend, _m_equip, _m_strength);
        }
        if (strcmp(type,"K") == 0){
            *(team+i) = new Knight(_m_code, _m_attack, _m_defend, _m_equip, _m_strength);
        } 
        char_ptr =nullptr;
    }   
    
}


void Team::print_all_infor () {
    int n = this->get_number_man();
    std::cout<< "number man = " << n << "\n";
    for ( int i = 0 ; i < n; i ++)     {
        team[i]->print_all_man_infor();
        std::cout << "\n";
    }
}

void Team::set_man_def(float value, int index){
    team[index]->set_m_def(value);
}

void Team::set_number_man (int _number) {
    this->number_man = _number;
}

int Team::get_number_man() {
    return this->number_man;
}

 char * Team::get_man_code(int index){
    return team[index]->get_m_code();
 }
float Team::get_man_attk (int index){
    return team[index]->get_m_attk();
}
float Team::get_man_def (int index){
    return team[index]->get_m_def();
}
bool Team::get_man_euip (int index){
    return team[index]->get_m_equip();
}
int Team::get_man_strength (int index){
    return this->team[index]->get_m_strength();
}
float Team::get_man_ex (){
    return this->ex;
}

/* Army_general = 1, Valiant = 2, Archer = 3, Knight = 4 */
int Team::get_kind_of_man (int index) {
    return team[index]->get_kind_of_man();
}


void Team::delete_a_man (char *_m_code){

    int number = this->number_man;
    
    if (number == 0) return;

    float _m_experience = 0;
    
    for (int i = 0 ; i < number ; i ++) {
        if (team[i]->get_m_code() == _m_code) {
            /* delete */
            for (int j = i ; j < number-1 ; j ++) {
                team[i]->set_all_infor(team[i+1]->get_m_code(),team[i+1]->get_m_attk(), team[i+1]->get_m_def(), 
                team[i+1]->get_m_equip(), team[i+1]->get_m_strength(), _m_experience);
            }
            delete team[number_man-1];
            team[number-1] = nullptr;
            number_man = number_man -1;

            return;
        }
    }
       
}


void Team::attack (Team &_team_b){

    int index_team_a = 1;
    int index_team_b = 1;    
    
    while (_team_b.get_number_man() != 0 && this->get_number_man() != 0 ){
        if (_team_b.get_number_man() ==1)
            index_team_b = 0;
        if (this->get_number_man() == 1)
            index_team_a =0;

        /* if attack == 1 team a win, == 0 team b win*/
        if (this->team[index_team_a]->attack_without_buff_effect 
        (
        
        _team_b.get_man_attk(index_team_b), _team_b.get_man_def(index_team_b), _team_b.get_man_euip(index_team_b),
        _team_b.get_man_strength(index_team_b), _team_b.get_kind_of_man(index_team_b), _team_b.get_man_ex(),
        
        this->get_man_euip(index_team_a), this->get_kind_of_man(index_team_a), this->get_man_ex()
        
        /* parameter of method attack_with_buff_effect(), which is buff by AG ex + kind of solder were set into each man profile when get_infor_of_a_team called .
        _team_b.get_man_attk(index_team_b), _team_b.get_man_def(index_team_b), _team_b.get_man_strength(index_team_b)
        */

        ) == 1) {
            
            /* team b lose 
            std::cout <<"team b lose\n";
            */

            /* delete and set value */
            this->team[index_team_a]->set_m_def(this->team[index_team_a]->get_m_def() -20);
            _team_b.delete_a_man(_team_b.get_man_code(index_team_b));

            /* print to test 
            std::cout <<"number man a: " << this->get_number_man()<< "\n";
            std::cout <<"number team b: " << _team_b.get_number_man() << "\n\n";
            */
        }
        else {
            /* team b win 
            std::cout <<"team b win "<< "\n";
            */
            this->delete_a_man(this->team[index_team_a]->get_m_code());
            _team_b.set_man_def((_team_b.get_man_def(index_team_b) -20) , index_team_b);
            
            /* print to test 
            std::cout <<"number man a: " << this->get_number_man()<< "\n";
            std::cout <<"number team b: " << _team_b.get_number_man() << "\n\n";
            */
        }        
    }
}