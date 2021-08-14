#include <iostream>
#include <string.h>
#include "man.h"

// Man::Man()
//     :m_attack(0.0f), m_defend(0.0f),m_equipment(0), m_strength(0){
//         /* std::cout<< "man \n"; */
//         memset(m_code, 0, sizeof(m_code));
//     }
    


int Man::attack_with_buff_effect(float _m_attack, float _m_defend, float _m_strength) {
    if (this->m_defend > _m_attack && this->m_attack > _m_defend) {
        /* enermy lose */        
        return 1;
    }else{
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
            
        }else{
            
            /* enermy win */
            return 0;
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