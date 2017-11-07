//
// Created by Kajetan Dymkiewicz on 07.11.2017.
//

#include "Interface.h"
#include <sstream>
#include "CTree.h"

bool isCommand(const string command, const char *mnemonic) {
    return command==mnemonic;
}

int main() {

    CTree tree;

    bool endOfProgram = false;

    while(!endOfProgram)
    {
        string line;
        string command;
        bool wrongArgument = true;

        cout << "podaj polecenie ";

        getline(cin,line);
        std::stringstream stream(line);
        stream >> command;

        // copy line on output with exclamation mark
        //cout << "!" << line << endl;;
        //cout << "command " << command << endl;

        if(isCommand(command,EXIT)) {
            endOfProgram = true;
            wrongArgument = false;
        }

        if(isCommand(command,ENTER)) {
            wrongArgument = false;

            string exprFromUser;

            cin >> exprFromUser;

            int result = tree.createTree(exprFromUser);

            if(result == CREATE_TREE_SUCCES){
                cout << CREATE_TREE_SUCCES_MESSAGE << endl;
            }else{
                cout << EXPR_WRONG << endl << EXPR_REBUILD_MSG << exprFromUser << endl;
            }
        }

        if(isCommand(command,VARS)) {
            wrongArgument = false;

            tree.printVariables(tree.getVariables());

        }

        if(isCommand(command,PRINT)) {
            wrongArgument = false;

            tree.printInOrder();

        }

        if(isCommand(command,COMP)) {
            wrongArgument = false;

            // TO DO

        }

        if(isCommand(command,JOIN)) {
            wrongArgument = false;

            // TO DO

        }

        if(wrongArgument){
            cout << NIEROZPOZNANO << line << endl;
        }
    }



    return 0;
}