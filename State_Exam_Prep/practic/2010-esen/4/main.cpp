#include <iostream>
#include <cassert>

int stringLenght(const char* str)
{
    int len=0;
    while(*(str+len)!='\0')
    {
        len++;
    }
    return len;
}
struct Node
{
    char data;
    Node* next;
    explicit Node(const char& data_,Node* next_=nullptr):data(data_),next(next_){}
};
class Stack
{
    private:
        Node* head;
        int size;
        void clear()
        {
            while(this->head!=nullptr)
            {
                Node* toDel= this->head;
                this->head=this->head->next;
                delete toDel;
            }
            this->size=0;
        }
        void copy(const Stack& rhs)
        {
            Node* traversal=rhs.head;
            Stack* helperStack=new Stack();
            while(traversal!=nullptr)
            {
                helperStack->push(traversal->data);
                traversal =traversal->next;
            }
            while(!helperStack->isEmpty())
            {
                this->push(helperStack->top());
                helperStack->pop();
            }
            delete helperStack;
        }

    public:
        Stack():head(nullptr),size(0){}
        Stack(const Stack& rhs):head(nullptr),size(0)
        {
            this->copy(rhs);
        }
        Stack& operator=(const Stack& rhs)
        {
            if(this!=&rhs)
            {
                this->clear();
                this->copy(rhs);
            }
            return *this;
        }
        ~Stack()
        {
            this->clear();
        }
        bool isEmpty()const
        {
            return this->size==0;
        }
        void push(const char& data)
        {
            Node* newly=new Node(data);
            if(this->head==nullptr)
            {
                this->head=newly;
            }
            else
            {
                newly->next=this->head;
                this->head=newly;
            }
            ++this->size;
        }
        void pop()
        {
            if(this->head==nullptr)
            {
                return;
            }
            else
            {
                Node* toDel=this->head;
                this->head=this->head->next;
                delete toDel;
                --this->size;
            }
        }
        char top()const
        {
            return this->head->data;
        }
        static bool areBracketsCorrect(const char* str)
        {
            int len=stringLenght(str);
            if(len==0 || len==1)
            {
                return false;
            }
            Stack* stack = new Stack();
            for (int i = len-1; i >= 0; i--)
            {
                //storing the string in the stack as the 0 index of the string is the head of the stack 
                stack->push(str[i]);
            }
            
            bool result=true;
            int cntBrackets=0;
            
            while(!stack->isEmpty())
            {
                char cur=stack->top();
                if(cur=='(')
                {
                    ++cntBrackets;
                }
                else if(cur==')')
                {
                    if(--cntBrackets<0)
                    {
                      result=false;
                      break;
                    }
                }

                stack->pop();
            }

            delete stack;

            if(result && cntBrackets!=0)
            {
                result=false;
            }
            return result;

        }
        //this is the most common solve
        static bool otherSol(const char* str)
        {
            int len=stringLenght(str);
            if(len==0 || len==1)
            {
                return false;
            }
            bool result=true;
            Stack* stack= new Stack();
            for (size_t i = 0; i < len; i++)
            {
                if(str[i]=='(')
                {
                    stack->push(str[i]);
                }
                else if(str[i]==')')
                {
                    if(stack->isEmpty())
                    {
                        result=false;
                        break;
                    }
                    else
                    {
                        stack->pop();
                    }
                }
            }
            if(!stack->isEmpty())
            {
                result=false;
            }            
            return result;
        }
};
int main()
{
    char * input = new char[101];
    std::cout<<"Your string input [max length 100 chars]: ";std::cin.getline(input,101);
    
    std::cout<<std::boolalpha<<Stack::otherSol(input)<<std::endl;

    assert(Stack::areBracketsCorrect("())") == false);
    assert(Stack::areBracketsCorrect("))") == false);
    assert(Stack::areBracketsCorrect("((()") == false);
    assert(Stack::areBracketsCorrect("((") == false);
    assert(Stack::areBracketsCorrect("))()()))") == false);
    assert(Stack::areBracketsCorrect("()") == true);
    assert(Stack::areBracketsCorrect("()()") == true);
    assert(Stack::areBracketsCorrect("(())") == true);
    assert(Stack::areBracketsCorrect("((()())") == false);
    assert(Stack::areBracketsCorrect("((()()))") == true);

    assert(Stack::otherSol("") == false);
    assert(Stack::otherSol("(a+b).c") == true);
    assert(Stack::otherSol("(((a+b).c).d).e+f.(g+h)") == true);
    assert(Stack::otherSol("1+(2+(3+4)+((5+6)+(7+8)+9))") == true);

    assert(Stack::otherSol("(") == false);
    assert(Stack::otherSol("a+b.c)") == false);
    assert(Stack::otherSol("(((a+b)).c).d).e+f.(g+h)") == false);
    assert(Stack::otherSol("()()())))()))") == false);


    delete input;
}