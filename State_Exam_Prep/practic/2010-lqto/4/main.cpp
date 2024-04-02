#include <iostream>
#include <cassert>

template<typename T>
struct Node
{
    T data;
    Node<T>* next;
    explicit Node(const T& data_,Node<T>* next_=nullptr):data(data_),next(next_){}
};

template<typename T>
class SinglyLinkedList //stack
{
    private:
        Node<T>* head;
        int size;

        void clear()
        {
            while (this->head!=nullptr)
            {
                Node<T>* toDel = this->head;
                this->head=this->head->next;
                delete toDel;                
            }
            this->size=0;
        }
        void copy(const SinglyLinkedList& rhs)
        {
            Node<T>*traversal=rhs.head;
            SinglyLinkedList<T>* helperStack = new SinglyLinkedList();

            while (traversal!=nullptr)
            {
                helperStack.push(traversal->data);
                traversal=traversal->next;
            }
            traversal=helperStack->head;
            while(traversal!=nullptr)
            {
                this->push(traversal->data);
                traversal=traversal->next;
            }
            this->size=rhs.size;
            delete helperStack;
            
        }



    public:
        SinglyLinkedList():head(nullptr),size(0){}
        SinglyLinkedList(const SinglyLinkedList& rhs):head(nullptr),size(0){}
        SinglyLinkedList& operator=(const SinglyLinkedList& rhs)
        {
            if(this!=&rhs)
            {
                this->clear();
                this->copy(rhs);
            }
            return *this;
        }    
        ~SinglyLinkedList()
        {
            this->clear();
        }
        void push(const T& value)
        {
            Node<T>* n = new Node<T>(value);
            if(this->head==nullptr)
            {   
                this->head=n;
            }
            else
            {
                n->next=this->head;
                this->head=n;
            }
            this->size++;            
        }
        bool pop()
        {
            if(this->head==nullptr)
            {
                return false;
            }
            else
            {
                Node<T>* toDel= this->head;
                this->head=this->head->next;
                this->size--;
                delete toDel;
                return true;
            }
        }
        const T top() const
        {
            return this->head->data;
        }
        int countSequances()const
        {
            if(this->size==0 || this->size==1)
            {
                return 0;
            }

            bool flag=false;
            int cnt=1,total=0;
            T last;

            Node<T>* traversal= this->head;
            while(traversal != nullptr)
            {
                if(flag == false)
                {
                    cnt=1;
                    last=traversal->data;
                    flag=true;
                }
                else
                {
                   if(last==traversal->data)
                   {
                      cnt++;
                   }
                   else
                   {
                     if(cnt > 1) {
                       total+=cnt;
                       cnt=1;
                     }
                     last=traversal->data;
                   }
                }
                traversal=traversal->next;
            }
            if(cnt > 1)
            {
                total+=cnt;
            }
            return (total > 1) ? total: 1;
        }
};  

int main()
{
    SinglyLinkedList<int> sll;
    sll.push(1);
    sll.push(2);
    sll.push(2);
    sll.push(3);
    sll.push(4);

    std::cout<<sll.countSequances()<<std::endl; //must be 2

    assert(sll.pop() == true);

    
    sll.push(3);
    std::cout<<sll.countSequances()<<std::endl; //must be 4

    SinglyLinkedList<int> sll1;
    sll1.push(3);
    sll1.push(3);
    sll1.push(2);
    sll1.push(4);
    sll1.push(4);
    sll1.push(4);

    std::cout<<sll1.countSequances()<<std::endl; //must be 5

    SinglyLinkedList<int> sll2;
    sll2.push(3);
    sll2.push(1);
    sll2.push(2);
    std::cout<<sll2.countSequances()<<std::endl; //must be 1
    
}