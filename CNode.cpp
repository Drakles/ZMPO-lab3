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

CNode::CNode(){
    this->value="";
    this->leftChild= nullptr;
    this->righChild = nullptr;
    this->parent = nullptr;
}

std::string CNode::toString(){
    return this->value;
}

CNode& CNode::operator=(CNode &otherNode) {

            parent = new CNode(*otherNode.parent);
            value = otherNode.value;

            if (otherNode.leftChild != nullptr) {
                leftChild = new CNode(*otherNode.leftChild);
            }

            if (otherNode.righChild != nullptr) {
                righChild = new CNode(*otherNode.righChild);
            }
    return *this;
}

CNode::~CNode() {
    delete leftChild;
    delete righChild;
}

CNode::CNode(const CNode &node) {
    if(&node != nullptr){
        this->value = node.value;
        this->parent = node.parent;

        if(node.leftChild != nullptr) this->leftChild = new CNode(*node.leftChild);
        if(node.righChild != nullptr) this->righChild = new CNode(*node.righChild);

    }
}

