#ifndef include_person_h
#define include_person_h

class Person
{
private:
    char person_id[30];
    char person_name[30];
public:
    Person();
    ~Person();

    void type_person_infor ();
    void print_all_person_infor ();
    void set_person_id (char *_person_id);
    void set_person_name (char *_person_name);

    char* get_person_id ();
    char* get_person_name ();

};


#endif