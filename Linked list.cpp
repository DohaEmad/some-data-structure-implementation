#include <iostream>
#include <algorithm>
using namespace std;

template<class t>
//node
struct node
{
    t info;
    node<t> *next;
};

template<class t>
class List
{
private:
    node<t> *head,*tail;
    int cnt;
public:
    //default constructor
    List()
    {
        head=NULL;
        tail=NULL;
        cnt=0;
    }
    List(List<t>&obj)
    {
        cnt=0;
        head=tail=NULL;
        iterator it=obj.begin();
        while (it!=obj.end())
        {
            this->push_back(*it);
            it++;
        }
        this->push_back(*it);

    }
    //constructs a list having ‘initial_size’
    List(t value,int initial_size)
    {
        cnt=initial_size;
        node<t> *temp=new node<t>;
        temp->info=value;
        temp->next=NULL;
        tail=temp;
        head=temp;
        for (int i = 0; i <initial_size-1; ++i) {
            node<t> *temp=new node<t>;
            temp->info=value;
            temp->next=NULL;
            tail->next=temp;
            tail=temp;
        }
    }
    //________________________
    class iterator {
    public:
        node<t> *ptr;
        node<t> *cpyHead;
    public:

        iterator()
        {
            ptr=NULL;
            cpyHead=NULL;
        }

        iterator( node<t>*point,node<t>*h)
        {
            ptr=point;
            cpyHead=h;
        }

        t& operator*()
        {
            return ptr->info;
        }

        bool operator==(const iterator& iter)
        {
            return ptr==iter.ptr;
        }

        bool operator!=(const iterator& iter)
        {
            return ptr != iter.ptr;
        }

        // Prefix ++ overload
        void operator++()
        {
            if(ptr->next==NULL)
            {
                throw "Out Of Range";
                return;
            }
            ptr=ptr->next;
        }

        // Postfix ++ overload
        void operator++(int)
        {
            if(ptr->next==NULL)
            {
                throw "Out Of Range";
                return;
            }
            ptr=ptr->next;
        }

        void operator--()
        {
            //exeption
            List<t>::iterator i;
            i.ptr= this->cpyHead;
            i.cpyHead= this->cpyHead;
            if(this->cpyHead== this->ptr)
            {throw "Out Of Range";}
            else
            {
                while(i.ptr->next!=NULL)
                {
                    if(i.ptr->next==this->ptr)
                    {
                        this->ptr=i.ptr;
                        return;
                    }
                    i++;
                }
            }
        }
        void operator--(int)
        {
            List<t>::iterator i;
            i.ptr= this->cpyHead;
            i.cpyHead= this->cpyHead;
            if(this->cpyHead== this->ptr)
            {throw "Out Of Range";}
            else
            {
                while(i.ptr->next!=NULL)
                {
                    if(i.ptr->next==this->ptr)
                    {
                        this->ptr=i.ptr;
                        return;
                    }
                    i++;
                }
            }
        }
    };
    //____________________________________

    int size()
    {
        return cnt;
    }

    void insert(const t& value , iterator position)
    {
        cnt++;
        node<t>* newNode = new node<t>;
        newNode->info=value;
        if (position == List<t>::iterator(head,head)) {
            newNode->next = head;
            head = newNode;
        }
        else if (!position.ptr->next) {
            position.ptr->next= newNode;
            tail=newNode;
            tail->next=NULL;
        }
        else {

            node<t>* tmp = new node<t>;
            tmp->info=value;
            tmp->next= position.ptr->next;
            position.ptr->next= tmp;
        }
    }

    //list1=list2
    List<t>& operator =(List<t>cpy)
    {
        if(this->head!= this->tail)
        {
            node<t> *current = this->head;
            while( current != NULL ) {
                node<t>* next = current->next;
                delete current;
                current = next;
            }
            head = NULL;
            this->cnt=0;
        }
        if(this==&cpy)
            return *this;
        iterator it=cpy.begin();
        while(it != cpy.end()){
            this->push_back(*it);
            ++it;
        }
        this->push_back(*it);
        return *this;
    }

    iterator erase(iterator position)
    {
        cnt--;
        if (position== List<t>::iterator(head,head))
        {
            node<t> *newNode=new node<t>;
            newNode=head;
            head=head->next;
            delete newNode;
            return List<t>::iterator(head->next,head);
        }
        else if(position==List<t>::iterator(tail,head))
        {
            node<t> *current;
            node<t> *previous;
            current=head;
            while (current->next!=NULL)
            {
                previous=current;
                current=current->next;
            }
            previous->next=NULL;
            tail=previous;
            delete current;
            return List<t>::iterator(NULL,head) ;
        }
        else
        {
            node<t> *current=new node<t>;
            node<t> *previous=new node<t>;
            current=head;
            while (current!=position.ptr)
            {
                previous=current;
                current=current->next;
            }
            previous->next=current->next;
            delete current;
            return List<t>::iterator(previous->next->next,head);

        }

    }
    void push_back(t element)
    {
        cnt++;
        node<t> *newNode=new node<t>;
        newNode->info=element;
        newNode->next=NULL;
        if(head==NULL)
        {
            tail=newNode;
            head=newNode;
            newNode=0;
        }
        else
        {
            tail->next=newNode;
            tail=newNode;
        }
    }

    void print()
    {
        node<t> *current;
        current=head;
        while(current!=NULL)
        {
            cout<<current->info<<" ";
            current=current->next;
        }
        cout<<endl;
    }

    iterator begin()
    {
        return iterator(head,head);
    }

    iterator end()
    {
        return iterator(tail,head);
    }

   ~List()
    {
        node<t> *current ;
        while( head != NULL ) {
            current=head;
            head=head->next;
            delete current;
        }
        tail=NULL;
        head=NULL;
        cnt=0;
    }

};
signed main()
{
    try {
        List<int> test1;
        test1.push_back(10);
        test1.push_back(1);
        test1.push_back(13);
        test1.push_back(17);
        cout<<"linked list after push some elements "<<endl;
        test1.print();
        cout<<"current size of linked list "<<endl;
        cout<<test1.size()<<endl;
        cout<<"value of first element "<<endl;
        List<int>::iterator it=test1.begin();
        cout<<*it<<endl;
        cout<<"iterator++ "<<endl;
        ++it;
        cout<<*it<<endl;
        cout<<"++it ++it --it "<<endl;
        ++it;++it;--it;
        cout<<*it<<endl;
        cout<<"insert value in the last position in linked list "<<endl;
        List<int>::iterator it2=test1.end();
        test1.insert(8,it2);
        test1.print();
        cout<<"erase value in position "<<endl;
        it2=test1.begin();
        it2++;
        test1.erase(it2);
        test1.print();
        List<int> test2(5,10);
        cout<<"initial_size elements whose values are value "<<endl;
        test2.print();
        cout<<"copy list1 to list list2=list1 "<<endl;
        test2=test1;
        test2.print();
        List<int>::iterator itt=test1.begin();
        --itt;
        //here is execption


    }
    catch (const char* error)
    {
        cout<<error<<endl;
    }


}

