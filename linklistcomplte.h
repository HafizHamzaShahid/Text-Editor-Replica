#pragma once
#include <iostream>
using namespace std;

template<class T>
class DoublyLinkedList
{
    class Node
    {
    public:
        T data;
        Node* next;
        Node* prev;
        Node(T val)
        {
            data = val;
            next = nullptr;
            prev = nullptr;
        }
    };

    //doubly link list head
    Node* head;

public:
    DoublyLinkedList()
    {
        head = new Node(0);  //dummy head
    }

    ~DoublyLinkedList()
    {
        Node* tmp = nullptr;
        while (head)
        {
            tmp = head;
            head = head->next;
            delete tmp;
        }
        head = NULL;
    }

    Node* getHead()
    {
        return head;
    }

    void Insertat_at_Head(T val)
    {
        Node* newnode = new Node(val);
        if (head->next == NULL)
        {
            head->next = newnode;
            newnode->prev = head;
        }
        else
        {
            newnode->next = head->next;
            head->next = newnode;
            newnode->next->prev = newnode;
        }
    }

    void Delete_from_Head()
    {
        Node* curr = head->next;

        if (curr != nullptr)
        {
            Node* n = curr->next;
            curr->next = head->next;
            delete curr;
            head->next = n;
        }
    }

    void Delete_All(T ele)
    {
        Node* temp, * del;

        if (!(head->next))
        {
            cout << "empty";
        }
        else
        {
            temp = head->next;
            while (temp->next != NULL)
            {

                if (temp->next->data == ele)
                {
                    del = temp;
                    temp = temp->prev;
                    temp->next = del->next;
                    delete del;
                }
                temp = temp->next;
            }
        }
    }

    void Swap(Node* l1, Node* r1)
    {
        Node* tmp;

        tmp = l1->prev;
        if (tmp)
        {
            tmp->next = r1;
        }

        r1->prev = tmp;
        l1->prev = r1;
        l1->next = r1->next;
        r1->next = l1;

        if (l1->next != nullptr)
        {
            l1->next->prev = l1;
        }
    }

    void DeleteVal(T val)
    {
        Node* find = search(val);
        Node* tmp = head->next;

        if (tmp == find)
        {
            head->next = tmp->next;
        }
        else
        {
            while (find != NULL)
            {
                if (tmp->next == find)
                {
                    tmp->next = find->next;
                    find->next->prev = tmp;
                    delete find;
                    return;
                }
                tmp = tmp->next;
            }
        }
    }

    class Iterator {
        friend class DoublyLinkedList;
        // The constructor is private, so only our friends can create instances of Iterators.
    public:
        Iterator(Node* newPtr) : current(newPtr) {}
        Node* current;

        Iterator() : current(nullptr) {}

        bool operator!=(const Iterator& itr) const {
            return current != itr.current;
        }

        bool operator==(const Iterator& itr) const {
            return current == itr.current;
        }

        T& operator*() const {
            return current->data;
        }

        Iterator operator++(int) {
            if (current != nullptr)
            {
                Iterator temp = *this;
                current = current->next;
                return temp;
            }
            else
                return *this;
        }

        Iterator operator ++()
        {
            if (current != nullptr)
            {
                current = current->next;
                return *this;
            }
            else
                return *this;
        }

        Iterator operator --(int)
        {
            if (current != nullptr)
            {
                Iterator temp = *this;
                current = current->prev;
                return  temp;
            }
        }

        Iterator operator --()
        {
            if (current != nullptr)
            {
                current = current->prev;
                return *this;
            }
            else
                return *this;
        }
    };

    Iterator Begin() const {
        return Iterator(head->next);
    }

    Iterator End() const {
        return NULL;
    }

    void Insert(Iterator position, T l)
    {
        Node* n = new Node(l);

        //insert at head
        if (position.current->prev == nullptr)   
        {
            position.current = n;
            n->prev = head->next;    //head---head->next
            head->next = n;

        }
        //insert at tail
        if (position.current->next == nullptr)
        {
            position.current->next = n;
            n->prev = position.current;
            n->next = nullptr;

        }
        //insert in middle
        else
        {
            Node* tmp = position.current->next;
            n->next = tmp;
            n->prev = position.current;
            position.current->next = n;
            n->next->prev = tmp;
        }
    }

    void DeleteIteratorPosition(Iterator position)
    {
        Node* curr = head->next;
        if (head->next != nullptr) {
            //delete from tail
            if (position.current->next == nullptr)
            {
                position.current->prev->next = nullptr;
                delete position.current;


            }
            // delete at head
            else if (position.current->prev == nullptr)
            {
                curr = head->next;
                delete head;
                head = curr;
            }
            // delete at any position
            else {
                curr = position.current->next;
                curr->prev = position.current->prev;
                delete position.current;
                curr->prev->next = curr;
            }
        }
    }

    void Delete_Pos(Iterator position)
    {
        if (position.current->next != nullptr)
        {
            Node* toDelete = position.current->next;
            position.current->next = position.current->next->next;
            delete toDelete;
        }
    }
   
    void BackSpace(Iterator position)
    {
        if (position.current->prev != nullptr)
        {
            Delete_Pos(position);
        }
    }

    void Delete(Iterator& position)
    {
        if (position.current->next != nullptr)
        {

            Delete_Pos(position);
        }
    }

    void Delete_In_Range(Iterator pos1, Iterator pos2)
    {
        Iterator pos = pos1;

        while (pos.current != pos2.current)
        {
            Delete(pos);
            pos++;
        }
    }

    Iterator SearchFirst(T x)
    {

        // Stores position of the integer in the doubly linked list
        Iterator pos = this->Begin();

        while (pos.current->data != x && pos.current->next != NULL)
        {
            // Update pos
            pos++;
        }
        if (pos.current->data != x)
            return NULL;

        return pos;
    }

    Iterator* SearchAll(T x)
    {
        Iterator pos = this->Begin();
        int i = 0;
        while (pos.current->next != NULL)
        {
            if (pos.current->data == x)
            {
                i++;
            }
            pos++;
        }
        if (i == 0)
            return NULL;

        int s = 0;
        Iterator* arr = new Iterator[i];
        Iterator pos1 = this->Begin();
        int k = i;
        int j = 0;
        while (pos1.current != NULL)
        {
            if (pos1.current->data == x)
            {
                arr[s] = pos1;
                s++;
            }
            pos1++;
        }
        return arr;
    }

    Iterator* SearchStringAll(T arr[])
    {
        int size = sizeof(arr) / sizeof(arr[0]);
        Iterator pos = this->Begin();
        int i = 0;
        bool found = false;
        while (pos.current->next != NULL)
        {
            if (pos.current->data == arr[i])
            {
                int j = 0;
                while (j != size)
                {
                    if (pos.current->data == arr[i])
                    {
                        i++;
                        j++;
                    }

                    pos++;
                }
            }
            pos++;
        }
        if (i == 0)
            return NULL;

        Iterator* arr1 = new Iterator[i];
        Iterator pos1 = this->Begin();
        int k = i;
        int s = 0;
        while (pos1.current->next != NULL)
        {
            if (pos1.current->data == arr[i])
            {
                int j = 0;
                while (j != size)
                {
                    if (pos1.current->data == arr[i])
                    {
                        arr1[i] = pos1.current;
                        i++;
                        j++;
                    }

                    pos1++;
                }
            }
            pos1++;
        }
        return arr1;
    }

    Iterator* Search_All(char* v, int size, int& s, int*& t)
    {
        if (head->next != nullptr)
        {
            Iterator pos = this->Begin();
            Iterator* temp;
            Iterator temp1 = this->Begin();
            while (temp1.current->next != nullptr)
            {
                temp1++;
            }
            Iterator e = temp1;
            int sa = size;
            while (sa > 0)
            {
                e--;
                sa--;
            }
            e++;
            bool found = false; int si = size, k = 0; int i = 0;
            for (Iterator p = this->Begin(); p != e && p.current->next != nullptr; )
            {
                found = false;
                si = size;
                if (*p == v[i])
                {
                    Iterator pi = p;
                    int j = i;
                    pi++; j += 1;
                    si -= 1;
                    found = true;
                    while (si > 0)
                    {
                        if (*pi == v[j])
                        {
                            found = true;
                        }
                        else
                        {
                            found = false;
                            break;
                        }
                        pi++;
                        j += 1;
                        si -= 1;
                    }

                    if (found == true)
                    {
                        k++;
                        int k = 0;
                        while (k < size)
                        {
                            p++;
                            k++;
                        }
                    }
                    else
                        p++;


                }
                else
                    p++;
            }

            t = new int[k];
            int n = 0, m = 0;

            s = k;
            temp = new Iterator[k];
            int l = 0;
            i = 0;
            found = false;  si = size;
            for (Iterator p = this->Begin(); p != e; p++)
            {

                found = false;
                si = size;
                if (*p == v[i])
                {
                    Iterator pi = p;
                    int j = i;
                    pi++; j += 1; si -= 1;
                    found = true;
                    while (si > 0)
                    {
                        if (*pi == v[j])
                        {
                            found = true;
                        }
                        else
                        {
                            found = false;
                            break;
                        }
                        pi++;
                        j += 1;
                        si -= 1;
                    }

                    if (found == true)
                    {
                        temp[l] = p.current;
                        l++;

                        t[n] = m;
                        n += 1;


                    }
                }
                if (*p == '\n')
                {
                    m += 1;
                }
            }
            return temp;
        }
    }

    void Search_And_Replace(char* v1, char* v2, int& s, int*& t)
    {
        Iterator* p1 = new Iterator[5000];

        int s1 = 0, s2 = 0;
        for (; v1[s1] != '\0'; s1++)
        {
        }
        for (; v2[s2] != '\0'; s2++)
        {
        }
        s1 -= 1;
        s2 -= 1;

        p1 = this->Search_All(v1, s1, s, t);
        if (s1 == s2)
        {
            for (int i = 0; i < s; i++)
            {
                Iterator pos = p1[i];
                for (int j = 0; j < s2; j++, pos++)
                {
                    pos.current->data = v2[j];
                }
            }
        }
        else if (s1 > s2)
        {
            for (int i = 0; i < s; i++)
            {
                Iterator pos = p1[i];
                for (int j = 0; j < s2; j++, pos++)
                {
                    pos.current->data = v2[j];
                }
                for (int i = 0; i < s1 - s2; i++)
                {
                    Iterator temp = pos;
                    pos++;
                    this->Delete_Pos(temp.current);

                }
            }
        }

        else if (s1 < s2)
        {
            for (int i = 0; i < s; i++)
            {
                Iterator pos = p1[i];
                int j = 0;
                for (j = 0; j < s1; j++, pos++)
                {
                    pos.current->data = v2[j];
                }
                pos--;
                for (int i = 0; i < s2 - s1; i++)
                {
                    this->Insert(pos.current, v2[j]);
                    pos++;
                    j++;
                }
            }
        }
    }

};


