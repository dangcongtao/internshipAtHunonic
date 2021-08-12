#include"Nha.h"
using namespace std;


Nha::Nha(){
    nguoi = nullptr;
    so_nguoi_trong_nha = 0;
    id_xom = 0;

};
Nha::~Nha(){

    int n = this->get_so_nguoi();
    delete[] nguoi;
    nguoi = nullptr;
    cout << "destructor cua Nha" << endl;
};


#pragma region  Nhập xuất.  
void Nha::nhap_tt_nha() {
    char _so_nha[30];
    int _id_xom, _so_nguoi_trong_nha;

    cout << "so nguoi: ";
    cin >> _so_nguoi_trong_nha;
    nguoi = new int[_so_nguoi_trong_nha];
    
    for (int i = 0 ; i < _so_nguoi_trong_nha ; i ++) {
        cout << "nguoi "  << i + 1 << ": " <<endl;
        nguoi[i].nhap_tt_nguoi();
        cout << endl;
    }

    cin.ignore();
    cout << "so nha: ";
    scanf("%[a-zA-Z0-9]", _so_nha);

    cout << "xom: ";
    cin >> _id_xom;

    this->set_id_xom(_id_xom);
    this->set_so_nguoi(_so_nguoi_trong_nha);
    this->set_so_nha(_so_nha);
}

void Nha::nhap_tt_nha(int _id_xom) {
    char _so_nha[30];
    int _so_nguoi_trong_nha;
    
    this->set_id_xom(_id_xom);

    cout << "so nguoi: ";
    cin >> _so_nguoi_trong_nha;
    this->set_so_nguoi(_so_nguoi_trong_nha);

    cin.ignore();
    cout << "so nha: ";
    scanf("%[a-zA-Z0-9]", _so_nha);
    this->set_so_nha(_so_nha);

    if (so_nguoi_trong_nha == 0) {
        delete nguoi;
        nguoi = nullptr;
    }
    else {
        nguoi = new int [so_nguoi_trong_nha];
    
        for (int i = 0 ; i < so_nguoi_trong_nha ; i ++) {
            cout << "nguoi "  << i + 1 << ": " <<endl;
            nguoi[i].nhap_tt_nguoi();
            cout << endl;
        }

    }
}

void Nha::print_all_infor () {
    cout << "So nha: " << so_nha << endl;
    cout << "Xom: " << id_xom << endl;
    cout << "So nguoi: " << so_nguoi_trong_nha << endl;
    cout << "Cac thanh vien gd: "<< endl;
    for (int i = 0 ; i < so_nguoi_trong_nha ; i ++) {
        nguoi[i].print_all_infor();
        cout <<endl;
    }
}

void Nha::set_so_nguoi (int _so_nguoi) { so_nguoi_trong_nha = _so_nguoi;}
void Nha::set_so_nha (char *_so_nha) { 
    memset(this->so_nha, 0, sizeof(this->so_nha));
    strcpy(so_nha, _so_nha); 
}
void Nha::set_id_xom (int _id_xom) { 
    id_xom = _id_xom;
}


int Nha::get_so_nguoi () { 
    return so_nguoi_trong_nha;
}
int* Nha::get_ds_nguoi() {
    return nguoi;
}
char* Nha::get_so_nha () {
    return so_nha;
}
int Nha::get_id_xom () {
    return id_xom;
}
#pragma endregion




/* ok */
const char* Nha::tim_so_nha_cua_nguoi (int _id) {
    for ( int i = 0 ; i < so_nguoi_trong_nha; i ++) {
        if (nguoi[i].get_ID() == _id) {
            return this->get_so_nha();
        }
    }
    return "khong tim thay";
}
