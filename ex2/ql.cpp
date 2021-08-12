
#include"ql.h"
using namespace std;

Quan_ly_khu_pho::Quan_ly_khu_pho(){
    this->pho = nullptr;
};
Quan_ly_khu_pho::~Quan_ly_khu_pho(){
    int n = this->get_so_luong_pho();
    /* for (int i = 0 ; i < n ; i ++) {
        this->pho[i].~Pho();
    } */
    delete[] pho;
    this->pho = nullptr;
    cout << "destructor cua Ql" << endl;
};


#pragma region Nhập xuất.  

void Quan_ly_khu_pho::nhap_TT_khu_pho(){
    cout <<"so luong khu pho: ";
    cin >>so_luong_pho;

    cin.ignore();
    if (so_luong_pho >0){

        pho = new Pho[so_luong_pho];
        for (int i = 0 ; i < so_luong_pho ; i ++) {
            pho[i].nhap_tt_pho();
            cin.ignore();
        }
    }else{
        delete pho;
        pho = nullptr;
    }
}

void Quan_ly_khu_pho::in_TT_khu_pho(){
    cout << "so luong khu pho: " << so_luong_pho;
    for (int i = 0 ; i <so_luong_pho ; i ++) {
        pho[i].print_all_infor();
    }
}

int Quan_ly_khu_pho::get_so_luong_nguoi(){
    int count = 0;
    for(int i = 0 ; i < so_luong_pho; i ++) {
        count = count + pho[i].get_so_luong_nguoi_cua_pho();
    }
    return count;
};

int Quan_ly_khu_pho::get_so_luong_nha (){
    int count = 0;
    for(int i = 0 ; i < so_luong_pho; i ++) {
        count = count + pho[i].get_so_luong_nha_cua_pho();
    }
    return count;
};

int Quan_ly_khu_pho::get_so_luong_tat_ca_xom(){
    int count = 0;
    for(int i = 0 ; i < so_luong_pho; i ++) {
        count = count + pho[i].get_so_luong_xom_cua_pho();
    }
    return count;
};

int Quan_ly_khu_pho::get_so_luong_pho(){
    return so_luong_pho;
};

#pragma endregion



#pragma region xoa.  




#pragma endregion
