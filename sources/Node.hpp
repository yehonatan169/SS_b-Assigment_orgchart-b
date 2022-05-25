#pragma once
#include <string>
#include <vector>
using namespace std;
class Node{

public:
    string info;
    vector<Node *> subordinates;
    int rank;
    Node *boss;
    Node(const string & info, int rank);
};