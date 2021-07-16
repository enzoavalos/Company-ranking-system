#include "List.h"
#include "Company.h"
#include<assert.h>

template <typename T> List<T>::List(){
}

template <typename T> List<T>::List(T new_element){
    node = new Node;
    node->data = new_element;
    first_node = this->node;
}

template <typename T> void List<T>::addElement(T new_element){
    if (node == NULL){
        node = new Node;
        node->data = new_element;
        if (first_node == NULL){ first_node = this->node;}
    }else{
        if (node->next == NULL){
            node->next = new List;
            node->next->first_node = first_node;
        }
        node->next->addElement(new_element);
    }
}

template <typename T> bool List<T>::listIsEmpty() const{
    if (node != NULL){
        return false;
    }
    return true;
}

template <typename T> void List<T>::initializeCursor(){
    cursor = first_node;
}

template <typename T> void List<T>::advanceCursor(){
    assert(cursor != NULL);
    if (cursor->next != NULL){
        cursor = cursor->next->node;
    }else{
        cursor = NULL;
    }
}

template <typename T> bool List<T>::cursorIsFinal() const{
    return (cursor == NULL);
}

template <typename T> T List<T>::getElementByCursor() const{
    assert(cursor != NULL);
    return cursor->data;
}

template <typename T> List<T>::~List(){
    delete node;
    node = NULL;
}

template class List<int>;
template class List<Company*>;
