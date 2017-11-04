//
// Created by Kajetan Dymkiewicz on 30.10.2017.
//

#ifndef LISTA3_CNODE_H
#define LISTA3_CNODE_H

#include <string>

class CNode {
    CNode(const std::string &value, CNode *parent);

    friend class CTree;


public:
    CNode *parent;
    CNode *righChild;
    std::string value;
    CNode *leftChild;

    std::string toString();
};


#endif //LISTA3_CNODE_H
