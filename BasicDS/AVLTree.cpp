#include <iostream>
#include <queue>
#include <string>
#include <cstring>
using namespace std;
template <typename K, typename E> class AVL;

template <typename K, typename E>
class AvlNode{
    friend class AVL<K, E>; //declare friend class
private:
    K key;
    E element;
    int bf; //balance facter
    AvlNode<K, E> *leftChild, *rightChild; //child pointer

public:
    AvlNode(const K& k, const E& e){ //initialize member variable
        key = k;
        element = e;
        bf = 0;
        leftChild = rightChild = NULL;
    }
};

template <typename K, typename E>
class AVL{
private:
    AvlNode<K, E>* root;

public:
    AVL() : root(NULL) {}; //initialize root pointer
    void Insert(const K&, const E&);
    void PrintLevel() const;
    void InOrder() const{ InOrder(root); cout << endl; };
    void InOrder(AvlNode<K, E>* node) const;
};

template <typename K, typename E>
void AVL<K, E>::Insert(const K& k, const E& e){
    if(!root){
        root = new AvlNode<K, E>(k, e);
        return;
    }

    AvlNode<K, E> *a = root, *ap = NULL; //ANode pointer
    AvlNode<K, E> *p = root, *pp = NULL; //location pointer of inserted node
    AvlNode<K, E> *rootSub = NULL;

    while(p){
        if(p->bf != 0){ //if bf is not 0
            a = p; ap = pp; //set ANode pointer
        }
        //locate current node
        if(k < p->key){
            pp = p;
            p = p->leftChild;
        }
        else if(k > p->key){
            pp = p;
            p = p->rightChild;
        }
        else{
            p->element = e;
            return;
        }
    }

    //y pointer is the location of inserted node
    AvlNode<K, E> *y = new AvlNode<K, E>(k, e);
    if(k < pp->key) pp->leftChild = y;
    else pp->rightChild = y;

    int d; //bf variation
    AvlNode<K, E>* aChild, *aGrandChild;
    if(k > a->key){ //if inserted node is located in right subtree of a
        aChild = p = a->rightChild;
        d = -1; //decrease bf
    }
    else{ //if inserted node is located in left subtree of a
        aChild = p = a->leftChild;
        d = 1; //increase bf
    }

    //if p(child of ANode) is not y(inserted node)
    //change bf between aChild and y
    while(p != y){
        if(k > p->key){
            p->bf = -1; p = p->rightChild;
        }
        else{
            p->bf = 1; p = p->leftChild;
        }
    }

    if(!(a->bf) || !(a->bf + d)){ //if tree is ballanced
        a->bf += d; return; //return 0 if tree is balanced after insert new node
    }

    if(d == 1){
        if(aChild->bf == 1){ //LL rotation
            a->leftChild = aChild->rightChild;
            aChild->rightChild = a;
            a->bf = aChild->bf = 0;
            rootSub = aChild; //aChild is the new root of the subtree
        }
        else{ //LR rotation : RR -> LL
            aGrandChild = aChild->rightChild;
            //RR
            aChild->rightChild = aGrandChild->leftChild;
            aGrandChild->leftChild = aChild;
            //LL
            a->leftChild = aGrandChild->rightChild;
            aGrandChild->rightChild = a;

            switch(aGrandChild->bf){
            case 1:
                a->bf = -1; aChild->bf = 0;
                break;
            case -1:
                a->bf = 0; aChild->bf = 1;
                break;
            case 0: //WHY THIS CASE SHOULD BE CONSIDERED??->one root node and its left or right child node case
                aChild->bf = a->bf = 0;
                break;
            }
            aGrandChild->bf = 0;
            rootSub = aGrandChild;
        }
    }
    else{
        if(aChild->bf == -1){ //RR rotation
            a->rightChild = aChild->leftChild;
            aChild->leftChild = a;
            a->bf = aChild->bf = 0;
            rootSub = aChild;
        }
        else{ //RL rotation : LL->RR
            aGrandChild = aChild->leftChild;
            //LL
            aChild->leftChild = aGrandChild->rightChild;
            aGrandChild->rightChild = aChild;
            //RR
            a->rightChild = aGrandChild->leftChild;
            aGrandChild->leftChild = a;

            switch(aGrandChild->bf){
            case 1:
                a->bf = 0; aChild->bf = -1;
                break;
            case -1:
                a->bf = 1; aChild->bf = 0;
                break;
            case 0:
                a->bf = 0; aChild->bf = 0;
            }
            aGrandChild->bf = 0;
            rootSub = aGrandChild;
        }
    }

    if(!ap) root = rootSub;
    else if(a == ap->leftChild) ap->leftChild = rootSub;
    else ap->rightChild = rootSub;
    return;
}

template <typename K, typename E>
void AVL<K, E>::PrintLevel() const{
    queue<AvlNode<K, E>*> qLevel;
    AvlNode<K, E>* node = root;

    while(node){
        cout << node->element << " ";
        if(node->leftChild) qLevel.push(node->leftChild);
        if(node->rightChild) qLevel.push(node->rightChild);
        if(qLevel.empty()) break;
        node = qLevel.front();
        qLevel.pop();
    }
    cout << endl;
}

template <typename K, typename E>
void AVL<K, E>::InOrder(AvlNode<K, E>* node) const{
    if(node){
        InOrder(node->leftChild);
        cout << node->element << " ";
        InOrder(node->rightChild);
    }
}


int main(){

    string cmd;
    AVL<int, int>* avlTree = new AVL<int, int>();
    
    try{
        do{
            cout << "insert <key> <value> / print {<level>|<in>} / exit>> ";
            getline(cin, cmd);

            if((cmd.length() >= 6) && !cmd.substr(0, 6).compare("insert")){
                char cStr[100];
                strcpy(cStr, cmd.substr(7).c_str());
                int k = atoi(strtok(cStr, " "));
                int e = atoi(strtok(NULL, " "));
                avlTree->Insert(k, e);
            }
            else if(cmd.length() >= 5 && !cmd.substr(0, 5).compare("print") ){
                if(!cmd.substr(6).compare("level")) avlTree->PrintLevel();
                else if(!cmd.substr(6).compare("in")) avlTree->InOrder();
                else cout << "Unexpected command." << endl;
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
        delete[] avlTree;
        return 0;
    }

    delete avlTree;
    return 0;
}
