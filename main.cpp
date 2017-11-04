#include <iostream>
#include "CTree.h"

int main() {

    using namespace std;

//    CTree c;
//
//    string expr = "+*12a";
//
//    c.createTree(expr);
//
//    c.printAsTree();
//
//
//    c.printInOrder();
//
//    cout << endl;
//
//    cout <<  c.getStringInNormalNotation() << endl;
//
//    c.printVariables();
//
//    c.printPostOrder();


    CTree a,b;

    string s = "+*12a";

    a.createTree(s);

    cout << "Drzewo pierwsze" << endl;

    a.printAsTree();

    cout << endl;

    string s1 = "+11";

    b.createTree(s1);

    cout << "Drzewo drugie" << endl;

    b.printAsTree();

    cout << endl;

    CTree c;

    c = b;

    cout << "Drzewo trzecie" << endl;

    c = c + a;

    c.printAsTree();


}