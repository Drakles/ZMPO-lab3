//
// Created by Kajetan Dymkiewicz on 07.11.2017.
//

#include "Interface.h"
#include <sstream>
#include "CTree.h"

bool isCommand(const string command, const char *mnemonic) {
    return command==mnemonic;
}


int main(){

    CTree a;
    string s = " * 3 4";

    a.createTree(s);

    cout << a.printAsTree()<<endl;

    CTree b;
    string s1 = " * 3 4";

    b.createTree(s1);

    cout << b.printAsTree()<<endl;

    b = a + b;

    cout << b.printAsTree() << endl;

}



int main1() {

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

        if(isCommand(command,EXIT)) {
            endOfProgram = true;
            wrongArgument = false;
        }

        if(isCommand(command,ENTER)) {
            wrongArgument = false;

            string exprFromUser;

            getline(cin,exprFromUser);

            string copyOfInput = exprFromUser;

            int result = tree.createTree(exprFromUser);

            if(result == CREATE_TREE_SUCCES){
                cout << CREATE_TREE_SUCCES_MESSAGE << endl;
            }else{
                cout << EXPRESSION << copyOfInput <<EXPR_WRONG << endl<<EXPR_REBUILD_MSG;
                cout << tree.printPostOrder() << endl;

            }
        }

        if(isCommand(command,VARS)) {
            wrongArgument = false;

            tree.printVariables(tree.getVariables());
        }

        if(isCommand(command,PRINT)) {
            wrongArgument = false;

            cout << tree.printInOrder() << endl;

        }

        if(isCommand(command,COMP)) {
            wrongArgument = false;

            set<double> values;

            set<string> setOfVariables = tree.getVariables();

            double numberFromUser;
            for (int i = 0; i < setOfVariables.size() ; ++i) {
                cin >> numberFromUser;
                values.insert(numberFromUser);
            }
            cout << tree.computeTree(values) << endl;
        }

        if(isCommand(command,JOIN)) {
            wrongArgument = false;

            string exprFromUser;

            getline(cin,exprFromUser);

            CTree newTree;

            int result = newTree.createTree(exprFromUser);

            if(result == CREATE_TREE_SUCCES){
                cout << CREATE_TREE_SUCCES_MESSAGE << endl;
            }else{
                cout << EXPR_WRONG << endl << EXPR_REBUILD_MSG << exprFromUser << endl;
            }
            tree = tree + newTree;
        }

        if(isCommand(command,PRINTASTREE)) {
            wrongArgument = false;
            cout << tree.printAsTree() << endl;
        }

        if(isCommand(command,PRINT_LEVELS)) {
            wrongArgument = false;
            cout << tree.printLevelOrder() << endl;
        }

        if(wrongArgument){
            cout << NIEROZPOZNANO << line << endl;
        }
    }



    return 0;
}