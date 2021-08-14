#ifndef include_knight_h
#define include_knight_h
#include "man.h"

class Knight: public Man
{
private:
    /* data */
public:
    Knight(char *_m_code, float _m_attack, float _m_defend, bool _m_equip, float _m_strength);
    
    /* Army_general = 1, Valiant = 2, Archer = 3, Knight = 4 */
    int get_kind_of_man () override;
};


#endif