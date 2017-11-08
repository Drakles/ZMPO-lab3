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

CTree::~CTree() {
    cout <<"wywolalem delete CTRee"<<endl;
    delete root;
}

CTree::CTree(CTree &tree){
    if(root != nullptr){
     delete root;
    }
    *root = *tree.root;
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
        cout << "nie jest ok"<<expr<<endl;
        makeStringCorrect(expr);
        cout << "poprawione="<<expr<<endl;
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

CTree CTree::operator+(CTree &otherTree){

    cout <<"wszledme do operatora+"<<endl;
    CTree ct;
   // ct->tmp = true;
    cout <<"stworzylem ct i ustawilem tmp true"<<endl;
    ct.root = this->root;
    cout <<"wykonalem ct->root = this->root"<<endl;
    CNode * p;
    *p = *ct.root;
    cout <<"stworzylem wskaznik p ustawilem go *p = *ct->root"<<endl;
    while (p->leftChild->leftChild != nullptr){
        p = p->leftChild;
    }
    *p->leftChild = *otherTree.root;

    //if(otherTree.tmp) delete &otherTree;
    cout <<"jestem przed zwroceniem *ct"<<endl;
    return ct;
}

CTree & CTree::operator=(CTree &t){
    if(root != nullptr) {
        cout << "wywolalem operator = dla tree" << endl;
        *root = *t.root;
        cout << "jestem w operator tree i zwracam *this" << endl;

        if(t.tmp) delete &t;

        return *this;
    }else cout <<"NIE DA SIE GLUPCZE"<<endl;
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

double CTree::computeTree(set<double> setOfValueOfVariables){
    return comp(root,setOfValueOfVariables);
}

bool CTree::isNumber(string valueToCheck){
    bool isNumber = true;

    for (int i = 0; i < valueToCheck.length(); ++i) {
        if(!isdigit(valueToCheck[0])) isNumber = false;
    }
    return isNumber;
}

int CTree::isExprCorrect(string expr){
    int numberOfOperators = 0;
    int numberOfVariables = 0;

    expr.append(SPACE_STRING);
    //cout <<"dodalem spacje na koncu, expr="<<expr<<"|"<<endl;

    while(expr.length()>1){

        while(expr[0] == SPACE_CHAR && expr.length() > 1){
            expr = expr.substr(1, expr.length());
            //cout <<"usunalem zbedna spacje na poczatku, expr="<<expr<<"|"<<endl;
        }
        if(isOperatorButNotSinOrCos(expr.at(0))) {
            numberOfOperators++;
            expr = expr.substr(1, expr.length());
            //cout <<"zwiekszylem liczbe op, expr="<<expr<<"|"<<endl;
        }else {
            if (isOperatorSinOrCos(expr.substr(0, 3))) {
                numberOfOperators++;
                expr = expr.substr(3, expr.length());
                //cout <<"zwiekszylem liczbe op, expr="<<expr<<"|"<<endl;
            } else if(!isspace(expr.at(0))){
                numberOfVariables++;
                expr = expr.substr(1, expr.length());
                //cout <<"zwiekszylem liczbe var, expr="<<expr<<"|"<<endl;
            }
        }
    }
//    cout <<"ilosc operator = "<<numberOfOperators<<endl;
//    cout <<"ilosc zmiennych lub stalych= "<<numberOfVariables<<endl;
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
    return (valueToCheck ==MULTPL_STRING || valueToCheck == DVSIN_STRING || valueToCheck == ADD_STRING
            || valueToCheck == SBSTR_STRING || valueToCheck == SIN || valueToCheck == COS);
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


void CTree::printInOrder(CNode *node,string &output){
    if(node->leftChild != nullptr){
        printInOrder(node->leftChild,output);
    }
    output.append(node->value);
    output.append(SPACE_STRING);
    if(node->righChild != nullptr){
        printInOrder(node->righChild,output);
    }
}

void CTree::printBinaryTree(CNode *node, int level,string &output) {
    if (node == nullptr) {
        return;
    }
    printBinaryTree(node->righChild, level + 1,output);
    if (level != 0) {
        for (int i = 0; i < level - 1; i++)
            output.append("|\t\t");
        output.append("|-------");
        output.append(node->value);
    } else
        output.append(node->value);
        output.append("\n");;
    printBinaryTree(node->leftChild, level + 1,output);
}

string CTree::printAsTree() {
    string output = "";
    printBinaryTree(root, 0,output);
    return output;
}

string CTree::printInOrder(){
    string output= "";
    printInOrder(root,output);
   return output;
}

string CTree::printVariables(set<string> setOfVariables){

    string output = "";
    set<string>::iterator it;

    for (it = setOfVariables.begin(); it!=setOfVariables.end() ; it++) {
        output.append(*it);
        output.append(",");
    }
}
string CTree::printPostOrder(){
    string output = "";
    printPostOrder(root,output);
    return output;
}


void CTree::printPostOrder(CNode *node,string &output) {
    output.append(node->value);
    output.append(SPACE_STRING);

    if(node->leftChild != nullptr) printPostOrder(node->leftChild,output);
    if(node->righChild != nullptr) printPostOrder(node->righChild,output);
}
