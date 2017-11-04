#include <iostream>
#include "CTree.h"

int main() {

    using namespace std;

    CTree c;

    string expr = "+*12a";

    c.createTree(expr);

    c.printAsTree();


    c.printInOrder();

    cout << endl;

    cout <<  c.getStringInNormalNotation() << endl;

    c.printVariables();

    c.printPostOrder();

}