//
// Created by Kajetan Dymkiewicz on 30.10.2017.
//

#include <iostream>
#include <set>
#include "CTree.h"
#include <math.h>

using namespace std;

CTree::CTree(){
    root = nullptr;
}

int CTree::createTree(string &expr){

    if(isExprCorrect(expr) == NUM_VAR_AND_NUM_OP_IS_CORRECT) {

        while (expr[0] == SPACE_CHAR) {
            expr = expr.substr(1, expr.length());
        }

        expr = expr.append(SPACE_STRING);

        if (isOperatorButNotSinOrCos(expr[0]) || isOperatorSinOrCos(expr.substr(0, 3))) {

            if (expr.substr(0, 3) == SIN || expr.substr(0, 3) == COS) {
                this->root = new CNode(expr.substr(0, 3), root);
                expr = expr.substr(3, expr.length());
                createTree(root, root, expr);
                return CREATE_TREE_SUCCES;
            } else {

                this->root = new CNode(expr.substr(0, 1), root);
                expr = expr.substr(1, expr.length());
                createTree(root, root, expr);
                return CREATE_TREE_SUCCES;
            }
        } else {
            this->root = new CNode(expr, root);
            return CREATE_TREE_SUCCES;
        }
    }else{
        makeStringCorrect(expr);
        createTree(expr);
        return STRING_INCORRECT;
    }
}


void CTree::createTree(CNode *&actualNode,CNode *&parentNode,string &expr){

    if(expr.length() > 0) {
        if (actualNode == nullptr) {

            while(expr[0] == SPACE_CHAR){
                expr = expr.substr(1, expr.length());
            }

            if(expr.substr(0,3) == SIN || expr.substr(0,3) == COS ){
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

double CTree::comp(CNode *node,set<double> &setOfValueOfVariables){
    if(node != nullptr) {
        if (isOperator(node->value)) {

            switch(node->value.at(0)){
                case MULTPL_CHAR:
                    return comp(node->leftChild,setOfValueOfVariables) * comp(node->righChild,setOfValueOfVariables);
                case DVSIN_CHAR:
                    return comp(node->leftChild,setOfValueOfVariables) / comp(node->righChild,setOfValueOfVariables);
                case ADD_CHAR:
                    return comp(node->leftChild,setOfValueOfVariables) + comp(node->righChild,setOfValueOfVariables);
                case SBSTR_CHAR:
                    return comp(node->leftChild,setOfValueOfVariables) - comp(node->righChild,setOfValueOfVariables);
                case S:
                    return sin((comp(node->leftChild,setOfValueOfVariables)*PI)/180);
                case C:
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
        cout << GET_VALUE<<endl;
        cin >> numberFromUser;
        values.insert(numberFromUser);
    }
    return values;
}

int CTree::isExprCorrect(string expr){
    int numberOfOperators = 0;
    int numberOfVariables = 0;

    expr.append(SPACE_STRING);

    while(expr.length()>1){

        while(expr[0] == SPACE_CHAR && expr.length() > 2){
            expr = expr.substr(1, expr.length());
        }
        if(isOperatorButNotSinOrCos(expr.at(0))) {
            numberOfOperators++;
            expr = expr.substr(1, expr.length());
        }else {
            if (isOperatorSinOrCos(expr.substr(0, 3))) {
                numberOfOperators++;
                expr = expr.substr(3, expr.length());
            } else {
                numberOfVariables++;
                expr = expr.substr(1, expr.length());
            }
        }
    }
    return (numberOfVariables-numberOfOperators);
}

void CTree::makeStringCorrect(string &expr){

    if(isExprCorrect(expr) < NUM_VAR_AND_NUM_OP_IS_CORRECT) {
        while (isExprCorrect(expr) != NUM_VAR_AND_NUM_OP_IS_CORRECT) {
            expr.append(SPACE_STRING);
            expr.append(ONE);
        }
    }else{
        while (isExprCorrect(expr) != NUM_VAR_AND_NUM_OP_IS_CORRECT) {
            expr= expr.substr(0,expr.length()-1);
        }
    }
}


bool CTree::isOperator(string valueToCheck){
    return (valueToCheck ==MULTPL_STRING || valueToCheck == DVSIN_STRING || valueToCheck == ADD_STRING || valueToCheck == SBSTR_STRING
            || valueToCheck == SIN || valueToCheck == COS);
}

bool CTree::isOperatorButNotSinOrCos(char valueToCheck){
    return (valueToCheck ==MULTPL_CHAR || valueToCheck == DVSIN_CHAR || valueToCheck == ADD_CHAR || valueToCheck == SBSTR_CHAR);
}

bool CTree::isOperatorSinOrCos(string operatorToCheck){
    return (operatorToCheck == SIN || operatorToCheck ==COS);
}

CNode*& CTree::findNodeToAttachedTree(CNode *&node){
    if(node->leftChild != nullptr) findNodeToAttachedTree(node->leftChild);
    else{
        return node;
    }
}



/* PRINTING FUNCTIONS ------------------------------------------------------------------------------------------------*/


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
