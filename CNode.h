//
// Created by Kajetan Dymkiewicz on 30.10.2017.
//

#ifndef LISTA3_CNODE_H
#define LISTA3_CNODE_H

#include <string>

class CNode {

    CNode();

    friend class CTree;

public:
    CNode(const std::string &value, CNode *parent);
    std::string toString();
    void operator=(CNode &otherNode);
    ~CNode();

private:
    std::string value;
    CNode *parent;
    CNode *righChild;
    CNode *leftChild;

};


#endif //LISTA3_CNODE_H
