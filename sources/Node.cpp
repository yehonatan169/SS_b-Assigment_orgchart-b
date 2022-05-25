#include "Node.hpp"
#include <queue>
#include <iostream>
Node::Node(const string &info,int rank) {
    this->info = info;
    this->boss = nullptr;
    this->subordinates = {};
    this->rank = rank;
}
