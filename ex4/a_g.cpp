#include <iostream>
#include <string.h>
#include "a_g.h"

Army_General::Army_General (char *_m_code, float _m_attack, float _m_defend, bool _m_equip, float _m_strength, float _m_experience) {
    strcpy(m_code, _m_code);
    m_attack = _m_attack;
    m_defend = _m_defend;
    m_equipment = _m_equip;
    m_strength = _m_strength;
    m_experience = _m_experience;
}

void Army_General::print_all_man_infor(){
    std::cout << get_m_code() << " " << get_m_attk() << " " << get_m_def();
    std::cout <<" " << get_m_equip() << " " << get_m_strength() << " " << this->get_m_experience();
}
float Army_General::get_m_experience () {
    return this->m_experience;
}
void Army_General::set_all_infor (char *_m_code, float _m_attack, float _m_defend, bool _m_equip, float _m_strength, float _m_experience) {
    strcpy(this->m_code, _m_code);
    this->m_attack = _m_attack;
    this->m_defend = _m_defend;
    this->m_equipment = _m_equip;
    this->m_strength = _m_strength;
    this->m_experience = _m_experience;
}


/* Army_general = 1, Valiant = 2, Archer = 3, Knight = 4 */
int Army_General::get_kind_of_man () {
    return 1;
}