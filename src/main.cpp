#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map> // better than map as faster lookup

using namespace std;
class node{
    public:
    int freq;
    char ch;
    node *left,*right;

    node(char character, int frequency){
        ch = character;
        freq = frequency;
        left = nullptr; 
        right = nullptr;
    }
};

class compare{
    public:
    bool operator()(node* a, node* b){
        return a->freq > b->freq;
    }
};

class huffmanTree{
    public:
    node* tree_contruct(priority_queue<node*, vector<node*>, compare> &minheap){
        while (minheap.size() > 1)
        {
            node* a = minheap.top(); minheap.pop();
            node* b = minheap.top(); minheap.pop();
            int combined_freq = a->freq + b->freq;
            node *internal = new node('\0',combined_freq);
            internal->left = a;
            internal->right = b;
            minheap.push(internal);
        }
        return minheap.top();
    }
};

int main(){
    priority_queue<node*, vector<node*>, compare> minheap;
    string inpstr;
    unordered_map<char, int> freqmap;

    cout<<"Enter String"<<endl;
    getline(cin, inpstr);

    for (char inpc: inpstr) {
        freqmap[inpc]++;
    }
    for (auto pair: freqmap) {
        minheap.push(new node(pair.first,pair.second));
    }


    // -------Printing Heap-----------
    // while(minheap.size() > 0) {
    //    node* top = minheap.top();
    //    cout << top->ch << " " << top->freq << endl;
    //    minheap.pop();
    // }
    
    // -------Manual Populate---------
    // minheap.push(new node('b', 2));
    // minheap.push(new node('s', 2));
    // minheap.push(new node('c', 2));
    // minheap.push(new node('a',3));

    huffmanTree mytree;

    node* k = mytree.tree_contruct(minheap);

    cout << "---------Root--------"<< endl;
    cout << "Value: " << k->ch << " ; Frequency: " << k->freq << endl;
    cout << "---------Root left child--------"<< endl;
    node* c = k->left;
    cout << "Value: " << c->ch << " ; Frequency: " << c->freq << endl;
    return 0;
}