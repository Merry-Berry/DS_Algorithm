#include <iostream>
#include <algorithm> //min(), copy()
# include <string> //string class
using namespace std;

template <typename T>
class Stack{
public:
    Stack(int stackCapacity = 10);
    ~Stack() {delete[] stack;}
    bool IsEmpty() const;
    T& Top() const;
    void Push(const T& item);
    void Pop();
    void Print() const;
    void SizeExpension(T*& arr, const int oldSize, const int newSize);
private:
    T* stack;
    int top;
    int capacity;
};

template <typename T>
Stack<T>::Stack(int stackCapacity){
    if(stackCapacity < 1)
        throw "Stack capacity must be larger than 0";
    stack = new T[stackCapacity];
    top = -1;
    capacity = stackCapacity;
}

template <typename T>
bool Stack<T>::IsEmpty() const{
    return top == -1;
}

template <typename T>
T& Stack<T>::Top() const{
    if(IsEmpty())
        throw "Stack is empty";
    return stack[top];
}

template <typename T>
void Stack<T>::Push(const T& item){
    if(top + 1 == capacity){
        SizeExpension(stack, capacity, capacity * 2);
        capacity *= 2;
    }

    stack[++top] = item;
}

template <typename T>
void Stack<T>::Pop(){
    if(IsEmpty())
        throw "Stack is empty";
    stack[top--].~T(); //call destructor of T
}

template <typename T>
void Stack<T>::Print() const{
    if(IsEmpty())
        cout << "Stack is empty" << endl;
    
    cout << "current Stack : ";
    for(int i = 0; i <= top; i++)
        cout << stack[i] << " ";
    cout << endl;
}

template <typename T>
void Stack<T>::SizeExpension(T*& arr, const int oldSize, const int newSize){
    if(newSize < 1)
        throw "New stack capacity must be larger than 0";
    
    int minSize = min(oldSize, newSize);
    T* newStack = new T[newSize];
    copy(arr, arr + minSize, newStack);
    delete[] arr;
    arr = newStack;
}

int main(){

    Stack<int>* intStack;
    try{
        intStack = new Stack<int>(5);

        string cmd;
        do{
            
            cout << "command : push N / pop / top / print / exit>>";
            getline(cin, cmd);

            if(cmd.length() >= 4 && !cmd.substr(0, 5).compare("push ")){
                intStack->Push(stoi(cmd.substr(5)));
            }
            else if(!cmd.compare("top")){
                cout << intStack->Top() << endl;
            }
            else if(!cmd.compare("pop")){
                intStack->Pop();
            }
            else if(!cmd.compare("print")){
                intStack->Print();
            }
            else if(!cmd.compare("exit")){
                break;
            }
            else{
                cout << "unexpected command." << endl;
            }

        }while(1);
    }
    catch(const char* excp){
        cout << excp << endl;
        delete intStack;
        return 0;
    }

    delete intStack;
    return 0;
}
