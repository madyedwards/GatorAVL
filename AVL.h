#pragma once
#include <iostream>
using namespace std;

// deal with mem in private functions, public ones do not
struct Node {
    //made struct for demo
    string name;
    string ufID;
    int height; //for computation purposes
    Node* left;
    Node* right;
public:
    //default constructor
    Node();
    Node(string studentName, string studentID);


};
class AVLTree {
private:
    // need to have helper bc its recursive and to have structure
    Node* InsertHelper(Node* node, string name, string ufID);
    bool CheckID(string ufID);
    bool RepeatID(Node* root, string target);
    Node* LeftRotate(Node* root);
    Node* RightRotate(Node* root);
    Node* LeftRightRotate(Node* root);
    Node* RightLeftRotate(Node* root);
    string IdSearchHelper(Node* root, string targetId);
    bool NameSearchHelper(Node* root, string targetName, bool found);
    int CalcLevelCount(Node* root, int count);
    void InorderHelper(Node* root, vector<string>& nodeStore);
    void PreorderHelper(Node* root, vector<string>& nodeStore);
    void PostorderHelper(Node* root, vector<string>& nodeStore);
    void RemoveIDHelper(Node* root, string targetID, Node* parent, bool isRight);
    void InorderRemovalTraversal(Node* root, vector<string>& ufIDStore);
    Node* FindMinNode(Node* node, string rootID, string rootName);
    void SwapInorder(Node *inorder, string rootID, string rootName);

public:
    Node* root;

    //insertion
    void Insert(string name, string ufID) {
        bool idCheck = CheckID(ufID); //check if id is right size
        bool repeatID = RepeatID(this->root, ufID); //check if id is unique

        if (idCheck && !repeatID) {
            this->root = InsertHelper(this->root, name, ufID);

        }
        else if (!idCheck) {
            cout << "unsuccessful" << endl;
        }
        else if (repeatID) {
        cout << "unsuccessful" << endl;
        }

    }
    //traversals
    void Inorder() {
        vector<string> nodeStore;
        InorderHelper(root, nodeStore);
        for (int i =0; i < nodeStore.size()-1; i++){
            cout << nodeStore[i] << ", ";
        }
        cout << nodeStore.at(nodeStore.size()-1) << endl;

    }
    void Preorder(){
        vector<string> nodeStore;
        PreorderHelper(root, nodeStore);
        for (int i =0; i < nodeStore.size()-1; i++){
            cout << nodeStore[i] << ", ";
        }
        cout << nodeStore.at(nodeStore.size()-1) << endl;
    }
    void Postorder(){
        vector<string> nodeStore;
        PostorderHelper(root, nodeStore);
        for (int i =0; i < nodeStore.size()-1; i++){
            cout << nodeStore[i] << ", ";
        }
        cout << nodeStore.at(nodeStore.size()-1) << endl;
    }//
    //level count
    void PrintLevelCount(){
        //int height = CalcLevelCount(root, 0);
        if (root == nullptr)
            cout << "0" << endl;
        else {
            //height of the root will always be the number of levels?
            int height = root->height;
            cout << height << endl;
        }
    }
    //deletion
    void RemoveInorder (int target) {
        vector<string> ufIDStore;
        InorderRemovalTraversal(root, ufIDStore);
        if (ufIDStore.size()-1 < target) {
            cout << "unsuccessful" << endl;
        }
        else {
            RemoveID(ufIDStore.at(target));
        }//can maybe do this in one so as to prevent more recursion?
    }
    //used to balance
    void CalcHeight(Node* root);
    //search functions
    void IDSearch(string targetID){
        string found = IdSearchHelper(root, targetID);

    }
    void NameSearch(string targetName) {
        bool found = false;
        bool search = NameSearchHelper(root, targetName, found);
        if (!search)
            cout << "unsuccessful" << endl;
    }
    //another deletion
    void RemoveID(string targetID){
        RemoveIDHelper(root, targetID, nullptr,true);
    }
    //validation for string and id
    bool LetterCheck(string input);
    bool NumberCheck(string input);
    AVLTree() : root() {}
    //destructor
    ~AVLTree();

};

