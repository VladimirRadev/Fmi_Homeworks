#include <iostream>
#include <vector>
#include <map>
#include <queue>

template<typename T>
struct Node{
    T data;
    std::vector<Node<T>*> children;
    explicit Node(const T& data_,const std::vector<Node<T>*>& children_=std::vector<Node<T>*>()) :data(data_),children(children_){}
};

template<typename T>
class Tree{
    private:
        Node<T>* root;
        void clear(Node<T>* root)
        {
            for (size_t i = 0; i < root->children.size(); i++)
            {
                clear(root->children[i]);
            }
            delete root;
        }
        Node<T>* copy(Node<T>*curRoot, Node<T>* rhsRoot)
        {
            if(curRoot==nullptr)
            {
                curRoot=new Node<T>(rhsRoot->data);
            }

            for (size_t i = 0; i < rhsRoot->children.size(); i++)
            {
                curRoot->children.push_back(copy(nullptr,rhsRoot->children[i]));
            }
            

            return curRoot;
        }
    public:
        Tree():root(nullptr){}
        Tree(const Tree& rhs):root(nullptr)
        {
            this->root=this->copy(this->root,rhs.root);
        }
        Tree& operator=(const Tree& rhs)
        {
            if(this != &rhs)
            {   
                this->clear(this->root);
                this->root=nullptr;
                this->root=this->copy(this->root,rhs.root);
            }
            return *this;
        }
        ~Tree()
        {
            this->clear(this->root);
        }
        Node<T>* getRoot()
        {
            return this->root;
        }

        void dfs(Node<T>* root, std::ostream& out)
        {
            if(root!=nullptr)
            {
                out<<root->data<<' ';
                int children_size = root->children.size();
                if(children_size==0)
                {
                    return;
                }
                
                for (size_t i = 0; i < children_size; i++)
                {
                    dfs(root->children[i],out);
                }
            }
        }
        void bfs(Node<T>* root, std::ostream& out)
        {
            std::queue<Node<T>*> elements;
            elements.push(root);

            int level=0;
            while (!elements.empty())
            {
                int curr_size = elements.size();
                out<<"Level "<<level<<": ";
                
                while(curr_size--)
                {
                    Node<T>* currNode=elements.front();
                    elements.pop();

                    out<<currNode->data<<' ';

                    for (size_t i = 0; i < currNode->children.size(); i++)
                    {
                        elements.push(currNode->children[i]);
                    }
                    
                }
                out<<'\n';
                level++;
            }
            
        }
        void buildTreeFromMap(const std::map<Node<int>*,Node<int>*>& treeBuilder)
        {
            auto iter=treeBuilder.begin();
            auto end=treeBuilder.end();
            
            while (iter!=end)
            {
                auto child= iter->first;
                auto parent=iter->second;
                iter++;

                if(parent==nullptr)
                {
                    this->root=child;
                    continue;
                }
                parent->children.push_back(child);
            }
            
        }
        void addNode(Node<T>*root, const T& value, const T& parentValue,bool& found)
        {
            if(root!=nullptr && !found)
            {
                if(root->data==parentValue)
                {
                    Node<T>* newNode = new Node<T>(value);
                    root->children.push_back(newNode);
                    found=true;
                    return;
                }

                for (size_t i = 0; i < root->children.size(); i++)
                {
                    addNode(root->children[i],value,parentValue,found);
                }
            }
        }

        Node<T>* findElement(Node<T>*root, const T& value)
        {
            if(root->data==value)
            {
                return root;
            }

            Node<T>* result=nullptr;
            for (size_t i = 0; i < root->children.size(); i++)
            {
                result=findElement(root->children[i],value);
                if(result!=nullptr)
                {
                    break;
                }
            }
            return result;
        }

};

int main()
{
    //child, parent
    std::map<Node<int>*,Node<int>*> treeBuilder;




    std::vector<Node<int>*> vec{
        new Node<int>(1), //0
        new Node<int>(3), //1
        new Node<int>(5), //2
        new Node<int>(7), //3
        new Node<int>(8), //4
        new Node<int>(10),//5
        new Node<int>(9),//6
    };
    //       1
    //      / \
    //     3   5
    //    / \  / \
    //   7  8  10 9
    // 
    //  input durvo

    treeBuilder[vec[0]]=nullptr;
    treeBuilder[vec[1]]=vec[0];
    treeBuilder[vec[2]]=vec[0];
    treeBuilder[vec[3]]=vec[1];
    treeBuilder[vec[4]]=vec[1];
    treeBuilder[vec[5]]=vec[2];
    treeBuilder[vec[6]]=vec[2];

    Tree<int> tree;
    tree.buildTreeFromMap(treeBuilder);
    tree.dfs(tree.getRoot(),std::cout);
    std::cout<<'\n'; // 1 3 8 7 5 10 9 //ili neshto podobno shoto mapa si gi podrejda po pameta

    //copy constructor works
    Tree<int> copyOfTree(tree);
    copyOfTree.dfs(copyOfTree.getRoot(),std::cout);
    std::cout<<'\n'; //1 3 8 7 5 10 9 //ili neshto podobno shoto mapa si gi podrejda po pameta

    bool found=false;
    copyOfTree.addNode(copyOfTree.getRoot(),2,7,found);
    copyOfTree.dfs(copyOfTree.getRoot(),std::cout);
    std::cout<<'\n'; //1 5 10 9 3 7 2 8 //ili neshto podobno shoto mapa si gi podrejda po pameta

    //operator = works
    tree=copyOfTree;
    tree.dfs(tree.getRoot(),std::cout);
    std::cout<<'\n'; //1 5 10 9 3 7 2 8 //ili neshto podobno shoto mapa si gi podrejda po pameta

    tree.bfs(tree.getRoot(),std::cout); 
                                        // Level 0: 1
                                        // Level 1: 3 5
                                        // Level 2: 8 7 9 10
                                        // Level 3: 2

    Node<int>* ptr= tree.findElement(tree.getRoot(),7);

    if(ptr!=nullptr && ptr->data==7 && ptr->children[0]->data==2)
    {
        std::cout<<"Yeah find element works well\n";
    }

    ptr= tree.findElement(tree.getRoot(),69);
    if(ptr==nullptr)
    {
        std::cout<<"Yeah find element works well . confirmed twice \n";
    }
    

    

}