#ifndef include_class_A
#define include_class_A

// #include<iostream>

class A {
private:
    int a;
    int private_variable_a = 0;
public:
    A();
    ~A();
    void set_private_var_a(int _number );
    int get_private_var_a ();
};


class B: private A
{
private:
    int private_variable_b = 12;
public:
    B();
    ~B();
    int get_private_variable_b();
    int get_private_variable_a_from_b();
};

#endif