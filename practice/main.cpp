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
        Node *temp = new Node();
        Node *duyetmang;
        temp->value.Nhap();
        temp->next = nullptr;

        if ( head ==nullptr) {
            head = temp;
        }else {
            duyetmang = this->head;
            while (duyetmang->next != nullptr) {
                duyetmang = duyetmang->next;
            }
            duyetmang->next = temp;
        }
        
    }

    void addStudent (Node *temp) {
        Node *duyetmang;
        if ( head ==nullptr) {
            head = temp;
        }else {
            duyetmang = this->head;
            while (duyetmang->next != nullptr) {
                duyetmang = duyetmang->next;
            }
            duyetmang->next = temp;
        }
    }

    void addStudent (SinhVien *sv) {
        Node *temp = new Node();
        Node *duyetmang;
        temp->value = *sv;
        temp->next = nullptr;

        if ( head ==nullptr) {
            head = temp;
        }else {
            duyetmang = this->head;
            while (duyetmang->next != nullptr) {
                duyetmang = duyetmang->next;
            }
            duyetmang->next = temp;
        }
    }


// have to create sv first, cant use setvalue.
    void addStudent (char *_MSV, char *_ten, int _tuoi, float _DTB) {
        SinhVien *sv = new SinhVien (_MSV, _ten, _tuoi,  _DTB);
        Node *temp = new Node;
        temp->value = *sv;
        temp->next = nullptr;
        
        Node *duyetmang;
        if ( head ==nullptr) {
            head = temp;
        }else {
            duyetmang = this->head;
            while (duyetmang->next != nullptr) {
                duyetmang = duyetmang->next;
            }
            duyetmang->next = temp;
        }        
    }


    void printAllStudents() {
        Node *duyetmang = head;

        if (duyetmang == nullptr) {
            cout<< "Khong co thong tin nao.";
            return;
        }

        while (duyetmang != nullptr) {
            cout << endl;
            duyetmang->value.print();

            duyetmang = duyetmang->next;            
        }
    }

    // find by tuoi-age.
    LinkList findStudent (int tuoi) {
        LinkList result;
        Node *duyetmang = head;

        while(duyetmang != nullptr) {
            if (duyetmang->value.getTuoi() == tuoi) {
                Node *temp = new Node;
                temp->value = duyetmang->value;
                temp->next = nullptr;

                result.addStudent(temp);
            }
            duyetmang= duyetmang->next;
        }
        return result;
    }

    // find by DTB
    LinkList findStudent (float _DTB) {
        LinkList result;
        Node *duyetmang = head;

        while(duyetmang != nullptr) {
            if (duyetmang->value.getDTB() == _DTB) {
                Node *temp = new Node;
                temp->value = duyetmang->value;
                temp->next = nullptr;

                result.addStudent(temp);
            }
            duyetmang= duyetmang->next;
        }
        return result;
    }
    
    // find by ID - MSV.
    LinkList findStudent ( char *_MSV) {
        LinkList result;
        Node *duyetmang = head;

        while(duyetmang != nullptr) {
            if (duyetmang->value.getMSV() == _MSV) {
                Node *temp = new Node;
                temp->value = duyetmang->value;
                temp->next = nullptr;

                result.addStudent(temp);
            }
            duyetmang= duyetmang->next;
        }
        return result;
    }
    
    // find by name.
    LinkList findStudentByName (char * _name)  {
        LinkList result;
        Node *duyetmang = head;

        while(duyetmang != nullptr) {
            if (duyetmang->value.getTen() == _name) {
                Node *temp = new Node;
                temp->value = duyetmang->value;
                temp->next = nullptr;

                result.addStudent(temp);
            }
            duyetmang= duyetmang->next;
        }
        return result;
    }

    // delete Student by ID - MSV
    void deleteStudent (char *_MSV) {
        Node *duyetmang = head;
        if (duyetmang == nullptr) return;

        // xoa phan tu dau.
        if (duyetmang->value.getMSV() == _MSV) {
            head = duyetmang->next;
            
            duyetmang->next = nullptr;
            delete duyetmang;
            return;
            // delete del;
        }
        
        // xoa phan tu khac head.
        while (duyetmang != nullptr) {
            if ((duyetmang->next)->value.getMSV() == _MSV){
                
                Node *del = duyetmang->next;
                duyetmang->next = duyetmang->next->next;
                del->next = nullptr;

                delete del;                
            }else {
                duyetmang = duyetmang->next;
            }
            
        }
        cout << "khong tim thay phan tu tu de xoa"<< endl;
    }

    // change MSV-ID.
    void changeStudentInfor (char * oldMSV, char *newMSV) {
        Node *duyetmang = head;
        while (duyetmang != nullptr){
            if (duyetmang->value.getMSV() == oldMSV ) {
                duyetmang->value.setMSV(newMSV);
                return;
            }
            duyetmang = duyetmang->next;
        }

        cout << "khong tim thay SV" << endl;
    }

    // change Name.
    void changeStudentName (char *_MSV, char *newName) {
        Node *duyetmang = head;
        while (duyetmang != nullptr) {
            if (duyetmang->value.getMSV() == _MSV ) {
                duyetmang->value.setTen(newName);
                return;
            }
            duyetmang= duyetmang->next;
        }
        cout << "khong tim thay SV" << endl;
    }

    void sortByName () {
        Node *i, *j;

        i = head;
        while (i != nullptr) {

            j = i->next;
            while (j != nullptr)
            {
                if (strcmp (i->value.getTen(), j->value.getTen()) > 0) {
                    
                    // swap.
                    SinhVien *temp = new SinhVien;
                    *temp = i->value;
                    i->value = j->value;
                    j->value = *temp;                    
                }
                j = j->next;
            }
            
            i = i->next;
        }
    }
};

LinkList::LinkList(/* args */)
{
}

LinkList::~LinkList()
{
}


int main () {
    LinkList ll1;

    // add 3 students.
    // SinhVien *sv1 = new SinhVien("DTC01", "An Nguyen", 19, 6.7f);
    // SinhVien *sv2 = new SinhVien("DTC02", "Nguyen Thanh", 20, 6.4f);
    // SinhVien *sv3 = new SinhVien("DTC03", "An Nguyen Thanh", 19, 7.1f);
    
    // ll1.addStudent(sv1);
    // ll1.addStudent(sv2);
    // ll1.addStudent(sv3);


    // add 3 students
    // ll1.addStudent("DTC01", "An Nguyen", 19, 6.7f);
    // ll1.addStudent("DTC02", "Nguyen Thanh", 20, 6.4f);
    // ll1.addStudent("DTC03", "An Nguyen Thanh", 19, 7.1f);
    // ll1.addStudent("DTC04", "An Nguyen Thanh", 19, 6.4f);
    

    // print all.
    // ll1.printAllStudents();

    // find students have 19 years old, find by DTB, Ten, Tuoi.
    // findStudent(19).printAllStudents();
    // ll1.findStudent(6.1f).printAllStudents();
    // ll1.findStudent(6.4f).printAllStudents();
    // ll1.findStudent("DTC01").printAllStudents();
    // ll1.findStudentByName("An Nguyen Thanh").printAllStudents();
    
    // Del a student.
    // ll1.deleteStudent("DTC01");
    // ll1.printAllStudents();

    // change value.
    // ll1.changeStudentName("DT01", "Thay ten");
    // ll1.printAllStudents();

    // sort
    ll1.addStudent("DTC01", "1", 19, 6.7f);
    ll1.addStudent("DTC02", "3", 20, 6.4f);
    ll1.addStudent("DTC03", "2", 19, 7.1f);
    ll1.addStudent("DTC04", "0", 19, 6.4f);
    
    ll1.sortByName();
    ll1.printAllStudents();

    return 0;
}