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

const char SPACE_CHAR = ' ';
const string SPACE_STRING = " ";

const string EXPR_WRONG = " do wczytania drzewa jest błędne ";
const string EXPRESSION = "wyrażenie:";
const string EXPR_REBUILD_MSG = "drzewo zostanie utworzone na podstawie wyrazenia: ";

const char MULTPL_CHAR ='*';
const char DVSIN_CHAR = '/';
const char ADD_CHAR = '+';
const char SBSTR_CHAR = '-';
const string MULTPL_STRING ="*";
const string DVSIN_STRING = "/";
const string ADD_STRING = "+";
const string SBSTR_STRING = "-";

const string SIN = "sin";
const string COS = "cos";
//const char S = SIN.at(0);
//const char C = COS.at(0);
const char S = 's';
const char C = 'c';


const string GET_VALUE = "podaj wartosc dla zmiennej";
const string ONE = "1";

const int STRING_INCORRECT = -1;
const int CREATE_TREE_SUCCES = 0;

class CTree {


    friend class CNode;

public:

    CTree(const CTree &tree);
    CTree();
    ~CTree();


    int createTree(string &expr);

    string printAsTree();
    string printInOrder();
    string printPostOrder();

    string printVariables(set<string> setOfVariables);
    set<string> getVariables();

    CTree & operator=(CTree &t);
    CTree& operator+(CTree &tree);

    double computeTree(set<double> setOfValueOfVariables);

    int isExprCorrect(string expr);
    void makeStringCorrect(string &expr);


    int height();

    string printLevelOrder();
private:

    CNode *root;
    bool tmp = false;

    void printInOrder(CNode *node, string &output);

    void createTree(CNode *&actualNode, CNode *&parentNode, string &expr);

    double comp(CNode *node, set<double> &setOfValueOfVariables);
    bool isOperator(string valueToCheck);
    bool isOperatorSinOrCos(string operatorToCheck);
    bool isOperatorButNotSinOrCos(char valueToCheck);

    bool isNumber(string valueToCheck);
    void getVariables(CNode *node, set<string> &setOfVariables);

    CNode *&findNodeToAttachedTree(CNode *&node);

    void printPostOrder(CNode *node, string &output);

    void printBinaryTree(CNode *node, int level, string &output);

    int height(CNode *node);

    void printGivenLevel(CNode *node, int level, string &output);
};

#endif //LISTA3_CTREE_H
