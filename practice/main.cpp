#include<iostream>
#include<string.h>
#include"Student.h"
using namespace std;


struct Node{
    SinhVien value;
    Node *next;
};
class LinkList
{
private:
    /* data */
    Node *head = nullptr;

public:
    LinkList(/* args */);
    ~LinkList();

    // method
    void addStudent () {
        Node *temp = new Node;
        Node *duyetMang;
        SinhVien sv;
        sv.Nhap();
        // sv.print(); ok

        temp->value = sv; 
        temp->next = nullptr;
        // temp.value.print(); ok

        if ( head ==nullptr) {
            head = temp;
        }else {
            duyetMang = head;
            while (duyetMang->next != nullptr) {
                duyetMang = duyetMang->next;
            }
            duyetMang->next = temp;
        }

        duyetMang = nullptr;        
    }

    void addStudent (Node temp) {
        Node *duyetMang;
        if ( head ==nullptr) {
            head = &temp;
        }else {
            duyetMang = head;
            while (duyetMang->next != nullptr) {
                duyetMang = duyetMang->next;
            }
            duyetMang->next = &temp;
        }
        
        duyetMang = nullptr;
    }

    void addStudent (SinhVien sv) {
        Node *temp = new Node;
        Node *duyetMang;
        temp->value = sv;
        temp->next = nullptr;

        if ( head ==nullptr) {
            head = temp;
        }else {
            duyetMang = this->head;
            while (duyetMang->next != nullptr) {
                duyetMang = duyetMang->next;
            }
            duyetMang->next = temp;
        }

         /* free ptr */
        duyetMang = nullptr;
    }


// have to create sv first, cant use setvalue.
    void addStudent (char *_MSV, char *_ten, int _tuoi, float _DTB) {
        SinhVien *sv = new SinhVien (_MSV, _ten, _tuoi,  _DTB);
        Node *temp = new Node;
        temp->value = *sv;
        temp->next = nullptr;
        
        Node *duyetMang;
        if ( head ==nullptr) {
            head = temp;
        }else {
            duyetMang = this->head;
            while (duyetMang->next != nullptr) {
                duyetMang = duyetMang->next;
            }
            duyetMang->next = temp;
        }

        /* free ptr */
        duyetMang = nullptr;     
    }


    void printAllStudents() {
        Node *duyetMang = head;

        if (duyetMang == nullptr) {
            cout<< "Khong co thong tin nao.";

            /* free ptr */
            duyetMang = nullptr;
            return;
        }

        while (duyetMang != nullptr) {
            cout << endl;
            duyetMang->value.print();

            duyetMang = duyetMang->next;            
        }

        /* free ptr */
        duyetMang = nullptr;
    }

    // find by tuoi-age.
    LinkList findStudent (int tuoi) {
        LinkList result;
        Node *duyetMang = head;

        while(duyetMang != nullptr) {
            if (duyetMang->value.getTuoi() == tuoi) {
                Node temp;
                temp.value = duyetMang->value;
                temp.next = nullptr;

                result.addStudent(temp);
            }
            duyetMang= duyetMang->next;
        }

        /* free ptr */
        duyetMang = nullptr;
        return result;
    }

    // find by DTB
    LinkList findStudent (float _DTB) {
        LinkList result;
        Node *duyetMang = head;

        while(duyetMang != nullptr) {
            if (duyetMang->value.getDTB() == _DTB) {
                Node temp;
                temp.value = duyetMang->value;
                temp.next = nullptr;

                result.addStudent(temp);
            }
            duyetMang= duyetMang->next;
        }

        /* free ptr */
        duyetMang = nullptr;
        return result;
    }
    
    /* find by ID - MSV. */
    LinkList findStudent ( char *_MSV) {
        LinkList result;
        Node *duyetMang = head;

        while(duyetMang != nullptr) {
            if (duyetMang->value.getMSV() == _MSV) {
                Node temp;
                temp.value = duyetMang->value;
                temp.next = nullptr;

                result.addStudent(temp);
            }
            duyetMang= duyetMang->next;
        }

        /* free ptr */
        duyetMang = nullptr;
        return result;
    }
    
    /* find by name. */
    LinkList findStudentByName (char * _name)  {
        LinkList result;
        Node *duyetMang = head;

        while(duyetMang != nullptr) {
            if (duyetMang->value.getTen() == _name) {
                Node temp;
                temp.value = duyetMang->value;
                temp.next = nullptr;

                result.addStudent(temp);

                
            }
            result.printAllStudents();
            cout << endl << "end" << endl;
            duyetMang= duyetMang->next;
        }
        
        /* free */
        duyetMang = nullptr;

        return result;
    }

    /* delete Student by ID - MSV */
    void deleteStudent (char *_MSV) {
        Node *duyetMang = head;
        if (duyetMang == nullptr) { duyetMang = nullptr; return;}

        /* xoa phan tu dau. */
        if (duyetMang->value.getMSV() == _MSV) {
            head = duyetMang->next;
            
            duyetMang->next = nullptr;

            /* Del ptr */
            duyetMang = nullptr;
            return;            
        }
        
        /* xoa phan tu khac head. */
        while (duyetMang != nullptr) {
            if ((duyetMang->next)->value.getMSV() == _MSV){
                
                Node *del = duyetMang->next;
                duyetMang->next = duyetMang->next->next;
                del->next = nullptr;

                /* del ptr*/
                delete del;
                del = nullptr;           
            }else {
                duyetMang = duyetMang->next;
            }
            
        }
        cout << "khong tim thay phan tu tu de xoa"<< endl;

        /* free ptr */
        duyetMang = nullptr;
    }

    /* change MSV-ID. */
    void changeStudentInfor (char * oldMSV, char *newMSV) {
        Node *duyetMang = head;
        while (duyetMang != nullptr){
            if (duyetMang->value.getMSV() == oldMSV ) {
                duyetMang->value.setMSV(newMSV);

                /* del ptr then and the method */
                duyetMang = nullptr;
                return;
            }
            duyetMang = duyetMang->next;
        }

        cout << "khong tim thay SV" << endl;
        
        /* del ptr */
        duyetMang = nullptr;
    }

    /* change Name. */
    void changeStudentName (char *_MSV, char *newName) {
        Node *duyetMang = head;
        while (duyetMang != nullptr) {
            if (duyetMang->value.getMSV() == _MSV ) {
                duyetMang->value.setTen(newName);

                /* free ptr */
                duyetMang = nullptr;
                return;
            }
            duyetMang= duyetMang->next;
        }
        cout << "khong tim thay SV" << endl;

        /*free ptr */
        duyetMang = nullptr;
    }

    void sortByName () {
        Node *i, *j;

        i = head;
        while (i != nullptr) {

            j = i->next;
            while (j != nullptr)
            {
                if (strcmp (i->value.getTen(), j->value.getTen()) > 0) {
                    
                    /* swap. */
                    SinhVien *temp = new SinhVien;
                    *temp = i->value;
                    i->value = j->value;
                    j->value = *temp;                    
                }
                j = j->next;
            }
            
            i = i->next;
        }

        i = nullptr;
        j = nullptr;
    }
};

LinkList::LinkList(/* args */)
{
}

/* Destructor */ 
LinkList::~LinkList()
{
    /* Need to delete more */
    // delete this->head;
    // head = nullptr;
    
    while ( head != nullptr) {
        Node *temp = head;
        head = head->next;
        delete temp;
        temp = nullptr;
    }
}


int main () {
    LinkList ll1;

    /* add 3 students. */
    /*
    SinhVien *sv1 = new SinhVien("DTC01", "An Nguyen", 19, 6.7f);
    SinhVien *sv2 = new SinhVien("DTC02", "Nguyen Thanh", 20, 6.4f);
    SinhVien *sv3 = new SinhVien("DTC03", "An Nguyen Thanh", 19, 7.1f);
    SinhVien sv4;
    sv4.Nhap() ;

    ll1.addStudent(sv1);
    ll1.addStudent(sv2);
    ll1.addStudent(sv3);
    ll1.addStudent(sv4);
    */


    /* add 4 students */
    /* */
    ll1.addStudent("DTC01", "An Nguyen", 19, 6.7f);
    ll1.addStudent("DTC02", "Nguyen Thanh", 20, 6.4f);
    ll1.addStudent("DTC03", "An Nguyen Thanh", 19, 7.1f);
    ll1.addStudent("DTC04", "An Nguyen Thanh", 19, 6.4f);
    

    
    

    /* find students have 19 years old, find by DTB, Ten, Tuoi. */
    /*
    ll1.findStudent(19).printAllStudents();
    ll1.findStudent(6.1f).printAllStudents();
    ll1.findStudent(6.4f).printAllStudents();
    ll1.findStudent("DTC01").printAllStudents();*//*
    ll1.findStudentByName("An Nguyen Thanh").printAllStudents();
    */
    
    
    /* Del a student. */
    /*
    ll1.deleteStudent("DTC01");
    ll1.printAllStudents();
    */

    /* change value. */
    /*
    ll1.changeStudentName("DT01", "Thay ten");
    ll1.printAllStudents();
    */

    /* sort */
    /*
    ll1.addStudent("DTC01", "1", 19, 6.7f);
    ll1.addStudent("DTC02", "3", 20, 6.4f);
    ll1.addStudent("DTC03", "2", 19, 7.1f);
    ll1.addStudent("DTC04", "0", 19, 6.4f);
    */

    /* sort by name 
    ll1.sortByName();
    ll1.printAllStudents();
    */

    /* print all. */
    /**/
    ll1.printAllStudents();
    return 0;
}
