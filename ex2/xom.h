#ifndef include_xom_h
#define include_xom_h

#include <iostream>
#include "Nha.h"

class Xom
{
private:
    int id_xom;
    char ten_xom[30];
    int id_pho;
    int so_luong_nha;
    Nha *nha = nullptr;

public:
    Xom(/* args */);
    ~Xom();

    void nhap_tt_xom ();
    void nhap_tt_xom (int id_pho);
    
    void print_all_infor ();


    char* get_ten_xom ();
    int get_so_luong_nha ();
    int get_ID_pho();
    int get_ID_xom();
    int get_so_nguoi_trong_xom ();
    Nha* get_ds_nha ();
    
    void set_ten_xom(char* _ten_moi) ;
    void set_id_xom (int _id_xom);
    void set_nha_cho_xom (Nha* _nha, int _so_luong_nha) ;
    void set_id_pho_cho_xom (int _id_pho);

    const char* tim_nguoi_tu_xom (int _id);
    const char* tim_nha_tu_xom (char *_so_nha);
};

#endif