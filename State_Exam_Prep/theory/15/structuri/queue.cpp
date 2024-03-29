#include <iostream>
#include <string>
template<typename T>
struct Node{
    T data;
    Node<T>* next;

    explicit Node(const T& data_,Node<T>* next_=nullptr):data(data_),next(next_){}
};

template<typename T>
class Queue{
    private:
        Node<T>* front;
        Node<T>* back;
        int size;

        bool isEmpty()const
        {
            return this->front==nullptr;
        }
        void copy(const Queue& rhs)
        {
            Node<T>* traversal=rhs.front;
            while(traversal!=nullptr)
            {
                this->push_back(traversal->data);
                traversal=traversal->next;
            }
        }
        void clear()
        {
            while(!this->isEmpty())
            {
                this->pop_front();
            }
        }
    public:
        Queue():front(nullptr),back(nullptr),size(0){}
        Queue(const Queue& rhs):front(nullptr),back(nullptr),size(0)
        {
            this->copy(rhs);
        }
        Queue& operator=(const Queue& rhs)
        {
            if(this!=&rhs)
            {
                this->clear();
                this->copy(rhs);
            }
            return *this;
        }
        ~Queue()
        {
            this->clear();
        }
        friend std::ostream& operator<<(std::ostream& out, const Queue& toPrint)
        {
            Node<T>* ou = toPrint.front;
            while (ou!=nullptr)
            {
                out<<ou->data<<' ';
                ou=ou->next;
            }
            out<<'\n';
            return out;
        }

        //front
        const T getFront() const
        {
            return this->front->data;
        }
        //back
        const T getBack() const
        {
            return this->back->data;
        }
        //push_back
        void push_back(const T& data)
        {
            Node<T>* n = new Node<T>(data);
            if(this->front==nullptr)
            {
                this->front=this->back=n;
            }
            else 
            {
                this->back->next=n;
                this->back=n;
            }
            size++;
        }
        bool pop_front()
        {
            if(this->front==nullptr)
            {
                return false;
            }
            else if(this->front==this->back)
            {
                delete this->front;
                this->front=this->back=nullptr;
                size--;
                return true;
            }
            else
            {
                Node<T>* toDel= this->front;
                this->front=this->front->next;
                delete toDel;
                size--;
                return true;
            }
        }
        const int getSize()const
        {
            return this->size;
        }
};


int main()
{
    Queue<int>* que = new Queue<int>();
    que->push_back(4);
    que->push_back(2);
    que->push_back(3);
    std::cout<<*que;//4 2 3

    std::cout<<que->getFront()<<std::endl;//4
    std::cout<<que->getBack()<<std::endl;//3

    while(que->getSize()!=0)
    {
        std::cout<<que->getFront()<<' ';
        que->pop_front();
    }
    std::cout<<'\n';//4 2 3

    que->push_back(5);
    que->push_back(6);

    //copy constructor
    Queue<int> copyQueue(*que);
    std::cout<<copyQueue;//5 6
    copyQueue.push_back(7);
    copyQueue.push_back(8);
    copyQueue.pop_front();

    //operator =
    *que=copyQueue;
    std::cout<<*que;//6 7 8


    
    delete que;
}