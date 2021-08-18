#include <iostream>
#include "ql.h"

using namespace std;


int main () {
    
    Quan_ly_khu_pho ql1;
    
    ql1.nhap_TT_khu_pho();
    
    cout <<endl << "----------in thong tin-----------------" << endl;
    ql1.in_TT_khu_pho();
    cout << "----------end in thong tin-----------------" << endl;
}