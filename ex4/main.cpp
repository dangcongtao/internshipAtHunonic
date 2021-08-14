#include <iostream>
#include <string.h>
#include "team.h"


int main () {
    Team team_a, team_b;
    FILE *file;

    file = fopen("input_file.txt", "r");
    team_a.get_infor_a_team_without_buff_effect (file);
    team_b.get_infor_a_team_without_buff_effect(file);
    fclose(file);

    std::cout << "\n\n\t*****print all infor *****\n";
    team_a.print_all_infor();
    
    std::cout << "\n\n\n\t*****print all infor *****\n";
    team_b.print_all_infor();

 
    team_a.attack(team_b);

    std::cout << "\n\n\t***** deleted *****\n";
    team_a.print_all_infor();
    
    std::cout << "\n\n\n\t***** deleted *****\n";
    team_b.print_all_infor();
/* */

    // Archer archer("A01", 70.f, 70.f, 1, 30 );
    // // Archer archer2("A01" 70f 70f 1 30 );
    // std::cout << archer.attack(60.f, 80.f, 40);
}