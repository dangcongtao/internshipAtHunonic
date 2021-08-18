#ifndef include_pho_h
#define include_pho_h

#include <iostream>
#include "xom.h"

class Pho
{
private:
    char ten_pho[20];
    int id;
    int so_luong_xom;
    Xom *xom = nullptr;
public:
    Pho(/* args */);
    ~Pho();

    void nhap_tt_pho ();
    void nhap_tt_pho (int _id_pho, int _id_xom, int _id_nguoi);
    void print_all_infor ();

    void set_ten_pho (char *_ten_pho);
    void set_id_pho(int _id);

    // void set_so_nha_moi (char *_old_so_nha, char *new_so_nha);
    void set_so_luong_xom(int _num);

    char *get_ten_pho ();
    int get_id_pho ();
    int get_so_luong_nha_cua_pho ();
    int get_so_luong_xom_cua_pho ();
    int get_so_luong_nguoi_cua_pho();
    Xom* get_xom_ds_xom_cua_pho ();

    const char* tim_nguoi_tu_pho (int _id_nguoi);
    const char* tim_nha_tu_pho (char* _so_nha);
    int tim_xom_tu_pho(int _id_xom);
    void tim_nha(char* _so_nha);
};


#endif