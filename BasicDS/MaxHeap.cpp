#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

//MaxHeap
template<typename T>
class MaxHeap{
private:
    T* heap;
    int heapSize;
    int capacity;

public:
    MaxHeap(int capacity = 10);
    void Push(const T& e);
    void Pop();
    bool IsEmpty() const;
    void Print() const;
    void ChangeSize1D(T*& a, const int oldSize, const int newSize);
};

template<typename T>
MaxHeap<T>::MaxHeap(int capacity){
    if(capacity < 1) throw "Capacity must be >= 1";
    this->capacity = capacity;
    heapSize = 0;
    heap = new T[capacity + 1];//index 0 is not used
}

template <typename T>
void MaxHeap<T>::Push(const T& e){
    if(heapSize <= capacity){
        ChangeSize1D(heap, capacity, capacity * 2);
    }
    capacity *= 2;

    int curNum = ++heapSize;
    while(curNum != 1 && heap[curNum / 2] < e){ //if curNum != root's num and parent's element < current element
        heap[curNum] = heap[curNum / 2]; //move parent's element to child
        curNum /= 2; //move current node to parent
    }
    heap[curNum] = e;
}

template <typename T>
void MaxHeap<T>::Pop(){
    if(IsEmpty()) throw "Heap is empty";

    heap[1].~T(); //delete root node
    T lastE = heap[heapSize--];//get last element

    int curNum = 1;
    int childNum = 2;
    while(childNum <= heapSize){ //while current node has child
        if(childNum < heapSize && heap[childNum] < heap[childNum + 1]) childNum++; //compare left-right child

        if(lastE > heap[childNum]) break;
        heap[curNum] = heap[childNum]; //move child node up
        curNum = childNum; //move current node down
        childNum *= 2; //set left child node
    }
    heap[curNum] = lastE;
}

template <typename T>
bool MaxHeap<T>::IsEmpty() const{
    return heapSize == 0;
}

template <typename T>
void MaxHeap<T>::Print() const{
    if(IsEmpty()) throw "Heap is empty";
    for(int i = 1; i <= heapSize; i++)
        cout << heap[i] << " ";
    cout << endl;
}

template <typename T>
void MaxHeap<T>::ChangeSize1D(T*& a, int oldSize, int newSize){
    if(newSize < 0) throw "New Size must be larger than 0";

    T* temp = new T[newSize];
    int num = min(oldSize, newSize);

    copy(a, a + num, temp);
    delete[] a;
    a = temp;
}

int main(){

    string cmd;
    MaxHeap<int> maxHeap;

    try{
        do{
            cout << "push N / pop / print / exit>> ";
            getline(cin, cmd);

            if((cmd.length() >= 6) && !cmd.substr(0, 5).compare("push ")){
                maxHeap.Push(stoi(cmd.substr(5)));
            }
            else if(!cmd.compare("pop")){
                maxHeap.Pop();
            }
            else if(!cmd.compare("print")){
                maxHeap.Print();
            }
            else if(!cmd.compare("exit")){
                break;
            }
            else{
                cout << "Unexpected command." << endl;
            }
        }while(1);
    }
    catch(const char* excp){
        cout << excp << endl;
        return 0;
    }

    return 0;
}
