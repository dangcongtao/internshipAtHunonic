#include <iostream>
#include <string.h>
#include "knight.h"

Knight::Knight(char *_m_code, float _m_attack, float _m_defend, bool _m_equip, float _m_strength){
    strcpy(m_code, _m_code);
    if (_m_equip){
        m_attack = _m_attack/**3*/;
        m_defend = _m_defend/**3*/;
    }else{
        m_attack = _m_attack;
        m_defend = _m_defend;
    }
    m_equipment = _m_equip;
    m_strength = _m_strength;
}

/* Army_general = 1, Valiant = 2, Archer = 3, Knight = 4 */
int Knight::get_kind_of_man () {
    return 4;
}