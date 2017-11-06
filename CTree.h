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

class CTree {


    friend class CNode;

public:
    int nodes();
    void printAsTree();
    CTree();
    void createTree(string &expr);
    void printInOrder();
    string getStringInNormalNotation();
    void printPostOrder();
    CTree & operator=(CTree &t);
    CTree& operator+(CTree &tree);
    double computeTree();
    void printVariables(set<string> setOfVariables);
    set<string> getVariables();
private:
    CNode *root;
    void printBinaryTree(CNode *node, int level);
    int nodes(CNode *node);
    bool isOperator(string valueToCheck);
    void createTree(CNode *&actualNode, CNode *&parentNode, string &expr);
    void printInOrder(CNode *node);
    void getStringInNormalNotation(CNode *node, string &outputString);
    bool isOperator(char valueToCheck);
    void printPostOrder(CNode *node);
    CNode *&findNodeToAttachedTree(CNode *&node);

    bool isOperatorSinOrCos(string operatorToCheck);


    void getVariables(CNode *node, set<string> &setOfVariables);

    //set<string> &*getVariables(CNode *node, set<string> *&setOfVariables);

    //set<string> &*getVariables(CNode *node, set<string> &*setOfVariables);
    //double comp(CNode *node, set<string> &setOfVariables);

    set<double> getValuesFromUser();

    bool isNumber(string valueToCheck);

    double comp(CNode *node, set<double> &setOfValueOfVariables);
};

#endif //LISTA3_CTREE_H
