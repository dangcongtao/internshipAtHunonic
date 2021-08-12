#include "xom.h"
using namespace std;


Xom::Xom() {
    this->id_pho = 0;
    this->id_xom = 0;
    this->so_luong_nha = 0;
    this->nha = nullptr;
}
Xom::~Xom() {
    int n = this->get_so_luong_nha();
    /*
    for ( int i = 0 ; i < n ; i ++) {
        nha[i].~Nha();        
    }
    */
    delete[] nha;
    this->nha = nullptr;
    cout << "destructor cua Xom. "<< endl;
}


#pragma region Nhập Xuất .

void Xom::nhap_tt_xom () {
    char _ten_Xom[50];
    
    cout << "id xom: ";
    cin>> id_xom;
    
    /* nha ten xom */
    cout << "Ten xom: ";
    cin.ignore();
    scanf("%[a-zA-Z0-9 ]", _ten_Xom);
    this->set_ten_xom(_ten_Xom);

    /* nhap ID pho. */
    cout << "id pho: ";
    cin>> id_pho;
    
    /* nhap so luong nha */
    cout <<"so luong nha: ";
    cin >> so_luong_nha;
    
    if (so_luong_nha > 0) {

        nha = new Nha[so_luong_nha];

        /* nhap thong tin cac nha. */
        for ( int i = 0 ; i < so_luong_nha ; i ++) {
            nha[i].nhap_tt_nha(this->id_xom);
            cout << endl;
        }
    }else{
        nha = nullptr;
    }
}

void Xom::nhap_tt_xom(int _id_pho) {
    char _ten_Xom[50];
    cout <<"nhap tt xom: "<< endl;
    cout << "id xom: ";
    cin >> id_xom;
    
    /* nha ten xom */
    cout << "Ten xom: ";
    cin.ignore();
    scanf("%[a-zA-Z0-9 ]", _ten_Xom);

    memset(ten_xom, 0, sizeof(ten_xom));
    strcpy(ten_xom,_ten_Xom);

    /* nhap ID pho. */
    this->id_pho = _id_pho;
    
    /* nhap so luong nha */
    cout <<"so luong nha: ";
    cin >> so_luong_nha;

    if (this->so_luong_nha > 0){
    
        this->nha = new Nha[this->so_luong_nha];
        for ( int i = 0 ; i < this->so_luong_nha ; i ++) {
            this->nha[i].nhap_tt_nha(id_xom);
            cout << endl;
        }
    }
    else  {
        delete this->nha;
        this->nha = nullptr;
    }

    /* nhap thong tin cac nha. */
}
void Xom::print_all_infor () {
    cout << "ten xom: ";
    puts(ten_xom);
    cout << "ID pho: " << this->get_ID_pho() << endl;
    cout <<"so luong nha: " << this->get_so_luong_nha()<< endl;
    for ( int i = 0 ; i < this->so_luong_nha ; i ++) {
        this->nha[i].print_all_infor();
        cout << endl;
    }
}



char* Xom::get_ten_xom () { 
    return this->ten_xom;
}
int Xom::get_so_luong_nha() {
    return this->so_luong_nha;
};
int Xom::get_ID_pho () {
    return this->id_pho;
};
int Xom::get_ID_xom () {
    return this->id_xom;
};

int Xom::get_so_nguoi_trong_xom (){
    int count = 0;
    for (int i = 0 ; i < so_luong_nha ; i ++) {
        count = count+this->nha[i].get_so_nguoi();
    } 
    return count;
};

void Xom::set_ten_xom(char *ten_moi) {
   memset(this->ten_xom, 0, sizeof(this->ten_xom));
    strcpy(this->ten_xom, ten_moi);
}
void Xom::set_id_xom(int _id_xom){ 
    this->id_xom = _id_xom; 
}

void Xom::set_id_pho_cho_xom(int _id_pho) {
    this->id_pho = _id_pho;
}
#pragma endregion

#pragma region tim kiem. 

const char* Xom::tim_nguoi_tu_xom (int _id) {
    for ( int i = 0 ; i < this->so_luong_nha ; i ++) {
        for ( int j = 0 ; j < nha[i].get_so_nguoi(); j ++) {
            if (strcmp(this->nha[j].tim_so_nha_cua_nguoi(_id),"khong tim thay") != 0){
                return this->nha[i].get_so_nha();
            }
        }
    }
    return "khong tim thay";
}

const char* Xom::tim_nha_tu_xom(char *_so_nha) {
    for ( int i = 0 ; i < this->so_luong_nha ; i ++) {
        if (strcmp(_so_nha, this->nha[i].get_so_nha()) == 0) {
            return nha[i].get_so_nha();
        }
    }
    return "khong tim thay";
}


#pragma endregion
