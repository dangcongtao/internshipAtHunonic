#ifndef include_Nha_h
#define include_Nha_h

#include <iostream>
#include "Nguoi.h"

class Nha
{
private:
    char so_nha[30];
    int id_xom;
    int so_nguoi_trong_nha;
    int *nguoi =nullptr;
public:
    Nha(/* args */) ;
    ~Nha();

    void nhap_tt_nha();
    void nhap_tt_nha (int id_xom);
    
    void print_all_infor () ;

    void set_so_nguoi (int _so_nguoi) ;
    void set_so_nha (char *_so_nha) ;
    void set_id_xom (int _id_xom) ;
    void set_nha(Nha _nha);
    
    int get_so_nguoi ();
    int* get_ds_nguoi() ;
    char* get_so_nha () ;
    int get_id_xom () ;

    void them_1_nguoi_tu_nha () ;

    /* tra ve so nha */
    const char* tim_so_nha_cua_nguoi (int _id) ;
};

#endif