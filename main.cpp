#include <iostream>
#include "CTree.h"

int main() {

    using namespace std;

    CTree a;

    string s = "+ + + 1 1 2 1 1 2324 a";

    a.createTree(s);

    cout << a.computeTree() << endl;

    a.printAsTree();


}