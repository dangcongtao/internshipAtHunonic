#include"pho.h"
using namespace std;

Pho::Pho(/* args */){
    memset(ten_pho, 0, sizeof(ten_pho));
    this->id = 0;
    this->so_luong_xom = 0;
    this->xom = nullptr;
};
Pho::~Pho(){
    int n = this->get_so_luong_xom_cua_pho();
    /* 
    for ( int i = 0 ; i <n ; i ++) {
        this->xom[i].~Xom();
    }
    */
    delete[] xom;
    this->xom = nullptr;
    cout << "destructor cua Pho." << endl;
};



#pragma region  Nhập Xuất. 
void Pho::nhap_tt_pho (){
    char _ten_pho[40];

    cout << "ten pho: ";
    scanf("%[a-zA-Z0-9 ]",_ten_pho);
    this->set_ten_pho(_ten_pho);

    cout << "id pho: ";
    cin >> id;

    cout << "so luong xom: ";
    cin>> so_luong_xom;
    
    if (so_luong_xom >0) {
        xom =new Xom[so_luong_xom];
        for ( int i = 0 ; i < so_luong_xom ; i ++) {
            cin.ignore();
            xom[i].nhap_tt_xom(this->get_id_pho());
        }
    }else{
        delete xom;
        xom = nullptr;
    }

};


void Pho::nhap_tt_pho (int _id_pho, int _id_xom, int _id_nguoi){
    char _ten_pho[40];
    cout << "ten pho: ";
    scanf("%[a-zA-Z0-9 ]",_ten_pho);
    
    strcpy(ten_pho,_ten_pho);

    cout << "id pho: ";
    cin >> id;

    cout << "so luong xom: ";
    cin>> so_luong_xom;
    cin.ignore();

    xom =new Xom[so_luong_xom];
    for ( int i = 0 ; i < so_luong_xom ; i ++) {
        xom[i].nhap_tt_xom();
    }

};


void Pho::print_all_infor (){
    cout << "Ten pho: "<< ten_pho << endl;
    cout << "id pho" << id<< endl;
    cout << "so luong xom: " << so_luong_xom <<endl;
    for (int i = 0 ; i < so_luong_xom ; i ++) {
        cout << "Xom "<< xom[i].get_ten_xom()<< ": " <<endl;
        xom[i].print_all_infor();
    }
};

/* set method */
void Pho::set_ten_pho (char *_ten_pho){
    memset(this->ten_pho, 0, sizeof(this->ten_pho));
    strcpy(ten_pho,_ten_pho);
};
void Pho::set_id_pho(int _id){ 
    this->id = _id;
};

void Pho::set_so_luong_xom(int _num)
{
    so_luong_xom = _num;
}


char* Pho::get_ten_pho ()
{
    return ten_pho;
}
int Pho::get_id_pho (){
    return id;
}

int Pho::get_so_luong_nha_cua_pho () {
    int count = 0;
    for (int i = 0 ; i < so_luong_xom ; i ++){
        count += xom[i].get_so_luong_nha();
    }
    return count;
};

int Pho::get_so_luong_xom_cua_pho (){
    return this->so_luong_xom;
};

int Pho::get_so_luong_nguoi_cua_pho(){
    int count =0;
    for (int i = 0 ; i <so_luong_xom ; i ++) {
        count += xom[i].get_so_nguoi_trong_xom();
    }
    return count;
};

Xom* Pho::get_xom_ds_xom_cua_pho () {
    return xom;
}

#pragma endregion


#pragma region tim tt. 

const char* Pho::tim_nguoi_tu_pho(int _id){
    for (int i = 0 ; i <so_luong_xom ; i ++) {
        if (strcmp(xom[i].tim_nguoi_tu_xom(_id),"khong tim thay") != 0){
            return xom[i].tim_nguoi_tu_xom(_id);
        }
    }
    return "khong tim thay";
}

const char* Pho::tim_nha_tu_pho(char *_so_nha) {
    for (int i = 0 ; i <so_luong_xom ; i ++) {
        if (strcmp(xom[i].tim_nha_tu_xom(_so_nha),"khong tin thay") != 0) {
            return xom[i].tim_nha_tu_xom(_so_nha);
        }
    }
    return "khong tim thay";
}

int Pho::tim_xom_tu_pho(int _id_xom) {
    for ( int i = 0 ; i <so_luong_xom ; i ++) {
        if (xom[i].get_ID_xom() ==_id_xom) {
            return xom[i].get_ID_xom();
        }
    }
    return 0;
}

#pragma endregion