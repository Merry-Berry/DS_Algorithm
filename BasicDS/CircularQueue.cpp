#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
class CircularQueue{
private:
    int capacity;
    int front;
    int rear;
    T* circularque;
public:
    CircularQueue(int capacity = 5);
    ~CircularQueue();

    T& Front() const;
    T& Rear() const;
    void Push(const T& item);
    void Pop();
    void sizeExpand(T*& arr, const int oldSize, const int newSize);
    void Print() const;
};

template <typename T>
CircularQueue<T>::CircularQueue(int capacity){
    if(capacity < 1)
        throw "queue size must be > 0";
    this->capacity = capacity;
    circularque = new T[capacity];
    front = rear = 0;
}

template <typename T>
CircularQueue<T>::~CircularQueue(){
    delete[] circularque;
}

template <typename T>
T& CircularQueue<T>::Front() const{
    if(front == rear)
        throw "stack is empty.";
    return circularque[front + 1];
}

template <typename T>
T& CircularQueue<T>::Rear() const{
    if(front == rear)
        throw "stack is empty.";
    return circularque[rear];
}

template <typename T>
void CircularQueue<T>::Push(const T& item){
    if(++rear % capacity == front){ //Full tank
        sizeExpand(circularque, capacity, capacity * 2);
        capacity *= 2;
    }
    rear %= capacity;
    circularque[rear] = item;
}

template <typename T>
void CircularQueue<T>::Pop(){
    if(front == rear) //empty
        throw "stack is empty.";
    else
        front = (front + 1) % capacity;
        circularque[front].~T();
}

template <typename T>
void CircularQueue<T>::sizeExpand(T*& arr, const int oldSize, const int newSize){
    T* temp = new T[newSize];
    copy(arr, arr + oldSize, temp);
    delete[] arr;
    arr = temp;
}

template <typename T>
void CircularQueue<T>::Print() const{
    cout << "Circular Queue : ";
    if(front == rear)
        cout << "empty";
    else{
        for(int i = (front + 1) % capacity; i != (rear + 1) % capacity; i = (i + 1) % capacity){
            cout << circularque[i] << " ";
        }
    }
    cout << endl;
}

int main(){

    string cmd;
    CircularQueue<int>* cQue = new CircularQueue<int>;

    try{
        do{
            cQue->Print();
            cout << "push N / pop / front / rear / exit>>";
            getline(cin, cmd);

            if((cmd.length() >= 4) && !cmd.substr(0, 5).compare("push ")){
                cQue->Push(stoi(cmd.substr(5)));
            }
            else if(!cmd.compare("pop")){
                cQue->Pop();
            }
            else if(!cmd.compare("front")){
                cout << cQue->Front() << endl;
            }
            else if(!cmd.compare("rear")){
                cout << cQue->Rear() << endl;
            }
            else if(!cmd.compare("exit")){
                break;
            }
            else{
                cout << "Unexpected command." << endl;
            }
        }while(1);
    }
    catch(char* excp){
        cout << excp << endl;
    }
    

    delete cQue;
    return 0;
}
