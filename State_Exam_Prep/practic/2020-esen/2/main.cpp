#include <iostream>
#include <stack>
#include <queue>
struct Node
{
    char text;
    Node *left, *right;
    explicit Node(const char& text,Node* left=nullptr,Node*right =nullptr):text(text),left(left),right(right){}
};
bool isValid(char c)
{
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') 
    || (c == '.') || (c == ',') || (c == '!') || (c=='?') )
    {
        return true;
    }
    return false;
}
void printText(Node* ptr)
{
    std::stack<char> result;

    std::queue<Node*> que;
    que.push(ptr);
    
    while(!que.empty())
    {
        int sizeOfLevel=que.size();
        bool isEndLine=true;
        while(sizeOfLevel--)
        {
            Node* cur = que.front();
            que.pop();
            if(cur == nullptr)
            {
                que.push(nullptr);
                que.push(nullptr);
                result.push(' ');
                continue;
            }
            if(cur != nullptr && isValid(cur->text))
            {
                result.push(cur->text);
            }
            
            if(cur->left != nullptr || cur-> right !=nullptr)
            {
                isEndLine=false;
            }
            que.push(cur->left);
            que.push(cur->right);
        }
        result.push('\n');
        if(isEndLine)
        {
            break;
        }
    }

    while(result.top()==' ')
    {
        result.pop();
    }
    std::stack<char> temp;
    while(!result.empty())
    {
        temp.push(result.top());
        result.pop();
    }
    while(!temp.empty())
    {
        std::cout<<temp.top();
        temp.pop();
    }
}  
int main()
{
    Node* i1 = new Node('I');
    Node* i2 = new Node('a');
    Node* i3 = new Node('m');
    Node* i4 = new Node('g');
    Node* i5 = new Node('o');
    Node* i6 = new Node('o');
    Node* i7 = new Node('d');
    Node* i8 = new Node('a');
    Node* i9 = new Node('t');
    Node* i10 = new Node('s');
    Node* i11 = new Node('o');
    Node* i12 = new Node('l');
    Node* i13 = new Node('v');
    Node* i14 = new Node('i');
    Node* i15 = new Node('n');
    Node* i16 = new Node('g');
    Node* i17 = new Node('p');
    Node* i18 = new Node('r');
    Node* i19 = new Node('o');
    Node* i20 = new Node('b');
    Node* i21 = new Node('l');
    Node* i22 = new Node('e');
    Node* i23 = new Node('m');
    Node* i24 = new Node('s');
    Node* i25 = new Node('!');

    //"I"
    i1->left=i2;
    i1->right=i3;

    //"a"
    i2->left=i4;
    i2->right=i5;

    //"m"
    i3->left=i6;
    i3->right=i7;

    //"g"
    i4->left=i8;
    i4->right=i9;

    //"o"
    i5->left=nullptr;
    i5->right=i10;

    //"o"
    i6->left=i11;
    i6->right=i12;

    //"d"
    i7->left=i13;
    i7->right=i14;

    //"a"
    i8->left=i15;
    i8->right=i16;

    //"t"
    i9->left=nullptr;
    i9->right=i17;

    //"s"
    i10->left=i18;
    i10->right=i19;

    //'o'
    i11->left=i20;
    i11->right=i21;

    //'l'
    i12->left=i22;
    i12->right=i23;

    //'v'
    i13->left=nullptr;
    i13->right=nullptr;

    //'i'
    i14->left=i14->right=nullptr;

    //'n'
    i15->left=i24;
    i15->right=nullptr;

    //'g'
    i16->left=nullptr;
    i16->right=i25;

    //'p'
    i17->left=i17->right=nullptr;


     //'r'
    i18->left=i18->right=nullptr;
      //'o'
    i19->left=i19->right=nullptr;
      //'b'
    i20->left=i20->right=nullptr;
      //'l'
    i21->left=i21->right=nullptr;
      //'e'
    i22->left=i22->right=nullptr;
      //'m'
    i23->left=i23->right=nullptr;


    printText(i1);

    delete i25;
    delete i24;
    delete i23;
    delete i22;
    delete i21;
    delete i20;
    delete i19;
    delete i17;
    delete i16;
    delete i15;
    delete i14;
    delete i13;
    delete i12;
    delete i11;
    delete i10;
    delete i9;
    delete i8;
    delete i7;
    delete i6;
    delete i5;
    delete i4;
    delete i3;
    delete i2;
    delete i1;

}