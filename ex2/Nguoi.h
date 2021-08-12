#ifndef include_Nguoi_h
#define include_Nguoi_h

#include<iostream>
#include<string.h>

class int
{
private:
    int id;
    char ten[30];
    int tuoi;
public:
    int(/* args */);
    // Person(int _id, const char *_ten, int _tuoi) ;
    ~int() ;

    void nhap_tt_nguoi ();

    void print_all_infor ();

    int get_ID ();
    int get_tuoi () ;
    char* get_ten ();

    void set_ID (int _id) ;
    void set_ten (char *_ten) ;
    void set_tuoi (int _tuoi);

};

#endif