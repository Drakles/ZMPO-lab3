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
    value = otherNode.value;
    parent = otherNode.parent;
    leftChild = otherNode.leftChild;
    righChild = otherNode.righChild;

    return *this;
}

