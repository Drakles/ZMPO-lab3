#include <iostream>
#include "CTree.h"

int main() {

    using namespace std;



    CTree a,b;

    string s = "+*22cos0";

    a.createTree(s);

    cout << "Drzewo pierwsze" << endl;

    a.printAsTree();

    a.printPostOrder();
    cout << endl;

    a.printInOrder();



}