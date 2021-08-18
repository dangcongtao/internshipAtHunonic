#include <iostream>
#include <string.h>
#include "valiant.h"

Valiant::Valiant(char *_m_code, float _m_attack, float _m_defend, bool _m_equip, float _m_strength) {
    
    strcpy(m_code, _m_code);
    m_attack = _m_attack;
    if (_m_equip)
        m_defend = _m_defend/**2*/;
    else
        m_defend = _m_defend;
    m_equipment = _m_equip;
    m_strength = _m_strength;
}

/* Army_general = 1, Valiant = 2, Archer = 3, Knight = 4 */
int Valiant::get_kind_of_man () {
    return 2;
}