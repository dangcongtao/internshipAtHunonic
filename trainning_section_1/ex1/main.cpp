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

        /* can't free ptr */
        // delete duyetMang;
        // duyetMang = nullptr;        
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
        
        /* free ptr */
        // delete duyetMang;
        // duyetMang = nullptr;
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
            return ;
        }

         /* free ptr */
        // delete duyetMang;
        // duyetMang = nullptr;
    }

    void addStudent ( int numberStudent) {
        for ( int i = 0 ; i < numberStudent ; i ++) {
            addStudent();
            cin.ignore();
        }
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
        // delete duyetMang;
        // duyetMang = nullptr;     
    }


    void printAllStudents() {
        Node *duyetMang = head;

        if (duyetMang == nullptr) {
            cout<< "Khong co thong tin nao.";

            /* free ptr */
            delete duyetMang;
            duyetMang = nullptr;
            return;
        }

        while (duyetMang != nullptr) {
            cout << endl;
            duyetMang->value.print();

            duyetMang = duyetMang->next;            
        }

        /* free ptr */
        delete duyetMang;
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
        delete duyetMang;
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
        delete duyetMang;
        duyetMang = nullptr;
        return result;
    }
    
    /* find by ID - MSV. */
    LinkList findStudent ( char *_MSV) {
        LinkList result;
        Node *duyetMang = head;

        while(duyetMang != nullptr) {
            if (strcmp(duyetMang->value.getMSV(), _MSV) == 0) {
                Node temp;
                temp.value = duyetMang->value;
                temp.next = nullptr;

                result.addStudent(temp);
            }
            duyetMang= duyetMang->next;
        }

        /* free ptr */
        delete duyetMang;
        duyetMang = nullptr;
        return result;
    }
    
    /* find by name. */
    LinkList findStudentByName (char * _name)  {
        LinkList result;
        Node *duyetMang = head;

        while(duyetMang != nullptr) {
            if (strcmp(duyetMang->value.getTen(), _name) == 0) {
                Node temp;
                temp.value = duyetMang->value;
                temp.next = nullptr;

                result.addStudent(temp);
                
            }
            
            duyetMang= duyetMang->next;
        }
        
        /* free */
        // delete duyetMang;
        // duyetMang = nullptr;

        return result;
    }

    /* delete Student by ID - MSV */
    void deleteStudent (char *_MSV) {
        Node *duyetMang = head;

        if (duyetMang == nullptr) {
            return;
        }

        /* xoa phan tu dau. */
        if (strcmp(duyetMang->value.getMSV() , _MSV)==0) {
            head = duyetMang->next;
            
            duyetMang->next = nullptr;

            /* Del ptr */
            delete duyetMang;
            duyetMang = nullptr;
            return;            
        }
        
        /* xoa phan tu khac head. */
        while (duyetMang != nullptr) {
            if (strcmp((duyetMang->next)->value.getMSV(), _MSV) == 0){
                
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
        delete duyetMang;
        duyetMang = nullptr;
    }

    /* change MSV-ID. */
    void changeStudentInfor (char * oldMSV, char *newMSV) {
        Node *duyetMang = head;
        while (duyetMang != nullptr){
            if (strcmp(duyetMang->value.getMSV(), oldMSV ) == 0 ){
                duyetMang->value.setMSV(newMSV);

                /* del ptr then and the method */
                delete duyetMang;
                duyetMang = nullptr;
                return;
            }
            duyetMang = duyetMang->next;
        }

        cout << "khong tim thay SV" << endl;
        
        /* del ptr */
        delete duyetMang;
        duyetMang = nullptr;
    }

    /* change Name. */
    void changeStudentName (char *_MSV, char *newName) {
        Node *duyetMang = head;
        while (duyetMang != nullptr) {
            if (strcmp(duyetMang->value.getMSV(), _MSV) == 0 ) {
                duyetMang->value.setTen(newName);

                /* free ptr */
                // delete duyetMang;
                // duyetMang = nullptr;
                return;
            }
            duyetMang= duyetMang->next;
        }
        cout << "khong tim thay SV" << endl;

        /*free ptr */
        // delete duyetMang;
        // duyetMang = nullptr;s
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

        delete i,j;
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
 
    int luaChon = -1;
    
    do {
        system("clear");
    printf ("1. nhap SV.\n 2. sua ten sinh vien. \n 3. xoa sinh vien theo MSV\n 4. tim kiem theo ten\n 5. sap xep theo ten\n 6. in danh sach.\n 0. thoat\n\n");
    cin >> luaChon;

        // nhap sv 
        if (luaChon == 1) {
            system("clear");
            int number = 0;
            cout << "nhap so sinh vien muon them vao: "<< endl;
            cin >> number;

            cin.ignore();
            ll1.addStudent(number);
        }

         // sua ten SV 
        if (luaChon == 2) {
            system("clear");

            cout << "---sua ten sinh vien----" << endl;
            
            char _MSV[30];
            char _Ten[30];
            char pause = ' ';

            cout <<"nhap MSV muon sua: ";
            cin.ignore();
            scanf ("%[A-Za-z0-9]",_MSV);
            cin.ignore();
            cout << "nhap ten moi: ";
            scanf ("%[A-Za-z ]", _Ten);

            cout <<"." <<_Ten << "." << _MSV<<"." << endl;

            ll1.changeStudentName(_MSV, _Ten);

            cout << endl << "doi ten thanh cong";
            cout << endl << "an phim bt ky."<<endl;

            ll1.printAllStudents();
            cin>> pause;
            
        }

        //  xoa SV theo MSV 
        if (luaChon == 3) {
            system("clear");

            cout << "---xoa sinh vien----" << endl;
            
            char _MSV[30];
            char pause = 'a';

            cout <<"nhap MSV muon xoa: ";
            cin.ignore();
            scanf ("%[A-Za-z0-9]",_MSV);

            ll1.deleteStudent(_MSV);
            cout << "da xoa."<< endl << "an Enter";
            cin >> pause;
        }
        
        // tiem kiem 
        if (luaChon == 4) {
            system("clear");

            cout << "---Tim kiem sinh vien bang ten---" << endl;

            cin.ignore();
            char _ten[30];
            int pause = 0;

            cout <<"nhap Ten Sinh Vien muon tim: ";
            scanf ("%[A-Za-z ]",_ten);
            cout << "Ten: " <<"." <<_ten << ".";

            system("clear");
            cout << "Ket qua tim kiem:"<<endl;
            ll1.findStudentByName(_ten).printAllStudents();

            // cout <<endl<< "";s
            cin>> pause;
        }

        if (luaChon == 5) {
            system("clear");
            
            char pause = ' ';
            ll1.sortByName();
            cout <<" ket qua sau khi sap xep:" << endl;
            
            ll1.printAllStudents();

            cout <<endl<< "An enter";
            cin>> pause;
        }
        if (luaChon == 6 ) {
            system("clear");

            char pause = '0';
            ll1.printAllStudents();
            cout <<endl<< "An enter";
            cin>> pause;
        }
    }
    while (luaChon != 0);
    /**/

    ll1.~LinkList();
    return 0;
}
