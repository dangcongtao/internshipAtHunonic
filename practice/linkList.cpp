#include<iostream>
using namespace std;

struct Node
{
    /* data */
    int value;
    Node *next;
};

class LinkedList
{
private:
    /* data */
    Node *head;
    Node *tail;

public:
    LinkedList(/* args */);
    ~LinkedList();

    // method
    void add (int _value){
        Node *temp = new Node;
        temp->value = _value;
        temp->next = nullptr;

        if(head == nullptr) {
            head = temp;
            tail = temp;
        }else {
            tail->next = temp;
            tail = tail->next;
        }
    }
    void print() {
        Node *temp = head;
        
        do{
            printf ("%d - > ", temp->value);
            temp = temp->next;
        }while (temp != nullptr);
        
    }

    // thay doi thu tu vi tri pos thanh vi tri target.
    void changPos (int pos, int target) {
        Node *arr = this->head;
        Node *temp = new Node;
        Node *temp1 = new Node;
        int count = 0;
        
        // 1. duyet de lay value.

        // duyet toi vi tri pos.
        while ( count != pos ) {
            arr = arr->next;
            count++;
        }
        temp->value =arr->value; 

        // duyet toi vi tri target
        while (count +1 != target){
            arr= arr->next;
        }
        
        temp1->value = ((arr->next)->next)->value;
        

        // 2. duyet linked list to set position.
        arr = head;
        count = 0;
        while (count + 1 != pos ) {
            arr= arr->next;
            ++count;
        }
        temp1->next = (arr->next)->next;
        
    }


    // xap xep theo gia tri
    void sort () {
        //
    }
};

LinkedList::LinkedList(/* args */)
{
    tail = nullptr;
    head = nullptr;
}

LinkedList::~LinkedList()
{
}


int main () {
    LinkedList ll1;

    ll1.add(1);
    ll1.add(22);
    ll1.add(3);

    ll1.print();
    return 0;
}