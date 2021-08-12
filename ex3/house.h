#ifndef include_house_h
#define include_house_h


class House
{
private:
    char house_id[30];
    int house_age;
public:
    House();
    ~House();


    void type_house_infor ();
    void print_all_house_infor ();
    void set_house_id (char *_house_id);
    void set_house_age (int _house_age);

    char* get_house_id ();
    int get_house_age ();
};


#endif