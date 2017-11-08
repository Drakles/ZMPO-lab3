//
// Created by Kajetan Dymkiewicz on 30.10.2017.
//

#include <iostream>
#include "CNode.h"

using namespace std;

CNode::CNode(const std::string &value, CNode *parent){
    this->value = value;
    this->leftChild = nullptr;
    this->righChild = nullptr;
    this->parent = parent;
}

std::string CNode::toString(){
    return this->value;
}

CNode &CNode::operator=(CNode &otherNode) {

    parent = this;
    cout << "wywolalem operator = dla noda o value=" << this->value << endl;
    cout << "a otherNode value=" << otherNode.value << endl;
    value = otherNode.value;
    cout << "zmienilem value, teraz this.value=" << this->value << endl;
    //*parent = *otherNode.parent;
    if (leftChild != nullptr) {
    *leftChild = *otherNode.leftChild;
    leftChild->parent = this;
        cout <<"zmienilem lewe dziecko"<<endl;
    }
    if(righChild != nullptr){
        *righChild = *otherNode.righChild;
        righChild->parent = this;
        cout << "zmienilem prawe dziecko" << endl;
    }
    return *this;
}

CNode::~CNode() {
    cout <<"wywolalem delete CNode"<<endl;
    if(leftChild != nullptr){
        delete leftChild;
    }
    if(righChild != nullptr) {
        delete righChild;
    }
}

