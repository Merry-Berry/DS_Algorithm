#include <iostream>
#include <string> //string class
#include <stack> //STL stack
#include <utility> //STL pair
#include <vector> //STL vector
using namespace std;


int main(){
    stack<int> pIdx;
    string formula;
    vector<pair<int, int>> pairArr;

    cin >> formula;
    for(int i = 0; i < formula.size(); i++){
        if(formula[i] == '(')
            pIdx.push(i);
        else if(formula[i] == ')'){
            if(pIdx.empty()){
                cout << "right parenthesis at " << i << " has no matching left parenthesis" << endl;
            }
            else{
                int openIdx = pIdx.top();
                pIdx.pop();
                pairArr.push_back(pair<int, int>(openIdx, i));
            }
        }
    }

    if(!pIdx.empty()){
        while(!pIdx.empty()){
            int openIdx = pIdx.top();
            pIdx.pop();
            cout << "left parenthesis at " << openIdx << " has no matching right parenthesis" << endl;
        }
    }

    for(auto it = pairArr.begin(); it != pairArr.end(); it++){
        cout << "(" << it->first << ", " << it->second << ") ";
    }
    cout << endl;

    return 0;
}
