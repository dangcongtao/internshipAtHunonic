#include"Nguoi.h"
using namespace std;

int::~int() {
    cout << "destrucot cua nguoi"<< endl;
};

int::int() {
    id = 0;
    memset(&this->ten, 0, sizeof(this->ten));
    tuoi = 0;
};

void int::nhap_tt_nguoi () {
    char _ten[30];
    int _tuoi;
    int _id;

    cout << "id: ";
    cin>> _id;
    
    cin.ignore();
    cout << "ten: ";
    scanf("%[a-zA-Z ]", _ten);

    cout << "tuoi: ";
    cin >> _tuoi;

    this->set_ID(_id);
    this->set_ten(_ten);
    this->set_tuoi(_tuoi);
};

void int:: print_all_infor () {
    cout << endl;
    cout << "ID: " << this->get_ID() << endl;
    cout << "Ten: " << this->get_ten() << endl;
    cout << "Tuoi: "<< this->get_tuoi() << endl;
};

int int:: get_ID () {return id;};
int int:: get_tuoi () {return tuoi;};
char* int:: get_ten () {return ten;};

void int:: set_ID (int _id) {id = _id;};
void int:: set_ten (char *_ten) {
    memset(&this->ten, 0, sizeof(this->ten));
    strncpy(this->ten, _ten, strlen(_ten));
};
void int:: set_tuoi (int _tuoi) {
    this->tuoi = _tuoi;
};

