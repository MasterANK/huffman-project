#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <unordered_map> // better than map as faster lookup

#define Hufffile "hufftree.huff"

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
        while (minheap.size() > 1) {
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
    void printtree(node *root, string output = "", bool isleft = false){
        if(root != nullptr){
            cout << output;
            cout << (isleft? "├──" : "└──");
            if(root->ch){
                cout << root->ch << ": (" <<root->freq << ")" << endl;
            }else {
                cout << '(' << root->freq << ")" << endl;
            }
            printtree(root -> left, output + (isleft ? "│   " : "    "), true);
            printtree(root -> right, output + (isleft ? "│   " : "    "), false);
        }
    }
    void storetree(node *root, ofstream &outfile){
        if(!root){
            return;
        }
        if(!root->left && !root->right){
            // ` = I ; \ = L
            if (root->ch == '`' || root->ch == '\\'){ 
                outfile << '\\' << root->ch;
            } else{
                outfile << root->ch;
            }
        } else{
            outfile << '`';
        }
        storetree(root->left, outfile); //Storing Left Subtree first
        storetree(root->right, outfile);
    }
    node *loadtree(ifstream &infile){
        char ch;
        infile.get(ch);
        if(ch != '`' && ch != '\\'){
            return new node(ch,0);
        } else if(ch == '\\'){
            infile.get(ch);
            return new node(ch,0);
        }
        node* newnode = new node('\0',0);
        newnode->left = loadtree(infile); //loading Left Subtree since its first
        newnode->right = loadtree(infile);
        return newnode;
    }
};

string readfile(string &filename){
    ifstream inFile(filename);
    if(!inFile){
        cerr << "Error Opening File: " << filename << endl;
        exit(1);
    }
    string text,line;
    while(getline(inFile, line)){
        text += line;
    }
    inFile.close();
    return text;
}

void writefile(string data, string &filename){
    ofstream outfile(filename);
    if(!outfile){
        cerr << "Error Writing Encoding to File: " << filename << endl;
        exit(1);
    }
    outfile << data;
    outfile.close();
}

void writeencoded(string &encoded,string &filename){
    ofstream outfile("Compressed_"+filename, ios::binary);
    if(!outfile){
        cerr << "Error Writing Encoding to File: " << filename << endl;
        exit(1);
    }
    outfile << encoded;
    outfile.close();
}

string readencoded(string &filename){
    ifstream infile(filename, ios::binary);
    if(!infile){
        cerr << "Error Writing Encoding to File: " << filename << endl;
        exit(1);
    }
    string encoded;
    infile >> encoded;
    infile.close();
    return encoded;
}

int main(){
    priority_queue<node*, vector<node*>, compare> minheap;
    string inpstr, filename, hufffile;
    unordered_map<char, int> freqmap;
    unordered_map<char, string> huffman_code;

    huffmanTree mytree;

    int choice; char debug_choice;
    cout << "-----Menu-----" << endl;
    cout << "1) Compress File" << endl;
    cout << "2) Decompress File" << endl;
    cout << "Enter Choice: "; cin >> choice;
    switch (choice) {
    case 1: {
        cout << "Enter File Name / File Path: ";
        cin >> filename;

        inpstr = readfile(filename);
        for (char inpc: inpstr) {
            freqmap[inpc]++;
        }
        for (auto pair: freqmap) {
            minheap.push(new node(pair.first,pair.second));
        }

        node* root = mytree.tree_contruct(minheap);

        mytree.encode(root, "", huffman_code);
        string encoded = mytree.huffman_str(inpstr, huffman_code);
        
        // Storing to File
        ofstream outfile(Hufffile);
        if(!outfile){
            cerr << "Error Writing .huff File: " << Hufffile << endl;
            exit(1);
        }
        mytree.storetree(root,outfile); // Storing TREE
        outfile.close();
        writeencoded(encoded,filename); // Storing Data

        cout << "======Successfully Compressed File========" << endl;
        cout << "Would You Like to print the Huffman Tree? (y/n): ";
        cin >> debug_choice;
        if(debug_choice == 'Y' || debug_choice == 'y'){
            mytree.printtree(root);
        } else{
            cout << endl << "Exiting Program";
        }
        break;
    }
    case 2: {
        cout << "Enter Compressed File Name / Path: ";
        cin >> filename;
        string encoded = readencoded(filename);

        cout << "Enter .huff File Name / Path: ";
        cin >> hufffile;
        ifstream infile(Hufffile);
        if(!infile){
            cerr << "Error Writing .huff File: " << Hufffile << endl;
            exit(1);
        }
        node *root = mytree.loadtree(infile); // Loading TREE
        infile.close();

        string decoded = mytree.decode(encoded, root);
        cout << "Enter New Name for the data file: ";
        cin >> filename;
        writefile(decoded, filename);
        cout << "======Successfully Decompressed File========" << endl;
        cout << "Would You Like to print the Huffman Tree? (y/n): ";
        cin >> debug_choice;
        if(debug_choice == 'Y' || debug_choice == 'y'){
            mytree.printtree(root);
        } else{
            cout << endl << "Exiting Program";
        }
        break;
    }
    default:
        cout << "Invalid Output. \n Self Destructing....." << endl;
        break;
    }


    // string decoded = mytree.decode(encoded, root);
    // cout << "Final decode Str: " <<decoded << endl;


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
    return 0;
}