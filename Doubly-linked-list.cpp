#include <iostream>
#include <cstdlib>
#include <string>


using namespace std;


template<class T> class node
{
  public:
    T data;
    node *next;
    node *prev;


    node(T d) { next = NULL; prev = NULL; data = d; }
};


template<class T>
class linked_list
{
  private:
    node<T> *head;
    node<T> *tail;
    node<T> *upoint;


  public:


    linked_list()
    {
        head = NULL;
        tail = NULL;
        upoint = NULL;


    }


    void reset_ptr()
    {
        upoint = head;
    }


    void adv_ptr()
    {


        if(upoint && upoint->next)
        {
            upoint = upoint->next;
        }


     else if(upoint == NULL)
     {
         cout << "ERROR: pointer is NULL." << endl;
     }


        else if(upoint->next == NULL)
        {
            cout<<"ERROR: Pointer out of bounds"<<endl;
        }
    }


    void rew_ptr()
    {


        if(upoint && upoint->prev)
        {
            upoint = upoint->prev;
            return;
        }


    cout<<"ERROR: Pointer out of bounds"<<endl;


    }


    T getup()
    {
        if(upoint == NULL)
        {
            cout<<"ERROR: Pointer is NULL"<<endl;


            return -1;
        }




        return upoint->data;


    }


    int size(){


        node<T> *tptr = head;


        int c = 0;


        while(tptr)
        {
            c++;
            tptr = tptr->next;
        }
        return c;
    }


    void add(int n, T d){


        node<T> *tptr = head;


        if(head==NULL && n==0)
        {
            head = new node<T>(d);
            tail = head;  //set tail when the first node is added
            return;
        }


        else if(n > size()){
            cout << "ERROR:This index is invalid" << endl;
            return;
        }


        else if(n >= 1){
            for(int i = 0; i < n-1; i++)
            {
                tptr = tptr->next;
            }
            node<T> *newtptr = new node<T>(d);


            newtptr->next = tptr->next;
            newtptr->prev = tptr;
            if(tptr->next)
                tptr->next->prev = newtptr;
            tptr->next = newtptr;


            if(newtptr->next == NULL) {
                tail = newtptr;  //ipdate tail if its the last node
            }
            return;
        }
        node<T> *newtptr = new node<T>(d);


        newtptr->next = tptr;
        newtptr->prev = NULL;  //new node is now the head
        tptr->prev = newtptr;
        head = newtptr;


        if(size() == 1) {
            tail = head;  //ensure tail is set if theres only one node
        }
    }


    void add_last(T d){


        if(!head)
        {
            head = new node<T>(d);
            tail = head;  //set tail when the first node is added
            return;
        }


        node<T> *newtptr = new node<T>(d);
        tail->next = newtptr;
        newtptr->prev = tail;
        tail = newtptr;
    }


    void add_first(T d){


        node<T> *newptr = new node<T>(d);


        newptr->next = head;
        newptr->prev = NULL;


        if(head)
            head->prev = newptr;


        head = newptr;


        if(size() == 1) {
            tail = head;  //tail is set if there's only one node
        }
    }


    T get(T n)
    {
        if(n > size() - 1)
        {
            cout << "ERROR: Index doesn't exist" << endl;
            return -1;
        }


        if(head == NULL)
        {
            cout << "List is empty" << endl;
            return -1;
        }


        node<T> *tptr = head;
        for(int i = 0; i < n; i++)
        {
            tptr = tptr->next;
        }


        return tptr->data;
    }


    T get_first()
    {


        if(head == NULL)
        {
            cout << "There are no nodes" << endl;
            return -1;
        }


        return head->data;
    }


    T get_last()
    {
        if(tail == NULL)
            return -1;


        return tail->data;
    }


    void remove(int n){


        if(n > size()-1)
        {
            cout << "This node doesn't exist. List size is: " << size() << endl;
            return;
        }


        node<T> *tptr = head;
        if(n == size()-1)
        {


            if(upoint == tail)
            {
                upoint = NULL;
            }
            remove_last();
            return;
        }


        if(n == 0)
        {


            if(upoint == head)
            {
                upoint = upoint->next;
            }


            remove_first();
            return;
        }


        for(int i = 0; i < n-1; i++)
        {
            tptr = tptr->next;
        }


        node<T> *delptr = tptr->next;


        if(upoint == delptr)
        {


            if(upoint->next)
            {
                upoint = upoint->next;
            }


            else if(upoint->prev)
            {
                upoint = upoint->prev;
            }


        }


        tptr->next = delptr->next;
        if(delptr->next)
            delptr->next->prev = tptr;
        delete delptr;
    }


    void remove_first()
    {
        if(head == NULL)
        {
            cout << "List is empty. List size: " << size() << endl;
            return;
        }


        if(size() == 1)
        {
            delete head;
            head = NULL;
            tail = NULL;  // Also clear the tail
            return;
        }


        node<T> *tptr = head;


        if(upoint == head)
        {


            if(upoint->next)
            {
                upoint = upoint->next;
            }


            else if(upoint->next == NULL)
            {
                upoint = NULL;
            }


        }




        head = head->next;
        if(head)
            head->prev = NULL;
        delete tptr;
    }


    void remove_last()
    {
        if(head == NULL)
        {
            cout << "ERROR: This list is empty. List size: " << size() << endl;
            return;
        }


        if(size() == 1)
        {
            delete head;
            head = NULL;
            tail = NULL;
            return;
        }


        node<T> *tptr = tail;


        if(upoint == tail)
        {


            if(upoint->prev)
            {
                upoint = upoint->prev;
            }


            else if(upoint->prev == NULL)
            {
                upoint = NULL;
            }


        }


        tail = tail->prev;
        if(tail)
            tail->next = NULL;
        delete tptr;
    }


    void dump()
    {
        node<T> *tptr;
        node<T> *ptptr;


        cout << "    DUMP: (size = " << size() << ", first = " << get_first() << ", last = " << get_last() << ")\n";


        if (head == NULL) {
            cout << "    DUMP: head = NULL\n\n";
            return;
        }


        tptr = head;
        ptptr = tail;


        while (tptr) {
            cout << "    DUMP:   data = : " << tptr->data << " data = : "<< ptptr->data << endl;
            tptr = tptr->next;
            ptptr = ptptr->prev;
        }
        cout << endl;
    }


};


    int main(void)
{
    linked_list<int> ll;
    string cmd;
    int d, i;


    while (cin >> cmd >> i >> d) {


        //cout << "MAIN: cmd = " << cmd << ", index = " << i
             //<< ", data = " << d << endl;


        if (cmd == "add")
            ll.add(i, d);
        else if (cmd == "addf")
            ll.add_first(d);
        else if (cmd == "addl")
            ll.add_last(d);
        else if (cmd == "rem")
            ll.remove(i);
        else if (cmd == "remf")
            ll.remove_first();
        else if (cmd == "reml")
            ll.remove_last();
        else if (cmd == "get") {
            d = ll.get(i);
            cout << "get returns: " << d << endl;
        } else if (cmd == "getf") {
            d = ll.get_first();
            cout << "getf returns: " << d << endl;
        } else if (cmd == "getl") {
            d = ll.get_last();
            cout << "getl returns: " << d << endl;
        } else if (cmd == "reset") {  // set user ptr to head of list
            ll.reset_ptr();
        } else if (cmd == "adv") {    // advance user ptr to next node
            ll.adv_ptr();
        } else if (cmd == "rew") {    // rewind  user ptr to prev node
            ll.rew_ptr();
        } else if (cmd == "getup") {   // return value at user ptr node
            int i = ll.getup();
            cout << "getup returns: " << i << endl;
        } else if (cmd == "dump")
            ll.dump();
        else if (cmd == "quit")
            exit(0);
    }
}
