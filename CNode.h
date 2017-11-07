//
// Created by Kajetan Dymkiewicz on 30.10.2017.
//

#ifndef LISTA3_CNODE_H
#define LISTA3_CNODE_H

#include <string>

class CNode {

    friend class CTree;

public:
    CNode(const std::string &value, CNode *parent);
    std::string toString();
    CNode & operator=(CNode &otherNode);

private:
    CNode *parent;
    CNode *righChild;
    std::string value;
    CNode *leftChild;

};


#endif //LISTA3_CNODE_H
