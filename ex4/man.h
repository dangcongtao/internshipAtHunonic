#ifndef include_class_man
#define include_class_man
#include <iostream>

class Man
{
protected:
    char m_code[5];
    float m_attack;
    float m_defend;
    bool m_equipment;
    int m_strength;
    
public:
    // Man();
    // ~Man();
    
    /* return m_code of the winner */
    int attack_with_buff_effect (float _m_attack, float _m_defend, float _m_strength);
    int attack_without_buff_effect (float _m_attack, float _m_defend, float _m_strength);
    virtual void print_all_man_infor ();
    
    virtual void set_all_infor(char *_m_code, float _m_attack, float _m_defend, bool _m_equip, float _m_strength, float _m_experience);

    char* get_m_code ();
    float get_m_attk ();    
    float get_m_def ();
    bool get_m_equip ();
    int get_m_strength();
    /* Army_general = 1, Valiant = 2, Archer = 3, Knight = 4 */
    virtual int get_kind_of_man ();

    void set_m_def (float _value);
};

#endif