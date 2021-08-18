class Person
{
private:
    /* data */
    char id[10];
    char name[31];
    int age;

public:
    Person(/* args */);
    ~Person();
    void change_name();
    void change_age();
};

Person::Person(/* args */)
{
}

Person::~Person()
{
}
