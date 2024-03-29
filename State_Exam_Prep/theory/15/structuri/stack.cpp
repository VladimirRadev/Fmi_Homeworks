#include <iostream>
#include <string>
template<typename T>
struct Node{
    T data;
    Node<T>* next;

    explicit Node(const T& data_,Node<T>* next_=nullptr):data(data_),next(next_){}
};

template<typename T>
class Stack{
    private:
        Node<T>* head;
        int size;

        bool isEmpty()const
        {
            return this->head==nullptr;
        }
        void copy(const Stack& rhs)
        {
            Node<T>* traversal= rhs.head;
            Stack<T>* stackHelper = new Stack();
            while(traversal!=nullptr)
            {
                stackHelper->push(traversal->data);
                traversal=traversal->next;
            }
            
            while(!stackHelper->isEmpty())
            {
                this->push(stackHelper->top());
                stackHelper->pop();
            }

            delete stackHelper;
        }
        void clear()
        {
            while(!this->isEmpty())
            {
                this->pop();
            }
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
        friend std::ostream& operator<<(std::ostream& out, const Stack& toPrint)
        {
            Node<T>* traversal = toPrint.head;
            while(traversal != nullptr)
            {
                out<<traversal->data<<' ';
                traversal=traversal->next;
            }
            out<<'\n';
            return out;
        }


        void push(const T& data)
        {
            Node<T>* n = new Node<T>(data);
            if(head==nullptr)
            {
                head=n;
            }
            else
            {
                n->next=this->head;
                this->head=n;
            }
            ++size;
        }
        void pop()
        {
            if(this->head!=nullptr)
            {
                Node<T>* toDel=this->head;
                this->head=this->head->next;
                delete toDel;
                --size;
            }
        }
        const T top()const
        {
            return this->head->data;
        }
        const int getSize()const
        {
            return this->size;
        }
};


int main()
{
    Stack<std::string>* stack1 = new Stack<std::string>();
    stack1->push("Sexy");
    stack1->push("kukla");
    stack1->push("na");
    stack1->push("Sariev");
    stack1->pop();

    std::cout<<stack1->top()<<'\n';//na
    std::cout<<stack1->getSize()<<'\n';//3
    std::cout<<*stack1;//na kukla Sexy

    while(stack1->getSize()!=0)
    {
        stack1->pop();
    }
    std::cout<<*stack1;// [prazen red]

    stack1->push("Ala");
    stack1->push("BAla");

    //copy constructor
    Stack<std::string> copStack1 = Stack<std::string>(*stack1);
    std::cout<<copStack1;//BAla \n Ala
    
    copStack1.push("Tosho");

    stack1->operator=(copStack1);
    std::cout<<*stack1;//Tosho \n BAla \n Ala


    delete stack1;
}