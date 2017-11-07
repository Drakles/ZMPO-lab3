#include <iostream>
#include "CTree.h"

int main() {

    using namespace std;

    CTree a;

    string s = "+ + ";

    a.createTree(s);

    cout << a.computeTree() << endl;

    a.printAsTree();


}