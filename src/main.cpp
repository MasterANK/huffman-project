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
    void encode(node *root, string code, unordered_map<char, string> &huffman_code){
        if(root == nullptr){
            return ;
        } 
        if(root->left == nullptr && root->right == nullptr){
            huffman_code[root->ch] = code;
        }
        encode(root->left,code + "0", huffman_code);
        encode(root->right,code + "1", huffman_code);
    }
    string huffman_str(string message,unordered_map<char, string> &huffman_code){
        string encoded_str = "";
        for (char i: message){
            encoded_str += huffman_code[i];
        }
        return encoded_str;
    }
    string decode(string message, node *root){
        string decoded_message = "";
        node * temp = root;
        for(char i : message){
            if(i=='0'){
                temp = temp->left;
            } else if (i == '1') {
                temp = temp->right;
            }
            if(temp->left == nullptr && temp->right == nullptr){
                decoded_message += temp->ch;
                temp = root;
            }
        }
        return decoded_message;
    }
};

int main(){
    priority_queue<node*, vector<node*>, compare> minheap;
    string inpstr;
    unordered_map<char, int> freqmap;
    unordered_map<char, string> huffman_code;

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

    node* root = mytree.tree_contruct(minheap);

    mytree.encode(root, "", huffman_code);
    string encoded = mytree.huffman_str(inpstr, huffman_code);
    cout << "Final encode Str: " <<encoded << endl;

    string decoded = mytree.decode(encoded, root);
    cout << "Final decode Str: " <<decoded << endl;

    return 0;
}