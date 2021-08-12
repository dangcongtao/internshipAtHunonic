#include<iostream>
#include<string.h>
using namespace std;

class SinhVien
{
private:
    /* data */
    char *MSV;
    char *ten;
    int tuoi;
    float DTB;
public:
    SinhVien(/* args */){
        MSV = nullptr;
        ten = nullptr;
        tuoi = 0;
        DTB = 0.0f;
    };
    SinhVien(char *_MSV,
    char *_ten,
    int _tuoi,
    float _DTB) {
        MSV = _MSV;
        ten = _ten;
        tuoi = _tuoi;
        DTB = _DTB;
    }
    ~SinhVien();

// Method

    // nhap tt sinhvien
    void Nhap () {
        char _Ten[30], _MSV[30];

        // Nhap MSV
        cout << "MSV: ";
        scanf ("%[a-zA-Z0-9]", _MSV);

        // khoi tao.
        this->MSV = (char *) malloc(sizeof(char)*strlen(_MSV));
        // for ( int i = 0 ; i < strlen(_MSV) ; i ++) {
        //     // *(this->MSV+i) = *(_MSV+i);
        //     this->MSV[i] = _MSV[i];
        // }
        strncpy(this->MSV, _MSV, strlen(_MSV));
        cin.ignore();
        // Nhap Ten
        cout << "Ten: ";
        scanf("%[a-zA-Z ]", _Ten);

        // cap phat
        this->ten = (char *) malloc(sizeof(char)*strlen(_Ten));
        for (int i = 0 ; i <strlen(_Ten); i ++) {
            *(this->ten+i) = *(_Ten+i);
        }

        cout << "Tuoi: ";
        cin>> this->tuoi;

        cout << "DTB: ";
        cin >> this->DTB;

        cout << endl;
    }

    // in thong tin SV
    void print () {
        printf ("Ten: %s\n",this->ten);
        printf("MSV: %s\n", this->MSV);
        printf("Tuoi: %d\n", tuoi);
        printf("DTB: %.2f\n", DTB);
    }

    // set/get
    char* getMSV() {return this->MSV;}
    void setMSV(char *_msv) {
        this->MSV = (char *) malloc(sizeof(char)*strlen(_msv));
        for (int i = 0 ; i <strlen(_msv); i ++) {
            *(this->ten+i) = *(_msv+i);
        }
    }

    char* getTen () {return this->ten;}
    void setTen (char *_ten) {
        this->ten = (char *) malloc(sizeof(char)*strlen(_ten));
        for (int i = 0 ; i <strlen(_ten); i ++) {
            *(this->ten+i) = *(_ten+i);
        }
        return;
    }

    int getTuoi () {return tuoi;}
    void setTuoi( int _tuoi) { tuoi = _tuoi;}

    float getDTB() { return DTB;}
    void setDTB (float _dtb) { DTB = _dtb;}
};


SinhVien::~SinhVien()
{
}


// Test

// int main () {
//     SinhVien *an = new SinhVien("DTC01", "An Nguyen", 19, 6.7f);

//     // an->Nhap();
//     // an->setTen("An Nguyen");
//     // an->print();
//     // puts (an->getTen());

//     an->print();
//     return 0;
// }