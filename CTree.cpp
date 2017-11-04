//
// Created by Kajetan Dymkiewicz on 30.10.2017.
//

#include <iostream>
#include <set>
#include "CTree.h"

void printPostOrder(CNode *pNode);

using namespace std;

 void CTree::printBinaryTree(CNode *node, int level) {
    if (node == nullptr) {
        return;
    }
    printBinaryTree(node->righChild, level + 1);
    if (level != 0) {
        for (int i = 0; i < level - 1; i++)
            std::cout << "|\t\t";
        std::cout << "|-------" << node->value << endl;
    } else
        std::cout << node->value << endl;
    printBinaryTree(node->leftChild, level + 1);
}

void CTree::printAsTree() {
    printBinaryTree(root, 0);
}

int CTree::nodes() {
    return this->nodes(this->root);
}

int CTree::nodes(CNode *node) {
    int numberOfNodes = 1;
    if (node->righChild != nullptr) numberOfNodes += nodes(node->righChild);
    if (node->leftChild != nullptr) numberOfNodes += nodes(node->leftChild);
    return numberOfNodes;
}

CTree::CTree(){
    root = nullptr;
}

void CTree::createTree(string &expr){
    if(root == nullptr) {
        this->root = new CNode(expr.substr(0, 1), root);
        expr = expr.substr(1, expr.length());
        createTree(root,root,expr);
    }else{
        createTree(root,root,expr);
    }
}


void CTree::createTree(CNode *&actualNode,CNode *&parentNode,string &expr){

    if(expr.length() > 0) {
        if (actualNode == nullptr) {
            actualNode = new CNode(expr.substr(0, 1), parentNode);
            expr = expr.substr(1, expr.length());
        }
        if (isOperator(actualNode->value)) { // if value is operator then it should has two children
            if (actualNode->leftChild == nullptr) {
                createTree(actualNode->leftChild,actualNode, expr);
            }
            if (actualNode->righChild == nullptr) {
                createTree(actualNode->righChild,actualNode, expr);
            }
        } else {
            createTree(actualNode->parent,parentNode->parent, expr);
        }
    }
}



void CTree::printInOrder(CNode *node){
    if(node->leftChild != nullptr){
        //cout << "(";
        printInOrder(node->leftChild);
    }
    cout <<node->value;
    if(node->righChild != nullptr){
        printInOrder(node->righChild);
        //cout << ")";
    }
}

void CTree::printInOrder(){
    printInOrder(root);
}

void CTree::getStringInNormalNotation(CNode *node, string &outputString){
    if(node->leftChild != nullptr) getStringInNormalNotation(node->leftChild,outputString);
    outputString.append(node->value);
    if(node->righChild != nullptr) getStringInNormalNotation(node->righChild,outputString);
}

string CTree::getStringInNormalNotation(){
    string output = "";
    getStringInNormalNotation(root,output);
    return output;
}

std::set<char> CTree::getVariables(){

    string expr = getStringInNormalNotation();

    set<char> setOfVariables;

    for (int i = 0; i < expr.length() ; ++i) {
        if(!isOpetator(expr[i]) && setOfVariables.count(expr[i])==0){
            setOfVariables.insert(expr[i]);
        }
    }
    return setOfVariables;
}

void CTree::printVariables(){

    set<char> setOfVariables = getVariables();

    set<char>::iterator it;

    for (it = setOfVariables.begin(); it!=setOfVariables.end() ; it++) {
        cout << *it << ",";
    }

    cout << endl;

}


void CTree::printPostOrder(){
    printPostOrder(root);
}

void CTree::printPostOrder(CNode *node) {
    cout << node->value;

    if(node->leftChild != nullptr) printPostOrder(node->leftChild);
    if(node->righChild != nullptr) printPostOrder(node->righChild);
}







bool CTree::isOperator(string valueToCheck){
    return (valueToCheck == "*" || valueToCheck == "/" || valueToCheck == "+" || valueToCheck == "-");
}

bool CTree::isOpetator(char valueToCheck){
    return (valueToCheck =='*' || valueToCheck == '/' || valueToCheck == '+' || valueToCheck == '-');
}