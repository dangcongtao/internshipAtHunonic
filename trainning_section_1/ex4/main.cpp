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
    
    std::cout << "\n\n\t***** infor team A *****\n";
    team_a.print_all_infor();
    
    std::cout << "\n\n\n\t***** infor team B *****\n";
    team_b.print_all_infor();

 
    team_a.attack(team_b);

    std::cout << "\n\n\t***** battle end - team A infor *****\n";
    team_a.print_all_infor();
    
    std::cout << "\n\n\n\t***** battle end - team B infor *****\n";
    team_b.print_all_infor();
}