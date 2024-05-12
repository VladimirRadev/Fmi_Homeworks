#include "Tree.hpp"
#include <iostream>
void Tree::clear(Node* root)
{
    if(root==nullptr)
    {
        return;
    }
    //leaf
    if(root->children.size()==0)
    {
        delete root;
        root=nullptr;
        return;
    }

    for (int i = 0; i < root->children.size(); i++)
    {
        clear(root->children[i]);
    }
    root->children.clear();
    delete root;
    root=nullptr;
}
Tree::Tree(Node* root):root(root){}
Tree::~Tree()
{
    this->clear(this->root);
}
Node* Tree::getRoot()const
{
    return this->root;
}
void Tree::dfs(Node* root)const
{
    if(root==nullptr)
    {
        return;
    }
    std::cout<<root->value<<' ';
    for (int i = 0; i < root->children.size(); i++)
    {
        dfs(root->children[i]);
    }
    
    
}

bool Tree::member(Node* root, int x)
{
    bool result = false;
    if(root==nullptr)
    {
        return result;
    }
    if(root->value==x)
    {
        result=true;
        return result;
    }
    for (int i = 0; i < root->children.size(); i++)
    {
        result=member(root->children[i],x);
        if(result)
        {
            break;
        }
    }
    return result;
    
}
void Tree::filterOdd(Node* root)
{
    if(root==nullptr)
    {
        return;
    }
    if(root->value % 2 == 1)
    {
        this->clear(root);
        
    }
    for (int i = 0; i < root->children.size(); i++)
    {
        if(root->children[i] && root->children[i]->value% 2 == 1)
        {
            clear(root->children[i]);
            root->children.erase(root->children.begin() + i);
        }
    }
}
