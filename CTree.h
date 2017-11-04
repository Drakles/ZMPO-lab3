//
// Created by Kajetan Dymkiewicz on 30.10.2017.
//

#ifndef LISTA3_CTREE_H
#define LISTA3_CTREE_H
#include "CNode.h"
#include <string>
#include <set>
    using namespace std;

class CTree {


    friend class CNode;

public:
    int nodes();
    void printAsTree();
    CTree();
    CNode *root;
    void createTree(string &expr);
    void printInOrder();
    string getStringInNormalNotation();
    void printVariables();
    void printPostOrder();
private:
    void printBinaryTree(CNode *node, int level);
    int nodes(CNode *node);
    bool isOperator(string valueToCheck);
    void createTree(CNode *&actualNode, CNode *&parentNode, string &expr);
    void printInOrder(CNode *node);
    void getStringInNormalNotation(CNode *node, string &outputString);
    bool isOpetator(char valueToCheck);

    std::set<char> getVariables();

    void printPostOrder(CNode *node);
};


#endif //LISTA3_CTREE_H
