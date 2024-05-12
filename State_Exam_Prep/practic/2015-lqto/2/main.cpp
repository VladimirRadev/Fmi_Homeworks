#include <iostream>
#include "Node.cpp"
#include "Tree.cpp"
int main()
{
   //leafs 
   Node* l1 = new Node(2);
   Node* l2 = new Node(4);
   Node* l3 = new Node(5);
   Node* l4 = new Node(6);
   Node* r1 = new Node(3);
   r1->children.push_back(l2); //4
   r1->children.push_back(l3); //5
   r1->children.push_back(l4); //6
   
   Node* root= new Node(8);
   root->children.push_back(l1); //2
   root->children.push_back(r1); //3

   Tree tree(root);
//    std::cout<<std::boolalpha<<tree.member(tree.getRoot(),8)<<std::endl; //true
//    std::cout<<std::boolalpha<<tree.member(tree.getRoot(),5)<<std::endl; //true
//    std::cout<<std::boolalpha<<tree.member(tree.getRoot(),69)<<std::endl; //false
//    std::cout<<std::boolalpha<<tree.member(tree.getRoot(),-2)<<std::endl; //false


   tree.dfs(tree.getRoot()); // 8 2 3 4 5 6 
   std::cout<<'\n';
   tree.filterOdd(tree.getRoot());
   tree.dfs(tree.getRoot()); // 8 2
   std::cout<<'\n';




}