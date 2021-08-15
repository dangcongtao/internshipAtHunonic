#include <iostream>
#include <string.h>
#include "man.h"

// Man::Man()
//     :m_attack(0.0f), m_defend(0.0f),m_equipment(0), m_strength(0){
//         /* std::cout<< "man \n"; */
//         memset(m_code, 0, sizeof(m_code));
//     }
    


int Man::attack_without_buff_effect 
(
    float _m_attack, float _m_defend, bool _m_equip ,float _m_strength, int kind_of_man_b,float _ex_b, 
    bool _team_a_equip, int kind_of_man_a,float _ex_a
){
    
    float buff_team_b = (float)1,
        buff_team_a = (float)1, team_a_atk = this->get_m_attk(), team_a_def = this->get_m_def();


    /* set up specification for the man of team B*/
    if ( _ex_b == 0 )
        buff_team_b =(float)0.5;
    if (_ex_b > 0 && _ex_b <= 2)
        buff_team_b = (float)0.8;
    if (_ex_b >2 && _ex_b <= 5)
        buff_team_b = (float)1.5;
    if (_ex_b > 5 )
        buff_team_b = (float)2;

    /* Army_general = 1, Valiant = 2, Archer = 3, Knight = 4 */
    if (kind_of_man_b == 2){
        if (_m_equip)
            _m_defend = ((_m_defend*(float)2));
    }
    if (kind_of_man_b == 3){
        if (_m_equip)
            _m_attack = ((_m_attack*(float)1.5));
    }
    if (kind_of_man_b == 4){
        if (_m_equip){
            _m_attack = ((_m_attack*(float)3));
            _m_defend = ((_m_defend*(float)3));
        }
    }
    _m_attack = _m_attack*buff_team_b;
    _m_defend = _m_defend*buff_team_b;


    /* set up specification for the man of team A */
    if ( _ex_a == 0 )
        buff_team_a = (float)0.5;
    if (_ex_a > 0 && _ex_a <= 2)
        buff_team_a = (float)0.8;
    if (_ex_a >2 && _ex_a <= 5)
        buff_team_a = (float)1.5;
    if (_ex_a > 5 )
        buff_team_a = (float)2;

    if (kind_of_man_a == (float)2){
        if (_team_a_equip)
            team_a_def = ((team_a_def*(float)2));
    }
    if (kind_of_man_a == 3){
        if (_team_a_equip)
            team_a_atk = ((team_a_atk*(float)1.5));
    }
    if (kind_of_man_a == 4){
        if (_team_a_equip){
            team_a_atk = ((team_a_atk*(float)3));
            team_a_def = ((team_a_def*(float)3));
        }
    }
    team_a_def = team_a_def*buff_team_a;
    team_a_atk = team_a_atk*buff_team_a;

/* 
    std::cout<< "\tteam A:\n";
    std::cout<< "\tex: " << _ex_a << "\n";
    std::cout<< "\tattk: " << team_a_atk << "\n";
    std::cout<< "\tdef: " << team_a_def << "\n";
    std::cout<< "\tstrength: " << this->m_strength<<"\n\n";
    std::cout<< "\tteam B:\n";
    std::cout<< "\tex: " << _ex_b << "\n";
    std::cout<< "\tattk: " << _m_attack << "\n";
    std::cout<< "\tdef: " << _m_defend << "\n";
    std::cout<< "\tstrength: " << _m_strength<<"\n\n";
 */
    if (team_a_def > _m_attack && team_a_atk > _m_defend) {
        /* enermy lose */        
        return 1;
    }
    if ( team_a_def == _m_attack && team_a_atk == _m_defend){
        /* equal */
        if ( this->m_strength > _m_strength) {                
            return 1;
        }else{
            if (this->m_strength < _m_strength){                    
                return 0;
            }else {
                return -1;
            }
        }
        
    }


    if (team_a_def < _m_attack && team_a_atk < _m_defend) {
        /* enermy win */        
        return 0;
    }
    if ( team_a_def == _m_attack && team_a_atk == _m_defend){
        /* equal */
        if ( this->m_strength < _m_strength) {                
            return 0;
        }else{
            if (this->m_strength > _m_strength){                    
                return 1;
            }else {
                return -1;
            }
        }
        
    }

    return -1;
};

int Man::attack_with_buff_effect(float _m_attack, float _m_defend, float _m_strength) {

    if (this->m_defend > _m_attack && this->m_attack > _m_defend) {
        /* enermy lose */        
        return 1;
    }
    if ( this->m_defend == _m_attack && this->m_attack == _m_defend){
        /* equal */
        if ( this->m_strength > _m_strength) {                
            return 1;
        }else{
            if (this->m_strength < _m_strength){                    
                return 0;
            }else {
                return -1;
            }
        }
        
    }

    if (this->m_defend < _m_attack && this->m_attack < _m_defend) {
        /* enermy win */        
        return 0;
    }
    if ( this->m_defend == _m_attack && this->m_attack == _m_defend){
        /* equal */
        if ( this->m_strength < _m_strength) {                
            return 0;
        }else{
            if (this->m_strength > _m_strength){                    
                return 1;
            }else {
                return -1;
            }
        }
        
    }

    return -1;
}


void Man::print_all_man_infor() {
        std::cout << get_m_code() << " " << get_m_attk() << " ";
        std::cout << get_m_def() <<" " << get_m_equip() << " " << get_m_strength();
}



void Man::set_all_infor (char *_m_code, float _m_attack, float _m_defend, bool _m_equip, float _m_strength, float _m_experience) {
    strcpy(this->m_code, _m_code);
    this->m_attack = _m_attack;
    this->m_defend = _m_defend;
    this->m_equipment = _m_equip;
    this->m_strength = _m_strength;
}

/* Army_general = 1, Valiant = 2, Archer = 3, Knight = 4 */
int Man::get_kind_of_man () {
    return 0;
}

char* Man::get_m_code () {
    return this->m_code;
}

float Man::get_m_attk () {
    return this->m_attack;
}

float Man::get_m_def () {
    return this->m_defend;
}    

bool Man::get_m_equip () {
    return this->m_equipment;
}

int Man::get_m_strength() {
    return m_strength;
}

void Man::set_m_def(float _value){
    if (_value <0 ) {
        this->m_defend = 0;
        return;
    }
    this->m_defend = _value;
}