#include <iostream>
#include <vector>
#include "AVL.h"
using namespace std;

//default constructor
Node::Node() {
    name = " ";
    ufID = " ";
    left = nullptr;
    right = nullptr;
    height = 1; //used only for balancing
}
//destructor
AVLTree::~AVLTree(){

}
//constructor
Node::Node(std::string studentName, std::string studentID) {
    this->name = studentName;
    this->ufID = studentID;
    this->left = nullptr;
    this->right = nullptr;
    this->height = 1;
}
//validations
bool AVLTree::LetterCheck(std::string input) {
    bool letterCheck = true;
    //checks if there is a letter inside the input
    for (int i = 0; i < input.length(); i ++) {
        letterCheck = isalpha(input[i]);
        if (input[i] == ' '){
            letterCheck = true;
        }
        if (!letterCheck) {
            break;
        }
    }
    return letterCheck;
}
bool AVLTree::NumberCheck(std::string input) {
    bool numberCheck = true;
    //checks if there is a number inside the input
    for (int i = 0; i < input.length(); i ++) {
        numberCheck = isdigit(input[i]);
        if (!numberCheck) {
            break;
        }
    }
    return numberCheck;
}

bool AVLTree::CheckID(std::string ufID) {
    int ufIDlength = ufID.length();
    //return false if it is not 8 int size
    //technically dont need this

    if (ufIDlength != 8) {
        return false;
    }
    else {
        return true;
    }
}
//calculate height for balancing
void AVLTree::CalcHeight(Node *root) {
    int heightCount = 1;
    int heightCountLeft = 1;
    int heightCountRight = 1;

    //takes in height of subtrees and uses the max one to determine what size to assign
    if(root->right != nullptr) {
        heightCountLeft = root->right->height;
        heightCountLeft++;
    }
    if (root->left != nullptr) {
        heightCountRight = root->left->height;
        heightCountRight++;
    }
    if (heightCountLeft > heightCountRight) {
        heightCount = heightCountLeft;
    }
    else if (heightCountLeft < heightCountRight) {
        heightCount = heightCountRight;
    }
    else {
        heightCount = heightCountRight;
    }

    root->height = heightCount;

}
int AVLTree::CalcLevelCount(Node* root, int count) {
    //recursively search adn compare the hegiht
    //onyl do this when function is called, otherwise we dont care

    if (root == nullptr){
        return count;
    }
    if (root->left != nullptr) {
        if (root->left->height > count) {
            count = root->left->height;
        }
        int newCalc = CalcLevelCount(root->left, count);
    }
    if (root->right != nullptr) {
        if (root->right->height > count) {
            count = root->right->height;
        }
        int newCalc = CalcLevelCount(root->right, count);
    }
    return count;

}

//search for repeated id
bool AVLTree::RepeatID(Node *root, std::string target) {
    //no while loop this time

    if (root == nullptr) {
        //return false if there are no repeats
        return false;
    }
    int rootInt = stoi(root->ufID);
    int targetInt = stoi(target);

    if (rootInt == targetInt) {
        return true;
    }
    else if (rootInt > targetInt) {
        //lesser
        bool tempRepeat = RepeatID(root->left, target);
        return tempRepeat;
    }
    else if (rootInt < targetInt) {
        //greater
        bool tempRepeat = RepeatID(root->right, target);
        return tempRepeat;
    }
    return false;

}
//search for name
bool AVLTree::NameSearchHelper(Node *root, std::string targetName, bool found) {
    //find name
    //print id if found
    //if found multiple times, print each idea on a new line w no otehr spaces in same order as preorder traversal
    //no exist, unsuccessful
    bool find = found;
    if(root == nullptr)
        return find;

    if (root->name == targetName) {
        //will account for multiple cases
        cout << root->ufID << endl;
        find = true;
        if (root->left != nullptr) {
            find = NameSearchHelper(root->left, targetName, find);
        }
        if (root->right != nullptr) {
            find = NameSearchHelper(root->right, targetName, find);
        }
    }
    else {
        if (root->left != nullptr) {
            find = NameSearchHelper(root->left, targetName, find);
        }
        if (root->right != nullptr) {
            find = NameSearchHelper(root->right, targetName, find);
        }
    }

    return find;
}

Node* AVLTree::LeftRotate(Node *root) {
    // like doing a switch a to b and b to a
    // make sure to reorganize the pointers
    //executed in a right-right case

    Node* newRoot = root->right;
    Node* child = newRoot->left;
    newRoot->left = root;
    root->right = child;


    //after rotation, heights are wrong, so fix here
    CalcHeight(root);
    CalcHeight(newRoot);

    return newRoot;
}
Node* AVLTree::RightRotate(Node *root) {
    //same as left but reversed

    Node* newRoot = root->left;
    Node* child = newRoot->right;
    newRoot->right = root;
    root->left = child;

    //after rotation, heights are wrong, so fix here
    CalcHeight(root);
    CalcHeight(newRoot);

    return newRoot;
}
Node* AVLTree::LeftRightRotate(Node *root) {
    //aa??
    root->left = LeftRotate(root->left);
    return RightRotate(root);
}
Node* AVLTree::RightLeftRotate(Node *root) {

    root->right = RightRotate(root->right);
    return LeftRotate(root);

}
//insertion
Node* AVLTree::InsertHelper(Node* root, string keyName, string keyID) {

    //empty tree
    if (root == nullptr) {
        std::cout << "successful" << endl;
        return new Node(keyName, keyID);
    }

    //creates into ints to compare and parse
    int intKeyID = stoi(keyID);
    int intID = stoi(root->ufID);

    if (intKeyID < intID ) {
        //lesser
        root->left = InsertHelper(root->left, keyName, keyID);
    }
    else if (intKeyID > intID){
        //greater
        root->right = InsertHelper(root->right, keyName,keyID);
    }
    //recalc height of root
    CalcHeight(root);

    //now to balance

    int rightHeight = 0;
    int leftHeight = 0;
    if(root->right != nullptr) {
        rightHeight = root->right->height;
    }

    if (root->left != nullptr) {
        leftHeight = root->left->height;
    }

    //balance factor calc here for balancing
    int balanceFactor = leftHeight - rightHeight;

    if (balanceFactor > 1) {
        //left-left case
        if (intKeyID < stoi(root->left->ufID)) {
            return RightRotate(root);
        }
        else{
            //left-right case
            return LeftRightRotate(root);
        }
    }
    else if (balanceFactor < -1) {
        if (intKeyID > stoi(root->right->ufID)) {
            //right-right rotato
            return LeftRotate(root);
        }
        else {
            //right-left case
            return RightLeftRotate(root);
        }
    }

    return root;
}
//traversals
void AVLTree::InorderHelper(Node* root, vector<string>& nodeStore) {
    if (root == nullptr)
        return;
    else {
        //LNR
        //should print ordered version
        AVLTree::InorderHelper(root->left, nodeStore);
        nodeStore.push_back(root->name);
        AVLTree::InorderHelper(root->right,nodeStore);
    }

}
void AVLTree::PreorderHelper(Node* root, vector<string>& nodeStore) {
    if (root == nullptr)
        return;
    else {
        //NLR
        nodeStore.push_back(root->name);
        AVLTree::PreorderHelper(root->left, nodeStore);
        AVLTree::PreorderHelper(root->right, nodeStore);

    }

}
void AVLTree::PostorderHelper(Node* root, vector<string>& nodeStore) {
    if (root == nullptr)
        return;
    else {
        //LRN
        AVLTree::PostorderHelper(root->left, nodeStore);
        AVLTree::PostorderHelper(root->right, nodeStore);
        nodeStore.push_back(root->name);
    }

}
//search for specific id
string AVLTree::IdSearchHelper(Node *root, std::string targetId) {
    // same as searching if id exists
    string result;

    if (root == nullptr) {
        result = "NULL";
        cout << "unsuccessful" << endl;
        return result;
    }
    else if (root->ufID == targetId) {
        result = root->name;
        cout << root->name << endl;
        return result;
    }
    //convert to int for parsing
    int intTargetId = stoi(targetId);
    int intRootId = stoi(root->ufID);

    if (intRootId > intTargetId) {
        //lesser
        string found = IdSearchHelper(root->left, targetId);

    }
    else if (intRootId < intTargetId) {
        //greater
        string found = IdSearchHelper(root->right, targetId);

    }
    return result;
}
Node* AVLTree::FindMinNode(Node *root, string rootID, string rootName) {
    //better than recursive iteration
    // only need one path anyways
    //used for 2 children case in deletion

    while(root->left != nullptr){
        root = root->left;
    }
    string inorderNodeID = root->ufID;
    string inorderNodeName = root->name;

    Node* inorderNode = new Node;
    inorderNode->ufID = inorderNodeID;
    inorderNode->name = inorderNodeName;

    root->ufID = rootID;
    root->name = rootName;

    return inorderNode;

}
void AVLTree::SwapInorder(Node *root, string rootID, string rootName) {
    //root is what is used to traverse
    while(root->left != nullptr){
        root = root->left;
    }
    root->ufID = rootID;
    root->name = rootName;

}
//deletion! main deletion
void AVLTree::RemoveIDHelper(Node *root, std::string targetID, Node* parent, bool isRight) {
    //gonna need three cases for this; no child, one child, two children

    // remember to update heights and balance at end
    //empty tree
    if (root == nullptr) {
        std::cout << "unsuccessful" << endl;
        return;
    }

    //convert to int for parsing
    int intTargetID = stoi(targetID);
    int rootID = stoi(root->ufID);

    if (intTargetID > rootID) {
        //greater
        RemoveIDHelper(root->right,targetID,root, true);
    }
    else if (intTargetID < rootID) {
        //lesser
        RemoveIDHelper(root->left, targetID, root, false);
    }
    else if (intTargetID == rootID) {
        // now deal with three cases:
        // 1. no children
        // 2. one child (left or right)
        // 3. two children

        // since checking for at least one null node first, can combine
        // case 1 and 2
        if (root->right == nullptr || root->left == nullptr) {
            //simplifies code instead of creating a whole left and right case for all 4

            //determine which has the child, if any
            Node* tempNode = nullptr;
            if (root->left != nullptr){
                tempNode = root->left;
            }
            else if (root->right != nullptr){
                tempNode = root->right;
            }

            //1. case: no children: easiest <3
            if (tempNode == nullptr) {
                //set temp node to root and then delete root
                //need parent to reassign its pointer

                if(parent != nullptr) {
                    if (isRight) {
                        parent->right = nullptr;

                    }
                    else{
                        parent->left = nullptr;
                    }
                }

                delete root;
                cout << "successful" << endl;

            }
            //2. one child
            else {
                //2. case: on child, on left or right
                //create temp pointer pointing at old item (to be deleted)
                //reassign root to tempNode/new child
                //delete using temp pointer that was pointin at old node
                //tempnode is what new thing will be

                Node* deletedNode = root; //is this needed?
                //*root = *tempNode;

                //need parent to reassign its pointer
                if(parent != nullptr) {
                    if (isRight) {
                        parent->right = tempNode;

                    }
                    else{
                        parent->left = tempNode;
                    }
                }

                delete deletedNode;
                cout << "successful" << endl;

            }
        }
        // 3. HELL CASE; 2 children
        else if (root->right != nullptr && root->left != nullptr) {
            string tempID = root->ufID;
            string tempName = root->name;

            Node* inorderNode = FindMinNode(root->right, tempID, tempName);//inorder successor
            //swapping the data in the inorder successor and the node to be deleted


            //SwapInorder(root, tempID, tempName);

            root->ufID = inorderNode->ufID;
            root->name = inorderNode->name;

            // recursively call but w identical id now, so it deletes easier
            RemoveIDHelper(root->right, tempID, root, true);

        }
    }

}
void AVLTree::InorderRemovalTraversal(Node *root, vector<string>& ufIDStore) {
  // call inorder traversal to get vector of all elements
    // if else to check if size is greater than the n value; if less than, it does not exist, so throw unsuccessful
    // taking into account starting at 0, go to element at n value
    // pass that into the removal function

    if (root == nullptr)
        return;
    else {
        InorderRemovalTraversal(root->left, ufIDStore);
        ufIDStore.push_back(root->ufID);
        InorderRemovalTraversal(root->right,ufIDStore);
    }

}
