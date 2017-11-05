#include <iostream>
#include "CTree.h"

int main() {

    using namespace std;



    CTree a,b;

    string s = "+*12a";

    a.createTree(s);

    cout << "Drzewo pierwsze" << endl;

    a.printAsTree();

    cout << endl;

    string s1 = "*34";

    b.createTree(s1);

    cout << "Drzewo drugie" << endl;

    b.printAsTree();

    cout << endl;

    CTree c;

//    cout << "Drzewo trzecie b+a" << endl;
//
//    c = b + a;
//
//    c.printAsTree();

    cout << "DRzewo czwarte" << endl;

    c = a + b;

    c.printAsTree();


}