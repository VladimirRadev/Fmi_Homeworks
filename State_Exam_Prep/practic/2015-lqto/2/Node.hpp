#pragma once
#include <vector>
struct Node
{
    int value;
    std::vector<Node *> children;
    explicit Node(const int &value, const std::vector<Node *>&  children = std::vector<Node *>());
};