#include <cassert>
#include <iostream>

using namespace std;



struct Node{
    int val;
    Node* next;
    Node* prev;
    Node(int v): val(v), next(nullptr), prev(nullptr){}
};



class Stack
{
public:
	Stack() : head(nullptr){}
	~Stack() {clear();}
    void push(int value){
        Node* new_node = new Node(value);
        new_node -> next = head;
        head = new_node;
    }

    void pop(){
        Node* temp = head;
        head = head -> next;
        delete temp;
    }

    int top()const{
        return head->val;
    }

 private:

    Node *head;
    void clear(){
        while (head){
            pop();
        }
        
    }
};


class Deque
{
public:
	Deque() : head(nullptr), tail(nullptr){}
	~Deque() {clear();}
    void push_front(int value){
        Node* new_node = new Node(value);
        new_node -> next = head;
        if(head) head->prev = new_node;
        head = new_node;
        if (!tail) tail = head;
    }

    void push_back(int value){   
        Node* new_node = new Node(value);
        new_node->prev = tail;
        if (tail) tail->next = new_node;
        tail = new_node;
        if(!head) head = tail;
    }

    void pop_front(){
        Node* temp = head;
        head = head->next;
        if(head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
    }

    void pop_back(){
        Node* temp = tail;
        tail = tail->prev;
        if(tail) tail->next = nullptr;
        else head= nullptr;
        delete temp;
    }

    int front()const{
        return head->val;
    }

    int back()const{
        return tail->val;
    }

    void print(){
        Node* current = tail;
        while(current){
            cout << current ->val << endl;
            current = current->prev;
        }
    }

private:
    Node* head;
    Node* tail;
    void clear(){
        while (head){
            pop_front();
        }
    }
};



int main()
{
	string op;
	int next_car = 0;
	Stack t0;
    int t0_size = 0;
	Deque t1;
    int t1_size = 0;
    Deque print;
	while (true) {
		cin >> op ;
		if (cin.eof()) break;
        if(op == "E0"){
            t0.push(next_car);
            next_car += 1;
            t0_size += 1;
        }
        if(op == "S0"){
            print.push_front(t0.top());
            t0.pop();
            t0_size -= 1;
        }
        if(op == "E1E"){
            t1.push_front(next_car);
            next_car += 1;
            t1_size += 1;
        }
        if(op == "E1D"){
            t1.push_back(next_car);
            next_car += 1;
            t1_size += 1;
        }
        if(op == "S1E"){
            print.push_front(t1.front());
            t1.pop_front();
            t1_size -= 1;
        }
        if(op == "S1D"){
            print.push_front(t1.back());
            t1.pop_back();
            t1_size -= 1;
        }
        if(op == "FIM"){     
            print.print();
            cout << t0_size << endl;
            cout << t1_size << endl;
            cout << endl;
            t0.~Stack();
            t1.~Deque();
            print.~Deque();
            t0_size = 0;
            t1_size = 0;
            next_car = 0;
        }
    
	}

}
