#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include<iostream>
using namespace std;

template <typename T>
class List{
    private:
        struct Node{
            List *next = NULL;
            T data;
        };
        Node *node = NULL;
        Node *first_node = NULL;
        Node *cursor = NULL;
    public:
        List();
        List(T new_element);
        virtual ~List();
        void addElement(T new_element);
        bool listIsEmpty() const;
        void initializeCursor();
        void advanceCursor();
        bool cursorIsFinal() const;
        T getElementByCursor() const;
};

#endif // LIST_H_INCLUDED
