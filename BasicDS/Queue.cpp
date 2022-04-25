#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

template <typename T>
class Queue{
private:
    int capacity;
    int rear;
    T* queue;
public:
    Queue(int capacity = 10);
    ~Queue();

    bool IsEmpty() const;
    T& Front() const;
    T& Rear() const;
    void Push(const T& item);
    void Pop();
    void sizeExpand(T*& arr, int oldSize, int newSize);
    void Print() const;
};

template <typename T>
Queue<T>::Queue(int capacity){
    if(capacity < 1)
        throw "queue size must be > 0";
    
    this->capacity = capacity;
    queue = new T[this->capacity];
    rear = -1;
}

template <typename T>
Queue<T>::~Queue(){
    delete[] queue;
}

template <typename T>
bool Queue<T>::IsEmpty() const{
    return rear == -1;
}

template <typename T>
T& Queue<T>::Front() const{
    if(IsEmpty())
        throw "queue is empty.";
    return queue[0];
}

template <typename T>
T& Queue<T>::Rear() const{
    if(IsEmpty())
        throw "queue is empty.";
    return queue[rear];
}

template <typename T>
void Queue<T>::Push(const T& item){
    if(capacity == rear + 1){
        sizeExpand(queue, capacity, capacity * 2);
        capacity *= 2;
    }
    queue[++rear] = item;
}

template <typename T>
void Queue<T>::Pop(){
    if(IsEmpty())
        throw "queu is empty.";
        
    queue[0].~T();
    for(int i = 0; i < rear; i++){
        queue[i] = queue[i + 1];
    }
    rear--;
}

template <typename T>
void Queue<T>::sizeExpand(T*& arr, int oldSize, int newSize){
    T* temp = new T[newSize];
    copy(arr, arr + oldSize, temp);
    delete[] arr;
    arr = temp;
}

template <typename T>
void Queue<T>::Print() const{
    cout << "queue : ";
    if(IsEmpty())
        cout << "empty";
    else{
        for(int i = 0; i <= rear; i++)
            cout << queue[i] << " ";
    }
    cout << endl;
}

int main(){

    string cmd;
    Queue<int>* que = new Queue<int>;

    try{
        do{
            que->Print();
            cout << "push N / pop / front / rear / exit>>";
            getline(cin, cmd);

            if((cmd.length() >= 6) && !cmd.substr(0, 5).compare("push ")){
                que->Push(stoi(cmd.substr(5)));
            }
            else if(!cmd.compare("pop")){
                que->Pop();
            }
            else if(!cmd.compare("front")){
                cout << que->Front() << endl;
            }
            else if(!cmd.compare("rear")){
                cout << que->Rear() << endl;
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
        delete[] que;
        return 0;
    }

    delete que;
    return 0;
}
