#include <iostream>
#include <queue>
#include <utility>
template<typename T>
struct Node{
    T data;
    Node<T>* left;
    Node<T>* right;
    explicit Node(const T& data_, Node<T>* left_=nullptr, Node<T>* right_=nullptr):data(data_),left(left_),right(right_){}
};

template<typename T>
class BST{
    private:
        Node<T>* root;
        void clear(Node<T>* root)
        {
            if(root->left ==nullptr && root->right==nullptr)
            {
                delete root;
                return;
            }
            if(root->left != nullptr) clear(root->left);
            if(root->right!=nullptr) clear(root->right);
            delete root;
        }
        Node<T>* copy(Node<T>* root, Node<T>* rhsRoot)
        {
            if(rhsRoot!=nullptr)
            {
                root=new Node<T>(rhsRoot->data);
            }

            if(rhsRoot->left!=nullptr)
            {
                root->left=copy(root->left,rhsRoot->left);
            }
            if(rhsRoot->right!=nullptr)
            {
                root->right=copy(root->right,rhsRoot->right);
            }
            return root;
        }
        Node<T>* getMaxAtLeft(Node<T>* node)
        {
            while (node != nullptr && node->right!=nullptr)
            {
                node=node->right;
            }
            return node;
        }
        static void bfs(std::ostream& out, const BST& rhs)
        {
            std::queue<std::pair<std::string,Node<T>*>> que;
            que.push(std::pair<std::string,Node<T>*>("ROOT_",rhs.root));

            int level=0;
            while(!que.empty())
            {
                int curr_size = que.size();
                out<<"Level "<<level<<": ";
                while(curr_size--)
                {
                    std::pair<std::string,Node<T>*> top= que.front();
                    que.pop();
                    out<<top.first<<top.second->data<<' ';

                    if(top.second->left!=nullptr)
                    {
                        que.push(std::pair<std::string,Node<T>*>("L_",top.second->left));
                    }
                    
                    if(top.second->right!=nullptr)
                    {
                        que.push(std::pair<std::string,Node<T>*>("R_",top.second->right));
                    }
                }
                level++;
                out<<'\n';
            }
        }
    public:
        BST():root(nullptr){}
        BST(const BST& rhs):root(nullptr)
        {
            this->root=this->copy(this->root,rhs.root);
        }
        BST& operator=(const BST& rhs)
        {
            if(this!=&rhs)
            {
                this->clear(this->root);
                this->root=nullptr;
                this->root=this->copy(this->root,rhs.root);
            }
            return *this;
        }
        ~BST()
        {
            this->clear(this->root);
        }
        friend std::ostream& operator<<(std::ostream& out, const BST& rhs)
        {
            bfs(out,rhs);
            return out;
        }

        Node<T>* getRoot()const
        {
            return this->root;
        }
        void setRoot(Node<T>* newRoot)
        {
            this->root=newRoot;
        }
        Node<T>* insert(Node<T>* root,const T& value)
        {   
            if(root==nullptr)
            {
                root=new Node<T>(value);
                return root;
            }
            else if(value< root->data) //left
            {
                root->left=insert(root->left,value);
            }
            else if(value > root->data)//right
            {
                root->right=insert(root->right,value);
            } 
            else    //already element of the tree
            {
                return root;
            }
            return root;    
            
        }
        //find element of the tree and return a pointer to it. If an element isn't present at the tree return nullptr.
        Node<T>* find(Node<T>*root, const T& value) const
        {
            if(root->data==value)
            {
                return root;
            }
            Node<T>* result=nullptr;
            if(root->left!=nullptr && value < root->data)
            {
                result=find(root->left,value);
            }
            else if(root->right!=nullptr && value > root->data)
            {
                result=find(root->right,value);
            }
            return result;
        }
        //erase an element from the tree
        Node<T>* erase(Node<T>* root, const T& value)
        {
            if(root==nullptr)
            {
                return root;
            }
            else if(value < root->data)
            {
                root->left=erase(root->left,value);
            }
            else if(root->data < value)
            {
                root->right=erase(root->right,value);
            }
            else
            {
                if(root->left==nullptr && root->right==nullptr)
                {
                    delete root;
                    return nullptr;
                }
                else if(root->left==nullptr)
                {
                    Node<T>* replacingWith = root->right;
                    delete root;
                    return replacingWith;
                }
                else if(root->right==nullptr)
                {   
                    Node<T>* replacingWith = root->left;
                    delete root;
                    return replacingWith;
                }
                else //has two children
                {
                    Node<T>* replacingWith = this->getMaxAtLeft(root->left);

                    // T newEraseData= root->data;
                    // root->data=replacingWith->data;
                    // replacingWith->data=newEraseData;

                    std::swap(replacingWith->data,root->data);

                    root->left = erase(root->left,replacingWith->data);
                }
            }
            return root;
        }
};

int main()
{
    BST<int> bst;
    bst.setRoot(bst.insert(bst.getRoot(),10));
    bst.setRoot(bst.insert(bst.getRoot(),5));
    bst.setRoot(bst.insert(bst.getRoot(),7));
    bst.setRoot(bst.insert(bst.getRoot(),6));
    bst.setRoot(bst.insert(bst.getRoot(),8));
    bst.setRoot(bst.insert(bst.getRoot(),3));
    bst.setRoot(bst.insert(bst.getRoot(),2));
    bst.setRoot(bst.insert(bst.getRoot(),4));
    bst.setRoot(bst.insert(bst.getRoot(),12));
    bst.setRoot(bst.insert(bst.getRoot(),11));
    bst.setRoot(bst.insert(bst.getRoot(),14));
    bst.setRoot(bst.insert(bst.getRoot(),15));

    std::cout<<bst; // Level 0: ROOT_10 
    //                 Level 1: L_5 R_12
    //                 Level 2: L_3 R_7 L_11 R_14
    //                 Level 3: L_2 R_4 L_6 R_8 R_15
    std::cout<<"\n\n\n";
    bst.setRoot(bst.erase(bst.getRoot(),15));
    std::cout<<bst; 
                    // Level 0: ROOT_10
                    // Level 1: L_5 R_12
                    // Level 2: L_3 R_7 L_11 R_14
                    // Level 3: L_2 R_4 L_6 R_8 

    std::cout<<"\n\n\n";
    bst.setRoot(bst.insert(bst.getRoot(),15));
    bst.setRoot(bst.erase(bst.getRoot(),14));
    std::cout<<bst; 
                    // Level 0: ROOT_10
                    // Level 1: L_5 R_12
                    // Level 2: L_3 R_7 L_11 R_15
                    // Level 3: L_2 R_4 L_6 R_8
    std::cout<<"\n\n\n";

    bst.setRoot(bst.erase(bst.getRoot(),15));
    bst.setRoot(bst.erase(bst.getRoot(),12));
    std::cout<<bst; 
                // Level 0: ROOT_10
                // Level 1: L_5 R_11
                // Level 2: L_3 R_7
                // Level 3: L_2 R_4 L_6 R_8 

    std::cout<<"\n\n\n";

    bst.setRoot(bst.erase(bst.getRoot(),5));
    std::cout<<bst;
            // Level 0: ROOT_10
            // Level 1: L_4 R_11
            // Level 2: L_3 R_7
            // Level 3: L_2 L_6 R_8
    std::cout<<"\n\n\n";

    Node<int>* ptr= bst.find(bst.getRoot(),3);
    if(ptr->left->data == 2 && ptr->right==nullptr)
    {
        std::cout<<"assert 0 correct\n";
    }
    ptr=bst.find(bst.getRoot(),54);
    if(ptr==nullptr)
    {
        std::cout<<"assert 1 correct \n";
    }
    std::cout<<"\n\n\n";

    //copy constructor
    BST<int> copyOfBST(bst);
    copyOfBST.setRoot(copyOfBST.insert(copyOfBST.getRoot(),54));
    std::cout<<copyOfBST;
                // Level 0: ROOT_10
                // Level 1: L_4 R_11
                // Level 2: L_3 R_7 R_54      ===== should match with down out
                // Level 3: L_2 L_6 R_8
    std::cout<<"\n\n\n";


    //operator = 
    bst=copyOfBST;    
    std::cout<<bst;
                // Level 0: ROOT_10
                // Level 1: L_4 R_11
                // Level 2: L_3 R_7 R_54      === should match with above out
                // Level 3: L_2 L_6 R_8


}