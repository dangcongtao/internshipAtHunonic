#ifndef include_ql
#define include_ql
#include"pho.h"

class Quan_ly_khu_pho
{
private:
    int so_luong_pho;
    Pho *pho;
public:
    Quan_ly_khu_pho();
    ~Quan_ly_khu_pho();

    void nhap_TT_khu_pho();
    void in_TT_khu_pho();

    int get_so_luong_nguoi();
    int get_so_luong_nha ();
    int get_so_luong_tat_ca_xom();
    int get_so_luong_pho();


    /* them 1 nguoi */
    void them_1_nguoi_tu_ql_pho (int _id_pho, int _id_xom, char *_so_nha);
    void them_1_nha_tu_pho_ql_pho (int _id_pho, int _id_xom);
    void them_1_pho_tu_ql_pho ();
    void them_1_xom_tu_ql_pho (int _id_pho);
};

#endif