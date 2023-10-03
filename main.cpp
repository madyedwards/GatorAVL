#include <iostream>
#include <regex>
#include "AVL.h"
using namespace std;

int main() {
    //read in the number of lines, this dictates how long the program will run
    int numLines;
    std::string line, command;
    std::getline(std::cin, line);
    numLines = stoi(line);
    //create the tree
    AVLTree tree;


    //program running
    while (numLines--) {
        //command tells the program what action to perform
        std::getline(std::cin, command);
        //makes command a stream obj and breaks it into action (ex. search, traversals, etc.)
        istringstream in(command);
        string action;
        in >> action;

        if (action == "insert") {
            //remmeber to check if there are integers in name and letters in ufid
            //getting the name
            string name, ID;
            in >> name;

            //checks if there are quotation marks to allow whitespace chars
            while (name.at(name.length()-1) != '\"') {
                string lastName;
                in >> lastName;
                name = name + " " + lastName;

            }
            name = name.substr(1, name.length()-2);


            //checks if the name has only letters and no numbers
            bool letterCheck = tree.LetterCheck(name);

            //getting id
            in >> ID;
            //checks if id consists of only numbers and no letters
            bool numberCheck = tree.NumberCheck(ID);


            //both work, now perform action
            if (numberCheck && letterCheck)
                tree.Insert(name, ID);
            else
                cout << "unsuccessful" << endl;

        }
        else if (action == "remove") {
            //id of node to remove
            string ID;
            in >> ID;

            //check if id is valid
            bool numberCheck = tree.NumberCheck(ID);

            if (numberCheck)
                tree.RemoveID(ID);
            else
                cout << "unsuccessful" << endl;


        }
        else if(action == "search") {
            string input;
            in >> input;

            if (input.at(0) == '\"') {
                //its a name
                // have to remove the quotations then
                if (input.at(input.length()-1) != '\"') {
                    string lastName;
                    in >> lastName;
                    input = input + " " + lastName;

                }
                input = input.substr(1, input.length()-2);

                //check valid name
                bool check = tree.LetterCheck(input);

                if (check)
                    tree.NameSearch(input);
                else
                    cout << "unsuccessful" << endl;

            }
            else{

                //check valid id
                bool check = tree.NumberCheck(input);

                if (check)
                    tree.IDSearch(input);
                else
                    cout << "unsuccessful" << endl;
            }

        }
        else if(action == "printInorder"){
            tree.Inorder();
        }
        else if(action == "printPreorder") {
            tree.Preorder();
        }
        else if(action == "printPostorder") {
            tree.Postorder();
        }
        else if (action == "printLevelCount") {
            tree.PrintLevelCount();
        }
        else if (action == "removeInorder") {
            // input is the nth node to remove when printed in order
            string input;
            in >> input;
            int level = stoi(input);

            tree.RemoveInorder(level);
        }
        else if (action == "printLevelCount") {
            tree.PrintLevelCount();
        }
        else{
            cout << "unsuccessful" << endl;
        }

    }

}
