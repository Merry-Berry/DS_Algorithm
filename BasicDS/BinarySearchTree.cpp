#include <iostream>
#include <queue>
#include <cstring>
#include <string>
using namespace std;

template <typename K, typename E>
class TreeNode{
private:
    K key;
    E element;
    TreeNode<K, E>* left, *right;
public:
    TreeNode(const K k, const E e) : key(k), element(e), left(NULL), right(NULL) {}
    ~TreeNode(){ cout << "Key: " << key << " deleted" << endl; key.~K(); element.~E(); }
    void setLeft(TreeNode<K, E>* node){ left = node; }
    void setRight(TreeNode<K, E>* node){ right = node; }
    TreeNode<K, E>* getLeft()const{ return left; }
    TreeNode<K, E>* getRight()const{ return right; }
    K& getKey(){ return key; }
    E& getElement(){ return element; }
};

template <typename K, typename E>
class BST{
private:
    TreeNode<K, E>* root;
    void Deallocation(TreeNode<K, E>* node);
    void PreOrder(TreeNode<K, E>* node);
    void InOrder(TreeNode<K, E>* node);
    void PostOrder(TreeNode<K, E>* node);
public:
    BST() : root(NULL) {}
    ~BST();
    void Insert(const K&, const E&);
    E Search(const K&) const;
    void Delete(const K&);
    void PreOrder();
    void InOrder();
    void PostOrder();
    void LevelOrder();
};

template <typename K, typename E>
BST<K, E>::~BST(){
    if(root) Deallocation(root);
}

template <typename K, typename E>
void BST<K, E>::Deallocation(TreeNode<K, E>* node){
    if(!node){
        Deallocation(node->getLeft());
        Deallocation(node->getRight());
        delete node;
    }
}

template <typename K, typename E>
void BST<K, E>::Insert(const K& k, const E& e){
    TreeNode<K, E>* newNode = new TreeNode<K, E>(k, e);
    
    if(root){
        TreeNode<K, E>* node = root, *p = NULL;
        while(node){
            p = node;
            if(node->getKey() == k) throw "Key is duplicated";
            else if(node->getKey() > k) node = node->getLeft();
            else node = node->getRight();
        }
        
        if(p->getKey() > k) p->setLeft(newNode);
        else p->setRight(newNode);
    }
    else root = newNode;
}

template <typename K, typename E>
E BST<K, E>::Search(const K& k) const{
    TreeNode<K, E>* node = root;
    while(node){
        if(node->getKey() == k) return node->getElement();
        else if(node->getKey() > k) node = node->getLeft();
        else node = node->getRight();
    }
    return NULL;
    
}

template <typename K, typename E>
void BST<K, E>::Delete(const K& k){
    if(!root) throw "Tree is empty";
    else{
        TreeNode<K, E>* target = root, *p = NULL;
        
        while(target && target->getKey() != k){
            p = target;
            if(target->getKey() > k) target = target->getLeft();
            else target = target->getRight();
        }
        if(!target) cout << "Not found" << endl;

        if(!target->getLeft() && !target->getRight()){
            if(target == root) root = NULL;
            else if(p->getLeft() == target) p->setLeft(NULL);
            else p->setRight(NULL);
        }
        else if(!target->getLeft() && target->getRight()){
            if(target == root) root = target->getRight();
            else if(p->getLeft() == target) p->setLeft(target->getRight());
            else p->setRight(target->getRight());
        }
        else if(target->getLeft() && !target->getRight()){
            if(target == root) root = target->getLeft();
            else if(p->getLeft() == target) p->setLeft(target->getLeft());
            else p->setRight(target->getLeft());
        }
        else{
            TreeNode<K, E>* aNode = target->getRight(), *ap = target;
            cout << "target: " << target->getKey() << endl;
            cout << "target parent: ";
            if(p) cout << p->getKey() << endl;
            else cout << "NULL" <<endl;
            cout << "aNode: " << aNode->getKey() << endl;
            while(aNode->getLeft()){
                ap = aNode;
                aNode = aNode->getLeft();
            }
            cout << "move after aNode: " << aNode->getKey() << endl;
            cout << "move after a parent: ";
            if(ap) cout << ap->getKey() << endl;
            else cout << "NULL" << endl;
            
            if(target == root) root = aNode;
            else if(p->getLeft() == target) p->setLeft(aNode);
            else p->setRight(aNode);

            aNode->setLeft(target->getLeft()); //set aNode's left to target's left child
            if(ap != target){ //if aNode moved, set aNode's parent's left child to aNode's right child
                ap->setLeft(aNode->getRight());
                aNode->setRight(ap);
            } //else, aNode get his right child continuously
        }
        delete target;
    }
}

template <typename K, typename E>
void BST<K, E>::PreOrder(){
    if(!root) throw "Tree is empty";
    PreOrder(root);
}

template <typename K, typename E>
void BST<K, E>::InOrder(){
    if(!root) throw "Tree is empty";
    else InOrder(root);
}

template <typename K, typename E>
void BST<K, E>::PostOrder(){
    if(!root) throw "Tree is empty";
    PostOrder(root);
}

template <typename K, typename E>
void BST<K, E>::LevelOrder(){
    if(!root) throw "Tree is empty";
    queue<TreeNode<K, E>*> qLevel;
    qLevel.push(root);

    while(!qLevel.empty()){
        TreeNode<K, E>* node = qLevel.front(); qLevel.pop();
        cout << "Key: " << node->getKey() << ", Element: " << node->getElement() << endl;
        if(node->getLeft()) qLevel.push(node->getLeft());
        if(node->getRight()) qLevel.push(node->getRight());
    }
}

template <typename K, typename E>
void BST<K, E>::PreOrder(TreeNode<K, E>* node){
    if(node){
        cout << "Key: " << node->getKey() << ", Element: " << node->getElement() << endl;
        PreOrder(node->getLeft());
        PreOrder(node->getRight());
    }
}

template <typename K, typename E>
void BST<K, E>::InOrder(TreeNode<K, E>* node){
    if(node){
        InOrder(node->getLeft());
        cout << "Key: " << node->getKey() << ", Element: " << node->getElement() << endl;
        InOrder(node->getRight());
    }
}

template <typename K, typename E>
void BST<K, E>::PostOrder(TreeNode<K, E>* node){
    if(node){
        PostOrder(node->getLeft());
        PostOrder(node->getRight());
        cout << "Key: " << node->getKey() << ", Element: " << node->getElement() << endl;
    }
}

int main(){
    string cmd;
    BST<int, char*> bst;

    try{
        do{
            cout << "print {<pre>|<in>|<post>|<level>} / insert <key> <value>/ delete <key> / search <key> / exit>> ";
            getline(cin, cmd);
            if(!cmd.compare("exit")) break;
            else if(!cmd.substr(0, 5).compare("print")){
                if(!cmd.substr(6).compare("pre"))
                    bst.PreOrder();
                else if(!cmd.substr(6).compare("in"))
                    bst.InOrder();
                else if(!cmd.substr(6).compare("post"))
                    bst.PostOrder();
                else if(!cmd.substr(6).compare("level"))
                    bst.LevelOrder();
            }
            else if(!cmd.substr(0, 6).compare("insert")){
                char cmd_cstr[110];
                strcpy(cmd_cstr, cmd.substr(7).c_str());
                int k = atoi(strtok(cmd_cstr, " "));
                char* e = new char[100];
                strcpy(e, strtok(NULL, " "));
                bst.Insert(k, e);
            }
            else if(!cmd.substr(0, 6).compare("search")){
                int k = stoi(cmd.substr(7));
                char* node = bst.Search(k);
                cout << ((node) ? node : "Not found") << endl;
            }
            else if(!cmd.substr(0, 6).compare("delete")){
                int k = stoi(cmd.substr(7));
                bst.Delete(k);
            }
            else cout << "Unexpected command." << endl;
        }while(1);
    }catch(const char* excp){
        cout << excp << endl;
        return 0;
    }

    return 0;
}
