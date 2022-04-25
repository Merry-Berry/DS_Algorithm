#include <iostream>
using namespace std;

template <typename T>
class Chain;

//ChainNode Class
template <typename T>
class ChainNode{
    friend class Chain<T>;

public:
    ChainNode(const T data, ChainNode<T>* link = NULL);

private:
    T data;
    ChainNode<T> *link;
};

template <typename T>
ChainNode<T>::ChainNode(const T data, ChainNode<T>* link){
    this->data = data;
    this->link = link;
} 

//Chain Class
template <typename T>
class Chain{
public:
    Chain();
    virtual ~Chain();

    bool IsEmpty() const;
    void Print() const;

    void StackPush(T data);
    void StackPop();
     void QueuePush(T data);
    void QueuePop();
protected:
    ChainNode<T>* first;
    ChainNode<T>* last;
};

template <typename T>
Chain<T>::Chain(){
    first = NULL;
    last = NULL;
}

template <typename T>
Chain<T>::~Chain(){
    ChainNode<T>* next = NULL;

    while(first != NULL){
        next = first->link;
        delete first;
        first = next;
    }
}

template <typename T>
bool Chain<T>::IsEmpty() const{
    return first == NULL;
}

template <typename T>
void Chain<T>::Print() const{
    ChainNode<T>* current = first;
    cout << "Chain : ";
    if(!current) cout << "empty" << endl;
    while(current != NULL){
        cout << current->data << " ";
        current = current->link;
    }
    cout << endl;
}

template <typename T>
void Chain<T>::StackPush(T data){
    if(IsEmpty())
        last = first = new ChainNode<T>(data, first);
    else
        first = new ChainNode<T>(data, first);
    cout << "StackPush: " << data << endl;
}

template <typename T>
void Chain<T>::StackPop(){
    ChainNode<T>* top = first;

    if(IsEmpty())
        cout << "StackPop: empty!" << endl;
    else{
        cout << "StackPop: " << top->data << endl;
        first = top->link;
        delete top;
    }
}

template <typename T>
void Chain<T>::QueuePush(T data){
    if(IsEmpty())
        first = last = new ChainNode<T>(data, NULL);
    else
        last = last->link = new ChainNode<T>(data, NULL);
    cout << "QueuePush: " << data << endl;
}

template <typename T>
void Chain<T>::QueuePop(){
    ChainNode<int>* front = first;

    if(IsEmpty())
        cout << "QueuePop: empty!" << endl;
    else{
        cout << "QueuePop: " << front->data << endl;
        first = front->link;
        delete front;
    }
}

int main(){
    string cmd;
    Chain<int>* chain = new Chain<int>;

    while(1){
        chain->Print();
        cout << "stackpush N / stackpop / queuepush N / queuepop / exit>>";
        getline(cin, cmd);
        
        if((cmd.length() >= 11) && !cmd.substr(0, 10).compare("stackpush ")){
            chain->StackPush(stoi(cmd.substr(10)));
        }
        else if(!cmd.compare("stackpop")){
            chain->StackPop();
        }        
        else if((cmd.length() >= 11) && !cmd.substr(0, 10).compare("queuepush ")){
            chain->QueuePush(stoi(cmd.substr(10)));
        }
        else if(!cmd.compare("queuepop")){
            chain->QueuePop();
        }
        else if(!cmd.compare("exit")){
            break;
        }
        else{
            cout << "Unexpected command." << endl;
        }
    }

    delete chain;
    return 0;
}
