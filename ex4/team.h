#include <iostream>
#include "man.h"
#include "a_g.h"
#include "archer.h"
#include "valiant.h"
#include "knight.h"


class Team
{
private:
    int number_man;
    Man **team;

public:
    Team();
    ~Team();

    void get_infor_a_team_with_buff_effect (FILE *file);
    void get_infor_a_team_without_buff_effect (FILE *file);
    void print_all_infor ();

    void set_number_man( int _number);
    void set_man_def(float value , int index);

    int get_number_man();
    char * get_man_code(int index);
    float get_man_attk (int index);
    float get_man_def (int index);
    bool get_man_euip (int index);
    int get_man_strength (int index);
    int get_kind_of_man (int index);
    
    void delete_a_man (char *_m_code);

    void attack (Team &_team_b);
};

