#include <iostream>

template<typename T>
struct Node{
    T data;
    Node<T>* next;
    
    explicit Node(const T& data_, Node<T>* next_=nullptr) : data(data_),next(next_) {}
};

template<typename T>
class SinglyLinkedList{
    private:
        Node<T>* head;
        Node<T>* tail;
        int size;
        bool isEmpty()const 
        {
            return this->head==nullptr ? true : false; 
        }
        void copy(const SinglyLinkedList<T>& rhs)
        {
            Node<T>* node = rhs.head;
            while(node!=nullptr)
            {
                this->add_at_tail(node->data);
                node=node->next;
            }
        }
        void clear()
        {
            while(!this->isEmpty())
            {
                this->remove_at_head();
            }
        }
    public:
        SinglyLinkedList():head(nullptr),tail(nullptr),size(0) {} 
        
        SinglyLinkedList(const SinglyLinkedList<T>& rhs):head(nullptr),tail(nullptr),size(0)
        {
            this->copy(rhs);
        }
        SinglyLinkedList& operator=(const SinglyLinkedList& rhs )
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
            clear();
        }
        //todo: predefine operator <<
        friend std::ostream& operator<<(std::ostream& out,const SinglyLinkedList& rhs)
        {
            Node<T>* traversal = rhs.head;
            while(traversal!=nullptr)
            {
                out<<traversal->data<<' ';
                traversal=traversal->next; 
            }
            out<<'\n';
            return out;
        }

        void add_at_tail(const T& toAdd)
        {
            Node<T>* n = new Node<T>(toAdd);
            if(head==nullptr)
            { 
               head=tail=n; 
               size++;
            }
            else 
            {
                tail->next=n;
                tail=n;
                size++;
            }
        }
        //todo
        void add_at_head(const T& rhs)
        {
            Node<T>* n = new Node<T>(rhs);

            if(head==nullptr)
            {
                this->head=this->tail=n;
            }
            else{
                n->next=this->head;
                this->head=n;
            }
            size++;
        }

        //todo: insertat position
        bool insert_at(const T& data,const int& pos)
        {
            if(0 < pos && pos < this->size)
            {
                Node<T>* traversal= this->head;
                int ind=0;
                while(ind!=(pos-1))
                {
                    traversal=traversal->next;
                    ++ind;
                }
                Node<T>* n = new Node<T>(data);
                n->next= traversal->next;
                traversal->next=n;
                size++;

                return true;
            }
            else if(pos==0)
            {
                this->add_at_head(data);
                return true;
            }
            else if(pos==this->size)
            {
                this->add_at_tail(data);
                return true;
            }
            else
            {
                return false;
            }
        }
        //todo: erase at position
        bool remove_at_pos(const int& pos)
        {
            if(0 < pos && pos < this->size)
            {
                Node<T>* traversal= this->head;
                int ind=0;
                while(ind!=(pos-1))
                {
                    traversal=traversal->next;
                    ++ind;
                }   
                Node<T>* toDel= traversal->next;
                traversal->next=traversal->next->next;
                delete toDel;
                
                //change the tail
                if(pos==this->size-1)
                {
                    this->tail=traversal;
                }

                this->size--;
                return true;
            }
            else if(pos==0)
            {
                return this->remove_at_head();
            }
            else
            {
                return false;
            }
        }


        bool remove_at_head()
        {  
            if(this->head==nullptr)
            {
                return false;
            }
            else if(this->head==this->tail)
            {
                delete head;
                head=tail=nullptr;
                size=0;
                return true;
            }
            else
            {
                Node<T>* toDel = head;
                head=head->next;
                size--;
                delete toDel;

                return true;
            }
        }
      
};

int main()
{
    // Node<int> root(0);
    // Node<int> el(1);
    // root.next=&el;

    // Node<int>* ptr = &root;

    // while(ptr !=nullptr)
    // {
    //     std::cout<<ptr->data<<" ";
    //     ptr=ptr->next;
    // }
    // std::cout<<std::endl;

    SinglyLinkedList<int>* singleLL = new SinglyLinkedList<int>();
    singleLL->add_at_tail(1);
    singleLL->add_at_tail(5);

    singleLL->add_at_tail(3);
    singleLL->add_at_tail(6);
    singleLL->add_at_tail(0);

    singleLL->remove_at_head();
    singleLL->remove_at_head();
    std::cout<<*singleLL; // 3 6 0

    singleLL->add_at_tail(2); // 3 6 0 2
    singleLL->insert_at(4,0); // 4 3 6 0 2
    singleLL->insert_at(1,5); // 4 3 6 0 2 1
    singleLL->remove_at_pos(5);//4 3 6 0 2

    std::cout<<*singleLL; //4 3 6 0 2

    singleLL->add_at_tail(3);
    std::cout<<*singleLL; //4 3 6 0 2 3

    //copy constructor
    SinglyLinkedList<int> cl = SinglyLinkedList<int>(*singleLL);
    std::cout<<cl; //4 3 6 0 2 3

    cl.add_at_head(5); //5 4 3 6 0 2 3

    *singleLL=cl;
    std::cout<<*singleLL; //5 4 3 6 0 2 3

    //operator= checks whether we give rhs object same as the lhs object
    *singleLL=*singleLL;
    std::cout<<*singleLL; //5 4 3 6 0 2 3

    delete singleLL;
}