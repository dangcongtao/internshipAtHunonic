#ifndef include_class_army_general
#define include_class_army_general
#include "man.h"

class Army_General: public Man
{
private:
    float m_experience;
public:
    Army_General(char *_m_code, float _m_attack, float _m_defend, bool _m_equip, float _m_strength, float _m_experience);
    void print_all_man_infor () override;
    float get_m_experience();
    void set_all_infor (char *_m_code, float _m_attack, float _m_defend, bool _m_equip, float _m_strength, float _m_experience) override;
    
    /* Army_general = 1, Valiant = 2, Archer = 3, Knight = 4 */
    int get_kind_of_man () override;

};



#endif