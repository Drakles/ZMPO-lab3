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

void CNode::operator=(CNode &otherNode) {

        if(this != nullptr) {
            //cout << "this nie jest nullptr" << endl;
            parent = this;

//            cout << "wywolalem operator = dla noda o value= " << this->value << endl;
//            cout << "a otherNode value=" << otherNode.value << endl;
            value = otherNode.value;

//            cout << "zmienilem value, teraz this.value=" << this->value << endl;
//
//            cout << "jestem przed ifami" << endl;

            if (otherNode.leftChild != nullptr) {
//                cout <<"robie *leftchild = *otherNode.leftChild"<<endl;
//                cout <<"a othernode.value="<<otherNode.value<<endl;
                leftChild = new CNode();
                *leftChild = *otherNode.leftChild;
//                cout << "mowie ze lewe dziecko rodzic to ja"<<endl;
//                cout << "a to lewe dziecko value= "<<leftChild->value<<endl;
                leftChild->parent = this;
                //cout << "zmienilem lewe dziecko" << endl;
            }

            if (otherNode.righChild != nullptr) {
            righChild = new CNode();
            *righChild = *otherNode.righChild;
            righChild->parent = this;
            //cout << "zmienilem prawe dziecko" << endl;
            }
            //return *this;
        }else{
            cout <<"NIE DA SIE GUPKU"<<endl;
        }
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

