//
// Created by Kajetan Dymkiewicz on 30.10.2017.
//

#ifndef LISTA3_CTREE_H
#define LISTA3_CTREE_H
#include "CNode.h"
#include <string>
#include <set>
    using namespace std;
#define PI 3.14159265
const int NUM_VAR_AND_NUM_OP_IS_CORRECT = 1;

class CTree {

    friend class CNode;

public:

    CTree();


    void createTree(string &expr);

    void printAsTree();
    void printInOrder();
    void printPostOrder();

    void printVariables(set<string> setOfVariables);
    set<string> getVariables();

    CTree & operator=(CTree &t);
    CTree& operator+(CTree &tree);

    double computeTree();

    int isExprCorrect(string expr);

private:
    CNode *root;

    void printBinaryTree(CNode *node, int level);
    void printInOrder(CNode *node);
    void printPostOrder(CNode *node);

    void createTree(CNode *&actualNode, CNode *&parentNode, string &expr);

    double comp(CNode *node, set<double> &setOfValueOfVariables);

    bool isOperator(string valueToCheck);
    bool isOperatorSinOrCos(string operatorToCheck);
    bool isOperatorButNotSinOrCos(char valueToCheck);
    bool isNumber(string valueToCheck);

    void getVariables(CNode *node, set<string> &setOfVariables);
    set<double> getValuesFromUser();

    void makeStringCorrect(string &expr);

    CNode *&findNodeToAttachedTree(CNode *&node);
};

#endif //LISTA3_CTREE_H
