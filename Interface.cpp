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
    string s = " * 3 4 ";
    int result = a.createTree(s);
    cout << result<<endl;
    cout << a.printAsTree()<<endl;

    string s1 = "+ 1 2";
    CTree b;
    int result1 = b.createTree(s1);
    cout <<result1<<endl;
    cout << b.printAsTree()<<endl;
    b=a;

    cout << b.printAsTree() << endl;
    cout << "jestem przed b = a+b"<<endl;
    b = a+b;
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

        if(wrongArgument){
            cout << NIEROZPOZNANO << line << endl;
        }
    }



    return 0;
}