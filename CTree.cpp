//
// Created by Kajetan Dymkiewicz on 30.10.2017.
//

#include <iostream>
#include <set>
#include "CTree.h"
#include <math.h>
#include <cctype>


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
        while(expr[0] == ' '){
            expr = expr.substr(1, expr.length());
        }

    expr = expr.append(" ");

    if(isOperator(expr[0]) || isOperatorSinOrCos(expr.substr(0,3))) {

        if (expr.substr(0, 3) == "sin" || expr.substr(0, 3) == "cos") {
            this->root = new CNode(expr.substr(0, 3), root);
            expr = expr.substr(3, expr.length());
            createTree(root, root, expr);
        } else {

            this->root = new CNode(expr.substr(0, 1), root);
            expr = expr.substr(1, expr.length());
            createTree(root, root, expr);
        }
    }else{
        this->root = new CNode(expr,root);
    }
}

void CTree::createTree(CNode *&actualNode,CNode *&parentNode,string &expr){

    if(expr.length() > 0) {
        if (actualNode == nullptr) {

            while(expr[0] == ' '){
                expr = expr.substr(1, expr.length());
            }

            if(expr.substr(0,3) == "sin" || expr.substr(0,3) == "cos" ){
                actualNode = new CNode(expr.substr(0, 3), parentNode);
                expr = expr.substr(3, expr.length());
            }else {

                string clearValue ="";

                clearValue.append(expr.substr(0,1));

                expr = expr.substr(1, expr.length());

                while (!isspace(expr.at(0)) && expr.length() > 0) {
                    clearValue.append(expr.substr(0, 1));
                    expr = expr.substr(1, expr.length());
                }

                actualNode = new CNode(clearValue, parentNode);
            }
        }
        if (isOperator(actualNode->value)) {


            if(isOperatorSinOrCos(actualNode->value)){ // if value is sin or cos
                if(actualNode->leftChild == nullptr) createTree(actualNode->leftChild,actualNode,expr);
            }else {

                // if value is operator but not cos or sin then it should has two children
                if (actualNode->leftChild == nullptr) {
                    createTree(actualNode->leftChild, actualNode, expr);
                }
                if (actualNode->righChild == nullptr) {
                    createTree(actualNode->righChild, actualNode, expr);
                }
            }
        } else {
            createTree(actualNode->parent,parentNode->parent, expr);
        }
    }
}

CNode*& CTree::findNodeToAttachedTree(CNode *&node){
    if(node->leftChild != nullptr) findNodeToAttachedTree(node->leftChild);
    else{
        return node;
    }
}



CTree& CTree::operator+(CTree &otherTree){

    CTree ct;

    ct.root = this->root;

    //ct.findNodeToAttachedTree(ct.root)->value="1234";

    CNode * p;
    p = ct.root;

    while (p->leftChild->leftChild != nullptr){
        p = p->leftChild;
    }

    p->leftChild = otherTree.root;

    return ct;
}

CTree & CTree::operator=(CTree &t){
    root = t.root;
    return *this;
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

void CTree::getVariables(CNode *node, set<string> &setOfVariables){

    set<string>::iterator it;

    if(node->leftChild != nullptr){
        getVariables(node->leftChild,setOfVariables);
    }

    if(!isOperator(node->value) && !isNumber(node->value)){
        setOfVariables.insert(node->value);
    }
    if(node->righChild != nullptr){
        getVariables(node->righChild,setOfVariables);
    }
}

set<string> CTree::getVariables(){
    set<string> setOfVariables;

    getVariables(root,setOfVariables);

    return setOfVariables;
}

void CTree::printInOrder(CNode *node){
    if(node->leftChild != nullptr){
        printInOrder(node->leftChild);
    }
    cout <<node->value;
    if(node->righChild != nullptr){
        printInOrder(node->righChild);
    }
}

void CTree::printInOrder(){
    printInOrder(root);
}
void CTree::printVariables(set<string> setOfVariables){

    set<string>::iterator it;

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


double CTree::comp(CNode *node,set<double> &setOfValueOfVariables){
    if(node != nullptr) {
        if (isOperator(node->value)) {

            switch(node->value.at(0)){
                case '*':
                    return comp(node->leftChild,setOfValueOfVariables) * comp(node->righChild,setOfValueOfVariables);
                case '/':
                    return comp(node->leftChild,setOfValueOfVariables) / comp(node->righChild,setOfValueOfVariables);
                case '+':
                    return comp(node->leftChild,setOfValueOfVariables) + comp(node->righChild,setOfValueOfVariables);
                case '-':
                    return comp(node->leftChild,setOfValueOfVariables) - comp(node->righChild,setOfValueOfVariables);
                case 's':
                    return sin((comp(node->leftChild,setOfValueOfVariables)*PI)/180);
                case 'c':
                    return cos((comp(node->leftChild,setOfValueOfVariables)*PI)/180);
            }
        }else{
            if(isNumber(node->value))return stoi(node->value);
            else{
                set<double>::iterator it= setOfValueOfVariables.begin();
                setOfValueOfVariables.erase(it);
                return *it;
            }
        }
    }
}

double CTree::computeTree(){
    set<double> setOfValueOfVariables = getValuesFromUser();
    return comp(root,setOfValueOfVariables);
}

bool CTree::isNumber(string valueToCheck){
    bool isNumber = true;

    for (int i = 0; i < valueToCheck.length(); ++i) {
        if(!isdigit(valueToCheck[0])) isNumber = false;
    }
    return isNumber;
}

set<double> CTree::getValuesFromUser(){
    set<double> values;

    set<string> setOfVariables = getVariables();

    for (int i = 0; i < setOfVariables.size() ; ++i) {
        double numberFromUser;
        cout << "podaj wartosc dla zmiennej"<<endl;
        cin >> numberFromUser;
        values.insert(numberFromUser);
    }
    return values;
}


bool CTree::isOperator(string valueToCheck){
    return (valueToCheck == "*" || valueToCheck == "/" || valueToCheck == "+" || valueToCheck == "-"
            || valueToCheck == "sin" || valueToCheck == "cos");
}

bool CTree::isOperator(char valueToCheck){
    return (valueToCheck =='*' || valueToCheck == '/' || valueToCheck == '+' || valueToCheck == '-');
}

bool CTree::isOperatorSinOrCos(string operatorToCheck){
    return (operatorToCheck == "sin" || operatorToCheck =="cos");
}