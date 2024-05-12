#pragma once
#include "Node.hpp"

class Tree
{
    private:
        Node* root;
        void clear(Node* root);
    public:
        Tree(Node* root=nullptr);
        ~Tree();
        Node* getRoot()const;
        void dfs(Node* root)const;
        bool member(Node* root, int x);
        void filterOdd(Node* root);
};